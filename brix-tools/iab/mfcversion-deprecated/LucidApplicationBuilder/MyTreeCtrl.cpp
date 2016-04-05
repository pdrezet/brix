// MyTreeCtrl.cpp : implementation file
//
#include "stdafx.h"

#include "stdafx.h"
#include "DrawProg.h"
#include "MyTreeCtrl.h"
#include "MainFrm.h"
#include "LucidConstants.h"
#include "DrawProgView.h"
#include "BlockOperations.h"
#include "GlobalFuncs_2.h"
#include "../common/General_Utilities/GlobalFuncs_3.h"
#include "userDefinedMessages.h"
#include "FileOperations.h"
#include <shlwapi.h>
#include <shellapi.h>
#include <cassert>
#include "ProjectDescriptionDialog.h"

#include "Markup.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TREE_INDEX_APP 1
#define TREE_INDEX_GUI 2
#define TREE_INDEX_PNG 3
#define TREE_INDEX_NLS 4
#define TREE_INDEX_RESOURCE 5
#define TREE_INDEX_INFO 6

// global variable declared in CDrawProgApp
extern char workDir[WORK_DIR_SIZE];

/////////////////////////////////////////////////////////////////////////////
// CMyTreeCtrl

/* This is the tree view for the projects */

CMyTreeCtrl::CMyTreeCtrl()
{
	openProject = TRUE;
	for (int i=0; i<MAX_PROJECTS; i++) {
		pProject[i] = NULL;
	}
	hSelItem = NULL;
}

CMyTreeCtrl::~CMyTreeCtrl()
{
	for (int i=0; i<MAX_PROJECTS; i++) {
		DeleteProject(i);
	}
}

void CMyTreeCtrl::Init() {
	imageList.Create (IDB_BITMAP2, 16, 1, RGB (0, 255, 0));
	SetImageList(&imageList,TVSIL_NORMAL);
	SetBkColor(RGB(235,250,245));
	SetTextColor(RGB(30,20,0));
	SetLineColor(RGB(30,200,30)); 
}

IMPLEMENT_DYNCREATE(CMyTreeCtrl, CTreeCtrl)

BEGIN_MESSAGE_MAP(CMyTreeCtrl, CTreeCtrl)
	//{{AFX_MSG_MAP(CMyTreeCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_DELETE_RESOURCE, OnResourceDelete)
	//}}AFX_MSG_MAP
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CMyTreeCtrl::OnNMDblclk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyTreeCtrl message handlers

void CMyTreeCtrl::OnLButtonDown(UINT nFlags, CPoint _point) 
{
	INXPoint point(_point.x, _point.x);
	// TODO: Add your message handler code here and/or call default
	UINT uFlags;
	INXString filename, drawGui, depPath, csProjectDir;
	Project* thisProject;
	INXString type = "";
	HTREEITEM hParent;

	hSelItem = HitTest( point, &uFlags );
	if(hSelItem && (uFlags & TVHT_ONITEM))
	{
		// Get the type of the selected item. It could be simplified by inheriting HTREEITEM and
		// having a type attribute
		thisProject = GetProjectPtr(hSelItem);
		thisProject->pProjMData->getProjectDir(csProjectDir);
		hParent = GetParentItem(hSelItem);
		// make sure project is not selected
		if (hParent) {
			type = GetItemText(hSelItem);
			// make sure DEP, GUI, BMP or TXT is not selected
			if (type != APP && type != "GUI" && type != "PNG" && type != "TXT" && type != "NLS" && type != "RESOURCE" && type != "INFO") {
				while (hParent && type != APP && type != "GUI" && type != "PNG" && type != "TXT" && type != "NLS" && type != "RESOURCE" && type != "INFO") {
					type = GetItemText(hParent);
					hParent = GetParentItem(hParent);
				}
			}
			else {
				type = "";
			}
		}

	}
	/*
	if (type == APP)  {
		// open document and view
		openProject = FALSE;
		CDocument* Subsystem = AfxGetApp( )->OpenDocumentFile(csProjectDir + DEPDIR +
			GetDEPPath(hSelItem) + GetItemText(hSelItem) + ".prg");
		openProject = TRUE;
		// if in debug mode set the DEP in the debugger
		if (thisProject->debug.debugMode != DBGSTOP) {
			POSITION pos = Subsystem->GetFirstViewPosition();
			CDrawProgView* pView = (CDrawProgView*) Subsystem->GetNextView(pos);
			OpenDebugDEP(pView);
		}
	}
	// open gui file in gui builder
	else if (type == "GUI") {
		//kwhite - designed for installed application.
		//kwhite - we need to remove LucidApplicationBuilder from end of path
		filename = "\"";
		filename += csProjectDir + GUIDIR + GetItemText(hSelItem);
		filename += "\"";
		
		
		/* For debugging 
		INXString tmp;
		int remove = strlen( (LPCSTR) AfxGetAppName() ); + 1;
		int workdir_size = strlen( workDir );
		tmp = (INXString)workDir;
		drawGui = tmp.GetBufferSetLength(workdir_size - remove);
		drawGui += "LucidGUIBuilder\\LucidGUIBuilder.exe"; 
		//drawGui += "Debug\\LucidGUIBuilder\\LucidGUIBuilder.exe"; 
		*/
		/*
		// For installation
		drawGui = (INXString)workDir;
		drawGui += "\\bin\\LucidGUIBuilder.exe"; 
		ShellExecute(NULL, "open", drawGui, filename, NULL, SW_SHOWNORMAL);
	}
	// open bmp file in paint
	else if (type == "PNG") {
		filename = csProjectDir + GUIDIR + GetItemText(hSelItem);
		ShellExecute(NULL, "open", "gimp-2.2.exe", filename, NULL, SW_SHOW);
	}
	// open textfile in notepad
	else if (type == "TXT") {
		filename = csProjectDir + DDATADIR + GetItemText(hSelItem);
		ShellExecute(NULL, "open", "notepad.exe", filename, NULL, SW_SHOW);
	}
	*/
	//ShellExecute(NULL, "open", "notepad.exe", "C:\\Documents and Settings\\Kwhite\\My Documents\\test.txt", NULL, SW_SHOWNORMAL);

	CTreeCtrl::OnLButtonDown(nFlags, point);
}

