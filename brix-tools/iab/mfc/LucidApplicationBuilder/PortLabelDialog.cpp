// PortLabelDialog.cpp : implementation file
//

#include "stdafx.h"
#include "DrawProg.h"
#include "PortLabelDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPortLabelDialog dialog


CPortLabelDialog::CPortLabelDialog(DEP* _pDEP, CWnd* pParent /*=NULL*/)
	: CDialog(CPortLabelDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPortLabelDialog)
	m_PortLabel = _T("");
	//}}AFX_DATA_INIT
	pDEP = _pDEP;
}


void CPortLabelDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPortLabelDialog)
	DDX_Text(pDX, IDC_PORT_EDIT, m_PortLabel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPortLabelDialog, CDialog)
	//{{AFX_MSG_MAP(CPortLabelDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPortLabelDialog message handlers

BOOL CPortLabelDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_PORT_EDIT);
	if(pEdit != NULL) {
		pEdit->SetFocus();
		return 0; //since we are explicity setting focus
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CPortLabelDialog::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	if (!IsUnique()) {
		AfxMessageBox("The port label is already in use. Choose a different one.");
	}
	else {
		CDialog::OnOK();
	}
}

// returns true if the port label is not used by another xport
bool CPortLabelDialog::IsUnique() {
	ConData* blob;
	INXPOSITION pos;
	bool ret = TRUE;

	pos = pDEP->condata->GetHeadPosition();
	while (pos) {
		blob = (ConData*)pDEP->condata->GetNext(pos);
		if ((blob->m_csIconType == "XSTART" || blob->m_csIconType == "XFINISH" || blob->m_csIconType.Find("XINPUT") != -1 || 
			blob->m_csIconType.Find("XOUTPUT") != -1) && blob->description == m_PortLabel.MakeLower()) {
			ret = FALSE;
		}
	}
	return ret;
}
