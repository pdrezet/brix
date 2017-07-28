#include "inx_config.h"

#include "DrawProg.h"
#include "ChildFrame.h"
#include "FileOperations.h"
#include <wx/msgdlg.h>
#include <wx/cmdline.h>

#include "Userconfig.h"


wxChar workDir[WORK_DIR_SIZE];

//wxIMPLEMENT_APP(DrawProg);

IMPLEMENT_APP(DrawProg)

BEGIN_EVENT_TABLE(DrawProg, wxApp)
    EVT_MENU(INX_SAVE_PROJECT, DrawProg::OnSaveProject)
	EVT_MENU(INX_NEW_PROJECT, DrawProg::OnNewProject)
	EVT_MENU(INX_OPEN_PROJECT, DrawProg::OnOpenProject)
END_EVENT_TABLE()

DrawProg::DrawProg(void)
{
	m_cProjTree = NULL;
	m_CurrentProject = NULL;

}

DrawProg::~DrawProg(void)
{
}

bool DrawProg::OnInit(){

	SetWorkDirGlobal(workDir);
	pDEP = NULL;
	m_frame = new MainFrame((wxWindow*)NULL);
	m_frame->Show(true);
	m_cProjTree = new MyTreeCtrl;

    return true;
}

bool DrawProg::DropFBInCurrentView(INXPoint point,INXString componentType,INXString component) {
	DrawProgView * pView = getActiveProgView();
	ConData *droppee, *draggee;
	INXPOSITION droppeePos, draggeePos;
	INXPoint droppeePoint, draggeePoint;
	bool bContinue = true;

	if( !m_CurrentProject || !m_CurrentProject->pProjMData->getLock() ){

		INX_MessageBox( PMD_LOCK_FAILURE_MESSAGE );

	} else {

		m_CurrentProject->pProjMData->readProjectFile();
		INXPoint relPoint = point - m_ActiveProgView->GetParent()->GetPosition();
		if (relPoint.x >= 0 && relPoint.y >= 0 ) {
			ConData* blob = pView->processComponentDrop(SnapToGrid(relPoint), componentType, component );
			// and now update the prject
			if (blob) {
				if (blob->m_iUserDefined) {
					// add this instance to the project tree
					/* todo pView->pFrame->m_wndProjectBar.m_cProjTree.AddItem2ProjectTree(blob, m_CurrentProject, pView->pDEP->hItem); */
					// Make sure gui widget tags are unique
					// add any gui widgets to the project meta data

					// todo do all the rest diferently with a single call?
					//INXTREEITEM hUserDefItem = pView->pFrame->m_wndProjectBar.m_cProjTree.GetUserDefChildItem( blob, pView->pDEP->hItem);

					//m_CurrentProject->getWidgetGroupNames(hUserDefItem, sWidgetGroupSet);
					//m_CurrentProject->setWidgetGroupNames(sWidgetGroupSet, vWidgetGroupPairVec);
					//m_CurrentProject->updateWidgetGroupNames(hUserDefItem, vWidgetGroupPairVec);

				}
				// Add Gui widgets to project file
				/* todo
			else if (blob->isGuiWidget()) {
				m_CurrentProject->addGuiWidget(blob);
			}
				 */
#if 0
				// Functionality for doing FB substitution
				droppee = pView->m_FBSubstitute.getDroppee();
				draggee = blob;
				if (droppee) {
					pView->m_FBSubstitute.setDraggee(draggee);
					// It seems that the message box causes a redraw, which displays the draggee. This looks unsightly,
					// so disable the draw function in this icon until after the message box.
					draggee->m_iShow = 0;
					// Copy parameters
					if (!pView->m_FBSubstitute.copyParamValues()) {
						if (pView->m_FBSubstitute.isParamValsModified()) {
							if (INX_MessageBox("Substitution will cause your parameters to be lost. Do you want to continue?",MB_YESNO|MB_ICONEXCLAMATION)==IDNO) {
								bContinue = FALSE;
							}
						}
					}

					draggee->m_iShow = 1;
					if (bContinue) {
						// make sure new FB is in same position as old FB
						draggeePoint = draggee->GetIconPos();
						droppeePoint = droppee->GetIconPos();
						draggeePos = pView->pDEP->getPosFromIcon(draggee);
						pView->pDEP->RenewPosition(draggeePos, droppeePoint, draggeePoint);

						// copy the FB id so don't have to change othericonid attribute on ports connected
						// to output and finish ports
						draggee->identnum = droppee->identnum;

						// Copy description if neither are encapsulated FB
						if (!draggee->m_iUserDefined && !droppee->m_iUserDefined) {
							draggee->description = droppee->description;
						}

						// Copy connections
						pView->m_FBSubstitute.setDEP(pView->pDEP);
						pView->m_FBSubstitute.connectDraggee();

						// Delete old FB
						droppeePos = pView->pDEP->getPosFromIcon(droppee);
						// Insert draggee into condata list at same point as droppee.
						// Shouldn't need to do this but avoided a bug writing out SODL for space invaders demo
						pView->pDEP->condata->RemoveAt(draggeePos);
						pView->pDEP->condata->InsertAfter(droppeePos, draggee);
						pView->pFrame->m_wndProjectBar.m_cProjTree.DeleteIcon(droppeePos, m_CurrentProject, pView->pDEP, 0);
					}
					else {
						draggeePos = pView->pDEP->getPosFromIcon(draggee);
						pView->pFrame->m_wndProjectBar.m_cProjTree.DeleteIcon(draggeePos, m_CurrentProject, pView->pDEP, 0);
					}
				}
#endif
				if (bContinue) {
					// if adding xport then don't allow undo
					if (!(blob->m_FbName.Find("XINPUT") != -1 || blob->m_FbName.Find("XOUTPUT") != -1 || blob->m_FbName == "XSTART"
							|| blob->m_FbName == "XFINISH")) {
						pView->SaveUndo();
					}
					else {
						//@todo - currently can't undo adding an xport
						pView->initUndo();
					}

					m_CurrentProject->SaveProject();
					m_CurrentProject->pProjMData->writeProjectFile();
					pView->RedrawWindow();
				}

			}
		}
		else {
			wxMessageBox("Please Drop components within a workspace window");
		}

		//return true;
	}

	if (m_CurrentProject) m_CurrentProject->pProjMData->releaseLock();
	return true;
}

