#if !defined(AFX_BLOCKNAMEDIALOG_H__D2B2209B_CB0A_4FDC_AD93_D79477EB2906__INCLUDED_)
#define AFX_BLOCKNAMEDIALOG_H__D2B2209B_CB0A_4FDC_AD93_D79477EB2906__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BlockNameDialog.h : header file
//
#include "Porting_Classes/INXString.h"

/////////////////////////////////////////////////////////////////////////////
// CBlockNameDialog dialog

class CBlockNameDialog : public CDialog
{
// Construction
public:
	CBlockNameDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBlockNameDialog)
	enum { IDD = IDD_BLOCK_NAME };
	INXString	m_BlockName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBlockNameDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBlockNameDialog)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BLOCKNAMEDIALOG_H__D2B2209B_CB0A_4FDC_AD93_D79477EB2906__INCLUDED_)
