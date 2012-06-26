#if !defined(AFX_DATSRC_H__07633A60_F080_11D3_A9AD_00001C21326E__INCLUDED_)
#define AFX_DATSRC_H__07633A60_F080_11D3_A9AD_00001C21326E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Datsrc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Datsrc dialog - Support for DDX
// NOTES: CAN BE REMOVED FROM PROJECT.

class Datsrc : public CDialog
{
// Construction
public:
	Datsrc(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Datsrc)
	enum { IDD = IDD_DATASRC };
	CString	m_directory;
	CString	m_filenaame;
	CString	m_option1;
	CString	m_option2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Datsrc)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Datsrc)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATSRC_H__07633A60_F080_11D3_A9AD_00001C21326E__INCLUDED_)
