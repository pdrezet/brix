// AddPortDialog.cpp : implementation file
//

#include "stdafx.h"
#include "DrawProg.h"
#include "AddPortDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddPortDialog dialog


CAddPortDialog::CAddPortDialog(ConData* _blob, CWnd* pParent /*=NULL*/)
	: CDialog(CAddPortDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddPortDialog)
	m_PortLabel = _T("");
	//}}AFX_DATA_INIT
	blob = _blob;
}


void CAddPortDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddPortDialog)
	DDX_Control(pDX, IDC_DATA_TYPE, m_DataType);
	DDX_Control(pDX, IDC_PORT_TYPE, m_PortType);
	DDX_Text(pDX, IDC_PORT_EDIT, (CString)m_PortLabel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddPortDialog, CDialog)
	//{{AFX_MSG_MAP(CAddPortDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddPortDialog message handlers

BOOL CAddPortDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here	
	// Added InputPort to resource properties to data, but don't know how to remove
	//m_PortType.AddString("InputPort");
	m_PortType.AddString("OutputPort");
	m_PortType.AddString("StartPort");
	m_PortType.AddString("FinishPort");
	m_PortType.SetCurSel(1);

	m_DataType.AddString("Boolean");
	m_DataType.AddString("Integer");
	m_DataType.AddString("Real");
	m_DataType.AddString("String");
	m_DataType.SetCurSel(0);

	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_PORT_EDIT);
	if(pEdit != NULL) {
		pEdit->SetFocus();
		return 0; //since we are explicity setting focus
	}	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAddPortDialog::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	if (m_PortLabel == "") {
		AfxMessageBox("You must enter a port label");
	}
	else if (!IsUnique()) {
		AfxMessageBox("The port label must be unique.");
	}
	else {
		m_PortType.GetWindowText(portType);
		m_DataType.GetWindowText(dataType);

		CDialog::OnOK();
	}
}

// check if port label is unique
bool CAddPortDialog::IsUnique() {
	bool unique = TRUE;

	for (UINT i=0; i<blob->inputport_num; i++) {
		if (blob->inputport[i]->description == m_PortLabel.MakeLower()) {
			unique = FALSE;
		}
	}
	for (UINT i=0; i<blob->startport_num; i++) {
		if (blob->startport[i]->description == m_PortLabel.MakeLower()) {
			unique = FALSE;
		}
	}
	for (UINT i=0; i<blob->outputport_num; i++) {
		if (blob->outputport[i]->description == m_PortLabel.MakeLower()) {
			unique = FALSE;
		}
	}
	for (UINT i=0; i<blob->finishport_num; i++) {
		if (blob->finishport[i]->description == m_PortLabel.MakeLower()) {
			unique = FALSE;
		}
	}

	return unique;
}
