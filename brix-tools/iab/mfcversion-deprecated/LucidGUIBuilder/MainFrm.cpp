// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "DrawGUI.h"
#include "../common/userDefinedMessages.h"
#include "MainFrm.h"
#include "DrawGUIDoc.h"
#include "DrawGUIView.h"
#include "LucidConstants.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_COPYDATA()
	//}}AFX_MSG_MAP


	//ON_MESSAGE( UWM_OPEN_LAYOUT, &CMainFrame::OnUWMOpenLayout )

	ON_COMMAND(ID_TOOLBAR_ALIGNMENT, &CMainFrame::OnToolbarAlignment)
	ON_UPDATE_COMMAND_UI(ID_TOOLBAR_ALIGNMENT, &CMainFrame::OnUpdateToolbarAlignment)
	ON_COMMAND(ID_TOOLBAR_OPTIONS, &CMainFrame::OnToolbarOptions)
	ON_UPDATE_COMMAND_UI(ID_TOOLBAR_OPTIONS, &CMainFrame::OnUpdateToolbarOptions)
	ON_COMMAND(ID_TOOLBAR_STANDARD, &CMainFrame::OnToggleToolbarStandard)
	ON_UPDATE_COMMAND_UI(ID_TOOLBAR_STANDARD, &CMainFrame::OnUpdateToolbarStandard)
	ON_COMMAND(ID_VIEW_ZCTRLTOOLBAR_VIZ, &CMainFrame::OnViewZctrltoolBarViz)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZCTRLTOOLBAR_VIZ, &CMainFrame::OnUpdateViewZctrlToolbarViz)
	ON_COMMAND(ID_TOOLBARS_OPTIONS, &CMainFrame::OnToolbarsOptions)
	ON_UPDATE_COMMAND_UI(ID_TOOLBARS_OPTIONS, &CMainFrame::OnUpdateToolbarsOptions)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

//////////////////////////////////////////
///////////////////////////////////
// CMainFrame construction/destruction


BOOL CMainFrame::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct) 
{

	//AfxMessageBox("Please debug me");
	CString strRecievedText = (LPCSTR) (pCopyDataStruct->lpData);

	CDrawGUIApp *pApp = ( CDrawGUIApp * ) AfxGetApp();
	pApp->OpenDocumentFile( strRecievedText );
	
	return CMDIFrameWnd::OnCopyData(pWnd, pCopyDataStruct);
}

LRESULT CMainFrame::OnUWMOpenLayout(WPARAM, LPARAM lParam)
{
	CString *cs = (CString *)lParam;

	AfxMessageBox( *cs );

	//delete cs;
	return 0;
}

CMainFrame::CMainFrame()
{
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{

	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

/*
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar( IDR_MAINFRAME ) )
	{
		TRACE0("Failed to create main toolbar\n");
		return -1;      // fail to create
	}
*/
 UINT assignedToolbarID = 3344500;
 DWORD style = WS_CHILD | WS_VISIBLE | CBRS_TOP |
  CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC;
 if( !m_wndToolBar.CreateEx( this, TBSTYLE_FLAT, style, CRect(1, 1, 1, 1), assignedToolbarID) )
  return -1;
 if( !m_wndToolBar.LoadToolBar( IDR_MAINFRAME ) )
  return -1;

// toolbar bitmap is comprosed of a strip of 16wx15h images for each button - for example if there are 30 buttons on the toolbar, the toolbar bitmap will be 30x16=480 pixels wide
//standard image size for mfc toolbar is 16wx15h
//int toolButtonHeight = 15;
//int toolButtonWidth = 16;
int toolButtonHeight = 24;
int toolButtonWidth = 24;
m_wndToolBar.SetSizes(CSize(toolButtonWidth + 7, toolButtonHeight + 6), CSize(toolButtonWidth, toolButtonHeight)); // NOTE - will fail unless button is bigger than image, +7 pixels w and +6 pixels h

// use IDR_MAINFRAME Toolbar_24bit.bmp or Toolbar_16bit.bmp in DrawProg.rc
// create a toolbar using the imagelist
CImageList *m_imagelist = new CImageList;
HBITMAP hbm = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),
   MAKEINTRESOURCE(IDR_MAINFRAME),
   IMAGE_BITMAP,
   0,0, // cx, cy
   LR_CREATEDIBSECTION | LR_LOADMAP3DCOLORS );
CBitmap bm;
bm.Attach(hbm);