void CMyTreeCtrl::OnRButtonDown(UINT nFlags, CPoint _point) 
{
	INXPoint point(_point.x, _point.y);
	UINT uFlags;
	INXString filename, drawGui, depPath, csProjectDir;
	Project* thisProject;
	INXString type = "";
	HTREEITEM hParent;

	hSelItem = HitTest( point, &uFlags );
	if(hSelItem && (uFlags & TVHT_ONITEM))
	{
		// Get the type of the selected item. It could be simplified by inheriting HTREEITEM and
		// having a type attribute
		thisProject = GetProjectPtr(hSelItem);
		thisProject->pProjMData->getProjectDir(csProjectDir);
		hParent = GetParentItem(hSelItem);
		// make sure project is not selected
		if (hParent) {
			type = GetItemText(hSelItem);
			// make sure DEP, GUI, BMP or TXT is not selected
			if (type != APP && type != "GUI" && type != "PNG" && type != "TXT" && type != "NLS" && type != "RESOURCE" && type != "INFO") {
				while (hParent && type != APP && type != "GUI" && type != "PNG" && type != "TXT" && type != "NLS" && type != "RESOURCE" && type != "INFO") {
					type = GetItemText(hParent);
					hParent = GetParentItem(hParent);
				}
			}
			else {
				type = "";
			}
		}

	}

	// if it is a resource item, show the right click context menu
	if (type == "RESOURCE")  {
		CMenu iconMenu;
		INXPoint menuPoint = point;
		ClientToScreen((LPPOINT)menuPoint);	// Convert to screen coordinates
	/*@todo MIGRATION_ISSUES iconMenu.LoadMenu
		iconMenu.LoadMenu(IDR_ICON_MENU); // Load the icon menu
		*/
		iconMenu.GetSubMenu(9)->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, menuPoint.x, menuPoint.y, this);
		CTreeCtrl::OnRButtonDown(nFlags, point);
	}
}


void CMyTreeCtrl::OnResourceDelete()
{
	Project* thisProject;
	thisProject = GetProjectPtr(hSelItem);

	ExtResourceFile eF;
	LucidErrEnum err = thisProject->pProjMData->getResourceFileByName( GetItemText(hSelItem), eF );

	if(err == kErr_NoErr){
		if(!thisProject->pProjMData->getLock()){
			AfxMessageBox(PMD_LOCK_FAILURE_MESSAGE);
		} else {
			// refresh project data before remove resource and write project file
			thisProject->pProjMData->readProjectFile();
			thisProject->pProjMData->removeResourceFile(eF);
			thisProject->pProjMData->writeProjectFile();
			thisProject->pProjMData->releaseLock();

			//update the tree
			DeleteItem(hSelItem);
		}
	}
}


// sets view and dep in debugger when new dep is opened
void CMyTreeCtrl::OpenDebugDEP(CDrawProgView* pView) {
	pView->pDEP->MapLineID(pView->pProject->flattened);
	pView->pProject->debug.setView(pView);
	//pView->pDEP->PropagateDebugData();
}

// Add a new project
Project* CMyTreeCtrl::AddProject(int projectNum, ProjectMetaData* pProjMData) {
	return pProject[projectNum] = new Project(pProjMData, projectNum);
}

// Delete a project
void CMyTreeCtrl::DeleteProject(int projectNum) {
	// When close project this function gets called twice
	// so make sure project exists before deleting
	if (projectNum >= 0 && projectNum < MAX_PROJECTS) {
		if (pProject[projectNum]) {
			delete pProject[projectNum];
			pProject[projectNum] = NULL;
		}
	}
}

// Return the project pointer
Project* CMyTreeCtrl::GetProjectPtr(int projectNum) {
	return pProject[projectNum];
}

Project* CMyTreeCtrl::GetProjectPtr(HTREEITEM hItem) {
	HTREEITEM hParent, hTmpItem;
	Project* itemProject;
	INXString csProjectName, hItemName;

	// get project name
	hParent = GetParentItem(hItem);
	if (!hParent) {
		hItemName = GetItemText(hItem);
	}
	else {
		while (hParent) {
			hTmpItem = hParent;
			hParent = GetParentItem(hTmpItem);
			if (!hParent) {
				hItemName = GetItemText(hTmpItem);
			}
		}
	}

	// get project 
	for (int i=0; i<MAX_PROJECTS; i++) {
		Project* tmpProject = GetProjectPtr(i);
		if (tmpProject) {
			tmpProject->pProjMData->getProjectName(csProjectName);
			if (csProjectName == hItemName) {
				itemProject = tmpProject;
			}
		}
	}
	return itemProject;
}

