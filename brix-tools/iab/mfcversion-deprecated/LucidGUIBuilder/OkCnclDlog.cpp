// OkCnclDlog.cpp : implementation file
//

#include "stdafx.h"
#include "OkCnclDlog.h"


// COkCnclDlog dialog

IMPLEMENT_DYNAMIC(COkCnclDlog, CDialog)

COkCnclDlog::COkCnclDlog(const CString &prompt, CWnd* pParent /*=NULL*/)
	: CDialog(COkCnclDlog::IDD, pParent)
{
	m_csPrompt = prompt;
}

COkCnclDlog::COkCnclDlog(CWnd* pParent /*=NULL*/)
	: CDialog(COkCnclDlog::IDD, pParent)
	, m_csPrompt(_T(""))
{

}

COkCnclDlog::~COkCnclDlog()
{
}

void COkCnclDlog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(COkCnclDlog, CDialog)
END_MESSAGE_MAP()


// COkCnclDlog message handlers

BOOL COkCnclDlog::OnInitDialog()
{
	CDialog::OnInitDialog();
	this->SetDlgItemTextA( IDC_STATIC, m_csPrompt );

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
