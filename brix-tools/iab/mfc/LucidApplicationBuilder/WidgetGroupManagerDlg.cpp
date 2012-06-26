// WidgetGroupManager.cpp : implementation file
//

#include "stdafx.h"
#include "WidgetGroupManagerDlg.h"


// CWidgetGroupManagerDlg dialog

IMPLEMENT_DYNAMIC(CWidgetGroupManagerDlg, CDialog)

CWidgetGroupManagerDlg::CWidgetGroupManagerDlg(vector<CString> _vWidgetGroupNames, CWnd* pParent /*=NULL*/)
	: CDialog(CWidgetGroupManagerDlg::IDD, pParent)
	, m_csDialogNum(_T(""))
	, m_csWidgetGroupName(_T(""))
{
	vWidgetGroupNames = _vWidgetGroupNames;
}

CWidgetGroupManagerDlg::~CWidgetGroupManagerDlg()
{
}

void CWidgetGroupManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_DIALOG_NUM, m_csDialogNum);
	DDX_CBString(pDX, IDC_WIDGET_GROUP_COMBO, m_csWidgetGroupName);
	DDX_Control(pDX, IDC_WIDGET_GROUP_COMBO, m_ctlWidgetGroupName);
}


BEGIN_MESSAGE_MAP(CWidgetGroupManagerDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CWidgetGroupManagerDlg::OnBnClickedOk)
END_MESSAGE_MAP()

// methods
CString CWidgetGroupManagerDlg::getWidgetGroupName()
{
	return m_csWidgetGroupName;
}

void CWidgetGroupManagerDlg::setWidgetGroupName(CString csWidgetGroupName)
{
	m_csWidgetGroupName = csWidgetGroupName;
}

void CWidgetGroupManagerDlg::setDialogCountString(CString csDialogCount)
{
	m_csDialogNum = csDialogCount;
}

void CWidgetGroupManagerDlg::setWidgetGroupDropList(vector<CString> vWidgetGrpNames)
{
	for (UINT i=0; i<vWidgetGrpNames.size(); i++) {
		m_ctlWidgetGroupName.AddString(vWidgetGrpNames[i]);
	}
}

// CWidgetGroupManagerDlg message handlers
BOOL CWidgetGroupManagerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	setWidgetGroupDropList(vWidgetGroupNames);

	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_WIDGET_GROUP_COMBO);
	if(pCombo != NULL) {
		pCombo->SetFocus();
		return 0; //since we are explicity setting focus
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CWidgetGroupManagerDlg::OnBnClickedOk()
{
	UpdateData(TRUE);

	if (m_csWidgetGroupName == "") {
		AfxMessageBox("The Widget Group name must have at least 1 character.");
	}
	else {
		OnOK();
	}
}
