// LucidStateMachineDialog.cpp : implementation file
//

#include "stdafx.h"
#include "DrawProg.h"
#include "LucidStateMachineDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// LucidStateMachineDialog dialog


LucidStateMachineDialog::LucidStateMachineDialog(CWnd* pParent /*=NULL*/)
	: CDialog(LucidStateMachineDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(LucidStateMachineDialog)
	m_csState = _T("");
	m_csTransitionsTo = _T("");
	m_bEntryActionCheckBox = FALSE;
	m_bTransitionActionCheck = FALSE;
	//}}AFX_DATA_INIT
}


void LucidStateMachineDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(LucidStateMachineDialog)
	DDX_Control(pDX, IDC_RADIO1, m_RadioButton);
	DDX_Text(pDX, IDC_EDIT1, m_csState);
	DDX_Text(pDX, IDC_EDIT3, m_csTransitionsTo);
	DDX_Check(pDX, IDC_CHECK1, m_bEntryActionCheckBox);
	DDX_Check(pDX, IDC_CHECK2, m_bTransitionActionCheck);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(LucidStateMachineDialog, CDialog)
	//{{AFX_MSG_MAP(LucidStateMachineDialog)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &LucidStateMachineDialog::OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// LucidStateMachineDialog message handlers

BOOL LucidStateMachineDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
//	MessageBox("LucidStateMachineDialog::OnInitDialog() ");
	m_RadioButton.SetCheck(1);
		

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

int LucidStateMachineDialog::GetRadioCheck()
{
	return m_nRadioValue;

}

void LucidStateMachineDialog::OnOK() 
{

	int r = GetCheckedRadioButton(IDC_RADIO1,IDC_RADIO2);//=0

	if(r == IDC_RADIO1) //=1125
	{	m_nRadioValue = 1;
	}
	else
	{ 
		m_nRadioValue = 0;
	}



	
	CDialog::OnOK();
}

void LucidStateMachineDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}
