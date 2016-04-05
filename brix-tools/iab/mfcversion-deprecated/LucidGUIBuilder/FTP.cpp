// FTP.cpp: implementation of the FTP class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DrawGUI.h"
#include "FTP.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

FTP::FTP()
{
	session = new CInternetSession("");
}

FTP::~FTP()
{
	delete session;
}

// Function that connects to a server
CFtpConnection* FTP::ftpConnect(LPCSTR server, LPCSTR username, LPCSTR password) {
	CString IDS_EXCEPTION = "An exception occurred when attempting to create an FTP connection.";
	CFtpConnection* pConn = NULL;
	try
	{
		pConn = session->GetFtpConnection(server, username, password);
	}
	catch (CInternetException* pEx)
	{
		// catch errors from WinINet
		TCHAR szErr[1024];
		if (pEx->GetErrorMessage(szErr, 1024))
			AfxMessageBox(szErr, MB_OK);
		else
			AfxMessageBox(IDS_EXCEPTION, MB_OK);
		pEx->Delete();

		pConn = NULL;
	}
	
	return pConn;
}

// Function that performs a ftp put
int FTP::ftpPut(LPCSTR localFile, LPCSTR remoteFile, CString mode, CFtpConnection* pConn) {
	int transferType;

	if (mode == "ascii") {
		transferType = FTP_TRANSFER_TYPE_ASCII;
	}
	else if (mode == "bin") {
		transferType = FTP_TRANSFER_TYPE_BINARY;
	}

	if (!pConn->PutFile(localFile, remoteFile, transferType))
	{
		return 0;
	}
	return 1;
}

// Function that closes an ftp session
void FTP::ftpClose() {
	session->Close();
}

// Function that sets the server directory
int FTP::ftpSetServerDir(LPCSTR serverDir, CFtpConnection* pConn) {
	if (!pConn->SetCurrentDirectory(serverDir))
	{
		return 0;
	}
	return 1;
}