void CMyTreeCtrl::PopulateProjectTree(INXObjList* iconList, Project* pProject) {
	HTREEITEM projItem, childItem, depItem, guiItem, pngItem, hNlsItem, topDEP, hRscItem, descItem;
	INXPOSITION iconPos;
	ConData* blob;
	INXString fileName, csProjectName, csProjectDir;
	vector<ExtGuiFile> guiFileVec;
	vector<ExtPngFile> pngFileVec;
	vector<ExtDataFile> dataFileVec;
	vector<ExtNlsFile> vNlsFileVec;
	vector<ExtResourceFile> xResourceFileVec;

	// create project item
	pProject->pProjMData->getProjectName(csProjectName);
	pProject->pProjMData->getProjectDir(csProjectDir);
	projItem = InsertItem(_T(csProjectName));
	depItem = InsertItem(_T(APP), TREE_INDEX_APP, TREE_INDEX_APP, projItem);
	guiItem = InsertItem(_T("GUI"), TREE_INDEX_GUI, TREE_INDEX_GUI, projItem);
	pngItem = InsertItem(_T("PNG"), TREE_INDEX_PNG, TREE_INDEX_PNG, projItem);
//	txtItem = InsertItem(_T("TXT"), 3, 3, projItem); //dk - Data Items removed from IAB
	hNlsItem = InsertItem(_T("NLS"), TREE_INDEX_NLS, TREE_INDEX_NLS, projItem);
	hRscItem = InsertItem(_T("RESOURCE"), TREE_INDEX_RESOURCE, TREE_INDEX_RESOURCE, projItem);
	descItem = InsertItem(_T("INFO"), TREE_INDEX_INFO, TREE_INDEX_INFO, projItem);
	
	// Populate DEP items
	topDEP = InsertItem(_T(csProjectName), TREE_INDEX_APP, TREE_INDEX_APP, depItem);
	hSelItem = topDEP;
	iconPos = iconList->GetHeadPosition();
	while(iconPos) {
		blob = (ConData *) (iconList->GetNext(iconPos));
		if (blob->m_iUserDefined == 1) {
			childItem = InsertItem(_T(blob->description), TREE_INDEX_APP, TREE_INDEX_APP, topDEP);
			PopulateNextLevel(childItem, csProjectDir);
		}
	}

	// Populate gui items
	pProject->pProjMData->getGuiFiles(guiFileVec);
	for (UINT i=0; i<guiFileVec.size(); i++) {
		guiFileVec.at(i).getHostFileName(fileName);
		InsertItem(_T(fileName), TREE_INDEX_GUI, TREE_INDEX_GUI, guiItem);
	}
	// Populate png items
	pProject->pProjMData->getPngFiles(pngFileVec);
	for (UINT i=0; i<pngFileVec.size(); i++) {
		pngFileVec.at(i).getHostFileName(fileName);
		InsertItem(_T(fileName), TREE_INDEX_PNG, TREE_INDEX_PNG, pngItem);
	}	
	// Populate data items
/* dk - Data Items removed from IAB
	pProject->pProjMData->getDataFiles(dataFileVec);
	for (UINT i=0; i<dataFileVec.size(); i++) {
		dataFileVec.at(i).getHostFileName(fileName);
		InsertItem(_T(fileName), 3, 3, txtItem);
	}	
*/
	// Populate nls items
	pProject->pProjMData->getNlsFiles(vNlsFileVec);
	for (UINT i=0; i<vNlsFileVec.size(); i++) {
		vNlsFileVec.at(i).getHostFileName(fileName);
		InsertItem(_T(fileName), TREE_INDEX_NLS, TREE_INDEX_NLS, hNlsItem);
	}
	// Populate resource items
	pProject->pProjMData->getResourceFiles(xResourceFileVec);
	for (UINT i=0; i<xResourceFileVec.size(); i++) {
		xResourceFileVec.at(i).getHostFileName(fileName);
		InsertItem(_T(fileName), TREE_INDEX_RESOURCE, TREE_INDEX_RESOURCE, hRscItem);
	}	
	// Populate project description
	InsertItem(_T("Project Name: " + pProject->pProjMData->m_csProjectAppCanonicalName), TREE_INDEX_INFO, TREE_INDEX_INFO, descItem);
	InsertItem(_T("Commercial Name: " + pProject->pProjMData->m_csProjectAppCommercialName), TREE_INDEX_INFO, TREE_INDEX_INFO, descItem);
	InsertItem(_T("Version: " + pProject->pProjMData->m_csProjectAppVersion), TREE_INDEX_INFO, TREE_INDEX_INFO, descItem);
	InsertItem(_T("Description: " + pProject->pProjMData->m_csProjectAppDescription), TREE_INDEX_INFO, TREE_INDEX_INFO, descItem);
}

void CMyTreeCtrl::PopulateNextLevel(HTREEITEM hItem, INXString projectDir)
{
	INXObjList* encapsulated;
	INXPOSITION iconPos;
	ConData* blob;
	INXString blockFile, newInstName, depPath;
	HTREEITEM childItem;
	BlockOperations bo;

	// Load the encapsulated block into a temporary list and check for any sub-blocks
	blockFile = projectDir + DEPDIR + GetDEPPath(hItem) + (INXString)GetItemText(hItem) + ".prg";
	encapsulated = bo.LoadBlock(blockFile);
	iconPos = encapsulated->GetHeadPosition();
	while(iconPos) {
		blob = (ConData *) (encapsulated->GetNext(iconPos));
		if (blob->m_iUserDefined) {
			//childItem = new HTREEITEM;
			childItem = InsertItem(_T(blob->description), TREE_INDEX_APP, TREE_INDEX_APP, hItem);
			PopulateNextLevel(childItem, projectDir);
		}
		delete blob;
	}
	delete encapsulated;
}

// Add an item to the project tree
void CMyTreeCtrl::AddItem2ProjectTree(ConData* userDefBlob, Project* pProject, HTREEITEM hItem) {
	HTREEITEM childItem;
	INXString csProjectDir;

	pProject->pProjMData->getProjectDir(csProjectDir);
	childItem = InsertItem(_T(userDefBlob->description), TREE_INDEX_APP, TREE_INDEX_APP, hItem);
	// if sub-block added has further sub-blocks populate the project tree with these
	PopulateNextLevel(childItem, csProjectDir);
}

// Delete an item and its children from the project tree
void CMyTreeCtrl::DelItemFromProjectTree(ConData* userDefBlob, HTREEITEM hItem) {
	HTREEITEM userDefItem;
	Project* pProject;

	userDefItem = GetUserDefChildItem(userDefBlob, hItem);
	pProject = GetProjectPtr(hItem);
	pProject->closeUserDefDoc(userDefItem);
	DeleteItem(userDefItem);
}

HTREEITEM CMyTreeCtrl::GetUserDefChildItem(ConData* userDefBlob, HTREEITEM hItem) {
	HTREEITEM childItem, userDefItem = NULL;

	// get the child item that corresponds to userDefBlob
	childItem = GetChildItem(hItem);
	if ((INXString)GetItemText(childItem) == userDefBlob->description) {
		userDefItem = childItem;
	}
	else {
		childItem = GetNextSiblingItem(childItem);
		while (childItem) {
			if ((INXString)GetItemText(childItem) == userDefBlob->description) {
				userDefItem = childItem;
				childItem = NULL;
			}
			else {
				childItem = GetNextSiblingItem(childItem);
			}
		}
	}
	return userDefItem;
}

INXString CMyTreeCtrl::GetDEPPath(HTREEITEM hItem) {
	HTREEITEM hParent;
	INXString depPath = "";

	hParent = GetParentItem(hItem);
	while ((INXString)GetItemText(hParent) != APP) {
		depPath  = (INXString)GetItemText(hParent) + "\\" + depPath;
		hParent = GetParentItem(hParent);
	}
	return depPath;
}

// This function checks that the block doesn't already exist in the project. Required by encapsulation
bool CMyTreeCtrl::NameExist(INXString blockName, HTREEITEM hItem) {
	HTREEITEM hProject, hParent;
	Project* activeProject;

	// get the first item in the tree for the project
	hParent = GetParentItem(hItem);
	if ((INXString)GetItemText(hParent) == APP) {
		hProject = hItem;
	}
	while ((INXString)GetItemText(hParent) != APP) {
		hProject = hParent;
		hParent = GetParentItem(hProject);
	}

	// go through each project item and check the block name is unique
	activeProject = GetProjectPtr(hProject);
	activeProject->SaveProject();
	return CheckItem(hProject, activeProject, blockName);
}

