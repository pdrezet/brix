#pragma once
#include "Resource.h"

// CYesY2ANoCnclDlog dialog

class CYesY2ANoCnclDlog : public CDialog
{
	DECLARE_DYNAMIC(CYesY2ANoCnclDlog)

public:
	CYesY2ANoCnclDlog(CWnd* pParent = NULL);   // standard constructor
	CYesY2ANoCnclDlog(const CString &prompt, CWnd* pParent = NULL);   // standard constructor
	virtual ~CYesY2ANoCnclDlog();

// Dialog Data
	enum { IDD = IDD_DIALOG_YES_Y2A_NO_CNCL };

protected:

	CString m_csPrompt;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonYes();
public:
	afx_msg void OnBnClickedButtonYes2all();
public:
	afx_msg void OnBnClickedButtonNo();
public:
	afx_msg void OnBnClickedButtonCancel();
public:
	virtual BOOL OnInitDialog();
};
