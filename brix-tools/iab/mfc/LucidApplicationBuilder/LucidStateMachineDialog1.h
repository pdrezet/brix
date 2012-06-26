#if !defined(AFX_LUCIDSTATEMACHINEDIALOG1_H__7257717B_2815_43CC_98A3_8962CF20A68E__INCLUDED_)
#define AFX_LUCIDSTATEMACHINEDIALOG1_H__7257717B_2815_43CC_98A3_8962CF20A68E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LucidStateMachineDialog1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLucidStateMachineDialog dialog

class CLucidStateMachineDialog : public CDialog
{
// Construction
public:
	CLucidStateMachineDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLucidStateMachineDialog)
	enum { IDD = IDD_DIALOG4 };
	CString	m_csState;
	CString	m_csNumTransitionsTo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLucidStateMachineDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLucidStateMachineDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LUCIDSTATEMACHINEDIALOG1_H__7257717B_2815_43CC_98A3_8962CF20A68E__INCLUDED_)
