#if !defined(AFX_GOTOTIMEDIALOG_H__3632FBA2_330D_4CF9_830E_0CB043096F97__INCLUDED_)
#define AFX_GOTOTIMEDIALOG_H__3632FBA2_330D_4CF9_830E_0CB043096F97__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GotoTimeDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGotoTimeDialog dialog

class CGotoTimeDialog : public CDialog
{
// Construction
public:
	CGotoTimeDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGotoTimeDialog)
	enum { IDD = IDD_GOTO_TIME };
	long	m_DbgHistTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGotoTimeDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGotoTimeDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GOTOTIMEDIALOG_H__3632FBA2_330D_4CF9_830E_0CB043096F97__INCLUDED_)
