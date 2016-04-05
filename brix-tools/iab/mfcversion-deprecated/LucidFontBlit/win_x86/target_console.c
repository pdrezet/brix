/** @file target_console.c
 * In this file, the target-specific console interface functions provided for EHS are defined.
 * 
 * @author: Dr Andrew Coombes
 * @version: $Revision: 982 $
 * @date: $Date: 2006-11-06 16:22:28 +0000 (Mon, 06 Nov 2006) $
 * 
 * Copyright (c) Ncapsa Ltd, 2006. All rights reserved.
 */

#define EHS_TGT_CODE /* Ensure header files include target-internal values */

#include "target.h"
#include "console_queue.h"
#include "globals.h"
#include <stdarg.h>
#include "messages.h"
#include "mem.h"

/**
 * Output the current state of EHS to the toolbar
 *
 * @param[in] szStatus Contains the state that's to be displayed
 */
EHS_GLOBAL void EhsTgtStatus_state(const ehs_char* szStatus);

/**
 * Output the an error message to the toolbar
 *
 * @param[in] szError Contains the error message to display
 */
EHS_GLOBAL void EhsTgtStatus_error(const ehs_char* szError);


/**
 * Contains input from the console.
 * Initialised by EhsSystemInit
 */
EhsConsoleQueueType EhsTgtConsoleInputQueue;

/**
 * Contains output to the console
 * Initialised by EhsSystemInit
 */
EhsConsoleQueueType EhsTgtConsoleOutputQueue;

/**
 * Contains input from the console.
 * Initialised by EhsSystemInit
 */
EhsConsoleQueueType* EhsTgtConsoleInputQueueRef;

/**
 * Contains output to the console
 * Initialised by EhsSystemInit
 */
EhsConsoleQueueType* EhsTgtConsoleOutputQueueRef;


/**
 * Read a line of text from the console up to the specified size.
 * Returned text includes the terminating \n.
 * This function only returns content if an entire line has been read
 * (i.e. if a \n is available). Partially received lines are buffered
 * until the end of line character has been received).
 *
 * @param buff Buffer to read the line into. Must be at least "size" long
 * @param size Size of buff
 * @return number of characters read (or zero if no line is available)
 */
ehs_uint32 EhsConsoleGetLine(ehs_char *buff, ehs_uint16 size)
{
	ehs_uint32 nLineSize;
	ehs_uint32 nRead = 0u;

	nLineSize = EhsConsoleQueue_peek(&EhsTgtConsoleInputQueue,EHS_CHAR_LF);
	if (0u == nLineSize)
	{
		nLineSize = EhsConsoleQueue_peek(&EhsTgtConsoleInputQueue,EHS_CHAR_CR);
	}

	if (nLineSize > 0u)
	{
		if (nLineSize >= size)
		{
			/* text to read exceeds buffer size - reduce text to read, leave space
			 * for a terminating null */
			nLineSize = size-1;
		}
		nRead = EhsConsoleQueue_pop(&EhsTgtConsoleInputQueue,(ehs_uint8*)buff,nLineSize);
		buff[nRead] = '\0';
		nRead++;
	}

	
	return nRead;
}

/**
 * Print text into the console output. This function blocks as long
 * as necessary to send the output.
 *
 * @param fmt Format specifier for output (as per printf)
 */