// Search the project tree to see if the block name exists
bool CMyTreeCtrl::CheckItem(HTREEITEM hItem, Project* activeProject, INXString blockName) {
	HTREEITEM hChild;
	INXPOSITION pos;
	INXObjList* tmpList;
	ConData* blob;
	BlockOperations bo;
	INXString csProjectDir;

	activeProject->pProjMData->getProjectDir(csProjectDir);
	hChild = GetChildItem(hItem);
	if (hChild) {
		//check hItem block
		// Could use inheritance instead. i.e. have a class that inherits from HTREEITEM and
		// has an attribute that is the library name of the encapsulated block
		tmpList = bo.LoadBlock(csProjectDir + DEPDIR + GetDEPPath(hItem) + (INXString)GetItemText(hItem) + ".prg");
		pos = tmpList->GetHeadPosition();
		while (pos) {
			blob = (ConData*)tmpList->GetNext(pos);
			if (blob->className == blockName) {
				return TRUE;
			}
			delete blob;
		}
		delete tmpList;
		if (CheckItem(hChild, activeProject, blockName)) {
			return TRUE;
		}
	}
	// check any siblings
	hChild = GetNextSiblingItem(hChild);
	while (hChild) {
		if (CheckItem(hChild, activeProject, blockName)) {
			return TRUE;
		}
		hChild = GetNextSiblingItem(hChild);
	}
	return FALSE;
}

void CMyTreeCtrl::CloseProject(HTREEITEM hItem, Project* activeProject) {
	HTREEITEM projItem;
	
	// if project is modified prompt user to save
	// Don't prompt user because project is saved on every action
	/*
	if (((CDrawProgApp*)AfxGetApp())->IsModified(activeProject)) {
		if (AfxMessageBox("Do you want to save the project before closing?",MB_YESNO) == IDYES) {
			activeProject->SaveProject();
		}
	}*/
	// Clean up project when closing app. 
	// Used to be done when saving project. However, project is saved after each action now.
	// Don't want to delete unused when saving project, because can't do undo for encapsulated blocks.
	activeProject->DeleteUnused(activeProject->pDEP[0]);
	activeProject->SaveProject();
	((CDrawProgApp*)AfxGetApp())->CloseProject(activeProject);
	projItem = GetParentItem(hItem);
	projItem = GetParentItem(projItem);
	DeleteItem(projItem);
	DeleteProject(activeProject->projectNum);	
}


// Saves the hierarchy name for each encapsulated block.These are used by flattening process when
// writing SODL.
void CMyTreeCtrl::SaveHierName(HTREEITEM hItem, INXString projectDir, Project* pProject) {
	INXObjList* tmpList = new INXObjList;
	INXPOSITION pos;
	ConData* blob;
	INXString hierName;
	BlockOperations bo;
	
	hierName = GetDEPPath(hItem) + (INXString)GetItemText(hItem);
	// if top level then want to update dep in memory
	if (pProject->pDEP[0]->hItem == hItem) {
		tmpList = pProject->pDEP[0]->condata;
	}
	else {
		tmpList = bo.LoadBlock(projectDir + DEPDIR + hierName + ".prg");
	}
	
	pos = tmpList->GetHeadPosition();
	while (pos) {
		blob = (ConData*) tmpList->GetNext(pos);
		if (blob->m_iUserDefined) {
			blob->hierarchyName = hierName + "\\";
			SaveHierName(GetUserDefChildItem(blob, hItem), projectDir, pProject);
		}
	}

	if (pProject->pDEP[0]->hItem != hItem) {
		bo.SaveBlock(projectDir + DEPDIR + hierName + ".prg", tmpList);
		bo.DeleteBlock(tmpList);
	}
}

/**
 * Check if DEP passed in has a parent DEP in the tree - at the moment this is how we define a subsystem
 * Returns true if it does, else returns false
 * @todo - better definition of a subsystem that allows them to be edited as a standalone component
 */
bool CMyTreeCtrl::IsSubsytem(Project* pProject, DEP* pDEP) {
	HTREEITEM hParent;
	INXString csProjectDir;
	bool bHasParent = false;

	pProject->pProjMData->getProjectDir(csProjectDir);
	hParent = GetParentItem(pDEP->hItem);
	//@todo - is this the best test we have for a DEP having a parent?
	if ((INXString)GetItemText(hParent) != APP) {
		bHasParent = true;
	}
	return bHasParent;
}

ConData* CMyTreeCtrl::AddXPort(INXString type, INXString portLabel, INXPoint point, Project* pProject, DEP* pDEP) {
	HTREEITEM hParent;
	INXString parentName, csProjectDir;
	ConData* xport;
	DEP* pParentDEP;
	CDrawProgView* pView;

	pProject->pProjMData->getProjectDir(csProjectDir);
	// When adding an xport find the parent item and add a port to the block icon
	hParent = GetParentItem(pDEP->hItem);
	if ((INXString)GetItemText(hParent) != APP) {
		parentName = GetItemText(hParent);
		// Open parent if it isn't already
		openProject = FALSE;
		hSelItem = hParent;
		pView = pProject->OpenView(csProjectDir + DEPDIR + GetDEPPath(hParent) + parentName + ".prg");
		pParentDEP = pView->pDEP;
		xport = pProject->AddXPort(pParentDEP, type, portLabel, point, pDEP);
		// Save both DEPs so they are consistent
		pDEP->SaveProg(csProjectDir + DEPDIR + GetDEPPath(pDEP->hItem) + pDEP->depFilename + ".prg");
		pParentDEP->SaveProg(csProjectDir + DEPDIR + GetDEPPath(hParent) + parentName + ".prg");
		// set modified flag in doc
		//pView->pDoc->SetModifiedFlag(TRUE);
		// return previous view to front
		hSelItem = pDEP->hItem;
		CDocument* Subsystem = AfxGetApp( )->OpenDocumentFile(csProjectDir + DEPDIR + 
			GetDEPPath(pDEP->hItem) + pDEP->depFilename + ".prg");
		openProject = TRUE;
		return xport;
	}
	// When there isn't a parent simply add the xport to the DEP
	else {
		return pDEP->AddXPort(type, portLabel, point);
	}
	return NULL;
}

