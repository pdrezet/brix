// ProjFileMgrDlog.cpp : implementation file
//

#include "stdafx.h"
#include <cassert>
#include <vector>
#include <algorithm>
#include <fstream>
#include "../common/LucidTypedefs.h"
#include "LucidEnums.h"
#include "ProjectFileManagerDialog.h"
#include "MainFrm.h"
#include "DeleteGUIFileDlog.h"
#include "CreateGUIFileDlog.h"
#include "CopyGuiFileDlog.h"
#include "../common/ScreenTagDialog.h"
#include "DrawGUI.h"
#include "DrawGUIDoc.h"
#include "DrawGUIView.h"
#include "../common/ProjectMetaData.h"
#include "../common/LucidConstants.h"
#include <afxadv.h>
#include "../LucidapplicationBuilder/FileOperations.h"


IMPLEMENT_DYNAMIC(ProjectFileManagerDialog, CDialog)

ProjectFileManagerDialog::ProjectFileManagerDialog(
	ProjectMetaData *pPMD,	CWnd* pParent /*=NULL*/)
	: CDialog(ProjectFileManagerDialog::IDD, pParent), 
	m_pProjectMetaData(pPMD)
{
}

ProjectFileManagerDialog::~ProjectFileManagerDialog()
{
}

void ProjectFileManagerDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_CLOSEPROJ_BTN, m_ctlCloseProjBtn);
	//DDX_Control(pDX, IDC_OPENPROJ_BTN, m_ctlOpenProjBtn);
	DDX_Control(pDX, IDC_DELETEFILE_BTN, m_ctlDeleteFileBtn);
	DDX_Control(pDX, IDC_NEWFILE_BTN, m_ctlNewFileBtn);
	DDX_Control(pDX, IDC_TAGDLOG_BTN, m_ctlScreenTagDlogBtn);
	//DDX_Control(pDX, IDC_OPENFILE_BTN, m_ctlOpenFileBtn);
	//DDX_Control(pDX, IDC_SCREEN_LIST, m_ctlScreenList);
	//DDX_Control(pDX, IDC_FILE_LIST, m_ctlFileList);
	//DDX_Control(pDX, IDC_SCREEN_DESCRIP_LIST, m_ctlScreenDesrcripList);
	//DDX_Control(pDX, IDC_FILE_DESCRIP_LIST, m_ctlFileDescripList);
	DDX_Control(pDX, IDC_COPY_BTN, m_ctlCopyBtn);
	DDX_Control(pDX, ID_OPEN_THEN_DISMISS, m_ctlOpenThenDismissBtn);
	DDX_Control(pDX, IDC_TAB_WIDGETGRP_TAB, m_ctlTab_WidgetGroups);
	DDX_Control(pDX, IDC_LISTCTRL_LAYOUTS, m_ctlListC_Layouts);
}


BEGIN_MESSAGE_MAP(ProjectFileManagerDialog, CDialog)
	//ON_BN_CLICKED(IDC_OPENPROJ_BTN, &ProjectFileManagerDialog::OnBnClickedOpenprojBtn)
	//ON_BN_CLICKED(IDC_CLOSEPROJ_BTN, &ProjectFileManagerDialog::OnBnClickedCloseprojBtn)
	ON_BN_CLICKED(IDC_NEWFILE_BTN, &ProjectFileManagerDialog::OnBnClickedNewfileBtn)
	ON_BN_CLICKED(IDC_TAGDLOG_BTN, &ProjectFileManagerDialog::OnBnClickedTagdlogBtn)
	ON_BN_CLICKED(IDC_DELETEFILE_BTN, &ProjectFileManagerDialog::OnBnClickedDeletefileBtn)
	//ON_BN_CLICKED(IDC_OPEN_BTN, &ProjectFileManagerDialog::OnBnClickedOpenBtn)
	ON_BN_CLICKED(IDC_COPY_BTN, &ProjectFileManagerDialog::OnBnClickedCopyBtn)
	ON_LBN_SELCHANGE(IDC_FILE_LIST, &ProjectFileManagerDialog::OnLbnSelchangeFileList)
	ON_LBN_DBLCLK(IDC_FILE_LIST, &ProjectFileManagerDialog::OnLbnDblclkFileList)
	ON_BN_CLICKED(ID_DISMISS, &ProjectFileManagerDialog::OnBnClickedDismiss)
	ON_BN_CLICKED(ID_OPEN_THEN_DISMISS, &ProjectFileManagerDialog::OnBnClickedOpenThenDismiss)
	//ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_WIDGETGRP_TAB, &ProjectFileManagerDialog::OnTcnSelchangeTabWidgetgrpTab)
	ON_NOTIFY(NM_CLICK, IDC_LISTCTRL_LAYOUTS, &ProjectFileManagerDialog::OnNMClickListctrlLayouts)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_OPENALLACTIVE, &ProjectFileManagerDialog::OnBnClickedOpenAllActive)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_WIDGETGRP_TAB, &ProjectFileManagerDialog::OnTcnSelchangeTabWidgetgrpTab)
