#if !defined(AFX_PORTLABELDIALOG_H__7BEEAA06_A332_4D60_BCDB_2F005BD60729__INCLUDED_)
#define AFX_PORTLABELDIALOG_H__7BEEAA06_A332_4D60_BCDB_2F005BD60729__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PortLabelDialog.h : header file
//
#include "Porting_Classes/INXString.h"
/////////////////////////////////////////////////////////////////////////////
// CPortLabelDialog dialog

class CPortLabelDialog : public CDialog
{
// Construction
public:
	CPortLabelDialog(DEP* _pDEP, CWnd* pParent = NULL);   // standard constructor

	// attributes
	DEP* pDEP;

	// methods
	bool IsUnique();

// Dialog Data
	//{{AFX_DATA(CPortLabelDialog)
	enum { IDD = IDD_PORT_LABEL };
	INXString	m_PortLabel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPortLabelDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPortLabelDialog)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	public:
	virtual BOOL OnInitDialog();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PORTLABELDIALOG_H__7BEEAA06_A332_4D60_BCDB_2F005BD60729__INCLUDED_)
