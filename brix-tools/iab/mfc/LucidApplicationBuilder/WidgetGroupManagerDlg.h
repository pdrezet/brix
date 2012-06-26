#pragma once
#include "ProjectMetaData.h"
#include "resource.h"
#include "afxwin.h"

// CWidgetGroupManagerDlg dialog

class CWidgetGroupManagerDlg : public CDialog
{
	DECLARE_DYNAMIC(CWidgetGroupManagerDlg)

public:
	CWidgetGroupManagerDlg(vector<CString> _vWidgetGroupNames, CWnd* pParent = NULL);   // standard constructor
	virtual ~CWidgetGroupManagerDlg();

	// methods
	CString getWidgetGroupName();
	void setWidgetGroupName(CString csWidgetGroupName);
	void setDialogCountString(CString csDialogCount);
	void setWidgetGroupDropList(vector<CString> vWidgetGrpNames);

// Dialog Data
	enum { IDD = IDD_WIDGET_GROUP_NAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	CString m_csWidgetGroupName;
	CString m_csDialogNum;
	CComboBox m_ctlWidgetGroupName;
	vector<CString> vWidgetGroupNames;

	// event handlers
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
