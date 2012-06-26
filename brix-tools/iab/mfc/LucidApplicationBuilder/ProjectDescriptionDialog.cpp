// ProjectDescriptionDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ProjectDescriptionDialog.h"


// ProjectDescriptionDialog dialog

IMPLEMENT_DYNAMIC(ProjectDescriptionDialog, CDialog)

ProjectDescriptionDialog::ProjectDescriptionDialog(ProjectMetaData* pProjMData, CWnd* pParent /*=NULL*/)
	: CDialog(ProjectDescriptionDialog::IDD, pParent)
{
	_pProjMData = pProjMData;
}

ProjectDescriptionDialog::~ProjectDescriptionDialog()
{
}

BOOL ProjectDescriptionDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	SetDlgItemTextA(IDC_PROJECT_NAME, _pProjMData->m_csProjectAppCanonicalName);
	SetDlgItemTextA(IDC_PROJECT_COMMERCIALNAME, _pProjMData->m_csProjectAppCommercialName);
	SetDlgItemTextA(IDC_PROJECT_VERSION, _pProjMData->m_csProjectAppVersion);
	SetDlgItemTextA(IDC_PROJECT_DESCRIPTION, _pProjMData->m_csProjectAppDescription);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void ProjectDescriptionDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_PROJECT_NAME, _pProjMData->m_csProjectAppCanonicalName);
	DDX_Text(pDX, IDC_PROJECT_COMMERCIALNAME, _pProjMData->m_csProjectAppCommercialName);
	DDX_Text(pDX, IDC_PROJECT_VERSION, _pProjMData->m_csProjectAppVersion);
	DDX_Text(pDX, IDC_PROJECT_DESCRIPTION, _pProjMData->m_csProjectAppDescription);

}


BEGIN_MESSAGE_MAP(ProjectDescriptionDialog, CDialog)
	ON_BN_CLICKED(IDOK, &ProjectDescriptionDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// ProjectDescriptionDialog message handlers

void ProjectDescriptionDialog::OnBnClickedOk()
{
	UpdateData(TRUE);

	OnOK();
}
