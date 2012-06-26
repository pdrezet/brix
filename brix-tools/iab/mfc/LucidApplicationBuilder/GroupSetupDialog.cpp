// GroupSetupDialog.cpp : implementation file
//

#include "stdafx.h"
#include "DrawProg.h"
#include "GroupSetupDialog.h"
#include "EditGroupDialog.h"
#include "BlockOperations.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGroupSetupDialog dialog


CGroupSetupDialog::CGroupSetupDialog(Project* _pProject, CWnd* pParent /*=NULL*/)
	: CDialog(CGroupSetupDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGroupSetupDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	pProject = _pProject;
}


void CGroupSetupDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGroupSetupDialog)
	DDX_Control(pDX, IDC_GROUP_LIST, m_Group);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGroupSetupDialog, CDialog)
	//{{AFX_MSG_MAP(CGroupSetupDialog)
	ON_BN_CLICKED(IDC_ADD_GROUP, OnAddGroup)
	ON_BN_CLICKED(IDC_EDIT_GROUP, OnEditGroup)
	ON_BN_CLICKED(IDC_DELETE_GROUP, OnDeleteGroup)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGroupSetupDialog message handlers

BOOL CGroupSetupDialog::OnInitDialog() 
{
	char szGroupID[4];
	char szGroupPeriod[32];
	char szGroupAlloc[32];
	vector<Group> vGroups;

	CDialog::OnInitDialog();
	
	m_Group.SetColumnWidth(100);
	// Initialise the list box with the current groups
	pProject->pProjMData->getGroupVec(vGroups);
	for (UINT i=0; i<vGroups.size(); i++) {
		_itoa_s(vGroups.at(i).ID, szGroupID, 10);
		_itoa_s(vGroups.at(i).Period, szGroupPeriod, 10);
		_itoa_s(vGroups.at(i).Alloc, szGroupAlloc, 10);
		group =  (CString)szGroupID + "\t" + vGroups.at(i).Name + "\t\t" + (CString)szGroupPeriod + 
			"\t\t" + (CString)szGroupAlloc;
		m_Group.AddString(group);
		groupID = vGroups.at(i).ID;
	}
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGroupSetupDialog::OnAddGroup() 
{
	CEditGroupDialog dialog(pProject, TRUE);
	char szGroupID[4];
	char szGroupPeriod[32];
	char szGroupAlloc[32];
	
	if (dialog.DoModal()==IDOK) {
		groupID++;
		_itoa_s(groupID, szGroupID, 10);
		_itoa_s(dialog.m_Period, szGroupPeriod, 10);
		_itoa_s(dialog.m_Alloc, szGroupAlloc, 10);
		group = (CString)szGroupID + "\t" + dialog.m_Name + "\t\t" + (CString)szGroupPeriod + "\t\t" + 
			(CString)szGroupAlloc;
		m_Group.AddString(group);
	}
}

void CGroupSetupDialog::OnEditGroup() 
{
	CEditGroupDialog dialog(pProject, FALSE);
	CString szGroupID, szGroupName;
	char szGroupPeriod[32];
	char szGroupAlloc[32];
	
	// get selected group
	int index = m_Group.GetCurSel();
	if (index == LB_ERR) {
		AfxMessageBox("Select a group to edit.");
		return;
	}
	m_Group.GetText(index, group);
	// Initialise the edit group dialog box with the parameters to edit
	szGroupID = ExtractParam();
	dialog.m_Name = ExtractParam();
	// delete 2nd tab
	group.Delete(0,1);
	dialog.m_Period = atoi(ExtractParam());
	// delete 2nd tab
	group.Delete(0,1);
	dialog.m_Alloc = atoi(group);
	if (dialog.DoModal()==IDOK) {
		_itoa_s(dialog.m_Period, szGroupPeriod, 10);
		_itoa_s(dialog.m_Alloc, szGroupAlloc, 10);
		group = szGroupID + "\t" + dialog.m_Name + "\t\t" + (CString)szGroupPeriod + "\t\t" + (CString)szGroupAlloc;
		// delete the old group and add the modified group
		m_Group.DeleteString(index);
		m_Group.InsertString(index, group);
	}
}

void CGroupSetupDialog::OnDeleteGroup() 
{
	CString szGroupID;
	UINT selectedID;

	// get selected group
	int index = m_Group.GetCurSel();
	m_Group.GetText(index, group);
	szGroupID = ExtractParam();
	selectedID = atoi(szGroupID);
	if (index == LB_ERR) {
		AfxMessageBox("Select a group to delete.");
	}
	// Save all DEP files, because have to check the saved copies to find out if the group is being used.
	// However, prompt user first
	else if (AfxMessageBox("Deleting a group will save all the DEP files in the project.\nDo you want to proceed?",MB_YESNO)==IDYES) {
		pProject->SaveProject();
		// if the group is set in a start port don't delete it
		if (GroupInUse(selectedID, pProject->pDEP[0]->depFilename)) {
			AfxMessageBox("The group is in use. Cannot delete.");
		}
		// delete the group
		else {
			m_Group.DeleteString(index);
			groupID--;
		}
	}
}

CString CGroupSetupDialog::ExtractParam() {
	int tabPos = group.Find("\t");
	CString param = group.Left(tabPos);
	group.Delete(0,tabPos+1);

	return param;
}

void CGroupSetupDialog::OnOK() 
{
	Group groupObj;
	vector<Group> vGroups;

	// Update Project with group changes. This is done by deleting all the old groups, and
	// then adding the groups in the dialog box.
	pProject->pProjMData->removeAllGroups();

	for (int i=0; i<m_Group.GetCount(); i++) {
		m_Group.GetText(i, group);
		// Add the parameters from each group to the project
		groupObj.ID = atoi(ExtractParam());		
		groupObj.Name = ExtractParam();
		// delete 2nd tab
		group.Delete(0,1);
		groupObj.Period = atoi(ExtractParam());
		// delete 2nd tab
		group.Delete(0,1);
		groupObj.Alloc = atoi(group);
		pProject->pProjMData->addGroup(groupObj);
	}
		
	CDialog::OnOK();
}

// Returns true if a start or internal port has its groupID set to the same ID
bool CGroupSetupDialog::GroupInUse(UINT selectedID, CString blockName) {
	INXObjList* condata;
	INXPOSITION pos;
	ConData* blob;
	BlockOperations bo;
	CString subBlockName, csProjectDir;
	UINT i;
	
	pProject->pProjMData->getProjectDir(csProjectDir);
	condata = bo.LoadBlock(csProjectDir + DEPDIR + blockName + ".prg");
	pos = condata->GetHeadPosition();
	while (pos) {
		blob = (ConData*) condata->GetNext(pos);
		if (blob->m_iUserDefined) {
			subBlockName = blockName + "\\" + blob->description;
			if (GroupInUse(selectedID, subBlockName)) {
				delete condata;
				return TRUE;
			}
		}
		else {
			for (i=0; i<blob->startport_num; i++) {
				if (blob->startport[i]->groupID == selectedID) {
					delete condata;
					return TRUE;
				}
			}
			for (i=0; i<blob->internalport_num; i++) {
				if (blob->internalport[i]->groupID == selectedID) {
					delete condata;
					return TRUE;
				}
			}
		}
	}
	delete condata;
	return FALSE;
}
