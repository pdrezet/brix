#if !defined(AFX_GROUPSETUPDIALOG_H__DB325094_665B_4D1B_8476_A142B9B150BE__INCLUDED_)
#define AFX_GROUPSETUPDIALOG_H__DB325094_665B_4D1B_8476_A142B9B150BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GroupSetupDialog.h : header file
//
#include "Project.h"

/////////////////////////////////////////////////////////////////////////////
// CGroupSetupDialog dialog

class CGroupSetupDialog : public CDialog
{
// Construction
public:
	CGroupSetupDialog(Project* _pProject, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGroupSetupDialog)
	enum { IDD = IDD_GROUP_SETUP };
	CListBox	m_Group;
	//}}AFX_DATA

	// Attributes
	Project* pProject;
	CString group;
	UINT groupID;

	// Methods
	CString ExtractParam();
	bool GroupInUse(UINT selectedID, CString blockName);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGroupSetupDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGroupSetupDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnAddGroup();
	afx_msg void OnEditGroup();
	afx_msg void OnDeleteGroup();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GROUPSETUPDIALOG_H__DB325094_665B_4D1B_8476_A142B9B150BE__INCLUDED_)
