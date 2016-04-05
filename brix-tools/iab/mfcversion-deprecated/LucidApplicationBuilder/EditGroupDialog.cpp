// EditGroupDialog.cpp : implementation file
//

#include "stdafx.h"
#include "DrawProg.h"
#include "EditGroupDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditGroupDialog dialog


CEditGroupDialog::CEditGroupDialog(Project* _pProject, bool _addGroup, CWnd* pParent /*=NULL*/)
	: CDialog(CEditGroupDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditGroupDialog)
	m_Alloc = 0;
	m_Period = 0;
	m_Name = _T("");
	//}}AFX_DATA_INIT
	pProject = _pProject;
	addGroup = _addGroup;
}


void CEditGroupDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditGroupDialog)
	DDX_Text(pDX, IDC_ALLOC_EDIT, m_Alloc);
	DDV_MinMaxInt(pDX, m_Alloc, 0, 2147483647);
	DDX_Text(pDX, IDC_PERIOD_EDIT, m_Period);
	DDV_MinMaxInt(pDX, m_Period, 0, 2147483647);
	DDX_Text(pDX, IDC_NAME_EDIT, (CString)m_Name);
	DDV_MaxChars(pDX, (CString&)m_Name, 20);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditGroupDialog, CDialog)
	//{{AFX_MSG_MAP(CEditGroupDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditGroupDialog message handlers

void CEditGroupDialog::OnOK() 
{	
	UpdateData(TRUE);
	if (m_Name == "") {
		AfxMessageBox("Enter a group name.");
	}
	else if (addGroup && NameExists()) {
		AfxMessageBox("The group name is already in use.");
	}
	else if (m_Name.Find(" ")>-1) {
		AfxMessageBox("Spaces are not allowed in the group name.");
	}
	else {
		CDialog::OnOK();
	}
}

bool CEditGroupDialog::NameExists() {
	vector<Group> vGroups;

	pProject->pProjMData->getGroupVec(vGroups);
	for (UINT i=0; i<vGroups.size(); i++) {
		if (m_Name == vGroups.at(i).Name) {
			return TRUE;
		}
	}
	return FALSE;
}
