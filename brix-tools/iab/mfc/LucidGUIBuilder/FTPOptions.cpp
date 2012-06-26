// FTPOptions.cpp : implementation file
//

#include "stdafx.h"
#include "DrawGUI.h"
#include "FTPOptions.h"
#include "../common/LucidConstants.h"

#include <fstream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// global variable declared in CDrawGUIApp
extern char workDir[4096];

/////////////////////////////////////////////////////////////////////////////
// FTPOptions dialog


FTPOptions::FTPOptions(CWnd* pParent /*=NULL*/)
	: CDialog(FTPOptions::IDD, pParent)
{
	//{{AFX_DATA_INIT(FTPOptions)
	m_password = _T("");
	m_server = _T("");
	m_username = _T("");
	m_serverDir = _T("");
	//}}AFX_DATA_INIT
	m_server = GetIniString("FTP Options", "server", workDir + OPTIONSFILE);
	m_username = GetIniString("FTP Options", "username", workDir + OPTIONSFILE);
	m_password = GetIniString("FTP Options", "password", workDir + OPTIONSFILE);
	m_serverDir = GetIniString("FTP Options", "server dir", workDir + OPTIONSFILE);
}


void FTPOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(FTPOptions)
	DDX_Text(pDX, IDCLGB_PASSWORD, m_password);
	DDX_Text(pDX, IDCLGB_SERVER, m_server);
	DDX_Text(pDX, IDCLGB_USERNAME, m_username);
	DDX_Text(pDX, IDCLGB_SERVERDIR, m_serverDir);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(FTPOptions, CDialog)
	//{{AFX_MSG_MAP(FTPOptions)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void FTPOptions::SaveFTPOptions()
{
	ofstream datafile(workDir + OPTIONSFILE);

	if (!datafile.good()) {
		AfxMessageBox("File could not be written");
	}
	
	datafile << "[FTP Options]" << endl;
	datafile << "server=" << m_server << endl;
	datafile << "username=" << m_username << endl;
	datafile << "password=" << m_password << endl;
	datafile << "server dir=" << m_serverDir << endl;
	datafile << endl;
}

// Function that gets the data from an ini file by specifying the section and key
CString FTPOptions::GetIniString(CString section, CString key, CString iniFile) 
{
	char szDestBuff[256]={'\0'};
	LPTSTR pDestBuff = &szDestBuff[0];
	CString csDestBuff = "";
	char szDefault[]={""};

	GetPrivateProfileString(section, key, szDefault, szDestBuff, sizeof(szDestBuff), iniFile);

	csDestBuff = pDestBuff;
	return csDestBuff;
}

/////////////////////////////////////////////////////////////////////////////
// FTPOptions message handlers
