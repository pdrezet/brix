#if !defined(AFX_FTPOPTIONS_H__0C76E34A_F748_4991_A5E8_82B96C9B9739__INCLUDED_)
#define AFX_FTPOPTIONS_H__0C76E34A_F748_4991_A5E8_82B96C9B9739__INCLUDED_

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
	INXString	m_server;
	INXString	m_username;
	INXString	m_password;
	INXString	m_serverDir;
	//}}AFX_DATA

// methods
	void SaveFTPOptions();
	INXString GetIniString(INXString section, INXString key, INXString iniFile);

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
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FTPOPTIONS_H__0C76E34A_F748_4991_A5E8_82B96C9B9739__INCLUDED_)
