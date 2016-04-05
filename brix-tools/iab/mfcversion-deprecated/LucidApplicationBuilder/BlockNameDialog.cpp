// BlockNameDialog.cpp : implementation file
//

#include "stdafx.h"
#include "DrawProg.h"
#include "BlockNameDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBlockNameDialog dialog


CBlockNameDialog::CBlockNameDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CBlockNameDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBlockNameDialog)
	m_BlockName = _T("");
	//}}AFX_DATA_INIT
}


void CBlockNameDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBlockNameDialog)
	DDX_Text(pDX, IDC_BLOCK_EDIT, (CString)m_BlockName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBlockNameDialog, CDialog)
	//{{AFX_MSG_MAP(CBlockNameDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBlockNameDialog message handlers

void CBlockNameDialog::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	if (m_BlockName == "") {
		AfxMessageBox("You must enter a block name.");
	}
	else if (m_BlockName.Find(" ")>-1) {
		AfxMessageBox("Spaces are not allowed in the block name.");
	}
	else {
		CDialog::OnOK();
	}
}

BOOL CBlockNameDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_BLOCK_EDIT);
	if(pEdit != NULL) {
		pEdit->SetFocus();
		return 0; //since we are explicity setting focus
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