END_MESSAGE_MAP()


// ProjectFileManagerDialog message handlers

void ProjectFileManagerDialog::OnBnClickedOpenprojBtn()
{

	// Record present project to tell if it has changed.
	CString csPreviousProjFullPath, csPresentProjFullPath;

	if(m_pProjectMetaData->projectIsSet()){

		m_pProjectMetaData->getFullPathProjectFile(csPreviousProjFullPath);
	}else { //if !(m_pProjectMetaData->projectIsSet())

		csPreviousProjFullPath = "";
	}


	// Show the 'open project' dialog:
	m_pProjectMetaData->showOpenProjectDialog();

	// The user may have cancelled or OK'd the dialog. 
	// If she cancelled it, and if the project wasn't set before it
	// opened, the project may still not be set.
	//
	// If she OK'd it, then the project might be changed, or it might be
	// still be the same proj (!).

	if(m_pProjectMetaData->projectIsSet()){

		// Detect if project has changed.
		m_pProjectMetaData->getFullPathProjectFile(csPresentProjFullPath);

		if(csPreviousProjFullPath != csPresentProjFullPath){
			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			// The required project is NOT the one currently open in this instance
			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!

			if(csPreviousProjFullPath.GetLength()){
				//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				// There WAS a project already loaded before project 
				// dlog chose a new one
				// We therefore need a new LGB instance for the new project.
				//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


				CString execName;
				((CDrawGUIApp *)AfxGetApp())->GetExecutableName(execName);

				//CString appName = "c:\\Lucid2\\tools\\LucidGUIBuilder\\Debug\\LucidGUIBuilder.exe";
				CString fullPath = csPresentProjFullPath;
				
				// Surround with quotes.
				fullPath = "\"" + fullPath + "\"";

					ShellExecute(
					NULL, 
					NULL, 
					execName,
					fullPath, 
					NULL, 
					SW_SHOW);

					// Dismiss this dialog.
					OnOK();

			} else {
				//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				// There WASN'T a project already loaded before project 
				// dlog chose a new one - open the new proj in this instance
				//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!		

				CString dummy1(PROJFILEMGRDLOG_FRAME_STUB_CAPTION);

				CString dummy2;
				m_pProjectMetaData->getProjectDir(dummy2);

				CString dummy3;
				m_pProjectMetaData->getProjectName(dummy3);

				this->SetWindowText(dummy1 + dummy2 + "::" + dummy3);

				//m_ctlCloseProjBtn.EnableWindow(true);
				//m_ctlOpenProjBtn.EnableWindow(true);
				m_ctlNewFileBtn.EnableWindow(true);
				m_ctlScreenTagDlogBtn.EnableWindow(true);
				m_ctlCopyBtn.EnableWindow(false);
				m_ctlDeleteFileBtn.EnableWindow(false);
				//m_ctlOpenFileBtn.EnableWindow(false);

			} 

		} // if(csPreviousProjFullPath != csPresentProjFullPath)

	}else{ // if !(m_pProjectMetaData->projectIsSet())

		//m_ctlCloseProjBtn.EnableWindow(false);
		//m_ctlOpenProjBtn.EnableWindow(true);
		m_ctlNewFileBtn.EnableWindow(false);
		m_ctlScreenTagDlogBtn.EnableWindow(false);
		m_ctlCopyBtn.EnableWindow(false);
		m_ctlDeleteFileBtn.EnableWindow(false);
		//m_ctlOpenFileBtn.EnableWindow(false);

		CString dummy1(PROJFILEMGRDLOG_FRAME_STUB_CAPTION);
		CString dummy2(PROJFILEMGRDLOG_NULL_PROJ_STR);
		this->SetWindowText(dummy1 + "::" + dummy2);
	}

	//m_pProjectMetaData->getGuiFiles(m_vContents);
	updateDisplayWithUnderlyingData();

}