void CMyTreeCtrl::DeleteIcon(INXPOSITION iconPos, Project* pProject, DEP* pDEP, bool bDelOutputs) {
	ConData* blob;
	HTREEITEM hParent, hUserDefItem;
	INXString parentName, csProjectDir;
	DEP* pParentDEP;
	CDrawProgView* pView;
	bool topLevelXport = TRUE;
	CFileOperation fo;

	pProject->pProjMData->getProjectDir(csProjectDir);
	blob = (ConData*) pDEP->condata->GetAt(iconPos);
	// if the icon is an xport delete the port on the block in the parent view
	if (blob->m_csIconType.Find("XINPUT") != -1 || blob->m_csIconType.Find("XOUTPUT") != -1 || 
		blob->m_csIconType == "XSTART" || blob->m_csIconType == "XFINISH") {
		hParent = GetParentItem(pDEP->hItem);
		if ((INXString)GetItemText(hParent) != APP) {
			topLevelXport = FALSE;
			parentName = GetItemText(hParent);
			// Open parent if it isn't already
			openProject = FALSE;
			hSelItem = hParent;
			pView = pProject->OpenView(csProjectDir + DEPDIR + GetDEPPath(hParent) + parentName + ".prg");
			pParentDEP = pView->pDEP;
			pProject->DeleteXPort(pParentDEP, blob->description, pDEP->depFilename);
			// set modified flag in doc
			//pView->pDoc->SetModifiedFlag(TRUE);
			// return previous view to front
			hSelItem = pDEP->hItem;
			CDocument *Subsystem = AfxGetApp( )->OpenDocumentFile(csProjectDir + DEPDIR + 
				GetDEPPath(pDEP->hItem) + pDEP->depFilename + ".prg");
			openProject = TRUE;
		}
	}
	// if user defined remove item from project tree and DEP
	else if (blob->m_iUserDefined) {
		hUserDefItem = GetUserDefChildItem(blob, pDEP->hItem);
		pProject->removeWidgetsInUserDefBlock(hUserDefItem);
		DelItemFromProjectTree(blob, pDEP->hItem); 
		fo.Delete(csProjectDir + DEPDIR + GetDEPPath(pDEP->hItem) + pDEP->depFilename + "\\" + blob->description + ".prg");
		fo.Delete(csProjectDir + DEPDIR + GetDEPPath(pDEP->hItem) + pDEP->depFilename + "\\" + blob->description);
	}
	else if (blob->isGuiWidget()) {
		pProject->removeGuiWidget(blob);
	}

	pDEP->DeleteIcon(iconPos, bDelOutputs);
	// If deleting a xport and it is not on the top level, save both DEPs so they are consistent
	if (!topLevelXport) {
		pDEP->SaveProg(csProjectDir + DEPDIR + GetDEPPath(pDEP->hItem) + pDEP->depFilename + ".prg");
		pParentDEP->SaveProg(csProjectDir + DEPDIR + GetDEPPath(hParent) + parentName + ".prg");
	}
}

void CMyTreeCtrl::DeleteBlockPort(INXPOSITION blockPos, int portNum, int portType, Project* pProject, DEP* pDEP) {
	openProject = FALSE;
	pProject->DeleteBlockPort(blockPos, portNum, portType, pDEP);
	openProject = TRUE;
}

void CMyTreeCtrl::RenameBlockPort(INXPOSITION iconPos, int portNum, int portType, Project* pProject, DEP* pDEP) {
	openProject = FALSE;
	pProject->RenameBlockPort(iconPos, portNum, portType, pDEP);
	openProject = TRUE;
}

void CMyTreeCtrl::RenameXport(INXPOSITION iconPos, Project* pProject, DEP* pDEP) {
	ConData* blob;
	HTREEITEM hParent;
	INXString parentName, csProjectDir, csNewPortLabel, csOldPortLabel;
	DEP* pParentDEP;
	CDrawProgView* pView;
	bool topLevelXport = TRUE;

	blob = (ConData*) pDEP->condata->GetAt(iconPos);
	csOldPortLabel = blob->description;

	pProject->RenameXport(iconPos, pDEP, csNewPortLabel);

	// rename port in parent view
	if (blob->m_csIconType.Find("XINPUT") != -1 || blob->m_csIconType.Find("XOUTPUT") != -1 || 
		blob->m_csIconType == "XSTART" || blob->m_csIconType == "XFINISH") {
		pProject->pProjMData->getProjectDir(csProjectDir);
		hParent = GetParentItem(pDEP->hItem);
		if ((INXString)GetItemText(hParent) != APP) {
			topLevelXport = FALSE;
			parentName = GetItemText(hParent);
			// Open parent if it isn't already
			openProject = FALSE;
			hSelItem = hParent;
			pView = pProject->OpenView(csProjectDir + DEPDIR + GetDEPPath(hParent) + parentName + ".prg");
			pParentDEP = pView->pDEP;
			pParentDEP->SetPortLabel(pDEP->depFilename, csOldPortLabel, csNewPortLabel);
			// return previous view to front
			hSelItem = pDEP->hItem;
			CDocument *Subsystem = AfxGetApp( )->OpenDocumentFile(csProjectDir + DEPDIR + 
				GetDEPPath(pDEP->hItem) + pDEP->depFilename + ".prg");
			openProject = TRUE;
		}
	}
}


/**
 * Updates the project description on the tree for the specified project
 */
void CMyTreeCtrl::UpdateProjectDescrptionOnTree(Project* pProject, DEP* pDEP) {
	HTREEITEM projItem, descItem, childItem;
	INXString childName;
	int ind = 0;

	projItem = GetProjectItem(pDEP->hItem);

	//NOTE - don't delete the node and re-add it, crashes IAB this function is called when dbl click on tree
	// update each node item for project description
	childItem = GetChildItem(projItem);
	while (childItem) {
		childName = GetItemText(childItem);
		if (childName == "INFO") {

			descItem = GetChildItem(childItem);
			while (descItem) {
				ind++;
				if (ind == 1)
					SetItemText(descItem, _T("Project Name: " + pProject->pProjMData->m_csProjectAppCanonicalName));
				else if (ind == 2)
					SetItemText(descItem, _T("Commercial Name: " + pProject->pProjMData->m_csProjectAppCommercialName));
				else if (ind == 3)
					SetItemText(descItem, _T("Version: " + pProject->pProjMData->m_csProjectAppVersion));
				else if (ind == 4)
					SetItemText(descItem, _T("Description: " + pProject->pProjMData->m_csProjectAppDescription));

				descItem = GetNextSiblingItem(descItem);
			}

			childItem = NULL;
/*
			DeleteItem(childItem);
			childItem = NULL;

			descItem = InsertItem(_T("INFO"), 6, 6, projItem);

			// Populate project description
			InsertItem(_T("Project Name: " + pProject->pProjMData->m_csProjectAppCanonicalName), 6, 6, descItem);
			InsertItem(_T("Commercial Name: " + pProject->pProjMData->m_csProjectAppCommercialName), 6, 6, descItem);
			InsertItem(_T("Version: " + pProject->pProjMData->m_csProjectAppVersion), 6, 6, descItem);
			InsertItem(_T("Description: " + pProject->pProjMData->m_csProjectAppDescription), 6, 6, descItem);
*/

		} else {
			childItem = GetNextSiblingItem(childItem);
		}
	}
}

