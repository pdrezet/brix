#pragma once

#include "Resource.h"
// COkCnclDlog dialog

class COkCnclDlog : public CDialog
{
	DECLARE_DYNAMIC(COkCnclDlog)

public:
	COkCnclDlog(CWnd* pParent = NULL);   // standard constructor

	COkCnclDlog(const CString &prompt, CWnd* pParent =NULL);

	virtual ~COkCnclDlog();

// Dialog Data
	enum { IDD = IDD_DIALOG_OK_CNCL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	CString m_csPrompt;
};
