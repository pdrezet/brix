#if !defined(AFX_INSTANCENAMEDIALOG_H__9E91CDF3_1BD4_48C3_8FD0_26889CB25ECF__INCLUDED_)
#define AFX_INSTANCENAMEDIALOG_H__9E91CDF3_1BD4_48C3_8FD0_26889CB25ECF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InstanceNameDialog.h : header file
//
#include "Condat.h"

/////////////////////////////////////////////////////////////////////////////
// CInstanceNameDialog dialog

class CInstanceNameDialog : public CDialog
{
// Construction
public:
	CInstanceNameDialog(ConData* blob, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInstanceNameDialog)
	enum { IDD = IDD_INSTANCE_NAME };
	CString	m_InstanceName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInstanceNameDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInstanceNameDialog)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INSTANCENAMEDIALOG_H__9E91CDF3_1BD4_48C3_8FD0_26889CB25ECF__INCLUDED_)
