// DrawGUI.cpp : Defines the class behaviors for the application.
//
#include "stdafx.h"

#include "DrawGUI.h"
#include <string.h>
#include <stdio.h>

#include "IconSelectionTester.h"

#include <direct.h>
#include "MainFrm.h"
#include "ChildFrm.h"
#include "DrawGUIDoc.h"
#include "DrawGUIView.h"

#include "../common/ScreenTagDialog.h"
#include "OkCnclDlog.h"
#include "YesY2ANoCnclDlog.h"
#include "../LucidApplicationBuilder/FileOperations.h"

#include "TgtTransProgDlog.h"
#include "ProjectFileManagerDialog.h"
#include "../common/ProjectMetaData.h"


//#include "DialogTester.h"
#include "../common/TransferErrorDlog.h"
#include "../common/ExtGuiFile.h"

#include "GlobalFuncs_2.h"
#include "Resource.h"

#include "LgbCommandLineInfo.h"
#include "../common/common.h" //getlowercase
#include "../common/LucidConstants.h"

//#include "./version.h"
#include "./revision.h"


#include "../common/LucidTcpipClientDlg.h"
#include "../common/LucidTcpipClient.h"
#include <cassert>
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <afxadv.h>

#include "LgbDeque.h"

#define SLEEP_TIME 5
#define FILE_NAME_NOBBLER "_TEMP_TARGET"

class CRecentFileList;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// global variable that stores the working directory
//char workDir[PATHBUFFER_SIZE];


//CTransferToTargetDialog * CDrawGUIApp::c_pTransferToTargetDialog;
//CTgtTransProgDlog * CDrawGUIApp::c_pTgtTransProgDlog;

/////////////////////////////////////////////////////////////////////////////
// CDrawGUIApp
//CTargetTransferDlog * CDrawGUIApp::c_pTargetTransferDlog;

//class LgbZOrderDlogBar;
//LgbZOrderDlogBar		*CDrawGUIApp::c_pLgbZOrderDlogBar;

BEGIN_MESSAGE_MAP(CDrawGUIApp, CWinApp)
	//{{AFX_MSG_MAP(CDrawGUIApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP

	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
	ON_COMMAND(ID_PROJECT_OPEN, &CDrawGUIApp::OnProjectOpen)
	ON_COMMAND(ID_TEST_TESTDIALOGS, &CDrawGUIApp::OnTestTestdialogs)
	ON_COMMAND(ID_TRANSFER_OPTIONS, &CDrawGUIApp::OnTransferOptions)
	ON_COMMAND(ID_FILE_CLOSEALL, &CDrawGUIApp::OnFileCloseAll)
	ON_COMMAND(ID_HELP_LGB_REFMANUAL, &CDrawGUIApp::OnHelpLgbRefManual)
	ON_COMMAND(ID_FILE_SAVEALLGUIS, &CDrawGUIApp::OnFileSaveAllGuis)
	ON_COMMAND(ID_HELP_TUTORIALS, &CDrawGUIApp::OnHelpTutorials)
	ON_UPDATE_COMMAND_UI(ID_LAUNCH_TRANSFER_DLG, &CDrawGUIApp::OnUpdateLaunchTransfer)
	ON_COMMAND(ID_PROJECT_CLOSE, &CDrawGUIApp::OnProjectClose)
	ON_COMMAND(ID_FILE_LAYOUTMANAGER, &CDrawGUIApp::OnFileLayoutmanager)
	ON_UPDATE_COMMAND_UI(ID_FILE_LAYOUTMANAGER, &CDrawGUIApp::OnUpdateFileLayoutManager)
	ON_UPDATE_COMMAND_UI(ID_PROJECT_CLOSE, &CDrawGUIApp::OnUpdateProjectClose)
END_MESSAGE_MAP()




/////////////////////////////////////////////////////////////////////////////
// CDrawGUIApp construction
//BOOL CDrawGUIApp::OnOpenRecentFile(UINT nID)
//{
//	ASSERT_VALID(this);
//	ENSURE(m_pRecentFileList != NULL);