bool DrawProg::SetWorkDirGlobal(wxChar * workDir){
	if(!CheckExecutableFolderContextIsOk()){
		wxMessageBox(wxT("The executable is NOT in a valid location: the app won't work. Seek support"));
		return false;
	}

	INXString baseDir;
	GetInstallationBaseDir(baseDir);

	//strcpy_s( workDir, WORK_DIR_SIZE, baseDir );
	//workDir = (wxChar*)baseDir.c_str();
	strcpy(workDir,baseDir.c_str());
	return TRUE;
}

bool DrawProg::CheckExecutableFolderContextIsOk()
{
	bool retVal = false;

	INXString baseDir;
	GetInstallationBaseDir(baseDir);

	CFileOperation fo;

	// Check various 'child' folders are present, otherwise the app won't
	// find bitmaps etc and will fail.

	// For some reason, the const INXStrings defining these
	// in LucidConstants.h haven't been set
	// at this point!
#if (_INX_PLATFORM_ == INXWINDOWS)	

	int result = fo.CheckPath( baseDir + "\\BMP\\"  );
	if(result != PATH_IS_FOLDER) return false;

	result = fo.CheckPath( baseDir + "\\IDF\\"  );
	if(result != PATH_IS_FOLDER) return false;

	result = fo.CheckPath( baseDir + "\\temp\\"  );
	if(result != PATH_IS_FOLDER) return false;

#elif (_INX_PLATFORM_ == INXMAC)

#elif (_INX_PLATFORM_ == INXLINUX)

	int result = fo.CheckPath( (INXString)(baseDir + (INXString)("/BMP/")));
	if(result != PATH_IS_FOLDER) return false;

	result = fo.CheckPath( (INXString)((baseDir + (INXString)("/IDF/"))));
	if(result != PATH_IS_FOLDER) return false;

	result = fo.CheckPath( (INXString)( baseDir + (INXString)("/temp/") ) );
	if(result != PATH_IS_FOLDER) return false;
#else
#error "_INXPLATFORM_ is not defined"
#endif

	return true;

}
bool DrawProg::GetInstallationBaseDir(INXString &installationBaseDir)
{
	//TCHAR test1[PATHBUFFER_SIZE];
	installationBaseDir.Empty();
	// Don't use this call as it returns the working dir which may well have
	// sweet FA to do with where the executable is - which is what we want.
	// MR
	//GetCurrentDirectory( PATHBUFFER_SIZE, test1 );
	INXString choppable;
	GetExecutableName( choppable); // Should now have full path to LucidDiddlyDo.exe file.

#if (_INX_PLATFORM_ == INXWINDOWS)
	int dumPos = choppable.Find("\\bin");
#elif (_INX_PLATFORM_ == INXMAC)

#elif (_INX_PLATFORM_ == INXLINUX)
		int dumPos = choppable.Find("/bin");
#else
#error "_INXPLATFORM_ is not defined"
#endif

	choppable = (INXString)choppable.Left(dumPos);
/*
	char zappedCopy[PATHBUFFER_SIZE];
	char*tempCh = (char*)choppable;
	strcpy(zappedCopy,  tempCh );
*/
	//getlowercase(zappedCopy, strlen(zappedCopy));

	installationBaseDir = choppable;
	//remove intital quotes
	//installationBaseDir = installationBaseDir.Right(installationBaseDir.GetLength()-1);
	installationBaseDir="./";
	return TRUE;
}
void DrawProg::GetExecutableName(INXString & execName){

#if (_INX_PLATFORM_ == INXWINDOWS)

	char* test1 = GetCommandLine();
	execName = test1;
	// remove all leading quotes and white spaces:
	while( execName.FindOneOf(" \"") == 0 ){
		execName = execName.Right(execName.GetLength()-1);
	}
	// remove all trailing quotes and white spaces:
	execName.MakeReverse();
	while( execName.FindOneOf(" \"") == 0 ){
		execName = execName.Right(execName.GetLength()-1);
	}
	execName.MakeReverse();

	// Now detect whether there is just one arg, or more than one, and strip off the
	// trailing args if present.

	// There will be a /" /" present in the middle of the overall string if more than one arg
	int pos = execName.Find("\" \"");
	if(pos != -1){
		execName = execName.Left(pos);
	}
#elif (_INX_PLATFORM_ == INXMAC)

#elif (_INX_PLATFORM_ == INXLINUX)

#else
#error "_INXPLATFORM_ is not defined"
#endif
	return;
}

