#if !defined(AFX_EXPORTDIALOG_H__64B1E484_7FE8_45AB_B956_8BA9F6EE5E15__INCLUDED_)
#define AFX_EXPORTDIALOG_H__64B1E484_7FE8_45AB_B956_8BA9F6EE5E15__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExportDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CExportDialog dialog

class CExportDialog : public CDialog
{
// Construction
public:
	CExportDialog(CWnd* pParent = NULL);   // standard constructor
	
	//Methods
	bool ExportExist(int index);

// Dialog Data
	//{{AFX_DATA(CExportDialog)
	enum { IDD = IDD_EXPORT };
	CListBox	m_Library;
	CListBox	m_Export;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExportDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CExportDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAdd();
	afx_msg void OnDelete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXPORTDIALOG_H__64B1E484_7FE8_45AB_B956_8BA9F6EE5E15__INCLUDED_)
