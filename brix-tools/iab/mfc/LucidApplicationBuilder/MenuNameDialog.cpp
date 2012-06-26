// MenuNameDialog.cpp : implementation file
//

#include "stdafx.h"
#include "MenuNameDialog.h"
#include "DrawProg.h"

// CMenuNameDialog dialog

IMPLEMENT_DYNAMIC(CMenuNameDialog, CDialog)

CMenuNameDialog::CMenuNameDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CMenuNameDialog::IDD, pParent)
	, m_csMenuName(_T(""))
{

}

CMenuNameDialog::~CMenuNameDialog()
{
}

void CMenuNameDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_MENU_NAME_COMBO, m_csMenuName);
	DDX_Control(pDX, IDC_MENU_NAME_COMBO, m_ctlMenuName);
}


BEGIN_MESSAGE_MAP(CMenuNameDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CMenuNameDialog::OnBnClickedOk)
END_MESSAGE_MAP()

// Methods
CString CMenuNameDialog::getMenuName()
{
	return m_csMenuName;
}

void CMenuNameDialog::setMenuNamesDropList(set<CString> sMenuNames)
{
	set<CString>::iterator it = sMenuNames.begin();
	while( it != sMenuNames.end() ){
		m_ctlMenuName.AddString(*it);
		it++;
	}
}

// CMenuNameDialog message handlers

void CMenuNameDialog::OnBnClickedOk()
{
	OnOK();
}

// CWidgetGroupManagerDlg message handlers
BOOL CMenuNameDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	set<CString> sL2LibMenuNames;

	// populate the menu name drop-list with the library level 2 menu names
	pFrame->m_cFuncBlockBar.m_cFuncBlckTree.getL2LibMenuNames(sL2LibMenuNames);
	setMenuNamesDropList(sL2LibMenuNames);

	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_MENU_NAME_COMBO);
	if(pCombo != NULL) {
		pCombo->SetFocus();
		return 0; //since we are explicity setting focus
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
