/** @file console_server.c
 * Contains the TcpIp server thread used for accessing EHS. 
 * Note symbols begining EhsSvcTcp... are defined here and
 * symbols that start with EhsTgtTcp are defined in the target-specific
 * part.
 * 
 * @author: Andrew Coombes, Kieron White
 * @version: $Revision: 1120 $
 * @date: $Date: 2006-10-30 05:05:44 +0000 (Mon, 30 Oct 2006), $
 * 
 * Copyright (c), Ncapsa Ltd, 2007. All rights reserved.
 */

#define EHS_TARGET_CODE
#include "target_tcp.h"
#include "console_server.h"
#include "globals.h"
#include "hal_time.h"
#include "hal_process.h"
#include "hal_console.h"

/*****************************************************************************/
/* Declare prototypes of local functions */

/**
 * Send data from EHS to the target.
 *
 * @return true if we remain connected to the target
 */
EHS_LOCAL ehs_bool EhsSvcTcp_send(void);

/**
 * Receive data from the target, then pass it on to EHS
 *
 * @return True if the client didn't request to disconnect.
 */
EHS_LOCAL ehs_bool EhsSvcTcp_receive(void);

/**
 * Replace all <esc>E in pData with <esc>, check for existance of 
 * <esc>D - indicates that we've received a disconnect instruction
 *
 * @param pData Pointer to the received data
 * @param nSize Amount of data to process
 * @param pbDisconnect True if the disconnect has been received
 * @return size of data now in pData (<= nSize)
 */
EHS_LOCAL ehs_uint32 EhsSvcTcp_expandEscapes(ehs_uint8 *pData, ehs_uint32 nSize, ehs_bool *pbDisconnect);

/**
 * Set up the TCP/IP connection and start waiting for a client to connect.
 */
EHS_LOCAL void EhsSvcTcp_waitForClient(void);

/**
 * Close the connection EhsTgtTcpSocketType
 */
EHS_LOCAL ehs_bool EhsSvcTcp_closeConnection(void);

/**
 * Open a new TCP/IP connection. This involves setting up a EhsTgtTcpSocketType, binding it
 * then listening for incoming connections.
 *
 * @return True if connection was opened successfully.
 */
EHS_LOCAL ehs_bool EhsSvcTcp_openConnection(void);

/*****************************************************************************/
/* Variables defined with file-scope */

/**
 * Socket used for listening for new connections
 */
EHS_LOCAL EhsTgtTcpSocketType EhsSvcTcpSocketListen;

/**
 * Socket used for the main connection between EHS and its client
 */
EHS_LOCAL EhsTgtTcpSocketType EhsSvcTcpSocketConnection;

/*****************************************************************************/
/* Provide configurable logging support */
#ifdef EHS_TGT_TCP_LOG_ENABLED

/**
 * Write log data to the log file.
 */
EHS_LOCAL void EhsSvcTcp_log(const ehs_char* params,...); /*lint !e960 Variable arguments required to support generalized printf */

/**
 * Log (potentially) binary data to the log file
 *
 * @param pData pointer to the data to log
 * @param nDataReceived amount of data to log
 */
EHS_LOCAL void EhsSvcTcp_logBinaryData(const ehs_uint8* pData, ehs_uint32 nDataReceived);

/**
 * How long line lengths should be when displaying data
 */
#define EHS_SVC_TCP_LOG_LINELEN 80u

/**
 * File that receives all log data
 */
EHS_LOCAL ehs_FILE* EhsSvcTcpLogfile;

/**
 * Write log data to the log file.
 */
void EhsSvcTcp_log(const ehs_char* params,...) /*lint !e960 Variable arguments required to support generalized printf */
{
	va_list argptr;
	ehs_uint32 nTime_us = EhsTgtTimer_tickTous(EhsCurrentTime());
	fprintf(EhsSvcTcpLogfile,"%03d.%03d %03d\t", nTime_us / 1000000u, (nTime_us / 1000u) % 1000u, nTime_us % 1000u);
	va_start (argptr,params);
	vfprintf(EhsSvcTcpLogfile,params,argptr); /*lint !e534 Ignoring return value of function - simply not of interest here */
	va_end(argptr);
	fflush(EhsSvcTcpLogfile);
}

/**
 * Log (potentially) binary data to the log file
 *
 * @param pData pointer to the data to log
 * @param nDataReceived amount of data to log
 */
