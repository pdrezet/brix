#if !defined(AFX_ZOOMDIALOG_H__CBDF6533_5F9C_464A_9794_19460FF262C4__INCLUDED_)
#define AFX_ZOOMDIALOG_H__CBDF6533_5F9C_464A_9794_19460FF262C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZoomDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CZoomDialog dialog
#include "Porting_Classes/INXString.h"
class CZoomDialog : public CDialog
{
// Construction
public:
	CZoomDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CZoomDialog)
	enum { IDD = IDD_ZOOM };
	CComboBox	m_scale;
	//}}AFX_DATA

	// Attributes
	INXString szScale;
	int iScale;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZoomDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CZoomDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZOOMDIALOG_H__CBDF6533_5F9C_464A_9794_19460FF262C4__INCLUDED_)