void DrawProg::OnNewProject(wxCommandEvent& event){
	ChildFrame *subframe = new ChildFrame(m_frame, wxDefaultPosition, wxSize(500,500),_T("Canvas Frame"));

    // Make a menubar
    wxMenu *file_menu = new wxMenu;
    file_menu->Append(wxID_EXIT, _T("&Exit"));
    wxMenuBar *menu_bar = new wxMenuBar;
    menu_bar->Append(file_menu, _T("&File"));
    subframe->SetMenuBar(menu_bar);
    subframe->CreateStatusBar();
    int width, height;
    subframe->GetClientSize(&width, &height);
    DrawProgView *canvas = new DrawProgView(subframe, wxDefaultPosition, wxSize(width, height),WX_GL_DOUBLEBUFFER);
    subframe->canvas = canvas;
    m_ActiveProgView = canvas;
    subframe->Show(true);
}

void DrawProg::OnSaveProject(wxCommandEvent& event){

}
void DrawProg::OnOpenProject(wxCommandEvent& event){

	ProjectMetaData* pProjMData = new ProjectMetaData;
	LucidErrEnum err = pProjMData->showOpenProjectDialog(m_frame);

	if (kErr_NoErr == err) {

		if(!pProjMData->getLock()){

			wxMessageBox( wxT(PMD_LOCK_FAILURE_MESSAGE));
		}else{

			LucidErrEnum err = pProjMData->readProjectFile();

			OpenProject(pProjMData);
			pProjMData->releaseLock();
		}

	} else if (err == kErr_InvalidProjectDir) {

		wxMessageBox(wxT("The project file contains\nan invalid project directory\n and/or an invalid project name."));
		delete pProjMData;

	} else {
		delete pProjMData;
	}
}