// Function that updates the project tree when an undo or redo is performed
void CMyTreeCtrl::UpdateTree(Project* pProject, DEP* pDEP) {
	INXPOSITION pos;
	ConData* blob;
	INXString childName;
	bool blockExists;
	HTREEITEM childItem;

	// update project tree
	// if a user defined block is not in the project tree then add it
	pos = pDEP->condata->GetHeadPosition();
	while (pos) {
		blob = (ConData*) pDEP->condata->GetNext(pos);
		if (blob->m_iUserDefined && !GetUserDefChildItem(blob, pDEP->hItem)) {
			AddItem2ProjectTree(blob, pProject, pDEP->hItem);
		}
	}
	// if an item is in the project tree but not in the DEP then delete from project tree
	childItem = GetChildItem(pDEP->hItem);
	while (childItem) {
		blockExists = FALSE;
		childName = GetItemText(childItem);
		if (childName != "") {
			pos = pDEP->condata->GetHeadPosition();
			while (pos) {
				blob = (ConData*) pDEP->condata->GetNext(pos);
				if (blob->m_iUserDefined && blob->description == childName) {
					blockExists = TRUE;
				}
			}
			if (!blockExists) {
				DeleteItem(childItem);
			}
		}
		childItem = GetNextSiblingItem(childItem);
	}
}

void CMyTreeCtrl::OpenParent(HTREEITEM hItem, Project* pProject) {
	HTREEITEM hParent;
	INXString csProjectDir;

	pProject->pProjMData->getProjectDir(csProjectDir);
	hParent = GetParentItem(hItem);
	if ((INXString)GetItemText(hParent) != APP) {
		openProject = FALSE;
		hSelItem = hParent;
		CDocument* Subsystem = AfxGetApp( )->OpenDocumentFile(csProjectDir + DEPDIR + 
			GetDEPPath(hParent) + (INXString)GetItemText(hParent) + ".prg");
		openProject = TRUE;

		// Propagate debug data
		POSITION pos = Subsystem->GetFirstViewPosition();
		CDrawProgView* pView = (CDrawProgView*) Subsystem->GetNextView(pos);
		if (pView->pProject->debug.debugMode != DBGSTOP) {
			pView->pDEP->ResetAllDbgEvents();
			pView->pDEP->PropagateDebugDataUp(hItem);
		}
		/*if (pProject->debug.debugMode != DBGSTOP) {
			POSITION pos = Subsystem->GetFirstViewPosition();
			CDrawProgView* pView = (CDrawProgView*) Subsystem->GetNextView(pos);
			OpenDebugDEP(pView);
		}*/
	}
}

/*
 * Deprecated, do not use.
 * Data Items removed from IAB
 */
void CMyTreeCtrl::AddDataFile(ExtDataFile &dataFile, HTREEITEM hItem) {
	HTREEITEM hProject, childItem, txtItem;
	INXString filename;

	dataFile.getHostFileName(filename);
	// Get the project item
	INXString depStr = GetItemText(hItem);
	hProject = GetProjectItem(hItem);
	if (ItemHasChildren(hProject)) {
		INXString projectStr = GetItemText(hProject);
	}
	
	// Get the text item 
	childItem = GetChildItem(hProject);
	if (GetItemText(childItem) == "TXT") {
		txtItem = childItem;
	}
	else {
		childItem = GetNextSiblingItem(childItem);
		while (childItem) {
			if (GetItemText(childItem) == "TXT") {
				txtItem = childItem;
				childItem = NULL;
			}
			else {
				childItem = GetNextSiblingItem(childItem);
			}
		}
	}
	
	// Add the file to the text item
	InsertItem(_T(filename), 3, 3, txtItem);
}

// Method that adds a resource file to the project tree
void CMyTreeCtrl::AddResourceFile(ExtResourceFile &xResourceFile, HTREEITEM hItem) {
	HTREEITEM hProject, hChildItem, hRscItem;
	INXString csFileName;

	xResourceFile.getHostFileName(csFileName);
	// Get the project item
	INXString csDepStr = GetItemText(hItem);
	hProject = GetProjectItem(hItem);
	if (ItemHasChildren(hProject)) {
		INXString csProjectStr = GetItemText(hProject);
	}
	
	// Get the text item 
	hChildItem = GetChildItem(hProject);
	if (GetItemText(hChildItem) == "RESOURCE") {
		hRscItem = hChildItem;
	}
	else {
		hChildItem = GetNextSiblingItem(hChildItem);
		while (hChildItem) {
			if (GetItemText(hChildItem) == "RESOURCE") {
				hRscItem = hChildItem;
				hChildItem = NULL;
			}
			else {
				hChildItem = GetNextSiblingItem(hChildItem);
			}
		}
	}
	
	// Add the file to the resource item
	InsertItem(_T(csFileName), TREE_INDEX_RESOURCE, TREE_INDEX_RESOURCE, hRscItem);
}

// Method that adds a widget group to the project explorer
// hItem is an item in the project to be added to
void CMyTreeCtrl::addWidgetGroup(INXString csWidgetGroupName, HTREEITEM hItem) {
	HTREEITEM hProject, hChildItem, hGuiItem;
	INXString csDefaultName;

	// Get the project item
	hProject = GetProjectItem(hItem);
	
	// Get the GUI item 
	hChildItem = GetChildItem(hProject);
	if (GetItemText(hChildItem) == "GUI") {
		hGuiItem = hChildItem;
	}
	else {
		hChildItem = GetNextSiblingItem(hChildItem);
		while (hChildItem) {
			if (GetItemText(hChildItem) == "GUI") {
				hGuiItem = hChildItem;
				hChildItem = NULL;
			}
			else {
				hChildItem = GetNextSiblingItem(hChildItem);
			}
		}
	}
	
	// Add the file to the GUI item
	csDefaultName = GUI_LAYOUT_DEFAULT_FILENAMEPREFIX + csWidgetGroupName;
	InsertItem(_T(csDefaultName), TREE_INDEX_GUI, TREE_INDEX_GUI, hGuiItem);
}