ehs_uint16 EhsConsolePrintf(const ehs_char* fmt, ...) /*lint !e960 Variable arguments required to support generalized printf */
{
	ehs_sint32 nLen = 0;
	static ehs_bool bInPrintf = EHS_FALSE; /* avoid nested calls to EhsConsolePrintf - could result from failure of EhsMemScratchpad_alloc */
	ehs_char cEmergencyBuff[100]; /* emergency message buffer in cae Scratchpad_alloc fails */

	if (!bInPrintf)
	{
		ehs_char* szBuffer;
		ehs_char *pBuff;
		ehs_uint32 nBuff;
		ehs_uint32 nPushed;
		EhsMemScratchpadMarkerType marker;

		/* format the message into a chunk of memory allocated especially */
		va_list args;
		bInPrintf = EHS_TRUE;
		marker = EhsMemScratchpad_setMarker();
		va_start(args,fmt);
		nLen = _vscprintf(fmt,args)+1;
		szBuffer = (ehs_char*)EhsMemScratchpad_alloc(nLen * sizeof(ehs_char));
		if (!szBuffer)
		{
			szBuffer = cEmergencyBuff;
		}
		if (szBuffer)
		{
			vsprintf(szBuffer,fmt,args);
			/* keep pushing the message until it's all gone */
			nBuff = (ehs_uint32)(nLen-1);
			pBuff = szBuffer;
			do
			{
				nPushed = EhsConsoleQueue_push(&EhsTgtConsoleOutputQueue,(ehs_uint8*)pBuff,nBuff);
				pBuff += nPushed;
				nBuff -= nPushed;
			}
			while (nBuff > 0u);

			/* determine message type to update status bar */
			if (!strnicmp(szBuffer,"=S",2))
			{
				/* update current state */
				EhsTgtStatus_state(&szBuffer[2]);
				/* if (EhsState == EHS_STATE_RUNNING)
				{
					EhsTgtStatus_error("");
				} */
			}
			else if (!strnicmp(szBuffer,"**",2))
			{
				/* output error message */
				EhsTgtStatus_error(&szBuffer[2]);
			}
		}
		/* else ignore the message */

		EhsMemScratchpad_freeMarker(marker);
		bInPrintf = EHS_FALSE;
	}
	return nLen;
}

/**
 * Check whether console input is available
 *
 * @return true if one or more characters is available
 */
ehs_bool EhsConsoleInputHit()
{
	ehs_bool bInputAvailable = !EhsConsoleQueue_isEmpty(&EhsTgtConsoleInputQueue);
	return bInputAvailable;
}

/**
 * Check whether a complete line is available for reading
 *
 * @return true if a line is available
 */
ehs_bool EhsConsoleLineReady()
{
	ehs_bool bLineReady = (EhsConsoleQueue_peek(&EhsTgtConsoleInputQueue,EHS_CHAR_LF) + EhsConsoleQueue_peek(&EhsTgtConsoleInputQueue,EHS_CHAR_LF)) > 0u;
	return bLineReady;
}

/**
 * Read a file from the console input into persistent storage.
 *
 * @param nSize Size to download. If we don't know how big the file is,
 * we can pass in EHS_UINT32_MAX. If the file size is zero, we create an
 * empty file.
 * @param name Name to store file as. This will conform to the EHS filename
 * standard (i.e. 8.3 with leading letter, only letters and digits)
 *
 * @return true if load is successful
 */
ehs_bool EhsConsoleLoadFile(ehs_uint32 nSize, const ehs_char* name)
{
	ehs_uint8 pInBuff[EHS_FILE_BUFF_SIZE];
	ehs_FILE* pOut;
	ehs_uint32 nSizeRemaining = nSize;
	EhsTickType tTimeOfLastRead = EhsCurrentTime();
	ehs_uint32 nRead; /* bytes to read or bytes that have been read */
	ehs_bool bRet = EHS_TRUE; /* assume success */
	
	/* open the output file */
	pOut = EhsFopen(name,"wb");

	/* read data until:
	   1. there is nothing left to read OR
	   2. no data has happened for a while
	   */
	while ((nSizeRemaining > 0u) &&
		   ((EhsCurrentTime() - tTimeOfLastRead) < EHS_TIMEOUT_READ_FILE))
	{
		nRead = (EHS_FILE_BUFF_SIZE < nSizeRemaining)?EHS_FILE_BUFF_SIZE:nSizeRemaining;
		nRead = EhsConsoleQueue_pop(&EhsTgtConsoleInputQueue,pInBuff,nRead);
		if (nRead > 0u)
		{
			tTimeOfLastRead = EhsCurrentTime();
			nSizeRemaining -= nRead;
			/* we must read in all of the data whether or not the file was
			 * opened successfully - hence we check here whether the pointer
			 * is valid
			 */
			if (pOut)
			{
				EhsFwrite(pInBuff,sizeof(ehs_uint8),nRead,pOut);
			}
		}
	}
	if (pOut)
	{
		EhsFclose(pOut);
		if ((nSizeRemaining > 0u) && (nSize > 0u))
		{
			/* timeout must have occured */
			EhsConsolePrintf(EHS_MSG_ERROR_FILE_TIMEOUT(name, nSizeRemaining, nSize));
			bRet = EHS_FALSE;
		}
	}
	else
	{
		EhsConsolePrintf(EHS_MSG_ERROR_FILE_NOT_OPEN(name));
		bRet = EHS_FALSE;
	}

	return bRet;
}
