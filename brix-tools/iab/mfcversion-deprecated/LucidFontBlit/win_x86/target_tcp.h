/** @file target_tcp.h
 * This file contains all of the target-specific definitions for using TCP/IP
 * 
 * @author: Dr Andrew Coombes
 * @version: $Revision: 744 $
 * @date: $Date: 2006-11-06 16:22:28 +0000 (Mon, 06 Nov 2006) $
 * 
 * Copyright (c) Ncapsa Ltd, 2006. All rights reserved.
 */

#ifndef EHS_TARGET_TCP_H
#define EHS_TARGET_TCP_H
/*lint -e(829) We need to use <stdio.h> for the Windows target */
#include "stdafx.h"
#include "target.h"
#include "console_queue.h"
#pragma comment(lib, "ws2_32.lib")
/*line +e(829) */

/**
 * Used to perform Logging of TCP/IP data
 */
#define EHS_TGT_TCP_LOG_ENABLED

/**
 * Size of buffer to use when sending to TCP/IP. For portability we make this less than or equal to MAXINT(ehs_sint16)
 */
#define EHS_TGT_TCP_OUT_BUFF_SIZE  32767u	
/**
 * Size of buffer to use when receiving from TCP/IP. For portability we make this less than or equal to MAXINT(ehs_sint16)
 */
#define EHS_TGT_TCP_IN_BUFF_SIZE  32767u
#define EHS_TGT_TCP_PORTNUM  11425u			/**< Port number to use for receiving TCP/IP connections */

#define EHS_TGT_TCP_LISTENTIME_us 20000 /**< Time to listen (uS) for incoming TCP/IP data */
#define EHS_TGT_TCP_SUSPENDTIME_us 20000LL /**< Time to sleep (uS) to allow main EHS thread to do processing */

/*lint -emacro( (960), EHS_TGT_TCP_INVALID_SOCKET) Standard definition from Windows header file - proven in use */
#define EHS_TGT_TCP_INVALID_SOCKET (INVALID_SOCKET)	/**< Value returned from socket to indicate failure */
#define EHS_TGT_TCP_SOCKET_ERROR (SOCKET_ERROR) /**< Value to be returned from socket-using functions to indicate failure */
#define EHS_TGT_TCP_SD_BOTH (SD_BOTH) /**< Indicates that a shutdown is to apply to both read and write channels */
#define EHS_TGT_TCP_CLOSE_SOCKET closesocket /**< Function called to close a socket */
/**
 * Allows the socket type to be hidden
 */
typedef SOCKET EhsTgtTcpSocketType;

typedef SOCKADDR_IN EhsTgtTcpSockAddrInType;

typedef SOCKADDR EhsTgtTcpSockAddrType;

/*
 * Abstraction of the type used to report error numbers
 */
typedef int EhsTgtTcpErrType;

/* Specific error codes required by console_server */

/**
 * Error code: Socket is not connected
 */
#define EHS_TGT_TCP_ERR_NOTCONN WSAENOTCONN
/**
 * Error code: try again. Returned by recv()
 */
#define EHS_TGT_TCP_ERR_AGAIN WSATRY_AGAIN

/**
 * Get the last error detected for the TCP/IP operation.
 *
 * @param[in] bFirstUse True if this is the first use of this call after a socket call, false if 
 * we're asking for the same error number again
 */
EHS_GLOBAL EhsTgtTcpErrType EhsTgtTcp_getErrorCode(ehs_bool bFirstUse);

/**
 * A fault has been detected with TCP/IP. Get an error message corresponding to the current problem.
 *
 * @param[in] nErrCode Code of the error for which we require the error text
 * @return pointer to the error text
 */
EHS_GLOBAL const ehs_char* EhsTgtTcp_getErrorText(EhsTgtTcpErrType nErrCode);

/**
 * Target-specific shutdown for the TCP/IP connection
 */
EHS_GLOBAL void EhsTgtTcp_term(void);

/**
 * Target-specific initialisation of Tcpip. Also waits until the main
 * EHS thread is up and running.
 *
 * @return true if initialisation was successful
 */
EHS_GLOBAL ehs_bool EhsTgtTcp_init(void);

/**
 * Target-specific non-blocking receive of Tcpip.
 *
 * @param[in] xRxSocket Socket to receive data on
 * @param[out] pData Pointer to memory to contain received data
 * @param[in] nData Maximum amount of data to return
 * @return number of bytes returned or EHS_TGT_TCP_SOCKET_ERROR
 */
EHS_GLOBAL ehs_sint32 EhsTgtTcp_recvNonblock(EhsTgtTcpSocketType xRxSocket, ehs_uint8* pData, ehs_uint32 nData);

#endif /* EHS_TARGET_TCP_H */
