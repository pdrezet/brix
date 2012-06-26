// LibraryDialog.cpp : implementation file
//

#include "stdafx.h"
#include "DrawProg.h"
#include "LibraryDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLibraryDialog dialog


CLibraryDialog::CLibraryDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CLibraryDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLibraryDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CLibraryDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLibraryDialog)
	DDX_Control(pDX, IDC_LIBRARY_COMBO, m_Library);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLibraryDialog, CDialog)
	//{{AFX_MSG_MAP(CLibraryDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLibraryDialog message handlers

BOOL CLibraryDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_Library.SetWindowText("POSIX");
	m_Library.AddString("POSIX");
	m_Library.AddString("microcontroller");
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLibraryDialog::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	m_Library.GetWindowText(library);
	
	if (library != "POSIX" && library != "microcontroller") {
		AfxMessageBox("This is not a valid library.");
	}
	else {
		CDialog::OnOK();
	}
}
