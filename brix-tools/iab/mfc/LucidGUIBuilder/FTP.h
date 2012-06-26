// FTP.h: interface for the FTP class.
//
//////////////////////////////////////////////////////////////////////


#pragma once

#include <afxinet.h>

class FTP : public CObject  
{
public:
	FTP();
	virtual ~FTP();

	// methods
	CFtpConnection* ftpConnect(LPCSTR server, LPCSTR username, LPCSTR password);
	int ftpPut(LPCSTR localFile, LPCSTR remoteFile, CString mode, CFtpConnection* pConn);
	void ftpClose();
	int ftpSetServerDir(LPCSTR serverDir, CFtpConnection* pConn);

	// attributes
	CInternetSession* session;
};