void ProjectFileManagerDialog::OnBnClickedCloseprojBtn()
{

	POSITION pos;

	CDocTemplate *pDocTemplate = NULL;

	pDocTemplate = ((CDrawGUIApp *) AfxGetApp( ))->m_pDocTemplate;
//		pos = afxGetpDocTemplate->GetFirstDocPosition();

	pos = pDocTemplate->GetFirstDocPosition();

	CDrawGUIDoc* pDoc = NULL;
	int filesOpenCount = 0;

	// Check no files open.

	while (pos) {
		pDoc = (CDrawGUIDoc*) pDocTemplate->GetNextDoc(pos);
		filesOpenCount++;
	}

	if(filesOpenCount){

		AfxMessageBox("Please close files before closing the project");

	}else{ // if(!filesOpenCount)

		m_pProjectMetaData->setProjectToNull();
		updateDisplayWithUnderlyingData();

		//m_ctlCloseProjBtn.EnableWindow(false);
		//m_ctlOpenProjBtn.EnableWindow(true);
		m_ctlScreenTagDlogBtn.EnableWindow(false);
		m_ctlNewFileBtn.EnableWindow(false);

		CString dummy1(PROJFILEMGRDLOG_FRAME_STUB_CAPTION);
		CString dummy2(PROJFILEMGRDLOG_NULL_PROJ_STR);
		this->SetWindowText(dummy1 + "::" + dummy2);

		//m_pProjectMetaData->getGuiFiles(m_vContents);
		updateDisplayWithUnderlyingData();

	} // if(!filesOpenCount)

}


void ProjectFileManagerDialog::OnBnClickedNewfileBtn()
{
	CCreateGuiFileDlog dlog(m_pProjectMetaData, getCurrentTabLabel() );

	if( dlog.DoModal() == IDOK){

		GuiFileEssentialData_t fileData;

		if(dlog.getGuiFileEssentials( fileData )== kErr_NoErr){

			if(m_pProjectMetaData->fileInProject( fileData.fileHostNameStub )){
				AfxMessageBox("File is already in this project!");
			}

			// add the guiFile to project
			LucidErrEnum err = m_pProjectMetaData->addGuiFile( fileData, true );

			// write project data to disk
			err = m_pProjectMetaData->writeProjectFile();
			assert( err == kErr_NoErr );

			// update this dialog
			updateDisplayWithUnderlyingData( m_ctlTab_WidgetGroups.GetCurSel() );

		}
	}
}


void ProjectFileManagerDialog::OnBnClickedTagdlogBtn()
{
//	LucidErrEnum err = m_pProjectMetaData->readProjectFile();
	//assert(err == kErr_NoErr);

	CScreenTagDialog dlog(m_pProjectMetaData);

	if( IDOK == dlog.DoModal() )
		updateDisplayWithUnderlyingData();

}


