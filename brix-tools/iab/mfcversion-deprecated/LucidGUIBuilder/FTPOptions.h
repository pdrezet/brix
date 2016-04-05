#if !defined(AFX_FTPOPTIONS_H__1358A843_7FAA_43E8_A509_9BC55697A2E6__INCLUDED_)
#define AFX_FTPOPTIONS_H__1358A843_7FAA_43E8_A509_9BC55697A2E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FTPOptions.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// FTPOptions dialog

class FTPOptions : public CDialog
{
// Construction
public:
	FTPOptions(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(FTPOptions)
	enum { IDD = IDD_FTP_OPTIONS };
	CString	m_password;
	CString	m_server;
	CString	m_username;
	CString	m_serverDir;
	//}}AFX_DATA

// methods
	void SaveFTPOptions();
	CString GetIniString(CString section, CString key, CString iniFile);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(FTPOptions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(FTPOptions)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FTPOPTIONS_H__1358A843_7FAA_43E8_A509_9BC55697A2E6__INCLUDED_)
