#pragma once
#include "afxwin.h"
#include "ProjectMetaData.h"
#include "resource.h"

// CMenuNameDialog dialog

class CMenuNameDialog : public CDialog
{
	DECLARE_DYNAMIC(CMenuNameDialog)

public:
	CMenuNameDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMenuNameDialog();

// methods
	CString getMenuName();
protected:
	void setMenuNamesDropList(set<CString> sMenuNames);

public:
// Dialog Data
	enum { IDD = IDD_MENU_NAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	CString m_csMenuName;
	CComboBox m_ctlMenuName;

// event handlers
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
