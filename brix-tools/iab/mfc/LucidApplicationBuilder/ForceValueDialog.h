#if !defined(AFX_FORCEVALUEDIALOG_H__DE95C252_624F_4374_A3F2_4C90DE64CCB8__INCLUDED_)
#define AFX_FORCEVALUEDIALOG_H__DE95C252_624F_4374_A3F2_4C90DE64CCB8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ForceValueDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CForceValueDialog dialog

class CForceValueDialog : public CDialog
{
// Construction
public:
	CForceValueDialog(int _dataType, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CForceValueDialog)
	enum { IDD = IDD_FORCE_VALUE };
	CString	m_ForceValue;
	//}}AFX_DATA

	int dataType;
	
	//methods
	bool isDigit(char c);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CForceValueDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CForceValueDialog)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORCEVALUEDIALOG_H__DE95C252_624F_4374_A3F2_4C90DE64CCB8__INCLUDED_)
