// Datsrc.cpp : implementation file
//
/*   Dialog box for data source

  */



#include "stdafx.h"
#include "DrawProg.h"
#include "Datsrc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Datsrc dialog


Datsrc::Datsrc(CWnd* pParent /*=NULL*/)
	: CDialog(Datsrc::IDD, pParent)
{
	//{{AFX_DATA_INIT(Datsrc)
	m_directory = _T("");
	m_filenaame = _T("");
	m_option1 = _T("");
	m_option2 = _T("");
	//}}AFX_DATA_INIT
}


void Datsrc::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Datsrc)
	DDX_Text(pDX, IDC_DIRECTORY, m_directory);
	DDX_Text(pDX, IDC_FILENAME, m_filenaame);
	DDX_Text(pDX, IDC_MACHINE, m_option1);
	DDX_Text(pDX, IDC_SUBJECT, m_option2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Datsrc, CDialog)
	//{{AFX_MSG_MAP(Datsrc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Datsrc message handlers

BOOL Datsrc::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if (m_directory =="_")m_directory ="";
	if (m_filenaame =="_")m_filenaame ="";
	if (m_option1=="_")m_option1="";
	if (m_option2=="_")m_option2="";

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
