// delims.cpp : implementation file
//
/* Serial data port setup

  */

#include "stdafx.h"
#include "DrawProg.h"
#include "delims.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// delims dialog


delims::delims(CWnd* pParent /*=NULL*/)
	: CDialog(delims::IDD, pParent)
{
	//{{AFX_DATA_INIT(delims)
	//}}AFX_DATA_INIT
	field=",";
	record="\n";
	baud="19200";
	bits="8";
	parity="NONE";
	stopbits="1";


}


void delims::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(delims)
	DDX_Control(pDX, IDC_SOFTWARE, m_software);
	DDX_Control(pDX, IDC_STOPBITS, m_stopbits);
	DDX_Control(pDX, IDC_PARITY, m_parity);
	DDX_Control(pDX, IDC_BITS, m_bits);
	DDX_Control(pDX, IDC_BAUD, m_baud);
	DDX_Control(pDX, IDC_RECORD, m_record);
	DDX_Control(pDX, IDC_FIELD, m_field);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(delims, CDialog)
	//{{AFX_MSG_MAP(delims)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// delims message handlers

BOOL delims::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if (field=="_") field=",";
	if (record=="_") record="\\n";
	if (baud=="_") baud="19200";
	if (bits=="_") bits ="8";
	if (parity=="_") parity="NONE";
	if (stopbits=="_") stopbits="1";
	if (software=="_") software="0";

	m_field.SetWindowText(field);
	m_record.SetWindowText(record);
	m_stopbits.SetWindowText(stopbits);
	m_bits.SetWindowText(bits);
	m_baud.SetWindowText(baud);
	m_parity.AddString("ODD");
	m_parity.AddString("EVEN");
	m_parity.AddString("NONE");
	if (parity=="ODD") m_parity.SetCurSel(0);
	if (parity=="EVEN")m_parity.SetCurSel(1);
	if (parity=="NONE")m_parity.SetCurSel(2);
	m_parity.SetWindowText(parity);
	if (software=="1") m_software.SetCheck(1);
	else m_software.SetCheck(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void delims::OnOK() 
{
	// TODO: Add extra validation here
	m_field.GetWindowText(field);
	m_record.GetWindowText(record);
	m_stopbits.GetWindowText(stopbits);
	m_bits.GetWindowText(bits);
	m_baud.GetWindowText(baud);
	m_parity.GetWindowText(parity);
	if (m_software.GetCheck()==1) software="1";
	else software="0";
	CDialog::OnOK();
}
