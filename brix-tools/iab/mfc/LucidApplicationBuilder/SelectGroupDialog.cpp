// SelectGroupDialog.cpp : implementation file
//

#include "stdafx.h"
#include "DrawProg.h"
#include "SelectGroupDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectGroupDialog dialog


CSelectGroupDialog::CSelectGroupDialog(Project* _pProject, CWnd* pParent /*=NULL*/)
	: CDialog(CSelectGroupDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelectGroupDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	pProject = _pProject;
}


void CSelectGroupDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectGroupDialog)
	DDX_Control(pDX, IDC_NAME_LIST, m_GroupName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectGroupDialog, CDialog)
	//{{AFX_MSG_MAP(CSelectGroupDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectGroupDialog message handlers

BOOL CSelectGroupDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	vector<Group> vGroups;

	pProject->pProjMData->getGroupVec(vGroups);
	for (UINT i=0; i<vGroups.size(); i++) {
		m_GroupName.AddString(vGroups.at(i).Name);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSelectGroupDialog::OnOK() 
{
	// TODO: Add extra validation here
	int index = m_GroupName.GetCurSel();
	if (index == LB_ERR) {
		AfxMessageBox("You must select a group.");
	}
	else {
		m_GroupName.GetText(index, (CString)selectedGroup);
		CDialog::OnOK();
	}
}