m_imagelist->Create(toolButtonWidth,toolButtonHeight,ILC_COLOR24|ILC_MASK,1,1); //24bit colour with colour mask
//m_imagelist->Create(toolButtonWidth,toolButtonHeight,ILC_COLOR16|ILC_MASK,1,1); //16bit colour with colour mask
m_imagelist->Add(&bm, RGB(215,215,215)); // back colour of Toolbar_24bit.bmp and Toolbar_16bit.bmp to use as colour mask
m_wndToolBar.GetToolBarCtrl().SetImageList(m_imagelist);
//m_wndToolBar.GetToolBarCtrl().SetDisabledImageList(m_imagelist);  // don't need this as mfc greys out buttons by default but if you want to design the images for disabled buttons, create an image list and add it here

/*
	if (!m_wndToolBarAlign.Create(this) ||
		!m_wndToolBarAlign.LoadToolBar( IDR_TOOLBAR_ALIGN ) )
	{
		TRACE0("Failed to create alignment toolbar\n");
		return -1;      // fail to create
	}
*/

 if( !m_wndToolBarAlign.CreateEx( this, TBSTYLE_FLAT, style, CRect(1, 1, 1, 1), assignedToolbarID) )
  return -1;
 if( !m_wndToolBarAlign.LoadToolBar( IDR_TOOLBAR_ALIGN ) )
  return -1;

m_wndToolBarAlign.SetSizes(CSize(toolButtonWidth + 7, toolButtonHeight + 6), CSize(toolButtonWidth, toolButtonHeight)); // NOTE - will fail unless button is bigger than image, +7 pixels w and +6 pixels h

 // use IDR_MAINFRAME Toolbar_24bit.bmp or Toolbar_16bit.bmp in DrawProg.rc
// create a toolbar using the imagelist
m_imagelist = new CImageList;
hbm = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),
   MAKEINTRESOURCE(IDR_TOOLBAR_ALIGN),
   IMAGE_BITMAP,
   0,0, // cx, cy
   LR_CREATEDIBSECTION | LR_LOADMAP3DCOLORS );
CBitmap bm2;
bm2.Attach(hbm);

m_imagelist->Create(toolButtonWidth,toolButtonHeight,ILC_COLOR24|ILC_MASK,1,1); //24bit colour with colour mask
//m_imagelist->Create(toolButtonWidth,toolButtonHeight,ILC_COLOR16|ILC_MASK,1,1); //16bit colour with colour mask
m_imagelist->Add(&bm2, RGB(215,215,215)); // back colour of Toolbar_24bit.bmp and Toolbar_16bit.bmp to use as colour mask
m_wndToolBarAlign.GetToolBarCtrl().SetImageList(m_imagelist);
//m_wndToolBarAlign.GetToolBarCtrl().SetDisabledImageList(m_imagelist);  // don't need this as mfc greys out buttons by default but if you want to design the images for disabled buttons, create an image list and add it here

/*
	if (!m_wndToolBarOptions.Create(this) ||
		!m_wndToolBarOptions.LoadToolBar( IDR_TOOLBAR_OPTIONS ) )
	{
		TRACE0("Failed to create options toolbar\n");
		return -1;      // fail to create
	}
*/

 if( !m_wndToolBarOptions.CreateEx( this, TBSTYLE_FLAT, style, CRect(1, 1, 1, 1), assignedToolbarID) )
  return -1;
 if( !m_wndToolBarOptions.LoadToolBar( IDR_TOOLBAR_OPTIONS ) )
  return -1;

m_wndToolBarOptions.SetSizes(CSize(toolButtonWidth + 7, toolButtonHeight + 6), CSize(toolButtonWidth, toolButtonHeight)); // NOTE - will fail unless button is bigger than image, +7 pixels w and +6 pixels h

 // use IDR_MAINFRAME Toolbar_24bit.bmp or Toolbar_16bit.bmp in DrawProg.rc
// create a toolbar using the imagelist
m_imagelist = new CImageList;
hbm = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),
   MAKEINTRESOURCE(IDR_TOOLBAR_OPTIONS),
   IMAGE_BITMAP,
   0,0, // cx, cy
   LR_CREATEDIBSECTION | LR_LOADMAP3DCOLORS );
CBitmap bm3;
bm3.Attach(hbm);

