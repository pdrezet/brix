#if !defined(AFX_DELIMS_H__AAA53783_D692_11D3_A9AD_00001C21326E__INCLUDED_)
#define AFX_DELIMS_H__AAA53783_D692_11D3_A9AD_00001C21326E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// delims.h : header file
//
#include "Porting_Classes/INXString.h"

/////////////////////////////////////////////////////////////////////////////
// delims dialog 
// NOTES: This is legacy and can be removed from the project

class delims : public CDialog
{
// Construction
public:
	delims(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(delims)
	enum { IDD = IDD_DIALOG2 };
	CButton	m_software;
	CEdit	m_stopbits;
	CComboBox	m_parity;
	CEdit	m_bits;
	CEdit	m_baud;
	CEdit	m_record;
	CEdit	m_field;
	//}}AFX_DATA
	INXString record,field,baud,parity,bits,stopbits,software;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(delims)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(delims)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DELIMS_H__AAA53783_D692_11D3_A9AD_00001C21326E__INCLUDED_)