void EhsSvcTcp_logBinaryData(const ehs_uint8* pData, ehs_uint32 nDataReceived)
{
	ehs_uint8 lLen = 0u; /* length of the line output so far */
	ehs_uint32 i; /* index into the data received */

	for (i = 0u; i < nDataReceived; i++)
	{
		ehs_uint8 cOut = pData[i]; /* character received */

		/* begin new lines with a tab */
		if (lLen == 0u)
		{
			EhsFputc('\t', EhsSvcTcpLogfile);
		}

		/* filter out funny (i.e. control) characters */
		cOut = (((cOut > 0x20u)&&(cOut < 0x7fu))||(cOut==EHS_CHAR_LF))?cOut:((ehs_uint8)('.'));

		/* output the character */
		EhsFputc((ehs_sint32)cOut,EhsSvcTcpLogfile);

		/* break the line if it exceeds EHS_SVC_TCP_LOG_LINELEN characters */
		lLen = (cOut == EHS_CHAR_LF)?0u:(lLen+1u);
		if (lLen > EHS_SVC_TCP_LOG_LINELEN)
		{
			EhsFputc((ehs_sint32)EHS_CHAR_LF,EhsSvcTcpLogfile);
			lLen = 0u;
		}
	}

	/* force a write of the file */
	fflush(EhsSvcTcpLogfile);
}

/**
 * Log the name of the EhsTgtTcpSocketType error that's just occured with the name of
 * the calling function
 *
 * @param[in] szCaller Console server function and the sockets function it called.
 * @param[in] nErrCode Error code that gives rise to this error message
 */
void EhsSvcTcp_logSocketError(const ehs_char* szCaller, EhsTgtTcpErrType nErrCode)
{
	const ehs_char* szError = EhsTgtTcp_getErrorText(nErrCode);
	
	EhsSvcTcp_log("**Error: TCP/IP error (%-d) in %s: %s\n", nErrCode, szCaller,szError);
}

#else
/* not logging, so stub out calls to log functions */
#define EhsSvcTcp_log(x) 
#define EhsSvcTcp_logBinaryData(a,b)
#endif

/*****************************************************************************/
/* Function definitions */

/**
 * Open a new TCP/IP connection. This involves setting up a EhsTgtTcpSocketType, binding it
 * then listening for incoming connections.
 *
 * @return True if connection was opened successfully.
 */
ehs_bool EhsSvcTcp_openConnection(void)
{
	EhsTgtTcpSockAddrInType connection; /* used to construct the address of the EhsTgtTcpSocketType we're creating */
	ehs_bool ret = EHS_FALSE; /* assume initialisation fails */

	/* set up connection ready for bind */
	memset(&connection, 0, sizeof(connection));
	connection.sin_family = AF_INET;
	connection.sin_addr.s_addr = htonl(INADDR_ANY);
	connection.sin_port = htons( EHS_TGT_TCP_PORTNUM );

	/* Create EhsTgtTcpSocketType */
	EhsSvcTcpSocketListen = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
	if (EhsSvcTcpSocketListen == EHS_TGT_TCP_INVALID_SOCKET) 
	{
		EhsSvcTcp_logSocketError("EhsSvcTcp_openConnection.EhsTgtTcpSocketType", EhsTgtTcp_getErrorCode(EHS_TRUE));
	}
	/* Bind EhsTgtTcpSocketType */
	else if ( bind( EhsSvcTcpSocketListen, (EhsTgtTcpSockAddrType*) &connection, (ehs_sint32)sizeof(connection) ) == EHS_TGT_TCP_SOCKET_ERROR) 
	{
		EhsSvcTcp_logSocketError("EhsSvcTcp_openConnection.bind", EhsTgtTcp_getErrorCode(EHS_TRUE));
	}
	/* Listen for incoming connections. Allows for 1 pending connection only */
	else if (listen( EhsSvcTcpSocketListen, 1) == EHS_TGT_TCP_SOCKET_ERROR)
	{
		EhsSvcTcp_logSocketError("EhsSvcTcp_openConnection.listen", EhsTgtTcp_getErrorCode(EHS_TRUE));
	}
	else
	{
		ret = EHS_TRUE;
	}

	return ret;
}

/**
 * Close the connection EhsTgtTcpSocketType
 */
ehs_bool EhsSvcTcp_closeConnection()
{
	ehs_bool bSuccess = EHS_FALSE; /* assume operation failed */

	if (shutdown(EhsSvcTcpSocketConnection,EHS_TGT_TCP_SD_BOTH) != 0)
	{
		if (EhsTgtTcp_getErrorCode(EHS_TRUE) != EHS_TGT_TCP_ERR_NOTCONN)
		{
			EhsSvcTcp_logSocketError("EhsSvcTcp_closeConnection.shutdown", EhsTgtTcp_getErrorCode(EHS_FALSE));
		}
		else
		{
			/* Ignore this warning, as we're already shutdown */
			bSuccess = EHS_TRUE;
		}
	}
	else
	{
		bSuccess = EHS_TRUE;
	}

	if (bSuccess)
	{
		if (EHS_TGT_TCP_CLOSE_SOCKET(EhsSvcTcpSocketConnection) != 0)
		{
			EhsSvcTcp_logSocketError("EhsSvcTcp_closeConnection.closeEhsTgtTcpSocketType", EhsTgtTcp_getErrorCode(EHS_TRUE));
		}
	}
	else
	{
		bSuccess = EHS_TRUE;
	}

	return bSuccess;
}

