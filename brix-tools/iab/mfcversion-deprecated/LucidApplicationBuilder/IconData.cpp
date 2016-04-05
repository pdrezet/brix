// IconData.cpp : implementation file
//

/* 

  updates icon data

*/


#include "stdafx.h"
#include "DrawProg.h"
#include "IconData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// IconData dialog

//IconData(Tags::IDD, pParent) {
//	CDialog::CDialog(Tags::IDD, pParent
//}

IconData::IconData(CWnd* pParent /*=NULL*/)
	: CDialog(IconData::IDD, pParent)
{
	//{{AFX_DATA_INIT(IconData)
	//}}AFX_DATA_INIT
	//CDialog::CDialog(IconData::IDD, pParent);
	deleteme=0;
	momentary=1;
	constant=0;
	negedge=0;
	plusedge=1;
	recorddelim="\\n";
	fielddelim=',';
	option2="";
	option1="";
	description="";
	fixedinfo="";
}


void IconData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(IconData)
	DDX_Control(pDX, IDC_FIXED, m_fixedinfo);
	DDX_Control(pDX, IDC_DESCRIPTION, m_description);
	DDX_Control(pDX, IDC_CHECK4, m_momentary);
	DDX_Control(pDX, IDC_CHECK3, m_constant);
	DDX_Control(pDX, IDC_CHECK2, m_negedge);
	DDX_Control(pDX, IDC_CHECK1, m_plusedge);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(IconData, CDialog)
	//{{AFX_MSG_MAP(IconData)
	ON_BN_CLICKED(ID_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_CHECK1, OnPlus)
	ON_BN_CLICKED(IDC_CHECK2, OnNeg)
	ON_BN_CLICKED(IDC_CHECK3, OnConst)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// IconData message handlers

void IconData::OnDelete() 
{
	// TODO: Add your control notification handler code here
	if (AfxMessageBox("Are you sure you want to delete this block?",MB_YESNO)==IDYES) {
		deleteme=1;
		CDialog::OnOK();
	}
}


void IconData::OnOK() 
{
	// TODO: Add extra validation here
	 	momentary=m_momentary.GetCheck();
	 	constant=m_constant.GetCheck();
		negedge=m_negedge.GetCheck();
		plusedge=m_plusedge.GetCheck();
		//m_recorddelim.GetWindowText(recorddelim);
		//m_fielddelim.GetWindowText(fielddelim);
		//m_option2.GetWindowText(option2);
		//m_option1.GetWindowText( option1);
		m_description.GetWindowText(description);
		m_fixedinfo.GetWindowText(fixedinfo);
		if (wantoption&&((option1.IsEmpty())||(option1=="_"))) {
		AfxMessageBox("Must specify a fixed location");
		return;
	}
		CDialog::OnOK();
}

BOOL IconData::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if (momentary)m_momentary.SetCheck(1);
	if (plusedge)m_plusedge.SetCheck(1);
	else if (negedge)m_negedge.SetCheck(1);
	else if (constant)m_constant.SetCheck(1);
	//m_recorddelim.SetWindowText(recorddelim);
	//m_fielddelim.SetWindowText(fielddelim);
	//m_option2.SetWindowText(option2);;
	//m_option1.SetWindowText(option1);;
	m_description.SetWindowText(description);;
	m_fixedinfo.SetWindowText(fixedinfo);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
	

void IconData::OnPlus() 
{
	// TODO: Add your control notification handler code here
	m_negedge.SetCheck(0);
	m_constant.SetCheck(0);
}

void IconData::OnNeg() 
{
	// TODO: Add your control notification handler code here
	m_plusedge.SetCheck(0);
	m_constant.SetCheck(0);
}

void IconData::OnConst() 
{
	// TODO: Add your control notification handler code here
	m_negedge.SetCheck(0);
	m_plusedge.SetCheck(0);
}