wxDocument* DrawProg::OpenProject(ProjectMetaData* pProjMData){
	INXString csProjectDir, csProjectName, csProjectPathName;
	Project* pProject;
	CFileOperation fo;
	bool bLockReleased = false;

	pProjMData->getProjectName(csProjectName);
	pProjMData->getProjectDir(csProjectDir);
#if (_INX_PLATFORM_ == INXWINDOWS)
	csProjectPathName = csProjectDir + wxT("\\") + csProjectName + PROJECTEXT;
#elif (_INX_PLATFORM_ == INXMAC)

#elif (_INX_PLATFORM_ == INXLINUX)
		csProjectPathName = (INXString)(csProjectDir + (INXString)("/") + csProjectName + PROJECTEXT);
#else
#error "_INXPLATFORM_ is not defined"
#endif
	
	//	INX_MessageBox("Opening :" + csProjectPathName);

	ifstream projectfile(csProjectPathName);

	// set the project number. There are two approaches. 1. When a project is deleted shift the projects.
	// 2. the approach used is to find a project number that is avaialable.
	bool projectSpace = FALSE;

	for (int i=0; i<MAX_PROJECTS; i++) {
		if (!m_cProjTree->pProject[i]) {
			pProject = m_cProjTree->AddProject(i, pProjMData);
			i = MAX_PROJECTS;
			projectSpace = TRUE;
		}
	}
	if (!projectSpace) {
		wxMessageBox(wxT("Unable to open the project. DrawProg contains the maximum projects allowed."));
		return NULL;
	}

	// Create nls.csv if it doesn't exist
	if (pProject->pProjMData->isLocked()) {
		pProject->pProjMData->releaseLock();
		bLockReleased = true;
	}

	if (!fo.CheckPath((INXString)(csProjectDir + NLSDIR + NLSFILE))) {
#ifdef __INX_NLS
		pProject->RunNlsExec();
#endif
		if (!pProject->pProjMData->getLock()) {
			wxMessageBox(wxT(PMD_LOCK_FAILURE_MESSAGE));
		}
		else {
			pProject->pProjMData->readProjectFile(); //@todo
			pProject->pProjMData->releaseLock();
		}
	}


	if (bLockReleased) {
		if (!pProject->pProjMData->getLock()) {
			assert(1==0);
		}
	}
	//try display the view


	// Load the DEP
	// The following 2 lines are a fudge so that CDrawProgDoc can get the Project pointer in the case when
	// a project is freshly opened. Need to find a better way.
	m_cProjTree->openProject = TRUE;
	m_cProjTree->openProj = pProject;
#if (_INX_PLATFORM_ == INXWINDOWS)
	wxDocument* Subsystem = OpenDocumentFile(csProjectDir + wxT("\\") + DEPDIR + csProjectName + wxT(".prg"));
#elif (_INX_PLATFORM_ == INXMAC)

#elif (_INX_PLATFORM_ == INXLINUX)
	wxDocument* Subsystem = OpenDocumentFile((INXString)(csProjectDir + "/" + DEPDIR + csProjectName + ".prg"));
#else
#error "_INXPLATFORM_ is not defined"
#endif
	//todo - Subsystem is null here always - what is this for !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!?????????????

	m_cProjTree->openProject = FALSE;
	INXString docFile(csProjectDir + DEPDIR + csProjectName + wxT(".prg"));
	displayView(pProject, docFile);
	// Add project to MRU file list
#ifdef _UNUSED_FUNCTIONS_TO_LOAD_THE_FILE
	for(int i=0;i < this->m_pRecentFileList->GetSize();i++)
	{
		INXString strFileName(this->m_pRecentFileList->m_arrNames[i]);
	}
#endif
	//this->m_pRecentFileList->Add(csProjectPathName); @todo
	//this->m_pRecentFileList->WriteList();
#ifdef _UNUSED_FUNCTIONS_TO_LOAD_THE_FILE
for(int i=0;i < this->m_pRecentFileList->GetSize();i++)
	{
		INXString strFileName(this->m_pRecentFileList->m_arrNames[i]);
	}
#endif

//INX_MessageBox("SubSystem:" + (INXString)(csProjectDir + "/" + DEPDIR + csProjectName + ".prg"));
return Subsystem;
}

