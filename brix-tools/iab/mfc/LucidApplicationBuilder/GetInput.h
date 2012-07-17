#if !defined(AFX_GETINPUT_H__AAA53782_D692_11D3_A9AD_00001C21326E__INCLUDED_)
#define AFX_GETINPUT_H__AAA53782_D692_11D3_A9AD_00001C21326E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// GetInput.h : header file
//
#include "Porting_Classes/INXString.h"
/////////////////////////////////////////////////////////////////////////////
// GetInput dialog

class GetInput : public CDialog
{
// Construction
public:
	GetInput(CWnd* pParent = NULL);   // standard constructor
	INXString m_string;
// Dialog Data
	//{{AFX_DATA(GetInput)
	enum { IDD = IDD_DIALOG1 };
	CEdit	m_editbox;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GetInput)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(GetInput)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GETINPUT_H__AAA53782_D692_11D3_A9AD_00001C21326E__INCLUDED_)