/**
 * Set up the TCP/IP connection and start waiting for a client to connect.
 */
void EhsSvcTcp_waitForClient()
{
	EhsSvcTcp_log("***Waiting for client\n");
	EhsSvcTcpSocketConnection = EHS_TGT_TCP_INVALID_SOCKET;
	while (EhsSvcTcpSocketConnection == EHS_TGT_TCP_INVALID_SOCKET)
	{
		EhsSvcTcpSocketConnection = accept( EhsSvcTcpSocketListen, NULL, NULL);
		if (EhsSvcTcpSocketConnection == EHS_TGT_TCP_INVALID_SOCKET)
		{
			EhsSvcTcp_logSocketError("EhsSvcTcp_waitForClient.accept (ignoring)", EhsTgtTcp_getErrorCode(EHS_TRUE));
		}
	}
}

/**
 * Replace all <esc>E in pData with <esc>, check for existance of 
 * <esc>D - indicates that we've received a disconnect instruction
 *
 * @param pData Pointer to the received data
 * @param nSize Amount of data to process
 * @param pbDisconnect True if the disconnect has been received
 * @return size of data now in pData (<= nSize)
 */
ehs_uint32 EhsSvcTcp_expandEscapes(ehs_uint8 *pData, ehs_uint32 nSize, ehs_bool *pbDisconnect)
{
	static ehs_bool bLastCharEsc = EHS_FALSE; /* true if the last character of the last packet was 'ESC' */
/**@todo handle unlikely situation where last packet received ended with ESC, and then we lost the connection */
	ehs_uint32 nCount = 0u;

	while (nCount < nSize)
	{
		if (bLastCharEsc)
		{
			switch (pData[nCount])
			{
			case 'D':
				*pbDisconnect = EHS_TRUE;
				/* if <esc> was last character of last packet, nSize is zero, otherwise it's nCount-1 */
				nSize = (nCount > 0u)?(nCount-1u):0u;
				break;
			case 'E':
				/* overwrite <esc>E with just <esc>. How to do this depends... */
				/* if E is the first character of the buffer, <esc> was last character of last packet & was ignored */
				if (nCount == 0u)
				{
					pData[nCount] = 0x1bu;
					nCount++; /* ensure that we don't "redetect" this escape after the switch statement */
				}
				else
				{
					/* move pData contents down one cell to overwrite E
					 * e.g if we have 12 entries (nSize = 12) and pCurrent (& nCount)
					 * points to entry 7, we want to move to 7, from 8, entries 8-11
					 * (i.e. len = 4 = (nSize-1) - nCount */
					nSize--;
					memmove((void*)(&(pData[nCount])), (const void*)(&(pData[nCount+1u])), (size_t)(nSize-nCount));
				}
				break;
			default: /* shouldn't happen */
				EhsSvcTcp_log("Unexpected escape sequence <esc>\0x%x\n",pData[nCount]);
			}
			bLastCharEsc = EHS_FALSE;
		}

		if (pData[nCount] == EHS_CHAR_ESC)
		{
			bLastCharEsc = EHS_TRUE;
			/* If the last character in the current buffer is escape - defer processing it until later */
			if ((nCount+1u) >= nSize)
			{
				nSize--;
			}
		}
		nCount++;
	}
	return nSize;

}

/**
 * Receive data from the target, then pass it on to EHS
 *
 * @return True if the client didn't request to disconnect.
 */