//	ENSURE_ARG(nID >= ID_FILE_MRU_FILE1);
//	ENSURE_ARG(nID < ID_FILE_MRU_FILE1 + (UINT)m_pRecentFileList->GetSize());
//	int nIndex = nID - ID_FILE_MRU_FILE1;
//	ASSERT((*m_pRecentFileList)[nIndex].GetLength() != 0);

//	TRACE(traceAppMsg, 0, _T("MRU: open file (%d) '%s'.\n"), (nIndex) + 1,
//			(LPCTSTR)(*m_pRecentFileList)[nIndex]);

//	if (OpenDocumentFile((*m_pRecentFileList)[nIndex]) == NULL)
//		m_pRecentFileList->Remove(nIndex);

//	return TRUE;
//}

CDrawGUIApp::CDrawGUIApp()
: m_bCurrentlyTransferring(false)
{ }

CDrawGUIApp::~CDrawGUIApp()
{
	delete c_pTgtTransProgressDlog;
	delete c_pTgtTransErrorDlog;
	if (c_Log.IsOpen()) {
		c_Log.Close();
	}
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDrawGUIApp object

CDrawGUIApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDrawGUIApp initialization

BOOL CDrawGUIApp::InitInstance()
{

	//AfxMessageBox("LGB::InitInstance");

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
//	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
//	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	c_bSendAllToTargetHasOccurred = false;

	// Change the registry key under which our settings are stored.
	// You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Lucid"));

	//First free the string allocated by MFC at CWinApp startup.
	//The string is allocated before InitInstance is called.
	free((void*)m_pszAppName);
	// Change the application name for AfxMessageBox
	//The CWinApp destructor will free the memory.
	m_pszAppName=_tcsdup(_T("Lucid GUI Builder"));

	LoadStdProfileSettings(10);  // Load standard INI file options (including MRU)

	//GetInstallationDir(m_csInstallationDir);

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	//CMultiDocTemplate* m_pDocTemplate;
	m_pDocTemplate = new CMultiDocTemplate(
		IDR_GUITYPE,
		RUNTIME_CLASS(CDrawGUIDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CDrawGUIView));
	AddDocTemplate(m_pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	//CCommandLineInfo cmdInfo;
	CLgbCommandLineInfo cmdInfo;

	// Fill up cmdInfo with command-line arguments.
	ParseCommandLine(cmdInfo);


	// DON'T display a new MDI child window during startup!!!
	if (cmdInfo.m_strFileName == "") {
		cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
	}

	// Dispatch commands specified on the command line
//	if (!ProcessShellCommand(cmdInfo))
//		return FALSE;

	// open log file
	c_Log.Open(LGB_LOG_FILE);

	// The main window has been initialized, so show and update it.
	if(cmdInfo.m_csFullProjectFilePath.GetLength() > 0){

		// A project HAS ben specified.

//		AfxMessageBox("project path: " + cmdInfo.m_csFullProjectFilePath);
		CString pathName = cmdInfo.m_csFullProjectFilePath + "\\..";
		m_ProjectMetaData.setProjectDir(pathName);

		if(!m_ProjectMetaData.getLock()){
			AfxMessageBox( PMD_LOCK_FAILURE_MESSAGE );
		}else{
			m_ProjectMetaData.readProjectFile(cmdInfo.m_csFullProjectFilePath);

			m_ProjectMetaData.releaseLock();
			setProjMetaData( &m_ProjectMetaData );

			CString dum1, dum2;
			m_ProjectMetaData.getProjectDir(dum1);
			m_ProjectMetaData.getProjectName(dum2);	
			//m_pMainWnd->SetWindowTextA(dum1 + "\\" + dum2 );
			pMainFrame->ShowWindow(m_nCmdShow);
			pMainFrame->SetWindowTextA( dum1 + "\\" + dum2 );
			pMainFrame->UpdateWindow();

			if(!CheckExecutableFolderContextIsOk()){
				AfxMessageBox("The LucidGUIBuilder executable is NOT in a valid location.\nPlease seek support from nCapsa");
				return false;	
			}

			// Has any given layout been specified?

			if(cmdInfo.m_csLayoutFilePath.GetLength() > 0){

				//Yes!  Open just this layout
				OpenDocumentFile( cmdInfo.m_csLayoutFilePath );

			}else{

				//No - open all active layouts
				openActiveLayouts();
			}
		}

	} else {

		pMainFrame->ShowWindow(m_nCmdShow);
		pMainFrame->SetWindowTextA( LGB_APP_NAME + NO_PROJECT_WARNING );
		pMainFrame->UpdateWindow();
	}

	// Load the fonts
	LgbTextIcon xTextIcon;
	xTextIcon.LoadFonts();
	
	LucidTcpipClient tcpClient;

	//c_pTransferToTargetDialog = new CTransferToTargetDialog();
	c_pTgtTransProgressDlog = new CTgtTransProgDlog();
	c_pTgtTransErrorDlog = new CTransferErrorDlog();

	assert( NULL != c_pTgtTransProgressDlog );
	assert( NULL != c_pTgtTransErrorDlog);

	c_pTgtTransProgressDlog->Create( _T("IDD_TARGET_TRANSFER_PROGRESS") );	//CTransferAppDialog::IDD );
	c_pTgtTransErrorDlog->Create( IDD_TRANSFER_ERROR );				//CTransferAppDialog::IDD );

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	//afx_msg void OnStnClickedStatic2();
public:
	afx_msg void OnStnClickedVersionDlg2();
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
	//ON_STN_CLICKED(IDC_STATIC2, &CAboutDlg::OnStnClickedStatic2)
	//ON_STN_CLICKED(ID_VERSION_DLG2, &CAboutDlg::OnStnClickedVersionDlg2)
END_MESSAGE_MAP()

// App command to run the dialog
void CDrawGUIApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CDrawGUIApp commands

void CDrawGUIApp::OnProjectClose()
{
	processProjectClosure();
	m_ProjectMetaData.setProjectToNull();
	m_pMainWnd->SetWindowTextA(NO_PROJECT_WARNING);

	c_bSendAllToTargetHasOccurred = false;
}


void CDrawGUIApp::openActiveLayouts()
{	

	vector<CString> tags;
	//CString layoutHostName;
	GuiFileEssentialData_t essData;


	m_ProjectMetaData.getScreenTags( tags );

	for(int layout=0;layout<tags.size();layout++){

		essData.screenTag = tags[layout];

		m_ProjectMetaData.getActiveLayout( essData.screenTag, essData.fileHostNameStub );

		// Build up full path of file to be opened.

		CString dummyPath = "";
		CString cs1 = "";

		m_ProjectMetaData.getProjectDir( cs1 );
		dummyPath += cs1;
		dummyPath += "\\DeviceData\\GUI\\";
		dummyPath += essData.fileHostNameStub;
		dummyPath += ".gui";

		CDrawGUIDoc* pGuiDocJustOpened = ( CDrawGUIDoc* ) AfxGetApp( )->
			OpenDocumentFile( dummyPath );

	// Set some document metadata for future reference eg transfer to target.
/*
		((CDrawGUIDoc *)pGuiDocJustOpened)->m_csHostFileNameStub = essData.fileHostNameStub;
		((CDrawGUIDoc *)pGuiDocJustOpened)->m_csFullHostFileName = essData.fileHostNameStub + ".gui";

		pGuiDocJustOpened->m_csScreenTag = essData.screenTag;

		CString targetFileName;
		m_ProjectMetaData.
			getTargetFileNameForGuiHostFileName(essData.fileHostNameStub, targetFileName);

		((CDrawGUIDoc *)pGuiDocJustOpened)->m_csTargetFileName = targetFileName;
*/
		POSITION pos = pGuiDocJustOpened->GetFirstViewPosition();
		CDrawGUIView *pView = ( CDrawGUIView * )pGuiDocJustOpened->GetNextView(pos);
		pView->LoadSODL();
		pView->BringWindowToTop();

	} // while(it != m_vCurrentSelections.end() )

}



void CDrawGUIApp::OnProjectOpen()
{	

	// Get current project, if any...
	CString oldFullProjPath;

	if(m_ProjectMetaData.projectIsSet())
		m_ProjectMetaData.getFullPathProjectFile( oldFullProjPath );
	else
		oldFullProjPath = "";

	// 1st show the user the project dialog.  Do this 1st, cos the user
	// may decide to cancel the dlog once it appears, and if she does so
	// won't want anything further to happen.
	LucidErrEnum err = m_ProjectMetaData.showOpenProjectDialog();

	if(err == kErr_NoErr ){

		// The user didn't cancel the dialog.

		if( m_ProjectMetaData.projectIsSet() ) {
			// It should always be, if the user didn't cancel !!!

			CString newFullProjPath = "";
			m_ProjectMetaData.getFullPathProjectFile( newFullProjPath );

			// Continue only if new proj is different from old proj.
			bool projectsAreDifferent = ( newFullProjPath != oldFullProjPath );

			if(projectsAreDifferent){
				
				processProjectClosure();

				CString dum1, dum2;
				m_ProjectMetaData.getProjectDir(dum1);
				m_ProjectMetaData.getProjectName(dum2);	
				m_pMainWnd->SetWindowTextA(dum1 + "\\" + dum2 );

			}

			// Set copy of PMD in aplication class.
			//CLabLgbBaseApp *pApp = (  )AfxGetApp();
			//pApp->
			setProjMetaData( &m_ProjectMetaData );

			// Show layout mgr even if new project is the same as old project.
			if(!m_ProjectMetaData.getLock()){
				AfxMessageBox( PMD_LOCK_FAILURE_MESSAGE );
			}else{
				m_ProjectMetaData.readProjectFile();
				ProjectFileManagerDialog dlog(&m_ProjectMetaData);
				dlog.DoModal();
				m_ProjectMetaData.releaseLock();
			}
			
		} // if(err == kErr_NoErr )

	} // if(notCancelled)
}

bool CDrawGUIApp::processProjectClosure()
{	
	bool notCancelled		= true;

	//Is a project currently open?
	if(m_ProjectMetaData.projectIsSet() ){

		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		// A project IS currently open
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
		if(anyDocsHaveUnsavedChanges()){

			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			// There ARE unsaved changes
			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

			bool yesToAll	= false;

			POSITION pos = m_pDocTemplate->GetFirstDocPosition();
			CDrawGUIDoc* pDoc = NULL;

			while ( pos && !yesToAll && notCancelled ) {

				pDoc = (CDrawGUIDoc*) m_pDocTemplate->GetNextDoc(pos);
				if(pDoc->IsModified()){

					CYesY2ANoCnclDlog dlog(pDoc->m_csFullHostFileName);

					int dum = dlog.DoModal();

					if(dum==IDC_BUTTON_YES2ALL){

						yesToAll = true;
						// save this doc
						pDoc->OnSaveDocument(pDoc->GetPathName());
						pDoc->OnCloseDocument();

						// save subsequent docs ...
						while (pos) {
							pDoc = (CDrawGUIDoc*) m_pDocTemplate->GetNextDoc(pos);
							pDoc->OnSaveDocument(pDoc->GetPathName());
							pDoc->OnCloseDocument();
						}

					}else if(dum==IDC_BUTTON_YES){

						pDoc->OnSaveDocument(pDoc->GetPathName());
						pDoc->OnCloseDocument();

					}else if(dum==IDC_BUTTON_NO){

						pDoc->OnCloseDocument();

					}else if(dum==IDC_BUTTON_CANCEL){
						notCancelled = false;
					}

				} else { // if(pDoc->IsModified())

					// Close the doc anyway if not modded
					pDoc->OnCloseDocument();

				}

			}

			// We've got thru the closure process without the user 'cancelling'
			// so set the project to NULL.
			//if(notCancelled){
			//	m_ProjectMetaData.setProjectToNull();
			//}	

		} else { // if(anyDocsHaveUnsavedChanges())

			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			// There are NO unsaved changes
			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

			//COkCnclDlog dlog("Project will be closed ...");
			//if(dlog.DoModal() == IDOK){	

				CloseAllDocuments(true);
				//m_ProjectMetaData.setProjectToNull();
			//}else{

				notCancelled = true;
			//}

		} // if( !anyDocsHaveUnsavedChanges())

	} // if(m_ProjectMetaData.m_bProjectIsSet())

	return notCancelled;

}

void CDrawGUIApp::OnTestTestdialogs()
{
//	CDialogTester dlog;
//	dlog.DoModal();
}



void CDrawGUIApp::OnTransferOptions()
{
	LucidTcpipClient tcpClient;
	tcpClient.ConfigDlg();

	//Assume new target is now connected, so set flag to say 'no transfer of all' yet done
	CDrawGUIApp *pApp = ( CDrawGUIApp * ) AfxGetApp();
	pApp->c_bSendAllToTargetHasOccurred = false;
}

CDocument* CDrawGUIApp::OpenDocumentFile( LPCTSTR lpszFileName )
{

	CString	csProjectFilePath;
	CString	csLayoutFilePath;
	CString csIncoming = CString(lpszFileName);

	// Parse the string, to see if it has a # in the middle.  If so, assume it is a project-path
	// followed by a layout name.  whatever, parse its contents.
//	AfxMessageBox("open document:[" + CString(lpszFileName) + "]");
	int iPos;
	if( (iPos = csIncoming.Find("#")) != -1 ){

		// Ensure something is to right of the #
		assert( iPos < (csIncoming.GetLength() -1 ) );

		csProjectFilePath = csIncoming.Left(iPos);

		int rPos = csIncoming.GetLength() - iPos -1;
		csLayoutFilePath = csIncoming.Right( rPos );

	}else if(csIncoming.Right(4) == ".lpj" ){

		csProjectFilePath = csIncoming;
		csLayoutFilePath = "";

	}else if(csIncoming.Right(4) == ".gui" ){

		csProjectFilePath = "";
		csLayoutFilePath = csIncoming;

	}else{

		csProjectFilePath = "";
		csLayoutFilePath = "";
	}

//	AfxMessageBox("csProjectFilePath:[" + CString(csProjectFilePath) + "]\ncsLayoutFilePath:[" + CString(csLayoutFilePath) + "]");


	int mruOrigSize = m_pRecentFileList->GetSize();

	// Create an array-type ref for the MRU names, for easy indexing.
	CString *refRecentNames = m_pRecentFileList->m_arrNames;

	// Create a temp holder for the strings
	CString *arrNameStore = new CString[mruOrigSize];

// Load the MRU strings into a store and remove them from the actual list.
// Do this because otherwise the parent CWinApp::OpenDocumentFile call will
// screwed up by adding a '.gui' type string to the list.

	for(int count=0;count<mruOrigSize;count++){
		arrNameStore[count] = refRecentNames[count];
	}

	for(int count=0;count<mruOrigSize;count++){
		m_pRecentFileList->Remove(count);
	}

	CDrawGUIDoc *pDoc = (CDrawGUIDoc *) 99; // If no doc opened, null return value causes the MRU item to be removed.



	if(csProjectFilePath.GetLength() > 0){

		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		// INCOMING PROJECT IS NON-NULL
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


		CString oldFullProjPath;

		bool openNewProject;

		if(m_ProjectMetaData.projectIsSet()) {

			m_ProjectMetaData.getFullPathProjectFile( oldFullProjPath );

			// Continue only if new proj is different from old proj.
			bool projectsAreDifferent = ( csProjectFilePath != oldFullProjPath );

			if(projectsAreDifferent){
				
				// Close the old project
				processProjectClosure();

				openNewProject = true;

			}else{

				openNewProject = false;
			}

		} else {

			openNewProject = true;

		}

		if(openNewProject){

			CString pathName = csProjectFilePath + "\\..";
			m_ProjectMetaData.setProjectDir(pathName);

			if(!m_ProjectMetaData.getLock()){

				AfxMessageBox( PMD_LOCK_FAILURE_MESSAGE );

			}else{
				// Open the new project
				LucidErrEnum err = m_ProjectMetaData.readProjectFile(csProjectFilePath);
				assert( err == kErr_NoErr);

				// Set the main wnd title
				CString dum1, dum2;
				m_ProjectMetaData.getProjectDir(dum1);
				m_ProjectMetaData.getProjectName(dum2);	
				m_pMainWnd->SetWindowTextA(dum1 + "\\" + dum2 );

				m_ProjectMetaData.releaseLock();

				CLabLgbBaseApp *pApp = ( CLabLgbBaseApp * ) AfxGetApp();
				pApp->setProjMetaData( &m_ProjectMetaData );
			}

		}

	} // if(csProjectFilePath.GetLength() > 0)

	// AfxMessageBox("33");

	if(csLayoutFilePath.GetLength() > 0){

		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		// INCOMING LAYOUT IS NON-NULL
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

		CDrawGUIApp *pApp = ( CDrawGUIApp *  )AfxGetApp();

		CDocTemplate *pDocTemplate = pApp->m_pDocTemplate;
		POSITION pos = pDocTemplate->GetFirstDocPosition();

		CString csHostFileName, csHostFileNameStub;
		int iPos = csLayoutFilePath.ReverseFind( '\\' );
		csHostFileName = csLayoutFilePath.Right( csLayoutFilePath.GetLength() - iPos - 1);
		csHostFileNameStub = csHostFileName.Left( csHostFileName.GetLength() - 4);

		bool bDocAlreadyOpen = false;

		// Loop through all ope docuents, intialising each one's clash-flag to false.
		while (pos && !bDocAlreadyOpen ){
			pDoc = (CDrawGUIDoc *) pDocTemplate->GetNextDoc(pos);
			if(csLayoutFilePath.Right( pDoc->m_csFullHostFileName.GetLength() ) == pDoc->m_csFullHostFileName )
				bDocAlreadyOpen = true;
		}


		if( !bDocAlreadyOpen ){

			pDoc = ( CDrawGUIDoc * )CWinApp::OpenDocumentFile(csLayoutFilePath);

			pDoc->InitialiseProjectMetas( &m_ProjectMetaData );

			LucidErrEnum err;

			ExtGuiFile egf;
			err = m_ProjectMetaData.getGuiFileByName( csHostFileNameStub, egf );
			assert(kErr_NoErr==err);


		// Set some document metadata for future reference eg transfer to target.

			pDoc->m_csHostFileNameStub = csHostFileNameStub;
			pDoc->m_csFullHostFileName = csHostFileName;

			err = egf.getScreenTag(pDoc->m_csScreenTag);
			assert(kErr_NoErr==err);

			CString targetFileName;
			err = m_ProjectMetaData.
				getTargetFileNameForGuiHostFileName(csHostFileNameStub, targetFileName);
			assert(kErr_NoErr==err);

			pDoc->m_csTargetFileName = targetFileName;


			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			//Setup the undo /redo store for this view
			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

			POSITION pos = pDoc->GetFirstViewPosition();
			CDrawGUIView* pView = (CDrawGUIView*) pDoc->GetNextView(pos);

			CString csStorageFileStub;
			m_ProjectMetaData.getProjectDir( csStorageFileStub );
			csStorageFileStub += LGB_TEMPDIR;


			// Create a unique ID for this layout's undo stores
			GUID guid;
			HRESULT hRes = CoCreateGuid(&guid);
			assert( hRes == S_OK );

			CString csDum = intToString(guid.Data1)+ "-";
			csDum += intToString(  guid.Data2)+ "-";
			csDum += intToString(guid.Data3)+ "-";
			csDum += intToString( (int) guid.Data4) + "__";

			csStorageFileStub += csDum;
			pView->m_cLgbUndoStore.init( );


			pView->LoadGUIInfFromGuiFile(pDoc->GetPathName());
			pView->resetUndoStore();


			for(int count=0;count<m_pRecentFileList->GetSize();count++){
				m_pRecentFileList->Remove(count);
			}

			// last of all update the gui based on the sodl
			pView->LoadSODL();


		}

	} //if(csLayoutFilePath.GetLength() > 0)

	else{

		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		// INCOMING LAYOUT IS NULL
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		openActiveLayouts();
	}


	for(int count=mruOrigSize-1;count>=0;count--){
		if(arrNameStore[count].GetLength()){
			m_pRecentFileList->Add(arrNameStore[count]);
		}
	}

	CMainFrame *pMainFrm = ( CMainFrame * ) AfxGetApp()->m_pMainWnd;
	pMainFrm->resetChildTitles();

	CString cStr1;
	m_ProjectMetaData.getFullPathProjectFile(cStr1);
	addProjectToMRUList(cStr1);

	delete[] arrNameStore;

	return pDoc;

}

BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	//this->SetDlgItemTextA( ID_VERSION_DLG, ID_VERSION );
	this->SetDlgItemTextA( ID_REVISION_DLG, LGB_REVISION_ID );
	return TRUE;  // return TRUE unless you set the focus to a control
}


void CDrawGUIApp::OnFileCloseAll()
{
	BOOL endSession = FALSE;
	SaveAllModified();
	CloseAllDocuments(endSession);
}

void CDrawGUIApp::OnHelpLgbRefManual()
{
	openDocInBackground( kLgbRefManual );
}

void CDrawGUIApp::OnHelpTutorials()
{
	openDocInBackground( kLgbLabTutorial );
}

void CDrawGUIApp::OnFileSaveAllGuis()
{
	CString csPathName;

	// update the list of font files in the project
	// TODO this is a quick fix for now and needs a better implementation
	if(!m_ProjectMetaData.getLock()){
		AfxMessageBox( PMD_LOCK_FAILURE_MESSAGE );
	}else{
		m_ProjectMetaData.readProjectFile();
		m_ProjectMetaData.RemoveAllBdfFiles();
		m_ProjectMetaData.writeProjectFile();
	}
	m_ProjectMetaData.releaseLock();

	// force all GUIs to be saved
	POSITION pos = m_pDocTemplate->GetFirstDocPosition();

	CDrawGUIDoc* pDoc = NULL;

	while (pos) {
		pDoc = (CDrawGUIDoc*) m_pDocTemplate->GetNextDoc(pos);
		pDoc->SetModifiedFlag(true);
		csPathName = pDoc->GetPathName();
		pDoc->OnSaveDocument(csPathName);
	}

	//SaveAllModified();
}

void CAboutDlg::OnStnClickedVersionDlg2()
{
	// TODO: Add your control notification handler code here
}

void CDrawGUIApp::OnUpdateLaunchTransfer(CCmdUI *pCmdUI)
{
	
	// Disable transfer to target button if no documents open.

	CDocTemplate *pDocTemplate = this->m_pDocTemplate;

	POSITION pos = pDocTemplate->GetFirstDocPosition();

	pCmdUI->Enable((pos!=NULL) && !m_bCurrentlyTransferring);
}

void CDrawGUIApp::AddToRecentFileList(LPCTSTR lpszPathName)
{
	// TODO: Add your specialized code here and/or call the base class

	CString cstr(lpszPathName);
	if(cstr.Right(4) == ".lpj"){
		CLabLgbBaseApp::AddToRecentFileList(lpszPathName);
	}
}

CDrawGUIDoc * CDrawGUIApp::getActiveDoc(void)
{
	CDrawGUIDoc *pDoc = NULL;
	CDocTemplate *pDocTemplate = this->m_pDocTemplate;
	POSITION pos = pDocTemplate->GetFirstDocPosition();
	pDoc = (CDrawGUIDoc *) this->m_pDocTemplate->GetNextDoc(pos);
	return pDoc;

}

bool CDrawGUIApp::anyDocsHaveUnsavedChanges(void)
{
	POSITION pos = m_pDocTemplate->GetFirstDocPosition();

	CDrawGUIDoc* pDoc = NULL;

	while (pos) {
		pDoc = (CDrawGUIDoc*) m_pDocTemplate->GetNextDoc(pos);
		if(pDoc->IsModified()) return true;
	}

	return false;
}

void CDrawGUIApp::OnFileLayoutmanager()
{
	if(!m_ProjectMetaData.getLock()){

		AfxMessageBox( PMD_LOCK_FAILURE_MESSAGE );

	}else{

		m_ProjectMetaData.readProjectFile();

		ProjectFileManagerDialog dlog(&m_ProjectMetaData);
		dlog.DoModal();
		m_ProjectMetaData.writeProjectFile();

		m_ProjectMetaData.releaseLock();

	}
}

void CDrawGUIApp::OnUpdateFileLayoutManager(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( m_ProjectMetaData.projectIsSet() );
}

void CDrawGUIApp::OnUpdateProjectClose(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( m_ProjectMetaData.projectIsSet() );
}
