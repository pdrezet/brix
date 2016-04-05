// DrawGUIDoc.cpp : implementation of the CDrawGUIDoc class
//

#include "stdafx.h"
#include "DrawGUI.h"
#include "DrawGUIView.h"

#include "DrawGUIDoc.h"

#include <fstream>
#include <cassert>
using namespace std;
#include <afxdlgs.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrawGUIDoc

IMPLEMENT_DYNCREATE(CDrawGUIDoc, CDocument)

BEGIN_MESSAGE_MAP(CDrawGUIDoc, CDocument)
	//{{AFX_MSG_MAP(CDrawGUIDoc)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_IMPORT, Import)
	ON_COMMAND(ID_FILE_OPEN32800, &CDrawGUIDoc::OnFileOpenFred)
	ON_BN_CLICKED(IDC_OPEN_BTN, &CDrawGUIDoc::OnBnClickedOpenBtn)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawGUIDoc construction/destruction

CDrawGUIDoc::CDrawGUIDoc()
: m_bScreenTagClashes(false)
//, m_bIsActive(false)
, m_pProjectMetaData(NULL)
{
	// TODO: add one-time construction code here
	m_csFullHostFileName = "";
	m_csHostFileNameStub = "";
	uptodate=1;
}

CDrawGUIDoc::~CDrawGUIDoc()
{
}

BOOL CDrawGUIDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	POSITION pos = GetFirstViewPosition();
	CDrawGUIView* pView = (CDrawGUIView*) GetNextView(pos);
	pView->LoadSODL();

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDrawGUIDoc serialization

void CDrawGUIDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDrawGUIDoc diagnostics

#ifdef _DEBUG
void CDrawGUIDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDrawGUIDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDrawGUIDoc commands


void CDrawGUIDoc::InitialiseProjectMetas(ProjectMetaData *pPMD ) 
{

	assert(pPMD != NULL);

	m_pProjectMetaData = pPMD;
	m_pProjectMetaData->getProjectDir(m_csProjectDir);

	m_pProjectMetaData->initProjFolderMinder(); 

	if(m_pProjectMetaData->folderStructureNotOk()){
		AfxMessageBox("Unable to open this project, because the directory structure is invalid");
		assert(1==0);
	}

	POSITION pos = GetFirstViewPosition();
	CDrawGUIView* pView = (CDrawGUIView*) GetNextView(pos);
	//pView->projectDir = m_csProjectDir;

	return;
}

BOOL CDrawGUIDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// WARNING! The project meta data isn't set yet.
	// Don't try to do much until 'InitialiseprojectMetas'
	// has been called for the doc.
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	return TRUE;
}

BOOL CDrawGUIDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// TODO: Add your specialized code here and/or call the base class
	CDrawGUIApp *pApp = ( CDrawGUIApp *  )AfxGetApp();
	POSITION pos = GetFirstViewPosition();
	CDrawGUIView* pView = (CDrawGUIView*) GetNextView(pos);
	//CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
	//CMDIChildWnd *pChild = (CMDIChildWnd *) pFrame->GetActiveFrame();
	//CDrawGUIView *pView = (CDrawGUIView *) pChild->GetActiveView();

	if(!pApp->m_ProjectMetaData.getLock()){

		AfxMessageBox( PMD_LOCK_FAILURE_MESSAGE );

	}else{

		pApp->m_ProjectMetaData.readProjectFile();
		pView->UpdateProjectMetaData();
		pApp->m_ProjectMetaData.updateTransferrables(false);
		pApp->m_ProjectMetaData.writeProjectFile();

		pView->SaveGUIInf(lpszPathName);
		SetModifiedFlag(false);
	}

	pApp->m_ProjectMetaData.releaseLock();

	return 1;//CDocument::OnSaveDocument(lpszPathName);
}

void CDrawGUIDoc::Import() {
	CString fname="";
	CFileDialog box(1,"gui","default.gui",OFN_FILEMUSTEXIST,"Form Setup Files (*.gui)|*.gui|");//stuff);;
	if (box.DoModal()==IDOK) {
		fname=box.GetFileName();
	}
	else return;
	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
	CMDIChildWnd *pChild = (CMDIChildWnd *) pFrame->GetActiveFrame();
	CDrawGUIView *pView = (CDrawGUIView *) pChild->GetActiveView();
	pView->LoadGUIInfFromGuiFile(fname);

}

BOOL CDrawGUIDoc::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	//if (nID==ID_FILE_IMPORT) {
	//	Import();
	//}
	return CDocument::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CDrawGUIDoc::OnFileOpenFred()
{
	// TODO: Add your command handler code here
}

void CDrawGUIDoc::OnBnClickedOpenBtn()
{
	// TODO: Add your control notification handler code here
}

void CDrawGUIDoc::setProjectMetaData(ProjectMetaData * pPMD)
{
	m_pProjectMetaData = pPMD;
}

ProjectMetaData * CDrawGUIDoc::getProjectMetaData(void)
{
	assert(m_pProjectMetaData != NULL);
	return m_pProjectMetaData;
}
