/** @file LucidTcpipClient.h 
 * Implements Client Class TCPIP interface 
 * 
 * @author: Kieron White
 * @version: $Revision: 000 $
 * @date: $Date: 2007-03-29 $
 */
#pragma once
#include <fstream>
using namespace std;
#pragma comment(lib, "ws2_32.lib")
#include <winsock.h>
#include "LucidEnums.h"
#include "LucidConstants.h"

#ifndef LUCIDTCPIPCLIENT_H
#define LUCIDTCPIPCLIENT_H

class TcpLogger
{
	char szFilename[256];	
	void LogAddMessage(CString csLog);
	void LogRemoveLinesFromFrontOfFile(int number_of_lines_to_remove);
	void LogClear();
public:
	static long s_lLogCount;
	static int s_iRunOnce;
	TcpLogger();
	long Log(const char* pszFormat, ...);
	long LogNumberOfLines();
};

class TcpTestSuite
{
	TcpLogger logger;
	void LoggerTest1();
	void LoggerTest2();
	void LoggerTest3();
public:
	void RunTests();
	void RunATest();
};

class CTgtTransProgDlog;

class LucidTcpipClient
{
private:
	SOCKET s_Socket;
	SOCKET s_TempSocket; //needed by AcceptSocket
	SOCKADDR_IN s_Connection;
	TcpLogger logger;
	TcpTestSuite tests;
	LtsStatusType SendText(char *szText, int size); //handles binary data
	LtsStatusType SendData(CString csSendBuffer);
	LtsStatusType SendData(const char *szSendBuffer, int size);
	LtsStatusType SendRawData(const char *szSendBuffer, int size);
	LtsStatusType RecvData(CString &csRecvBuffer);
	LtsStatusType InitialiseWinsock();
	LtsStatusType CreateSocket();
	LtsStatusType ServerConnect();
	LtsStatusType SetSocketOptions();
	CString csTempLineBuffer;
	CString csTempBlockBuffer;
	static const char* szEscape; // represents escape character over TCP/IP
	static const char* szDisconnect; // TCP/IP disconnect signal sent over TCP/IP
public:	
	static int s_iPort;	
	static CString s_csIpAddress;	
	LucidTcpipClient(void);
	~LucidTcpipClient(void);
	LtsStatusType Connect();
	LtsStatusType DisConnect();
	LtsStatusType SendFileContents(CString csFilePath);
	LtsStatusType SendFileContents(CString csFilePath, CTgtTransProgDlog *pDlog );
	
	LtsStatusType SendText(CString csText);	
	LtsStatusType ReceiveTextLine(CString &csReceiveText); // receives a line of text 
	LtsStatusType ReceiveTextBlock(CString &csReceiveText); // receives a block of text i.e. includes line breaks


	//! Receives a delimited block of text i.e. includes line breaks - either to leftmost or rightmost limiter
	/*!
	\param csReceiveText Get's loaded with the text block
	\param csDelimToken The delimiter between blocks
	\param bGetLeftBlock If true, get only leftmost block.  Otherwise get all *complete* blocks.
	*/
	LtsStatusType ReceiveTextBlock( 
		CString &csReceiveText, 
		CString &csDelimToken,
		const bool &bGetLeftBlock ); 

	void ConfigDlg();
	void GetLastError();

	//Used for config dialog interface
	int GetPort();
	CString GetIPAddress();
	void SetPort(int iPort);
	void SetIPAddress(CString csIpAddress);

	//Helper functions
	int FileSize(CString csFullPath);
	LtsStatusType WaitForServer(CString &csReceive);

	LtsStatusType SendFile(CString csFilePath, CString csTargetFileName );
	LtsStatusType SendFile(CString csFilePath, CString csTargetFileName, CTgtTransProgDlog *pDlog );

	void InitTcpipClient();
};
#endif