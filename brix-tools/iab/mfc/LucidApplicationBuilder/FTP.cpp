// FTP.cpp: implementation of the FTP class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DrawProg.h"
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
	//session = new CInternetSession("");
}

FTP::~FTP()
{
	//delete session;
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

// Function that sets the server directory
int FTP::ftpSetServerDir(LPCSTR serverDir, CFtpConnection* pConn) {
	if (!pConn->SetCurrentDirectory(serverDir))
	{
		return 0;
	}
	return 1;
}

// Function that performs a ftp put
int FTP::ftpPut(LPCSTR localFile, LPCSTR remoteFile, CFtpConnection* pConn, int transferType) {		
	if (!pConn->PutFile(localFile, remoteFile, transferType))
	{
		return 0;
	}
	return 1;
}

// Function that performs a ftp get
int FTP::ftpGet(LPCSTR remoteFile, LPCSTR localFile, CFtpConnection* pConn) {
	// bFailIfExists is set to FALSE. This means that if the local file already exists it 
	// will be overwritten.
	if (!pConn->GetFile(remoteFile, localFile, FALSE, FILE_ATTRIBUTE_NORMAL, FTP_TRANSFER_TYPE_ASCII))
	{
		return 0;
	}
	return 1;
}

// Function that closes an ftp session
void FTP::ftpClose() {
	session->Close();
	delete session;
}

// Function that opens an ftp session
void FTP::ftpOpen() {
	session = new CInternetSession("");
}

// Function that renames a file
int FTP::ftpRename(LPCSTR existingFile, LPCSTR newFile, CFtpConnection* pConn) {
	if (!pConn->Rename(existingFile, newFile))
	{
		return 0;
	}
	return 1;
}