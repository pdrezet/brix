// DeleteGUIFileDlog.cpp : implementation file
//

#include "stdafx.h"
#include "DeleteGUIFileDlog.h"


// CDeleteGUIFileDlog dialog

IMPLEMENT_DYNAMIC(CDeleteGUIFileDlog, CDialog)

CDeleteGUIFileDlog::CDeleteGUIFileDlog(const CString &hostFileName,
									   CWnd* pParent /*=NULL*/)
	: CDialog(CDeleteGUIFileDlog::IDD, pParent),
	m_csHostFileName(hostFileName)
{

}

CDeleteGUIFileDlog::~CDeleteGUIFileDlog()
{
}

void CDeleteGUIFileDlog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDCANCEL, m_ctl_ButtonCancel);
	DDX_Control(pDX, IDC_FILENAME_EDIT_RO, m_ctl_EditFileName);
	DDX_Control(pDX, IDOK, m_ctl_ButtonConfirm);
}


BEGIN_MESSAGE_MAP(CDeleteGUIFileDlog, CDialog)
	ON_BN_CLICKED(IDCANCEL, &CDeleteGUIFileDlog::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CDeleteGUIFileDlog::OnBnClickedConfirm)
END_MESSAGE_MAP()


// CDeleteGUIFileDlog message handlers

void CDeleteGUIFileDlog::OnBnClickedFileDeleteButton()
{
	// TODO: Add your control notification handler code here
}

void CDeleteGUIFileDlog::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}

BOOL CDeleteGUIFileDlog::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctl_EditFileName.SetWindowText(m_csHostFileName);

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDeleteGUIFileDlog::OnBnClickedConfirm()
{
	OnOK();
}