ehs_bool EhsSvcTcp_receive(void)
{
	ehs_uint8 bBuffIn[EHS_TGT_TCP_IN_BUFF_SIZE]; /* buffer for incoming data */
	ehs_sint32 nDataReceived;
	/* amount of data received by TCP/IP */
	ehs_uint8 *pData = bBuffIn;
	ehs_bool bDisconnect = EHS_FALSE; /* assume we want to stay connected */

	nDataReceived = EhsTgtTcp_recvNonblock(EhsSvcTcpSocketConnection, pData, EHS_TGT_TCP_IN_BUFF_SIZE);

	if (nDataReceived > 0) /* did we receive data? */
	{
		nDataReceived = (ehs_sint32)EhsSvcTcp_expandEscapes(pData,(ehs_uint32)nDataReceived,&bDisconnect);
		if(bDisconnect)
		{
			EhsSvcTcp_log("***Client instructed a disconnect\n");
		}			
		EhsSvcTcp_log("***Received %d bytes\n", nDataReceived);
		EhsSvcTcp_logBinaryData(pData,(ehs_uint32)nDataReceived);

		/* pass received data onto EHS */
		while (nDataReceived > 0) {
			/* push data onto the queue until no data remains */
			ehs_sint32 nDataPushed = (ehs_sint32)EhsConsoleQueue_push(EhsTgtConsoleInputQueueRef, pData, (ehs_uint32)nDataReceived);
			EhsSvcTcp_log("***Pushed %d bytes\n", nDataPushed);
			EhsSvcTcp_logBinaryData(pData,(ehs_uint32)nDataPushed);

			/* advance pointer to start of data that hasn't yet been pushed */
			pData += nDataPushed;
			nDataReceived = (nDataReceived - nDataPushed);
			/* If EHS couldn't handle everything, give it a chance to consume the data that's on the queue already */
			if (nDataReceived > 0L)
			{
				EhsSleep(EHS_TIME_us(EHS_TGT_TCP_SUSPENDTIME_us));
			}
		} 
	}
	else if (nDataReceived == EHS_TGT_TCP_SOCKET_ERROR)
	{
		if(EhsTgtTcp_getErrorCode(EHS_TRUE) != EHS_TGT_TCP_ERR_AGAIN)
		{
			EhsSvcTcp_logSocketError("EhsSvcTcp_receive.recv", EhsTgtTcp_getErrorCode(EHS_FALSE));
			bDisconnect = EHS_TRUE;		
		}
	}
	else
	{
		/* we didn't receive anything, but it's ok */
		bDisconnect = EHS_FALSE;
	}

	return (!bDisconnect); /*lint !e960 This is not an implicity type conversion */
}

/**
 * Send data from EHS to the target.
 *
 * @return true if we remain connected to the target
 */
ehs_bool EhsSvcTcp_send()
{
	ehs_bool bConnected = EHS_TRUE; /* assume that we stay connected */

	/* do we have any data to send? */
	if (!EhsConsoleQueue_isEmpty(EhsTgtConsoleOutputQueueRef))
	{
		ehs_uint8 bBuffOut[EHS_TGT_TCP_OUT_BUFF_SIZE];
		ehs_sint32 nDataSize;

		/* send one bufferful of data. This prevents EHS from monopolising a conversation. */
		printf("QPop: in = %d, out = %d\n", EhsTgtConsoleOutputQueueRef->uInIdx, EhsTgtConsoleOutputQueueRef->uOutIdx);
		nDataSize = (ehs_sint32)EhsConsoleQueue_pop(EhsTgtConsoleOutputQueueRef, bBuffOut, EHS_TGT_TCP_OUT_BUFF_SIZE);
		EhsSvcTcp_log("***Sent %d bytes\n", nDataSize);
		EhsSvcTcp_logBinaryData((const ehs_uint8*)bBuffOut, (ehs_uint32)nDataSize);

		/***** send bBuff to TCP/IP ****/
		if (EHS_TGT_TCP_SOCKET_ERROR == send((EhsTgtTcpSocketType)EhsSvcTcpSocketConnection, (const ehs_char *)bBuffOut , (ehs_sint32)nDataSize, (ehs_sint32)0))
		{
			EhsSvcTcp_logSocketError("EhsSvcTcp_send.send", EhsTgtTcp_getErrorCode(EHS_TRUE));
			bConnected = EHS_FALSE;
		}
	}
	return bConnected;
}
/**
 * Thread function handling Tcpip connections to EHS.
 * Once a client is connected, alternately poll to see if data has been received by TCP/IP,
 * then if there's outgoing data waiting in the outbound queue.
 */
void EhsSvcTcp_server(void)
{
	ehs_bool init;
#ifdef EHS_TGT_TCP_LOG_ENABLED
	EhsSvcTcpLogfile = fopen("ehs_tcpip.log","w");
#endif
	/* wait for initialisation to finish */
	while (!(*EhsTgtInitCompleteRef))
	{
		EhsSleep(EhsTgtTimer_usToTick(EHS_TGT_TCP_SUSPENDTIME_us));
	}

	init = EhsTgtTcp_init();

	if (init)
	{
		init = EhsSvcTcp_openConnection();
	}

	while(init)
	{
		/* tcpip initialisation */
		ehs_bool ClientConnected = EHS_TRUE;
		ehs_uint32 TestUsageCount = 0u;

		EhsSvcTcp_waitForClient();
		EhsSvcTcp_log("***Client connected\n");

		while (ClientConnected)
		{
			TestUsageCount++;
			ClientConnected = EhsSvcTcp_receive();

			if (ClientConnected)
			{
				ClientConnected = EhsSvcTcp_send();
			}
			
			if (EhsTgtProcess_isOrphan())
			{
				EhsSvcTcp_closeConnection();
				init = EHS_FALSE;
				break;
			}
		}
		init = EhsSvcTcp_closeConnection();
		EhsSvcTcp_log("UsageCount %d\n", TestUsageCount);		
	}

	EhsTgtTcp_term();
}
