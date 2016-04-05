#if !defined(AFX_DBGMSGDIALOG_H__89E025C3_F7AB_4CB0_93AB_6AB7FCE3F317__INCLUDED_)
#define AFX_DBGMSGDIALOG_H__89E025C3_F7AB_4CB0_93AB_6AB7FCE3F317__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DbgMsgDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDbgMsgDialog dialog

class CDbgMsgDialog : public CDialog
{
// Construction
public:
	CDbgMsgDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDbgMsgDialog)
	enum { IDD = IDD_DEBUG_MSG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDbgMsgDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDbgMsgDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBGMSGDIALOG_H__89E025C3_F7AB_4CB0_93AB_6AB7FCE3F317__INCLUDED_)
