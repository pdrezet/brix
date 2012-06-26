#if !defined(AFX_LIBRARYDIALOG_H__991463E4_0057_406F_B931_6B854D940236__INCLUDED_)
#define AFX_LIBRARYDIALOG_H__991463E4_0057_406F_B931_6B854D940236__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LibraryDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLibraryDialog dialog

class CLibraryDialog : public CDialog
{
// Construction
public:
	CLibraryDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLibraryDialog)
	enum { IDD = IDD_LIBRARY_CHOOSER };
	CComboBox	m_Library;
	//}}AFX_DATA

	// Attributes
	CString library;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLibraryDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLibraryDialog)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LIBRARYDIALOG_H__991463E4_0057_406F_B931_6B854D940236__INCLUDED_)