wxDocument* DrawProg::OpenDocumentFile(INXString lpszFileName)
{
	INXString ext = lpszFileName;
	ext = (INXString)ext.Right(4);
	// This function is called by MRU file list which is now a project file
	if (ext == wxT(".prg")) {
	#ifdef _UNUSED_FUNCTIONS_TO_LOAD_THE_FILE
		CDocument* subsys = wxApp::OpenDocumentFile(lpszFileName);
		// Remove .prg from MRU file list
		for(int i=0;i < this->m_pRecentFileList->GetSize();i++)
		{
			INXString strFileName(this->m_pRecentFileList->m_arrNames[i]);
			if (strFileName.Right(4) == ".prg") {
				this->m_pRecentFileList->Remove(i);
			}
		}
	#endif
		return NULL;
	}
	else if (ext == wxT(".lpj")) {

		INXString pathName = (INXString)(lpszFileName + "\\..");
		ProjectMetaData* pProjMData = new ProjectMetaData(pathName);

		if(!pProjMData->getLock()){

			wxMessageBox( wxT(PMD_LOCK_FAILURE_MESSAGE) );

		}else{
			LucidErrEnum err = pProjMData->readProjectFile((INXString)lpszFileName);
			pProjMData->releaseLock();

			if (kErr_NoErr == err) {
				return OpenProject(pProjMData);
			}
			else {
#ifdef _DEBUG
				wxMessageBox("OpenDocumentFile() - readProjectFile returned an error value");
#endif
			}
		}
	}
	return NULL;
}

void DrawProg::displayView(Project *proj, INXString doc_file){
	INXString filename;
	// Extract filename
	//proj->pProjMData->getFullPathProjectFile(filename);
	/*
	//filename = filename.SpanExcluding(".");
	filename.MakeReverse();
	filename = filename.SpanExcluding("\\");
	filename.MakeReverse();
	// remove .prg to get filename
	len = filename.GetLength() - 4;
	filename = filename.Left(len);*/
	//INX_MessageBox("displayView " + doc_file);
	pDEP = proj->AddDEP();
	pDEP->LoadProg(doc_file);
	pDEP->InitTagLists();
	pDEP->depFilename = doc_file;

	/* Set this as the default project */
	m_CurrentProject=proj;

	ChildFrame *subframe = new ChildFrame(m_frame, wxDefaultPosition, wxSize(500,450),_T("Canvas Frame"));

	int width, height;
    subframe->GetClientSize(&width, &height);
    DrawProgView *canvas = new DrawProgView(subframe, wxDefaultPosition, wxSize(width, height),WX_GL_DOUBLEBUFFER);
	canvas->pDEP = pDEP;
    subframe->canvas = canvas;
    m_ActiveProgView = canvas;
	subframe->Show();

}

/* Project management methods */
void DrawProg::setProjMetaData(ProjectMetaData* projMetadata ){
	///\brief sets metadata ....

	// look at original ...
}
void DrawProg::setProject(Project *){
	///\brief sets active project (but not metadata) ....

	// look at original ...
}

bool DrawProg::copyTransferrablesToExports(ProjectMetaData* projMetadata, bool a, bool b){

}

///\brief gets active project reference.
Project* DrawProg::getCurrentProject(){
return m_CurrentProject;
}

DrawProgView* DrawProg::getActiveProgView(){
	return m_ActiveProgView;
}

///\brief gets active DEP (graphical Model) object reference.
DEP* DrawProg::getCurrentDEP(){
return pDEP;
}
