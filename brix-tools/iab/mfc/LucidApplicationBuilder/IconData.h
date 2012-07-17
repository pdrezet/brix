#if !defined(AFX_ICONDATA_H__D87EC240_9883_11D3_A9AD_00001C21326E__INCLUDED_)
#define AFX_ICONDATA_H__D87EC240_9883_11D3_A9AD_00001C21326E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// IconData.h : header file
//
#include "Infobaxbase.h"
#include "Porting_Classes/INXString.h"

/////////////////////////////////////////////////////////////////////////////
// General Purpose IconData dialog box for inputing parameter data for a  
// processing icon.
///////////////////////////////////////////////////////////////////////////

class IconData : public CDialog
{	
protected:
	//friend class Infoaxbase;
// Construction
public:
	
	//IconData(Tags::IDD, pParent);
	IconData(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(IconData)
	enum { IDD = IDD_DATA };
	CEdit	m_fixedinfo;
	CEdit	m_description;
	CButton	m_momentary;
	CButton	m_constant;
	CButton	m_negedge;
	CButton	m_plusedge;
	//}}AFX_DATA
	int deleteme;
	int 	momentary;
	int 	constant;
	int		negedge;
	int		plusedge;
	int wantoption;
	INXString	recorddelim;
	INXString	fielddelim;
	INXString	option2;
	INXString	option1;
	INXString	description;
	INXString	fixedinfo;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(IconData)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(IconData)
	afx_msg void OnDelete();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnPlus();
	afx_msg void OnNeg();
	afx_msg void OnConst();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ICONDATA_H__D87EC240_9883_11D3_A9AD_00001C21326E__INCLUDED_)
