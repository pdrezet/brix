#pragma once
#include "ProjectMetaData.h"
#include "resource.h"
#include "afxwin.h"
#include "Porting_Classes/INXString.h"
// CWidgetGroupManagerDlg dialog

class CWidgetGroupManagerDlg : public CDialog
{
	DECLARE_DYNAMIC(CWidgetGroupManagerDlg)

public:
	CWidgetGroupManagerDlg(vector<INXString> _vWidgetGroupNames, CWnd* pParent = NULL);   // standard constructor
	virtual ~CWidgetGroupManagerDlg();

	// methods
	INXString getWidgetGroupName();
	void setWidgetGroupName(INXString csWidgetGroupName);
	void setDialogCountString(INXString csDialogCount);
	void setWidgetGroupDropList(vector<INXString> vWidgetGrpNames);

// Dialog Data
	enum { IDD = IDD_WIDGET_GROUP_NAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	INXString m_csWidgetGroupName;
	INXString m_csDialogNum;
	CComboBox m_ctlWidgetGroupName;
	vector<INXString> vWidgetGroupNames;

	// event handlers
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
