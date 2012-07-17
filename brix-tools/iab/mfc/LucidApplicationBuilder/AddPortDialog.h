#if !defined(AFX_ADDPORTDIALOG_H__4A12F202_0176_44E3_8C46_2834EF9E90B1__INCLUDED_)
#define AFX_ADDPORTDIALOG_H__4A12F202_0176_44E3_8C46_2834EF9E90B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddPortDialog.h : header file
//
#include "Condat.h"
#include "Porting_Classes/INXString.h"

/////////////////////////////////////////////////////////////////////////////
// CAddPortDialog dialog

class CAddPortDialog : public CDialog
{
// Construction
public:
	CAddPortDialog(ConData* _blob, CWnd* pParent = NULL);   // standard constructor
	
	// attributes
	//char portType[16];
	//char dataType[16];
	INXString portType;
	INXString dataType;
	ConData* blob;

	// Methods
	bool IsUnique();

// Dialog Data
	//{{AFX_DATA(CAddPortDialog)
	enum { IDD = IDD_ADD_PORT };
	CComboBox	m_DataType;
	CComboBox	m_PortType;
	INXString	m_PortLabel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddPortDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddPortDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDPORTDIALOG_H__4A12F202_0176_44E3_8C46_2834EF9E90B1__INCLUDED_)
