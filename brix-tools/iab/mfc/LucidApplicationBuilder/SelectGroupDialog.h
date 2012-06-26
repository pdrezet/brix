#if !defined(AFX_SELECTGROUPDIALOG_H__D66D1F12_C68A_47C4_84E7_C7BCD4ABB69C__INCLUDED_)
#define AFX_SELECTGROUPDIALOG_H__D66D1F12_C68A_47C4_84E7_C7BCD4ABB69C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectGroupDialog.h : header file
//
#include "Project.h"

/////////////////////////////////////////////////////////////////////////////
// CSelectGroupDialog dialog

class CSelectGroupDialog : public CDialog
{
// Construction
public:
	CSelectGroupDialog(Project* _pProject, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSelectGroupDialog)
	enum { IDD = IDD_SELECT_GROUP };
	CListBox	m_GroupName;
	//}}AFX_DATA

	// Attributes
	Project* pProject;
	CString selectedGroup;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectGroupDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSelectGroupDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTGROUPDIALOG_H__D66D1F12_C68A_47C4_84E7_C7BCD4ABB69C__INCLUDED_)