void ProjectFileManagerDialog::OnBnClickedDeletefileBtn()
{

	UpdateData();

	if(somethingIsSelected() ){ // something is selected

		int selCount= loadCurrentSelections();
		bool doDeletion = true;
		GuiFileEssentialData_t *pEssData = NULL;
		CString activeLayoutHostName;
		CString layoutHostName;

		// Get all the selections ...
		for(size_t seln=0;seln<m_vCurrentSelections.size();seln++ ){

			pEssData = &(m_vCurrentSelections[seln]);

			// Get name of 'active' layout
			LucidErrEnum err =
				m_pProjectMetaData->getActiveLayout( pEssData->screenTag, activeLayoutHostName );

			assert( kErr_NoErr == err );

			if( pEssData->fileHostNameStub == activeLayoutHostName){

				AfxMessageBox("This is the active file for this Widget-Group.\nIt should therefore not be deleted");
				doDeletion = false;

			} else { // if(selFileName == pDoc->m_csHostFileNameStub)

				// get user to confirm deletion
				CDeleteGUIFileDlog dlog(pEssData->fileHostNameStub);

//				GuiFileMonty_t *pGFM;

				int i=dlog.DoModal();

				if(i==IDOK){

					CDrawGUIDoc* pDoc = NULL;
					POSITION pos;


					CDocTemplate *pDocTemplate = NULL;

					pDocTemplate = ((CDrawGUIApp *) AfxGetApp( ))->m_pDocTemplate;
					pos = pDocTemplate->GetFirstDocPosition();

					while (pos  && doDeletion ) {

						pDoc = (CDrawGUIDoc*) pDocTemplate->GetNextDoc(pos);

						if( pDoc->m_csHostFileNameStub == pEssData->fileHostNameStub ){
							AfxMessageBox("This file is open, and therefore cannot be deleted");
							doDeletion = false;
						} // if(selFileName == pDoc->m_csHostFileNameStub)	
					} // while (pos) 

				}

				if(doDeletion){

					// remove file from project.
					LucidErrEnum err = m_pProjectMetaData->removeGuiFile(ExtGuiFile(pEssData->fileHostNameStub));
					assert(err==kErr_NoErr);

					// remove file from local display
					/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					vector<GuiFileMonty_t>::iterator it2 = m_vContents.begin();
					while(it2 != m_vContents.end()){
						pGFM = &(*it2);
						if(pGFM->fileHostNameStub == pEssData->fileHostNameStub){

							m_vContents.erase(it2);
							break;
						}
						it2++;
					} // while(it != m_vContents.end())
					!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

					// Perform file system delete.
					CFileOperation fo;
					CString srcFile  = "";

					m_pProjectMetaData->getProjectDir( srcFile );
					srcFile += "\\DeviceData\\GUI\\";
					srcFile += pEssData->fileHostNameStub + ".gui";

					fo.Delete( srcFile );

				} // if(doDeletion)

				// write project data to proj file.
				err = m_pProjectMetaData->writeProjectFile();
				assert( err == kErr_NoErr );



			} // if(i==IDOK)

		} // while(it != m_vCurrentSelections.end() )

	} // if(int selCount

	updateDisplayWithUnderlyingData( m_ctlTab_WidgetGroups.GetCurSel() );
}

