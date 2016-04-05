/** @file hal_file.c
 * Definitions for Common utilities for supporting file access 
 *
 * @author: Andrew Coombes
 * @version: $Revision: 1120 $
 * @date: $Date$
 * 
 * Copyright (c) Ncapsa Ltd, 2007. All rights reserved.
 */


/**
 * @page Verification Verification report
 * @section target_timer
 * @anchor target_timer
 * @subsection misra MISRA compliance:
 * test.c demonstrated MISRA compliant on 
 * Last modified on $Date:$
 *
 * This file contained no derogations to the MISRA standard.
 */

/*****************************************************************************/
/* Included files */
#include "hal_file.h"
#include "hal_string.h"

/*****************************************************************************/
/* Declare macros and local typedefs used by this file */


/*****************************************************************************/
/* Declare prototypes of local functions */

/*****************************************************************************/
/* Variables defined with file-scope */

/*****************************************************************************/
/* Variables defined with global-scope */

/*****************************************************************************/
/* Function definitions */

/**
 * Consume the current line up until the end of line character
 * @param[in] pFile Pointer to the file to use
 * @return True if the end of line character was found, false otherwise, we've
 * probably hit the end of the file
 */
ehs_bool EhsFconsumeLine(ehs_FILE* pFile)
{
	ehs_bool bRet = EHS_FALSE;
	
	if (pFile)
	{
		ehs_sint16 nChar;
		do
		{
			nChar = EhsFgetc(pFile);
			if (nChar == EHS_EOL)
				bRet = EHS_TRUE;
		}
		while ((nChar != EHS_EOF) && (nChar != EHS_EOL));
	}
	return bRet;
}

/**
 * Get a single word from the current file. Word is terminated by whitespace unless
 * the szSeparators parameter is set. Doesn't trim leading whitespace/separators
 * @param[in] pFile File to get the word from
 * @param[in,out] szWord Pointer to the area of memory to hold the word we've just read
 * @param[in] nLen Maximum Length of the word we're going to read (including terminator) 
 * @param[in] szSeparators Characters that separate one word from another. NULL means
 * white space. In the NULL case, leading white space is stripped from strings
 * @return Pointer to the characters we've read unless we encounter end of line or end of file.
 */
ehs_char* EhsFgetWord(ehs_FILE* pFile, ehs_char* szWord, ehs_uint16 nLen, const ehs_char* szSeparators)
{
	ehs_sint16 nChar;
	ehs_uint16 nIdx = 0;
	ehs_bool bTerm = EHS_FALSE; /* have we hit a terminator - end of line or end of file? */
	ehs_bool bSeparator; /* have we hit a separator? */
	ehs_char* szRet = NULL;
	
	/* adjust nLen so that we have room for the terminator. Put the terminator on the end
	 * of the string in case we need it */
	nLen--;
	szWord[nLen] = '\0';
	
	/* loop until: we hit a separator, end of line, end of file */
	do
	{
		nChar = EhsFgetc(pFile);
		
		if (nChar == EHS_EOF || nChar == EHS_EOL)
			bTerm = EHS_TRUE;
		else
		{
			/* normal character */
			if (szSeparators)
				bSeparator = (0 != EhsStrchr(szSeparators,nChar));
			else
			{
				bSeparator = EhsStrIsSpace(nChar);
				if (bSeparator && (nIdx == 0))
				{
					/* it isn't a separator, it's leading whitespace - ignore it */ 
					bSeparator = EHS_FALSE;
					continue;
				}
			}
			
			if (!bSeparator)
			{
				/* only copy characters as long as we can fit them into szWord.
				 * Continue to consume them however */
				if (nIdx < nLen)
					szWord[nIdx++] = (ehs_char)nChar;
			}
		}
	}
	while (!bTerm && !bSeparator);
	szWord[nIdx] = '\0'; /* make sure that a string terminator is provided */
	
	if (!bTerm)
		szRet = szWord;
	
	return szRet;
}