// Method that updates the widget groups in the project explorer.
// It removes all widget groups, and then inserts the ones in the project meta data
void CMyTreeCtrl::updateWidgetGroups(HTREEITEM hItem) {
	HTREEITEM hProject, hChildItem, hGuiItem, hGuiChildItem;
	INXString csWidgetGroupName;
	Project* pProject;
	vector<ExtGuiFile> vGuiFileVec;

	// Get the project item
	hProject = GetProjectItem(hItem);
	
	// Get the GUI item 
	hChildItem = GetChildItem(hProject);
	if (GetItemText(hChildItem) == "GUI") {
		hGuiItem = hChildItem;
	}
	else {
		hChildItem = GetNextSiblingItem(hChildItem);
		while (hChildItem) {
			if (GetItemText(hChildItem) == "GUI") {
				hGuiItem = hChildItem;
				hChildItem = NULL;
			}
			else {
				hChildItem = GetNextSiblingItem(hChildItem);
			}
		}
	}
	
	// delete all the gui items
	hGuiChildItem = GetChildItem(hGuiItem);
	while (hGuiChildItem) {
		DeleteItem(hGuiChildItem);
		hGuiChildItem = GetChildItem(hGuiItem);
	}

	// re-populate the gui items from the project meta-data
	pProject = GetProjectPtr(hItem);
	pProject->pProjMData->getGuiFiles(vGuiFileVec);
	for (UINT i=0; i<vGuiFileVec.size(); i++) {
		vGuiFileVec.at(i).getHostFileName(csWidgetGroupName);
		InsertItem(_T(csWidgetGroupName), TREE_INDEX_GUI, TREE_INDEX_GUI, hGuiItem);
	}

}

HTREEITEM CMyTreeCtrl::GetProjectItem(HTREEITEM hItem) {
	HTREEITEM hParent, hProject;

	// get the first item in the tree for the project
	hParent = GetParentItem(hItem);
	while (hParent) {
		hProject = hParent;
		hParent = GetParentItem(hParent);
	}

	return hProject;
}

void CMyTreeCtrl::SaveProjectAs(INXString projectName, HTREEITEM hItem) {
	HTREEITEM hProject, hDEPItem;

	// Rename the project item
	hProject = GetProjectItem(hItem);
	SetItemText(hProject, projectName);
	// Rename the top level DEP item
	hDEPItem = GetChildItem(hProject);
	hDEPItem = GetChildItem(hDEPItem);
	SetItemText(hDEPItem, projectName);
}

