#if !defined(AFX_PROJECTCHOOSER_H__0FC50522_EDE1_4005_A3EF_0F7963976903__INCLUDED_)
#define AFX_PROJECTCHOOSER_H__0FC50522_EDE1_4005_A3EF_0F7963976903__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProjectChooser.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProjectChooser dialog

class CProjectChooser : public CDialog
{
// Construction
public:
	CProjectChooser(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CProjectChooser)
	enum { IDD = IDD_NEW_PROJECT };
	CEdit	m_ctrlProjectName;
	CEdit	m_ctrlPathName;
	CString	m_strPathName;
	CString	m_strProjectName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProjectChooser)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProjectChooser)
	afx_msg void OnBrowser();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROJECTCHOOSER_H__0FC50522_EDE1_4005_A3EF_0F7963976903__INCLUDED_)
