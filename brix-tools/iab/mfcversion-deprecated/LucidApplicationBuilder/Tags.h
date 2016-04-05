#if !defined(AFX_TAGS_H__45154762_CF1D_11D3_A9AD_00001C21326E__INCLUDED_)
#define AFX_TAGS_H__45154762_CF1D_11D3_A9AD_00001C21326E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Tags.h : header file
//
#include "Infobaxbase.h"
#include "Porting_Classes/INXString.h"
#include "Porting_Classes/INXObjArray.h"
/////////////////////////////////////////////////////////////////////////////
// Tags dialog: This is 
//
//

class Tags : public CDialog
{
protected:
	//friend class Infobaxbase;
// Construction
public:
	
	Tags(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Tags)
	enum { IDD = IDD_TAGS };
	CListBox	m_list;
	//}}AFX_DATA
	INXObjArray<INXString> *TagList;
	int assigned;
	int selected;
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
	//{{AFX_VIRTUAL(Tags)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Tags)
	virtual BOOL OnInitDialog();
	afx_msg void OnDelete();
	virtual void OnOK();
	afx_msg void OnDblclkList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TAGS_H__45154762_CF1D_11D3_A9AD_00001C21326E__INCLUDED_)
