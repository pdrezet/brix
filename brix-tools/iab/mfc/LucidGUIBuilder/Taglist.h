#if !defined(AFX_TAGLIST_H__75A233C2_D756_11D3_A9AD_00001C21326E__INCLUDED_)
#define AFX_TAGLIST_H__75A233C2_D756_11D3_A9AD_00001C21326E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Taglist.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Taglist dialog

class Taglist : public CDialog
{
// Construction
public:
	Taglist(CWnd* pParent = NULL);   // standard constructor
	TagListbuf;
// Dialog Data
	//{{AFX_DATA(Taglist)
	enum { IDD = IDD_TAGS };
	CListBox	m_taglist;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Taglist)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Taglist)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TAGLIST_H__75A233C2_D756_11D3_A9AD_00001C21326E__INCLUDED_)
