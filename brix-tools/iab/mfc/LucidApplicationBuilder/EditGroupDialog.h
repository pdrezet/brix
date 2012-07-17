#if !defined(AFX_EDITGROUPDIALOG_H__7FB97941_43E2_4977_9C17_8F928098ADF5__INCLUDED_)
#define AFX_EDITGROUPDIALOG_H__7FB97941_43E2_4977_9C17_8F928098ADF5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditGroupDialog.h : header file
//
#include "Project.h"
#include "Porting_Classes/INXString.h"
/////////////////////////////////////////////////////////////////////////////
// CEditGroupDialog dialog

class CEditGroupDialog : public CDialog
{
// Construction
public:
	CEditGroupDialog(Project* _pProject, bool _addGroup, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEditGroupDialog)
	enum { IDD = IDD_EDIT_GROUP };
	int		m_Alloc;
	int		m_Period;
	INXString	m_Name;
	//}}AFX_DATA

	Project* pProject;
	bool addGroup;
	
	// Methods
	bool NameExists();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditGroupDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEditGroupDialog)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITGROUPDIALOG_H__7FB97941_43E2_4977_9C17_8F928098ADF5__INCLUDED_)
