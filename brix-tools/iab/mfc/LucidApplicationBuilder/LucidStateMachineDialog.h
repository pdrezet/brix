#if !defined(AFX_LUCIDSTATEMACHINEDIALOG_H__0D513D54_9AF8_411F_A8EB_2B5119B45FD8__INCLUDED_)
#define AFX_LUCIDSTATEMACHINEDIALOG_H__0D513D54_9AF8_411F_A8EB_2B5119B45FD8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LucidStateMachineDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// LucidStateMachineDialog dialog

class LucidStateMachineDialog : public CDialog
{
// Construction
public:
	int GetRadioCheck();
	LucidStateMachineDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(LucidStateMachineDialog)
	enum { IDD = IDD_DIALOG3 };
	CButton	m_RadioButton;
	CString	m_csState;
	CString	m_csTransitionsTo;
	BOOL	m_bEntryActionCheckBox;
	BOOL	m_bTransitionActionCheck;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(LucidStateMachineDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int m_nRadioValue;
	// Generated message map functions
	//{{AFX_MSG(LucidStateMachineDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LUCIDSTATEMACHINEDIALOG_H__0D513D54_9AF8_411F_A8EB_2B5119B45FD8__INCLUDED_)