void CMyTreeCtrl::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{

	INXString filename, drawGui, depPath, csProjectDir, csFullPathProjFile;
	Project* thisProject;
	INXString type = "";
	HTREEITEM hParent;

	//hSelItem = HitTest( point, &uFlags );
	hSelItem = GetSelectedItem();
	//system(

	if(hSelItem )//&& (uFlags & TVHT_ONITEM))
	{
		// Get the type of the selected item. It could be simplified by inheriting HTREEITEM and
		// having a type attribute
		thisProject = GetProjectPtr(hSelItem);
		thisProject->pProjMData->getProjectDir(csProjectDir);
		thisProject->pProjMData->getFullPathProjectFile(csFullPathProjFile);
		hParent = GetParentItem(hSelItem);
		// make sure project is not selected
		if (hParent) {
			type = GetItemText(hSelItem);
			// make sure DEP, GUI, BMP or TXT is not selected
			if (type != APP && type != "GUI" && type != "PNG" && type != "TXT" && type != "NLS" && type != "RESOURCE" && type != "INFO") {
				while (hParent && type != APP && type != "GUI" && type != "PNG" && type != "TXT" && type != "NLS" && type != "RESOURCE" && type != "INFO") {
					type = GetItemText(hParent);
					hParent = GetParentItem(hParent);
				}
			}
			else {
				type = "";
			}
		}

	}

	if (type == APP)  {

		
		// open document and view
		openProject = FALSE;
		CDocument* Subsystem = AfxGetApp( )->OpenDocumentFile(csProjectDir + DEPDIR +
			GetDEPPath(hSelItem) + (INXString)GetItemText(hSelItem) + ".prg");
		openProject = TRUE;
			POSITION pos = Subsystem->GetFirstViewPosition();
			CDrawProgView* pView = (CDrawProgView*) Subsystem->GetNextView(pos);
			pView->RedrawWindow();
		// if in debug mode set the DEP in the debugger
		if (thisProject->debug.debugMode != DBGSTOP) {
			OpenDebugDEP(pView);
		}
		
	}

	else if (type == "PNG") {
		filename = csProjectDir + GUIDIR + (INXString)GetItemText(hSelItem);
		filename = cloneBackSlashes(filename);
		ShellExecute(NULL, "open", filename, NULL, NULL, SW_SHOW);
	}
/* dk - Data Items removed from IAB
	// open textfile in notepad
	else if (type == "TXT") {
		filename = csProjectDir + DDATADIR + GetItemText(hSelItem);
		ShellExecute(NULL, "open", filename, NULL, NULL, SW_SHOW);
	}
*/
	// open using windows file association
	else if (type == "RESOURCE") {
		filename = csProjectDir + RESOURCEDIR + (INXString)GetItemText(hSelItem);
		//@todo - this works in windows ok, but in wine most file types fail. .txt files do open using notepad but png, jpgs all open Wine Explorer with a blank document
		// should we detect wine environment and do something more intelligent based on file extension?
		// note that in wine registry, image files are all associated with iexplorer.exe where as text files are associated with notepad.exe - so could use wine registry to make some associations at install time
		ShellExecute(NULL, "open", filename, NULL, NULL, SW_SHOW);
	}

	// open gui file in gui builder
	else if (type == "GUI") {

		/*BIG WORKAROUND!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

		MR 30Nov07.

		ShellExecute can be used 
		
		A/
		with the:
		executable as the 3rd arg, and filename as the 4th arg, as in ( NULL, NULL, "fred.exe", "fre4dFodder.txt", ...)
		OR 
		
		B/
		with the:
		verb as the 2nd arg, document as the 3rd arg, as in ( NULL, "open", "fre4dFodder.txt", ...

		B/ 
		1. Finds the associated executable from the registry
		2. The name of the process can have ~'s in it (with A/, the process has the specific name xxx.exe name!)
		3. The arguments don't get through to the called process.

		We need the called process (LGB) to get the arguments, as these are parsable combo of proj and gui 
		to open.

		We are therefore better calling with method A.
		This gives us control about calling the right exec between dev / installer cases, and gives a good
		handle to the name of the LGB process - which is important, as we search for this to find
		instances of LGB already running.
		The disadvantage of this is that we have to work-out
		the name of the installed or local/ development executable.

		!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

		filename = csProjectDir + GUIDIR + (INXString)GetItemText(hSelItem) + ".gui\0";

		INXString csLgbShortExecName;
		INXString csLgbExecutablePath;
		INXString csInstalledLgbExecName;


#ifdef _DEBUG

		//csInstalledLgbExecName = _T(installedLGBExecName);

		CLabLgbBaseApp *pApp = ( CLabLgbBaseApp * ) AfxGetApp();

		INXString csDevExecDir;
		pApp->GetInstallationBaseDir( csDevExecDir );

		csDevExecDir += LUCID_DIST_DIR;
		csDevExecDir += LUCID_EXECUTABLES_DIR;

		INXString csLabFullExecName;
		pApp->GetExecutableName( csLabFullExecName );

		int iPos = csLabFullExecName.Find("Application");
		INXString csLgbFullExecName = csLabFullExecName.Left( iPos );

		csLabFullExecName = csLabFullExecName.Right( csLabFullExecName.GetLength() - iPos - 11  );
		csLgbFullExecName = csLgbFullExecName + "GUI" + csLabFullExecName;
		iPos = csLgbFullExecName.ReverseFind( '\\' );
		csLgbShortExecName = csLgbFullExecName.Right( csLgbFullExecName.GetLength() - iPos -1 );
		csLgbExecutablePath = csLgbFullExecName;

#else

		TCHAR installedLGBExecName[MAX_PATH];
		HINSTANCE hInst = ::FindExecutable( 
			cloneBackSlashes(filename),
			cloneBackSlashes(""),
			installedLGBExecName
		);

		csInstalledLgbExecName = _T(installedLGBExecName);
		int iPos = csInstalledLgbExecName.ReverseFind( '\\' );
		csLgbShortExecName = csInstalledLgbExecName.Right( csInstalledLgbExecName.GetLength() - iPos -1 );
		csLgbExecutablePath = csInstalledLgbExecName;

#endif


		TCHAR psAppName[300];
		_tcscpy_s( psAppName, 300, _T(csLgbShortExecName) );	

		TCHAR psWindowTitle[300];
		_tcscpy_s( psWindowTitle, 300, _T(csProjectDir) );


		// Find any LGB window with the right title - ie any already-open instances of LGB running this
		// project.  If there are any, send them to the fore.
		HANDLE hProcess;
		HWND hWnd = getTitledApplicationWindow( 
			psAppName, psWindowTitle, hProcess );

		//csProjectDir.ReleaseBuffer();

		if(hWnd!=NULL){

			// There IS already an LGB running this proj.
			// Tell it to open the particular layout!

			::SetForegroundWindow( hWnd );

			COPYDATASTRUCT cpd;
			cpd.dwData = 0;
			cpd.cbData = filename.GetLength()+1;
			cpd.lpData = (void*)filename.GetBuffer(cpd.cbData);
			filename.ReleaseBuffer();

			::SendMessage( hWnd, WM_COPYDATA, 0, (LPARAM)&cpd );
			//csProjectDir.ReleaseBuffer();

		}else{

			// There is no LGB for this project, but see if there is an LGB running 
			// with 'no project set'.  If so, take this over for our project,
			// rather than opening a completely new one, and leaving the empty one doing nowt.

			INXString csNoProjWarning = NO_PROJECT_WARNING;
			//TCHAR* psWindowTitle = _T(csNoProjWarning.GetBuffer());
			TCHAR psWindowTitle[300];
			_tcscpy( psWindowTitle, _T(csNoProjWarning) );
			//csNoProjWarning.ReleaseBuffer();
			hWnd = getTitledApplicationWindow( 
			psAppName, psWindowTitle, hProcess );

			if(hWnd!=NULL){

				// There is a null-project LGB.  Take it over with the project we want to see opened
				::SetForegroundWindow( hWnd );

				INXString csFullProjectFilePath;
				thisProject->pProjMData->getFullPathProjectFile(csFullProjectFilePath);

				INXString csArgument = csFullPathProjFile + "#" + filename;

				COPYDATASTRUCT cpd;
				cpd.dwData = 0;
				cpd.cbData = csArgument.GetLength()+1;
				cpd.lpData = (void*)csArgument.GetBuffer(cpd.cbData);
				csArgument.ReleaseBuffer();

				::SendMessage( hWnd, WM_COPYDATA, 0, (LPARAM)&cpd );

				//csNoProjWarning.ReleaseBuffer();

			} else {


				// There is *NO* LGB running this proj.

				INXString csFullProjectFilePath;
				thisProject->pProjMData->getFullPathProjectFile(csFullProjectFilePath);
				INXString csInstallDir;
				CLabLgbBaseApp *pApp = ( CLabLgbBaseApp * )AfxGetApp();
				pApp->GetInstallationBaseDir( csInstallDir );

				INXString csArgument = "\"" + csFullPathProjFile + "#" + filename + "\"";

				ShellExecute(NULL, NULL, cloneBackSlashes( csLgbExecutablePath ), csArgument, NULL, SW_SHOW);

				/*
				SHELLEXECUTEINFO fred;
				memset( &fred, 0, sizeof(fred) );
				fred.lpVerb = "open";
				//INXString crp = cloneBackSlashes( filename );
				fred.lpFile = cloneBackSlashes( csLgbExecutablePath );
				fred.lpParameters = 0;//csArgument;
				fred.nShow = SW_SHOW;
				fred.hwnd = NULL;
				fred.lpDirectory = NULL;
				fred.cbSize = sizeof( SHELLEXECUTEINFO );
				*/

				
			}

		}	

		
	}	//else if (type == "GUI")

	else if (type == "NLS") {
		if (thisProject->RunNlsExec()) {
			thisProject->OpenNlsFile();
		}
	}
	else if (type == "INFO") {
		ProjectDescriptionDialog projDlg(thisProject->pProjMData);

		if (projDlg.DoModal()==IDOK) {
			thisProject->pProjMData->writeProjectDescriptionFile();
			UpdateProjectDescrptionOnTree(thisProject, thisProject->pDEP[thisProject->DEPNum]);
		}
	}
	int i=0;
	//if(pResult)*pResult = 0;

}