m_imagelist->Create(toolButtonWidth,toolButtonHeight,ILC_COLOR24|ILC_MASK,1,1); //24bit colour with colour mask
//m_imagelist->Create(toolButtonWidth,toolButtonHeight,ILC_COLOR16|ILC_MASK,1,1); //16bit colour with colour mask
m_imagelist->Add(&bm3, RGB(215,215,215)); // back colour of Toolbar_24bit.bmp and Toolbar_16bit.bmp to use as colour mask
m_wndToolBarOptions.GetToolBarCtrl().SetImageList(m_imagelist);
//m_wndToolBarOptions.GetToolBarCtrl().SetDisabledImageList(m_imagelist);  // don't need this as mfc greys out buttons by default but if you want to design the images for disabled buttons, create an image list and add it here


	if( !m_cZOrderDlogBar.Create( this, IDD_LGB_ZORDER_DIALOG, CBRS_RIGHT, -1) )
	{
	//	TRACE0("Failed to create dialog bar\n"):
		return -1;
	}

	if( !m_cZOrderDlogBar.initDialog() )
	{
	//	TRACE0("Failed to create dialog bar\n"):
		return -1;
	}
	ShowControlBar(&m_cZOrderDlogBar, WS_VISIBLE, FALSE);
	m_cZOrderDlogBar.EnableDocking(CBRS_ORIENT_ANY);


	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// add combo box to toolbar
	CRect rect;
	int nIndex = m_wndToolBar.GetToolBarCtrl().CommandToIndex(ID_IGB_EHS_HOST_COMBO);
	m_wndToolBar.SetButtonInfo(nIndex, ID_IGB_EHS_HOST_COMBO, TBBS_SEPARATOR, 110); // this sets the width and makes it a separator type - may need to change back to button type if want to work with larger toolbar buttons 32x32
	m_wndToolBar.GetToolBarCtrl().GetItemRect(nIndex, &rect);
	rect.top = 4; // added y-offset for 24x24 toolbar
	rect.bottom = rect.top + 250 /*drop height*/;
	if(!m_combo.Create(CBS_DROPDOWNLIST | CBS_AUTOHSCROLL | WS_VISIBLE |
		WS_TABSTOP | WS_VSCROLL, rect, &m_wndToolBar, ID_IGB_EHS_HOST_COMBO))
	{
		TRACE(_T("Failed to create combo-box\n"));
		return FALSE;
	}
	m_combo.AddString(TARGET_DISPLAY_NAME_LOCAL);
	m_combo.AddString(TARGET_DISPLAY_NAME_REMOTE);
	m_combo.AddString(TARGET_DISPLAY_NAME_BLANK); // no app server functionality in GUI Builder
	CFont *m_Font = m_wndStatusBar.GetFont();
	m_combo.SetFont(m_Font);



	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	m_wndToolBarAlign.SetBarStyle(m_wndToolBarAlign.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	m_wndToolBarOptions.SetBarStyle(m_wndToolBarOptions.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBarAlign.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBarOptions.EnableDocking(CBRS_ALIGN_ANY);


	EnableDocking( CBRS_ORIENT_ANY );

	DockControlBar( &m_wndToolBar );
	DockControlLeftOf( &m_wndToolBarAlign, &m_wndToolBar );
	DockControlLeftOf( &m_wndToolBarOptions, &m_wndToolBarAlign );

	DockControlBar( &m_cZOrderDlogBar );

	return 0;
}

//void CMainFrame::SetWindowText(
  // LPCTSTR lpszString 
//)
//{
//	CWnd::SetWindowTextA(lpszString);
//}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// DONT do the std MFC thing of updating the frame title to the name
	// of the child-window's file, each time child is clicked.  This is 
	// because we want to set the file + screen tag + [clash] if necessary.
	cs.style &= ~ FWS_ADDTOTITLE;
	return CMDIFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::resetChildTitles(void)
{

// Check whether gui files for the same screentag are open simultaneously.

	// Initialise variables.
	CString titleStr;
	ProjectMetaData *pProjectMetaData = NULL;
	CDrawGUIDoc *pOuterDoc = NULL;
	CDrawGUIDoc *pInnerDoc = NULL;

	bool repeatedScreentag = false;

	CDrawGUIApp *pApp = ( CDrawGUIApp *  )AfxGetApp();
	pProjectMetaData = &(pApp->m_ProjectMetaData);

	CDocTemplate *pDocTemplate = pApp->m_pDocTemplate;

	POSITION viewPos = NULL;
	CDrawGUIView *pView = NULL;
	CFrameWnd *pOuterParentFrameWnd = NULL;	
	CFrameWnd *pInnerParentFrameWnd = NULL;	

	// Do old-fashioned bubble-search on screen-tag clashes, with
	// outer- andd inner document loops.
	POSITION outerPos = pDocTemplate->GetFirstDocPosition();
	POSITION innerPos = NULL;

	// Loop through all open docuents, intialising each one's clash-flag to false.
	while (outerPos){
		pOuterDoc = (CDrawGUIDoc *) pDocTemplate->GetNextDoc(outerPos);
		pOuterDoc->m_bScreenTagClashes = false; 
	}

	// Now work through each doc, detecting / setting flags for clashes ...

	outerPos = pDocTemplate->GetFirstDocPosition();

	while (outerPos){

		pOuterDoc = (CDrawGUIDoc *) pDocTemplate->GetNextDoc(outerPos);
		innerPos = outerPos;

		// For each doc including and after the present doc in the outer loop
		while(innerPos){

			pInnerDoc = (CDrawGUIDoc*) pDocTemplate->GetNextDoc(innerPos);

			if(pInnerDoc->m_csTargetFileName ==
						pOuterDoc->m_csTargetFileName){

				// There is a widget-group clash 

				viewPos = pOuterDoc->GetFirstViewPosition();
				pView = ( CDrawGUIView * ) pOuterDoc->GetNextView(viewPos);
				pOuterParentFrameWnd = pView->GetParentFrame();
				// When called as a result of closing a window, the 'closed'
				// view may still linger in the template's list even though
				// it has already been zapped.

				viewPos = pInnerDoc->GetFirstViewPosition();
				pView = ( CDrawGUIView * ) pInnerDoc->GetNextView(viewPos);
				pInnerParentFrameWnd = pView->GetParentFrame();

				// When called as a result of closing a window, the 'closed'
				// view may still linger in the template's list evemn though
				// it has already been zapped.
				if(pOuterParentFrameWnd && pInnerParentFrameWnd ){
					pOuterDoc->m_bScreenTagClashes = true;
					pInnerDoc->m_bScreenTagClashes = true;
				}				

			} // if(pInnerDoc->m_csTargetFileName ==

		} // while(innerPos)

	} //while (outerPos)


	// Now we have identified all the clashes, use this info to set frame titles accordingly.

	bool bIsActive = false;
	CString csActiveLayoutName;
	outerPos = pDocTemplate->GetFirstDocPosition();

	while (outerPos){

		pOuterDoc = (CDrawGUIDoc *) pDocTemplate->GetNextDoc(outerPos);

		// Get the view for this doc.
		viewPos = pOuterDoc->GetFirstViewPosition();
		pView = ( CDrawGUIView * ) pOuterDoc->GetNextView(viewPos);

		LucidErrEnum err = pProjectMetaData->getActiveLayout( pOuterDoc->m_csScreenTag, csActiveLayoutName );

		bIsActive = ( pOuterDoc->m_csHostFileNameStub == csActiveLayoutName );

		titleStr.Empty();

		titleStr += "[  ";
		titleStr += pOuterDoc->m_csScreenTag;
		titleStr += "  ]    ";
		//titleStr += ":";
		titleStr += pOuterDoc->m_csFullHostFileName;


		if(bIsActive){
			titleStr += " -ACTIVE";
		}
		//titleStr += " ]";
		
		if(pOuterDoc->m_bScreenTagClashes){
			titleStr += ".............[CLASH!]";
		}

		pOuterParentFrameWnd = pView->GetParentFrame();

		// When called as a result of closing a window, the 'closed'
		// view may still linger in the template's list even though
		// it has already been zapped.
		if(pOuterParentFrameWnd){
			pOuterParentFrameWnd->SetWindowTextA( titleStr );
		}

	} // while (outerPos)

}

void CMainFrame::OnToolbarsOptions()
{
	ShowControlBar( &m_wndToolBarOptions, ( m_wndToolBarOptions.GetStyle() & WS_VISIBLE ) == 0, false );
}

void CMainFrame::OnUpdateToolbarsOptions(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( ( m_wndToolBarOptions.GetStyle() & WS_VISIBLE ) != 0 );
}


void CMainFrame::OnToolbarOptions()
{}

void CMainFrame::OnToolbarAlignment()
{
	ShowControlBar( &m_wndToolBarAlign, ( m_wndToolBarAlign.GetStyle() & WS_VISIBLE ) == 0, false );
}

void CMainFrame::OnUpdateToolbarOptions(CCmdUI *pCmdUI)
{}

void CMainFrame::OnUpdateToolbarAlignment(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( ( m_wndToolBarAlign.GetStyle() & WS_VISIBLE ) != 0 );
}

void CMainFrame::OnToggleToolbarStandard()
{
	ShowControlBar( &m_wndToolBar, ( m_wndToolBar.GetStyle() & WS_VISIBLE ) == 0, false );
}

void CMainFrame::OnUpdateToolbarStandard(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( ( m_wndToolBar.GetStyle() & WS_VISIBLE ) != 0 );
}
/*
void CMainFrame::DockControlLeftOf(CToolBar * bar1, CToolBar * bar2)
{
	CRect rect;
	RecalcLayout();
	bar2->GetWindowRect( &rect );
	rect.OffsetRect(1,0);
	DockControlBar( bar1, AFX_IDW_DOCKBAR_LEFT, &rect );
}
*/
void CMainFrame::DockControlLeftOf(CToolBar* Bar, CToolBar* LeftOf)
{
	CRect rect;
	DWORD dw;
	UINT n;

	// get MFC to adjust the dimensions of all docked ToolBars
	// so that GetWindowRect will be accurate
	RecalcLayout(TRUE);

	LeftOf->GetWindowRect(&rect);
	rect.OffsetRect(1,0);
	dw=LeftOf->GetBarStyle();
	n = 0;
	n = (dw&CBRS_ALIGN_TOP) ? AFX_IDW_DOCKBAR_TOP : n;
	n = (dw&CBRS_ALIGN_BOTTOM && n==0) ? AFX_IDW_DOCKBAR_BOTTOM : n;
	n = (dw&CBRS_ALIGN_LEFT && n==0) ? AFX_IDW_DOCKBAR_LEFT : n;
	n = (dw&CBRS_ALIGN_RIGHT && n==0) ? AFX_IDW_DOCKBAR_RIGHT : n;

	// When we take the default parameters on rect, DockControlBar will dock
	// each Toolbar on a seperate line. By calculating a rectangle, we
	// are simulating a Toolbar being dragged to that location and docked.
	DockControlBar(Bar,n,&rect);
}
void CMainFrame::OnViewZctrltoolBarViz()
{
	ShowControlBar( &m_cZOrderDlogBar, (m_cZOrderDlogBar.GetStyle() & WS_VISIBLE)==0, FALSE );
}

void CMainFrame::SetZctrltoolBarVisible( const bool &visible )
{
	//ShowControlBar( &m_cZOrderDlogBar, visible, FALSE );
}

void CMainFrame::OnUpdateViewZctrlToolbarViz(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(  (m_cZOrderDlogBar.GetStyle() & WS_VISIBLE) !=0 );
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	if( m_cZOrderDlogBar.OnCmdMsg( nID,  nCode, pExtra, pHandlerInfo ))
		return true;

	return CMDIFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


void CMainFrame::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{

	AfxMessageBox("778");
	//CDialogBar::OnVScroll(nSBCode, nPos, pScrollBar);

}

LgbZOrderDlogBar * CMainFrame::getZOrderDlogBarPtr(void) {
	return &m_cZOrderDlogBar;
}

void CMainFrame::setFrameCaption()
{
	CString cStr1;
	ProjectMetaData *pProjectMetaData = &(((CDrawGUIApp *)AfxGetApp())->m_ProjectMetaData);

	if(pProjectMetaData->projectIsSet()){
		pProjectMetaData->getFullPathProjectFile(cStr1);
		((CDrawGUIApp *) AfxGetApp())->AddToRecentFileList(cStr1);
		((CDrawGUIApp *) AfxGetApp())->WriteMruList();
	}

	CWnd * m_pMainWnd = AfxGetApp()->m_pMainWnd;

	if(pProjectMetaData->projectIsSet()){

		CString dum, dum2;
		pProjectMetaData->getProjectDir(dum);
		pProjectMetaData->getProjectName(dum2);	
		m_pMainWnd->SetWindowTextA(LGB_APP_NAME + dum + ":" +dum2);

	} else {// if(m_ProjectMetaData.projectIsSet())

		m_pMainWnd->SetWindowTextA(LGB_APP_NAME + NO_PROJECT_WARNING);
	}

	//CDialog::OnOK();
}

