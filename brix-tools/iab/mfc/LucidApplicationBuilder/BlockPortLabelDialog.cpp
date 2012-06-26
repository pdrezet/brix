// BlockPortLabelDialog.cpp : implementation file
//

#include "stdafx.h"
#include "BlockPortLabelDialog.h"


// CBlockPortLabelDialog dialog

IMPLEMENT_DYNAMIC(CBlockPortLabelDialog, CDialog)

CBlockPortLabelDialog::CBlockPortLabelDialog(CString csOldLabel, ConData* pBlock, DEP* pDEP, CWnd* pParent /*=NULL*/)
	: CDialog(CBlockPortLabelDialog::IDD, pParent)
{
	m_csPortLabel = csOldLabel;
	m_csOldPortLabel = csOldLabel;
	m_pBlock = pBlock;
	m_pDEP = pDEP;
}

CBlockPortLabelDialog::~CBlockPortLabelDialog()
{
}

void CBlockPortLabelDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBlockPortLabelDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CBlockPortLabelDialog::OnOk)
END_MESSAGE_MAP()


// CBlockPortLabelDialog message handlers

BOOL CBlockPortLabelDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	SetDlgItemTextA(IDC_BLOCK_PORT_EDIT,m_csPortLabel);

	UpdateData(FALSE);

	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_BLOCK_PORT_EDIT);
	if(pEdit != NULL) {
		pEdit->SetFocus();
		return 0; //since we are explicity setting focus
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CBlockPortLabelDialog::OnOk()
{
	UpdateData(TRUE);

	GetDlgItemTextA(IDC_BLOCK_PORT_EDIT, m_csPortLabel);

	if (m_csPortLabel == "") {
		AfxMessageBox("The port label must contain at least one character.");
	}
	else if (m_csPortLabel != m_csOldPortLabel) {
		if (!IsUnique()) {
			AfxMessageBox("The port label is already in use. Choose a different one.");
		}
		else {
			OnOK();
		}
	}
	else {
		OnOK();
	}
}

CString CBlockPortLabelDialog::GetPortLabel()
{
	return m_csPortLabel;
}

// returns true if the port label is unique
bool CBlockPortLabelDialog::IsUnique() 
{
	INXPOSITION pos;
	ConData* blob;
	bool ret = TRUE;

	if (m_pBlock->m_iUserDefined) {
		for (UINT i=0; i<m_pBlock->inputport_num; i++) {
			if (m_pBlock->inputport[i]->description == m_csPortLabel.MakeLower()) {
				ret = FALSE;
			}
		}

		for (UINT i=0; i<m_pBlock->outputport_num; i++) {
			if (m_pBlock->outputport[i]->description == m_csPortLabel.MakeLower()) {
				ret = FALSE;
			}
		}

		for (UINT i=0; i<m_pBlock->startport_num; i++) {
			if (m_pBlock->startport[i]->description == m_csPortLabel.MakeLower()) {
				ret = FALSE;
			}
		}

		for (UINT i=0; i<m_pBlock->finishport_num; i++) {
			if (m_pBlock->finishport[i]->description == m_csPortLabel.MakeLower()) {
				ret = FALSE;
			}
		}
	}
	else if (m_pBlock->m_csIconType.Find("XINPUT") != -1 || m_pBlock->m_csIconType.Find("XOUTPUT") != -1 || 
		m_pBlock->m_csIconType == "XSTART" || m_pBlock->m_csIconType == "XFINISH") {
		pos = m_pDEP->condata->GetHeadPosition();
		while (pos) {
			blob = (ConData*)m_pDEP->condata->GetNext(pos);
			if (blob != m_pBlock && blob->description == m_csPortLabel.MakeLower()) {
				ret = FALSE;
			}
		}
	}

	return ret;
}
