// YesY2ANoCnclDlog.cpp : implementation file
//

#include "stdafx.h"
#include "YesY2ANoCnclDlog.h"


// CYesY2ANoCnclDlog dialog

IMPLEMENT_DYNAMIC(CYesY2ANoCnclDlog, CDialog)

CYesY2ANoCnclDlog::CYesY2ANoCnclDlog(CWnd* pParent /*=NULL*/)
	: CDialog(CYesY2ANoCnclDlog::IDD, pParent)
{

}

CYesY2ANoCnclDlog::CYesY2ANoCnclDlog(const CString &prompt, CWnd* pParent /*=NULL*/)
	: CDialog(CYesY2ANoCnclDlog::IDD, pParent)
{
	m_csPrompt = prompt;
}

CYesY2ANoCnclDlog::~CYesY2ANoCnclDlog()
{
}

void CYesY2ANoCnclDlog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CYesY2ANoCnclDlog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_YES, &CYesY2ANoCnclDlog::OnBnClickedButtonYes)
	ON_BN_CLICKED(IDC_BUTTON_YES2ALL, &CYesY2ANoCnclDlog::OnBnClickedButtonYes2all)
	ON_BN_CLICKED(IDC_BUTTON_NO, &CYesY2ANoCnclDlog::OnBnClickedButtonNo)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CYesY2ANoCnclDlog::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// CYesY2ANoCnclDlog message handlers

void CYesY2ANoCnclDlog::OnBnClickedButtonYes()
{
	this->EndDialog(IDC_BUTTON_YES);
}

void CYesY2ANoCnclDlog::OnBnClickedButtonYes2all()
{
	this->EndDialog(IDC_BUTTON_YES2ALL);
}

void CYesY2ANoCnclDlog::OnBnClickedButtonNo()
{
	this->EndDialog(IDC_BUTTON_NO);
}

void CYesY2ANoCnclDlog::OnBnClickedButtonCancel()
{
	this->EndDialog(IDC_BUTTON_CANCEL);
}

BOOL CYesY2ANoCnclDlog::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString dum = "Save changes to " + m_csPrompt + "?";

	this->SetDlgItemTextA( IDC_STATIC, dum );

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
