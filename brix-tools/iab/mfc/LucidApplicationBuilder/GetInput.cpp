// GetInput.cpp : implementation file
//

/* 

  General Purpose box for inputting  data string data from a Dialog box

 */

#include "stdafx.h"
#include "DrawProg.h"
#include "GetInput.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GetInput dialog


GetInput::GetInput(CWnd* pParent /*=NULL*/)
	: CDialog(GetInput::IDD, pParent)
{
	//{{AFX_DATA_INIT(GetInput)
	//}}AFX_DATA_INIT
	
}


void GetInput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GetInput)
	DDX_Control(pDX, IDC_EDIT1, m_editbox);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GetInput, CDialog)
	//{{AFX_MSG_MAP(GetInput)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GetInput message handlers

BOOL GetInput::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_editbox.SetWindowText(m_string);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void GetInput::OnOK() 
{
	// TODO: Add extra validation here
	m_editbox.GetWindowText(m_string);
	CDialog::OnOK();
}