BOOL ProjectFileManagerDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctlListC_Layouts.setProjMgrDlog( this );

	m_ctlTab_WidgetGroups.m_pProjectFileManagerDialog = this;

	ListView_SetExtendedListViewStyle(m_ctlListC_Layouts.m_hWnd,
                                  LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_INFOTIP);

	// (De-) Activate the file buttons:

	m_ctlDeleteFileBtn.EnableWindow(false);
	//m_ctlOpenFileBtn.EnableWindow(false);
	m_ctlCopyBtn.EnableWindow(false);


	setupListColumns(); // ie layout name, layout description, etc

	if( m_pProjectMetaData->projectIsSet() ){

		CString dummy1(PROJFILEMGRDLOG_FRAME_STUB_CAPTION);
		CString dummy2;
		m_pProjectMetaData->getProjectDir(dummy2);
		CString dummy3;
		m_pProjectMetaData->getProjectName(dummy3);


		this->SetWindowText(dummy1 + dummy2 + "::" + dummy3);


		//m_ctlOpenProjBtn.EnableWindow(true);
		//m_ctlCloseProjBtn.EnableWindow(true);
		m_ctlNewFileBtn.EnableWindow(true);
		m_ctlScreenTagDlogBtn.EnableWindow(true);

		//setupTabs();
		//setupListColumns(); // ie layout name, layout description, etc

		updateDisplayWithUnderlyingData();

	} else {

		CString dummy1(PROJFILEMGRDLOG_FRAME_STUB_CAPTION);
		CString dummy2(PROJFILEMGRDLOG_NULL_PROJ_STR);
		this->SetWindowText(dummy1 + "::" + dummy2);

		m_ctlNewFileBtn.EnableWindow(false);
		m_ctlScreenTagDlogBtn.EnableWindow(false);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void ProjectFileManagerDialog::updateDisplayWithUnderlyingData( const int &tabIndex // =-1
															   )
{

	m_ctlListC_Layouts.m_nCheckedItem = -1;
	//m_ctlTab_WidgetGroups.DeleteAllItems();

	setupTabs( tabIndex ); // These correspond to widget-groups

	// The only time this method is called with tabIndex == -1 is from initDialog.
	// Set the columns up once at this point, as they never change.  Otherwise,
	// you finish up with loads of repeated columns.
	//if(tabIndex == -1)
//		setupListColumns(); // ie layout name, layout description, etc

	loadLayoutData( ); // load up the layout data for th selcted tab ( ie widget-group)

	CString widgetGroup = getCurrentTabLabel();

	CString activeLayoutName;
	LucidErrEnum err = m_pProjectMetaData->getActiveLayout( widgetGroup, activeLayoutName);

	assert(err==kErr_NoErr);

	int nRows = m_ctlListC_Layouts.GetItemCount();
	int row = 0;

	bool keepGoing = true;

	while(keepGoing && (row<nRows) )
	{
		CString dum = m_ctlListC_Layouts.GetItemText( row, 1 );

		if( dum == activeLayoutName ) {
			m_ctlListC_Layouts.CheckItem(row);
			keepGoing = false;
		}
		row++;
	}

	// display in dlog itself.
	UpdateData(false);

	return;

}

/*
void ProjectFileManagerDialog::setFrameCaption()
{
	CString cStr1;

	if(m_pProjectMetaData->projectIsSet()){
		m_pProjectMetaData->getFullPathProjectFile(cStr1);
		((CDrawGUIApp *) AfxGetApp())->AddToRecentFileList(cStr1);
		((CDrawGUIApp *) AfxGetApp())->WriteMruList();
	}

	CWnd * m_pMainWnd = AfxGetApp()->m_pMainWnd;

	if(m_pProjectMetaData->projectIsSet()){

		CString dum, dum2;
		m_pProjectMetaData->getProjectDir(dum);
		m_pProjectMetaData->getProjectName(dum2);	
		m_pMainWnd->SetWindowTextA(LGB_APP_NAME + dum + ":" +dum2);

	} else {// if(m_ProjectMetaData.projectIsSet())

		m_pMainWnd->SetWindowTextA(LGB_APP_NAME + NO_PROJECT_WARNING);
	}

	//CDialog::OnOK();
}
*/

void ProjectFileManagerDialog::OnBnClickedOpenThenDismiss()
{

	UpdateData();
	CMainFrame *pMainFrm = ( CMainFrame * ) AfxGetApp()->m_pMainWnd;

	if( somethingIsSelected() ){ // something is selected

		int selCount = loadCurrentSelections();

		GuiFileEssentialData_t *pEssData = NULL;

		for(size_t seln=0;seln<m_vCurrentSelections.size();seln++ ){

			pEssData = &(m_vCurrentSelections[seln]);

		// Build up full path of file to be opened.

			CString dummyPath = "";
			CString cs1 = "";

			m_pProjectMetaData->getProjectDir( cs1 );
			dummyPath += cs1;
			dummyPath += "\\DeviceData\\GUI\\";
			dummyPath += pEssData->fileHostNameStub;
			dummyPath += ".gui";

			CDrawGUIDoc* pGuiDocJustOpened = ( CDrawGUIDoc* ) AfxGetApp( )->
				OpenDocumentFile( dummyPath );

		// Set some document metadata for future reference eg transfer to target.

			((CDrawGUIDoc *)pGuiDocJustOpened)->m_csHostFileNameStub = pEssData->fileHostNameStub;
			((CDrawGUIDoc *)pGuiDocJustOpened)->m_csFullHostFileName = pEssData->fileHostNameStub + ".gui";

			pGuiDocJustOpened->m_csScreenTag = pEssData->screenTag;

			CString targetFileName;
			m_pProjectMetaData->
				getTargetFileNameForGuiHostFileName(pEssData->fileHostNameStub, targetFileName);

			((CDrawGUIDoc *)pGuiDocJustOpened)->m_csTargetFileName = targetFileName;

			POSITION pos = pGuiDocJustOpened->GetFirstViewPosition();
			CDrawGUIView *pView = ( CDrawGUIView * )pGuiDocJustOpened->GetNextView(pos);
			pView->LoadSODL();

		} // while(it != m_vCurrentSelections.end() )

		// Must call this from here, NOT from (say) 'OnCreate' in CDrawGUIView,
		// as otherwise the host filename etc wouldn't be set on the doc, hence
		// frame titles wopuld be naff.

		CMainFrame *pMainFrm = ( CMainFrame * ) GetParentFrame();
		pMainFrm->resetChildTitles();

	} // 	if(int selCount=getCurrentSelectionCount() )

	pMainFrm->setFrameCaption();

	//OnOK();

}

void ProjectFileManagerDialog::OnBnClickedCopyBtn()
{

	UpdateData();

	if(somethingIsSelected() ){ // something is selected

		int selCount = loadCurrentSelections();

		GuiFileEssentialData_t *pEssData = NULL;

		//vector<GuiFileEssentialData_t>::iterator it = m_vCurrentSelections.begin();

		for(size_t seln=0;seln<m_vCurrentSelections.size();seln++ ){

			pEssData = &(m_vCurrentSelections[seln]);


			CCopyGuiFileDlog dlog(
				m_pProjectMetaData, pEssData->fileHostNameStub, pEssData->fileDescr );

			if(dlog.DoModal()==IDOK){


				if(m_pProjectMetaData->fileInProject(dlog.m_csNewFileName)){

					AfxMessageBox("File is already in this project!");

				} else {


			// File system copy operations:
					CString folder = "";
					CString srcFile  = "";
					CString dstFile = "";

					m_pProjectMetaData->getProjectDir( folder );
					folder += "\\DeviceData\\GUI\\";

					srcFile = pEssData->fileHostNameStub + ".gui";
					dstFile	 = dlog.m_csNewFileName + ".gui";


			// Now handle the project meta data.

					GuiFileEssentialData_t gED;
					gED.fileHostNameStub = dlog.m_csNewFileName;
					gED.fileDescr = dlog.m_csNewFileDescription;
					gED.screenTag    = pEssData->screenTag;
					LucidErrEnum err = m_pProjectMetaData->addGuiFile( gED, false );
					assert(  err == kErr_NoErr );

					updateDisplayWithUnderlyingData(m_ctlTab_WidgetGroups.GetCurSel() );

					CFileOperation fo;
					fo.CopyFileGood( folder, srcFile, folder, dstFile );
					err = m_pProjectMetaData->writeProjectFile(); 
					assert(err == kErr_NoErr );

				}

			} // while(it != m_vCurrentSelections.end() )

		} // if(dlog.DoModal()==IDOK)

	} // if(int selCount=getCurrentSelectionCount() )

}

void ProjectFileManagerDialog::OnLbnSelchangeFileList()
{


}

void ProjectFileManagerDialog::OnLbnDblclkFileList()
{
	//OnBnClickedOpenBtn();
}

void ProjectFileManagerDialog::OnBnClickedDismiss()
{
		// Must call this from here, NOT from (say) 'OnCreate' in CDrawGUIView,
		// as otherwise the host filename etc wouldn't be set on the doc, hence
		// frame titles wopuld be naff.

	CMainFrame *pMainFrm = ( CMainFrame * ) GetParentFrame();
	pMainFrm->resetChildTitles();
	pMainFrm->setFrameCaption();
	OnCancel();
}

int ProjectFileManagerDialog::loadCurrentSelections(void)
{

	GuiFileEssentialData_t essData;

	UpdateData();
	m_vCurrentSelections.clear();

	int nCount = 0;
	POSITION pos = m_ctlListC_Layouts.GetFirstSelectedItemPosition();

	if (pos != NULL){

		CString widgetGroup = getCurrentTabLabel();

		while (pos) {

			int nItem = m_ctlListC_Layouts.GetNextSelectedItem(pos);

			essData.fileHostNameStub	= m_ctlListC_Layouts.GetItemText( nItem, 1 );
			essData.fileDescr			= m_ctlListC_Layouts.GetItemText( nItem, 2 );
			essData.screenTag			= widgetGroup;
			m_vCurrentSelections.push_back( essData );
			nCount++;
	   }

	} // if (pos != NULL)

	return nCount;
}

bool ProjectFileManagerDialog::somethingIsSelected(void)
{
	UpdateData();

	POSITION pos = m_ctlListC_Layouts.GetFirstSelectedItemPosition();
	return (pos != NULL);
}


void ProjectFileManagerDialog::loadLayoutData()
{

	m_ctlListC_Layouts.DeleteAllItems();

	vector< GuiFileMonty_t> vGuiData;
	m_pProjectMetaData->getGuiFiles( getCurrentTabLabel(), vGuiData );

	char buff[100];

	// insert items
	LV_ITEM lvi;
	wchar_t dummyWide[100];
	size_t sz;

	for(size_t layout = 0; layout < vGuiData.size(); layout++)
	{
		//sprintf_s( buff, 100, "TabIndx %d, item i%d", tabIndex, i );
		mbstowcs_s(&sz, dummyWide, vGuiData[layout].fileHostNameStub, 100 );

		lvi.mask = LVIF_TEXT ;//| LVIF_IMAGE | LVIF_STATE;
		lvi.iItem = layout;
		lvi.iSubItem = 0;
		CString crp( buff);
		//lvi.pszText = (LPSTR) vGuiData[layout].fileHostNameStub.GetString();
		lvi.pszText = (LPSTR) "";
		lvi.iImage = layout;
		lvi.stateMask = LVIS_STATEIMAGEMASK;
		lvi.state = INDEXTOSTATEIMAGEMASK(1);

		m_ctlListC_Layouts.InsertItem(&lvi);
	}

	for(size_t layout = 0; layout < vGuiData.size(); layout++)
	{
		m_ctlListC_Layouts.SetItemText(layout, 1, vGuiData[layout].fileHostNameStub.GetString() ); 
		m_ctlListC_Layouts.SetItemText(layout, 2, vGuiData[layout].fileDescr.GetString() ); 
	}

}

void ProjectFileManagerDialog::setupListColumns()
{

	m_ctlListC_Layouts.ModifyStyle( LVS_TYPEMASK, LVS_REPORT & LVS_TYPEMASK );

	m_ctlListC_Layouts.DeleteAllItems();

	for(int col=0;col<=3;col++)
		m_ctlListC_Layouts.DeleteColumn( col );


	LVCOLUMN lvc;
	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

	lvc.iSubItem = 0;
	//lvc.pszText = _T("Layout Name (√ = 'Active')");//_gszColumnLabel[i];
	lvc.pszText = _T("Active");//_gszColumnLabel[i];
	lvc.cx = 40;//_gnColumnWidth[i];
	lvc.fmt = LVCFMT_RIGHT; //_gnColumnFmt[i];
	m_ctlListC_Layouts.InsertColumn(0,&lvc);

	lvc.iSubItem = 1;
	lvc.pszText = TEXT("Layout Name");//_gszColumnLabel[i];
	lvc.cx = 250;//_gnColumnWidth[i];
	lvc.fmt = LVCFMT_LEFT; //_gnColumnFmt[i];
	m_ctlListC_Layouts.InsertColumn(1,&lvc);

	lvc.iSubItem = 2;
	lvc.pszText = TEXT("Description");//_gszColumnLabel[i];
	lvc.cx = 200;//_gnColumnWidth[i];
	lvc.fmt = LVCFMT_LEFT; //_gnColumnFmt[i];
	m_ctlListC_Layouts.InsertColumn(2,&lvc);
}

void ProjectFileManagerDialog::setupTabs( const int &tabIndex )
{

	// InitDialog often gets called twice!  (hence this does).  delete b4 addding
	// so as not to double-up on the tabs.
	m_ctlTab_WidgetGroups.DeleteAllItems();

	vector<CString> tags;

	m_pProjectMetaData->getScreenTags( tags );

	for(size_t i=0;i<tags.size();i++)
		m_ctlTab_WidgetGroups.InsertItem( i, tags[i] );

	// if tabIndex==-1, this is being initialised, so set sel tab to 0.
	if( tabIndex != -1 )
		m_ctlTab_WidgetGroups.SetCurSel( tabIndex );
	else
		m_ctlTab_WidgetGroups.SetCurSel( 0 );
}

void ProjectFileManagerDialog::processListChange()
{
	if(somethingIsSelected()){ // something is selected

		m_ctlDeleteFileBtn.EnableWindow(true);
		m_ctlCopyBtn.EnableWindow(true);

	}else{

		m_ctlDeleteFileBtn.EnableWindow(false);
		m_ctlCopyBtn.EnableWindow(false);
	}
}

void ProjectFileManagerDialog::processTabChange(const int &tabIndex)
{
	// Reset this upon tab change, because the listCtrl is shared between all
	// tabs.  On tab change, the rows of layout data will be re-written, and we
	// mut therefore also reset this 'presently selected row' indicator
	m_ctlListC_Layouts.m_nCheckedItem = -1;

	// 
	updateDisplayWithUnderlyingData( tabIndex );

	// Do this because nothing will be selected in the new contents for this tab,
	// so we must set the 'copy' and 'delete' buttons dosabled.
	processListChange();


}

CString ProjectFileManagerDialog::getCurrentTabLabel()
{

	int selIndex = m_ctlTab_WidgetGroups.GetCurSel();

   TCITEM tcItem;
   
   //  Get the current tab item text.
   char buffer[256] = {0};
   tcItem.pszText = buffer;
   tcItem.cchTextMax = 256;
   tcItem.mask = TCIF_TEXT;
   m_ctlTab_WidgetGroups.GetItem(selIndex, &tcItem);
   
   //  Set the new text for the item.
   //m_ctlTab_WidgetGroups.pszTex = pszString.GetBuffer(256);

   return CString( tcItem.pszText );

}
void ProjectFileManagerDialog::OnNMClickListctrlLayouts(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void ProjectFileManagerDialog::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnLButtonDown(nFlags, point);
}

void ProjectFileManagerDialog::OnBnClickedOpenAllActive()
{

	CDrawGUIApp *pApp = (CDrawGUIApp *) AfxGetApp();

	pApp->openActiveLayouts();
	
	/*
	vector<CString> tags;
	//CString layoutHostName;
	GuiFileEssentialData_t essData;

	UpdateData();

	m_pProjectMetaData->getScreenTags( tags );

	for(int layout=0;layout<tags.size();layout++){

		essData.screenTag = tags[layout];

		m_pProjectMetaData->getActiveLayout( essData.screenTag, essData.fileHostNameStub );

		// Build up full path of file to be opened.

			CString dummyPath = "";
			CString cs1 = "";

			m_pProjectMetaData->getProjectDir( cs1 );
			dummyPath += cs1;
			dummyPath += "\\DeviceData\\GUI\\";
			dummyPath += essData.fileHostNameStub;
			dummyPath += ".gui";

			CDrawGUIDoc* pGuiDocJustOpened = ( CDrawGUIDoc* ) AfxGetApp( )->
				OpenDocumentFile( dummyPath );

		// Set some document metadata for future reference eg transfer to target.

			((CDrawGUIDoc *)pGuiDocJustOpened)->m_csHostFileNameStub = essData.fileHostNameStub;
			((CDrawGUIDoc *)pGuiDocJustOpened)->m_csFullHostFileName = essData.fileHostNameStub + ".gui";

			pGuiDocJustOpened->m_csScreenTag = essData.screenTag;

			CString targetFileName;
			m_pProjectMetaData->
				getTargetFileNameForGuiHostFileName(essData.fileHostNameStub, targetFileName);

			((CDrawGUIDoc *)pGuiDocJustOpened)->m_csTargetFileName = targetFileName;

			POSITION pos = pGuiDocJustOpened->GetFirstViewPosition();
			CDrawGUIView *pView = ( CDrawGUIView * )pGuiDocJustOpened->GetNextView(pos);
			pView->LoadSODL();

		} // while(it != m_vCurrentSelections.end() )

		// Must call this from here, NOT from (say) an OnCreate' in CDrawGUIView,
		// as otherwise the host filename etc wouldn't be set on the doc, hence
		// frame titles wopuld be naff.

		CMainFrame *pMainFrm = ( CMainFrame * ) GetParentFrame();
		pMainFrm->resetChildTitles();


	setFrameCaption();
*/
	OnOK();
}

void ProjectFileManagerDialog::OnTcnSelchangeTabWidgetgrpTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
}
