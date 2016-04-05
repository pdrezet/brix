/** @file DrawGUIView.cpp
 * Implementation of CDrawGUIView class.
 * @author: Matthew Rutherford
 * @version: $Revision: 576 $
 * @date: $Date$
 * 
 * Copyright (c) Ncapsa Ltd, 2007. All rights reserved.
 */

#include "stdafx.h"
#include "LgbDrawable.h"

#include "DrawGUIDoc.h"
#include "DrawGUIView.h"
#include "DrawGUI.h"
#include "LgbTextIcon.h"
#include "LgbPatchIcon.h"
#include "../LucidApplicationBuilder/FileOperations.h"
#include "MainFrm.h"
#include "../common/GlobalFuncs_2.h"
#include "..\common\bmpfile.h"
#include "../common\TgtTransProgDlog.h"
#include "config.h"
#include "FTP.h"
#include "../common/LucidConstants.h"
#include "ColourEdit.h"
#include "ColourStatic.h"
#include "Properties_Textbox.h"
#include "Properties_Patch.h"
#include "Properties_Image.h"
#include "Properties_Drawable.h"
#include <fstream>
#include <cassert>
#include <math.h>
#include <direct.h>
#include "common.h"
#include "LgbZOrderDlog.h"
#include "../common/LucidTypedefs.h"
#include "LgbImageIcon.h"
#include "LgbColorsDef.h"
#include "../common/GlobalFuncs_1.h"
#include "../common/EHSParamsDialog.h"
#include "LucidRegAccess.h"

#include <vector>

#define FLAG_NOT_YET_SET -1

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// global variable declared in CDrawGUIApp
//extern char workDir[4096];

#define HEIGHT 600
#define WIDTH 1000

int CDrawGUIView::c_iInstanceCount = 0;

//#include "ContDef.h"
/////////////////////////////////////////////////////////////////////////////
// CDrawGUIView

IMPLEMENT_DYNCREATE(CDrawGUIView, CView)

BEGIN_MESSAGE_MAP(CDrawGUIView, CView)
	//{{AFX_MSG_MAP(CDrawGUIView)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(LOADAFXSODL, OnLOADAFXSODL)
	ON_COMMAND(ID_SCANNEWSODL, OnLOADAFXSODL)
//	ON_COMMAND(IDLGB_FTP_OPTIONS, OnFtpOptions)
	ON_COMMAND(ID_ICON_PROPERTIES, OnIconProperties)
//	ON_COMMAND(ID_FTP_GUI, OnFtpGui)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_COMMAND(ID_ALIGNMENT_LEFTEDGES, &CDrawGUIView::OnAlignmentLeftEdges)
	ON_COMMAND(ID_ALIGNMENT_RIGHTEDGES, &CDrawGUIView::OnAlignmentRightEdges)
	ON_COMMAND(ID_ALIGNMENT_LEFTRIGHTCENTRES, &CDrawGUIView::OnAlignmentLeftRightCentres)
	ON_COMMAND(ID_ALIGNMENT_TOPEDGES, &CDrawGUIView::OnAlignmentTopEdges)
	ON_COMMAND(ID_ALIGNMENT_BOTTOMEDGES, &CDrawGUIView::OnAlignmentBottomEdges)
	ON_COMMAND(ID_ALIGNMENT_TOPBOTTOMCENTRES, &CDrawGUIView::OnAlignmentTopBottomCentres)
	ON_COMMAND(ID_RESIZE_WIDTH, &CDrawGUIView::OnResizeWidth)
	ON_COMMAND(ID_RESIZE_HEIGHT, &CDrawGUIView::OnResizeHeight)
	ON_COMMAND(ID_ICON_BRINGTOFRONT, &CDrawGUIView::OnIconBringTofront)
	ON_COMMAND(ID_ICON_SENDTOREAR, &CDrawGUIView::OnIconSendToRear)
	ON_COMMAND(ID_ICON_MOVEFORWARD, &CDrawGUIView::OnIconMoveForward)
	ON_COMMAND(ID_ICON_MOVEBACKWARD, &CDrawGUIView::OnIconMoveBackward)
	ON_COMMAND(ID_ICON_EQUALISETOFRONTMOST, &CDrawGUIView::OnIconEqualiseToFrontmost)
	ON_COMMAND(ID_ICON_EQUALISETOREAR, &CDrawGUIView::OnIconEqualiseToRearmost)
	ON_COMMAND(ID_OPTIONS_SELECTALLWIDGETS, &CDrawGUIView::OnOptionsSelectAllWidgets)
	ON_COMMAND(ID_OPTIONS_DISPLAYWIDGETLABELS, &CDrawGUIView::OnOptionsDisplayWidgetLabels)
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_Z_RENUMBERCONSECTIVELY, &CDrawGUIView::OnZRenumberConsectively)
	ON_COMMAND(ID_Z_RENUMBER, &CDrawGUIView::OnZRenumberKeepGaps)
	ON_COMMAND(ID_SELECTION_SELECTALLBITMAPS, &CDrawGUIView::OnSelectionSelectAllBitmaps)
	ON_COMMAND(ID_SELECTION_SELECTALLTEXTBOXES, &CDrawGUIView::OnSelectionSelectAllTextBoxes)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_DISPLAYWIDGETLABELS, &CDrawGUIView::OnUpdateOptionsDisplayWidgetLabels)
	ON_UPDATE_COMMAND_UI(ID_ALIGNMENT_LEFTEDGES, &CDrawGUIView::OnUpdateAlignment)
	ON_UPDATE_COMMAND_UI(ID_ALIGNMENT_RIGHTEDGES, &CDrawGUIView::OnUpdateAlignment)
	ON_UPDATE_COMMAND_UI(ID_ALIGNMENT_TOPEDGES, &CDrawGUIView::OnUpdateAlignment)
	ON_UPDATE_COMMAND_UI(ID_ALIGNMENT_BOTTOMEDGES, &CDrawGUIView::OnUpdateAlignment)
	ON_UPDATE_COMMAND_UI(ID_ALIGNMENT_LEFTRIGHTCENTRES, &CDrawGUIView::OnUpdateAlignment)
	ON_UPDATE_COMMAND_UI(ID_ALIGNMENT_TOPBOTTOMCENTRES, &CDrawGUIView::OnUpdateAlignment)
	ON_UPDATE_COMMAND_UI(ID_RESIZE_WIDTH, &CDrawGUIView::OnUpdateAlignment)
	ON_UPDATE_COMMAND_UI(ID_RESIZE_HEIGHT, &CDrawGUIView::OnUpdateAlignment)
	ON_COMMAND(ID_VIEW_ZDIALOG, &CDrawGUIView::OnViewZdialog)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZDIALOG, &CDrawGUIView::OnUpdateViewZdialog)
	ON_COMMAND(ID_OPTIONS_NATIVEVIEWBGROUND, &CDrawGUIView::OnOptionsNativeviewbground)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_NATIVEVIEWBGROUND, &CDrawGUIView::OnUpdateOptionsNativeviewbground)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_ICON_SETFULLYOPAQUE, &CDrawGUIView::OnIconSetfullyopaque)
	ON_COMMAND(ID_ICON_DECREMENTOPACITY10, &CDrawGUIView::OnIconDecrementOpacity)
	ON_COMMAND(ID_LGBTRANSFERMANAGER, &CDrawGUIView::OnLgbShowTransferManager)
	//ON_COMMAND(ID_LAUNCH_TRANSFER_DLG, &CDrawGUIView::OnLaunchTransferDlg)
	ON_COMMAND(ID_EDIT_UNDO32878, &CDrawGUIView::OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO32878, &CDrawGUIView::OnUpdateEditUndo)
	ON_COMMAND(ID_EDIT_REDO32879, &CDrawGUIView::OnEditRedo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO32879, &CDrawGUIView::OnUpdateEditRedo)
	ON_COMMAND(ID_LGB_TRANSFERALLDATA, &CDrawGUIView::OnLgbTransferAll)
	ON_COMMAND(ID_LGB_SENDCHANGEDDATA, &CDrawGUIView::OnLgbSendDataChanged)
	ON_UPDATE_COMMAND_UI(ID_LGB_TRANSFERALLDATA, &CDrawGUIView::OnUpdateLgbTransferAll)
	ON_UPDATE_COMMAND_UI(ID_LGB_SENDCHANGEDDATA, &CDrawGUIView::OnUpdateLgbTransferChanged)
	ON_COMMAND(ID_SELECTION_SELECTALLPATCHES, &CDrawGUIView::OnSelectionSelectAllPatches)

	ON_COMMAND(ID_EHS_START, &CDrawGUIView::OnEHSStartRestart)
	ON_COMMAND(ID_EHS_STOP, &CDrawGUIView::OnEHSStop)
	ON_COMMAND(ID_EHS_ALWAYSON, &CDrawGUIView::OnEHSTopmost)
	ON_COMMAND(ID_EHS_ALWAYSON32893, &CDrawGUIView::OnEHSBottommost)
	ON_COMMAND(ID_EHS_NORMALZORDER, &CDrawGUIView::OnEHSNormalZOrder)
	ON_COMMAND(ID_EHS_INITIALPARAMETERS, &CDrawGUIView::OnEHSInitParams)
	ON_COMMAND(ID_IGB_EHS_MANAGEEHSLOCALLY, &CDrawGUIView::OnEHSManageLocally)
	ON_COMMAND(ID_IGB_EHS_MANAGEEHSREMOTELY, &CDrawGUIView::OnEHSManageRemotely)
	ON_UPDATE_COMMAND_UI(ID_IGB_EHS_MANAGEEHSLOCALLY, &CDrawGUIView::OnUpdateEHSManageLocally)
	ON_UPDATE_COMMAND_UI(ID_IGB_EHS_MANAGEEHSREMOTELY, &CDrawGUIView::OnUpdateEHSManageRemotely)
	ON_UPDATE_COMMAND_UI(ID_EHS_START, &CDrawGUIView::OnUpdateEHSStartRestart)
	ON_UPDATE_COMMAND_UI(ID_EHS_STOP, &CDrawGUIView::OnUpdateEHSStop)
	ON_UPDATE_COMMAND_UI(ID_EHS_INITIALPARAMETERS, &CDrawGUIView::OnUpdateEHSInitParams)
	ON_CBN_SELCHANGE(ID_IGB_EHS_HOST_COMBO, &CDrawGUIView::OnSelChangeEHSHostCombo)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawGUIView construction/destruction



CDrawGUIView::CDrawGUIView()
: m_iNumberIconsCurrentlySelected(0)
, m_bMouseIsDown(false)
{
	init();
}


// Method that sets the text start of the status bar
void CDrawGUIView::setStatusBarText(CString csText)
{
	int paneIndex = 0;
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	pFrame->m_wndStatusBar.GetStatusBarCtrl().SetText(csText, paneIndex, 0);
}


void CDrawGUIView::init()
{

	m_cZDatVals.zClipVal = FLAG_NOT_YET_SET;
	m_cZDatVals.zLeanVal = 0;

	// From a user perspective, there must be only 1 dialog for all views, otherwise
	// there would be little dialogs all over the screen getting in the way.
	// This is a 'Cod' singleton implementation.  I couldn't get classic singleton version (ie with an Instance() method)
	// of ZOrderDlog to work properly!

	CMainFrame *pMnFrm = ( CMainFrame * ) AfxGetMainWnd();
	m_pLgbZOrderDlogBar = pMnFrm->getZOrderDlogBarPtr();

	c_iInstanceCount++;

	// If the view isn't the 1st one, the dlog is already visible
	// unless the user has chosen to hide it.
	if(c_iInstanceCount==1) {
		CMainFrame *pMnFrm = ( CMainFrame * )AfxGetMainWnd();
		pMnFrm->SetZctrltoolBarVisible(true);
	}

	// Show the dialog - doesn't matter if another view has already caused it to be shown.

	CDrawGUIApp *pApp = (CDrawGUIApp *) AfxGetApp();
	CWnd *pWnd = pApp->GetMainWnd();
	WINDOWPLACEMENT mainLpwndpl;
	pWnd->GetWindowPlacement( &mainLpwndpl );


	//m_cLgbUndoStore.init( "aabbccc", 5 );
	//CString fileName = m_cLgbUndoStore.reset( m_bEnableUndo, m_bEnableRedo, m_csUndoPrompt, m_csRedoPrompt );
	//SaveGUIInf( fileName );

	m_eSelnMode=k_LgbDrawableOutside;

	m_bShowTags = true;
	m_cDrawableBag.setTagShowState( m_bShowTags );

	m_bZSliderNeverMoved = true;

	m_cStdNativeBackgroundColors = RGB( 0, 0, 0 );

	m_cStdWarningBackgroundColors = RGB( 255, 0, 0 );

	m_cStdEditingBackgroundColors = RGB( 200, 200, 200 );

	m_bNativeBackgroundColors = true;
	m_bWarningBackgroundColors = false;
	m_bIsDirtySODL = false;

	isFocusEventStarted = false;
	isFocusEventFinished = false;
}

CDrawGUIView::~CDrawGUIView()
{
	// This avoids a crash upon closing the app or at least a view within the app.
	m_cDrawableBag.freeAllMemory();

	// We should work out here if this is the last view - if so, hide the z-dlog.
	// delete c_pLgbZOrderDlog;
	c_iInstanceCount--;
	if(!c_iInstanceCount) {
		CMainFrame *pMnFrm = ( CMainFrame * )AfxGetMainWnd();
		pMnFrm->SetZctrltoolBarVisible(false);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDrawGUIView drawing

void CDrawGUIView::OnDraw(CDC* pDC)
{
	BlitCompo();
}

/////////////////////////////////////////////////////////////////////////////
// CDrawGUIView printing

BOOL CDrawGUIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDrawGUIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDrawGUIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDrawGUIView diagnostics

#ifdef _DEBUG
void CDrawGUIView::AssertValid() const
{
	CView::AssertValid();
}

void CDrawGUIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDrawGUIDoc* CDrawGUIView::GetDocument() // non-debug version is inline
{
	CDrawGUIApp *pApp = ( CDrawGUIApp * ) AfxGetApp();
	//POSITION pos = pApp->m_pDocTemplate->GetFirstDocPosition();
	//pDoc = (CDrawGUIDoc *) pApp->m_pDocTemplate->GetNextDoc(pos);

	CDrawGUIDoc *pDoc = (CDrawGUIDoc *)CView::GetDocument();
	ASSERT(pDoc!=NULL);
	ASSERT(pDoc->IsKindOf(RUNTIME_CLASS(CDrawGUIDoc)));
	return pDoc;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDrawGUIView message handlers

LgbRectSelTypeEnum CDrawGUIView::getSelectedIcon(
									  const CPoint &point, 
									  LgbDrawable *  &icon )

{
	return m_cDrawableBag.getSelectedIcon(point, icon );
}


void CDrawGUIView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{

	// Show the properties dialog for the selection.
	LgbDrawable *pIcon = NULL;
	LgbRectSelTypeEnum selMode = getSelectedIcon(point, pIcon );

	if (selMode != k_LgbDrawableOutside) {
		ClientToScreen(&point);	// Convert to screen coordinates
		OnIconProperties();
	}
}

void CDrawGUIView::OnRButtonDown(UINT nFlags, CPoint point) 
{

	// Show the right-click popup menu.

	CMenu iconMenu;

	//const bool firstOnly = true;

	LgbDrawable *pIcon;  // Convenience pointer to the selected icon

	LgbRectSelTypeEnum selMode = getSelectedIcon(point, pIcon );

	if(selMode == k_LgbDrawableOutside){ // no icon WAS clicked upon

		// un-select and un-master everything in d-bag
		m_cDrawableBag.setCollectiveState( LgbDrawable::k_Selected, false );
		m_cDrawableBag.setCollectiveState( LgbDrawable::k_Master, false );

		// Reset the selections bag
		m_cSelectionBag.reset();

		m_iNumberIconsCurrentlySelected = 0;
		BlitCompo();

	} else {

		// If this icon isn't selected, select it and de-select everything else.
		// If it IS already selected, then don't touch selections - just show what is 
		// already selected.

		if( !pIcon->m_bIsSelected ){

			// un-select and un-master everything in d-bag
			m_cDrawableBag.setCollectiveState( LgbDrawable::k_Selected, false );
			m_cDrawableBag.setCollectiveState( LgbDrawable::k_Master, false );

			// Select just the thing that was R-clicked
			pIcon->m_bIsSelected = true;
			m_cSelectionBag.push_back( pIcon );
			m_cDrawableBag.setMasterIcon( pIcon );
			m_iNumberIconsCurrentlySelected = 1;
			
			BlitCompo();

		} 

		pDoc->uptodate=0;
		pDoc->SetModifiedFlag();

		//OnIconProperties();

		iconMenu.LoadMenu(IDB_ICON_MENU); // Load the icon menu
		ClientToScreen(&point);	// Convert to screen coordinates
		// display icon menu pop-up
		iconMenu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, point.x, point.y, this);

	}

	CView::OnRButtonDown(nFlags, point);
}

/** Handle left-button down events.
    See User Interface Spec for how this is supposed to work - but for quick inspiration see how 
	textboxes and their selections are handled in MS Excel.
	In fact, although this all works quite well, there is a structural problem with the way this is
	all handled, as follows...
	When the user clicks on free space ( no icon) she may be wishing to de-select everything, or
	she may be just about to draw a marquee, in which case - if the control key is down - we can
	only process selections on left button up.  Hence some of this code should be moved to OnLButtonUp */
void CDrawGUIView::OnLButtonDown(UINT nFlags, CPoint point) 
{

	m_vMouseActions.clear();

	// Set initial click pt to where the user clicked.
	m_cInitialClickPt	= point;

	// For good measure, init the time being set 'last point moved to' to this also.
	m_cPreviousPt		= point;

	m_bMouseIsDown = true; // good to keep your own record of mouse dowwn / up - don't rely on nFlags!

	m_eSelnMode=k_LgbDrawableOutside; // We don't yet know if user clicked 'on' anything

	// Find out if control-key is pressed
	SHORT keyState = GetKeyState(VK_CONTROL);
	bool m_bCtrlKeyDown = (GetKeyState(VK_CONTROL)<0);

	LgbDrawable *pIcon = NULL;  // convenience ptr to selected icon

	bool m_bClickedOnSomething = false; // Did user click on an icon

	bool m_bThingWasAlreadySelected = false; // ie was the icon cclicked-upon already selected.

	int iconSelected=-1;
	int selectionIndex = -1;

	// Did the user click on an icon - if so, was it the left edge, centre, etc.
	m_eSelnMode = m_cDrawableBag.getSelectedIcon( point, pIcon );

	m_bClickedOnSomething = (m_eSelnMode != k_LgbDrawableOutside);

	if(m_bClickedOnSomething){
		m_bThingWasAlreadySelected = pIcon->m_bIsSelected;
	}



	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// Process the selections!
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	if(!m_bClickedOnSomething){

		if( !m_bCtrlKeyDown ){

			// The user clicked on free-space, without the control key down
			// bus reqs imply -> Clear all selections
			// NB If ctrl was down, leave selections as they are, and toggle
			// them if they are in the marquee the user draws

			// un-select and un-master everything in d-bag
			m_cDrawableBag.setCollectiveState( LgbDrawable::k_Selected, false );
			m_cDrawableBag.setCollectiveState( LgbDrawable::k_Master, false );

			// Reset the selections bag
			m_cSelectionBag.reset();

			m_iNumberIconsCurrentlySelected = 0;

			m_vMouseActions.push_back( k_SelectionsCleared );

		}

	} else { // if(m_bClickedOnSomething)

		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		// The user did click on something.
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

		if( m_bCtrlKeyDown ){

			// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			// The control key was down - toggle the selection of this *one* icon
			// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

			// Toggle the selection of what was clicked
			pIcon->m_bIsSelected = !(pIcon->m_bIsSelected);

			m_vMouseActions.push_back( k_SelectionToggled );

			// The selection state of the icon was either toggled on or off ....
			if(pIcon->m_bIsSelected){

				//If it was de-selected, it should NOT already be in there
				assert( !m_cSelectionBag.isAlreadyInList( pIcon ) );

				// if there are no other items selected, make this the master icon
				if( m_iNumberIconsCurrentlySelected == 0 ){
					m_cDrawableBag.setMasterIcon( pIcon );
				}

				// Record its selection so that it can be set to be the master if necessary
				m_cSelectionBag.push_back( pIcon );
				m_iNumberIconsCurrentlySelected++;

			}else{

				//If it was selected, it should already be in there
				assert( m_cSelectionBag.isAlreadyInList( pIcon ) );

				// Erase this item from the list of potential masters

				LgbDrawableConstIt_t it = m_cSelectionBag.find( pIcon );

				// NB next 2 lines because 'find' is a const method, needs 
				// a const iterator, erase needs a non-const
				LgbDrawable *pDum = *it;
				//it2 = it;

				m_cSelectionBag.erase(  pDum );
				m_iNumberIconsCurrentlySelected--;

				if( m_iNumberIconsCurrentlySelected ){
					// Just in case the icon just de-selected was the master, reset the master
					// which might the same as before, or might be the next in the list IF
					// the one just erase d was at the front of the list
					LgbDrawable *pNewMasterIcon = m_cSelectionBag.front();
					m_cDrawableBag.setCollectiveState( LgbDrawable::k_Master, false );
					m_cDrawableBag.setMasterIcon( pNewMasterIcon );

				}

			}


		} // if( m_bCtrlKeyDown )

		else {

			// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			// The control key was NOT down
			// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

			// Only do something with selections if the thing
			// clicked was NOT already selected.
			// NB.  Bus Reqs imply that, if thing WAS already selected, do nothing to the state of selections
			// as we assume rather that the user wants to move/resize etc the selections.

			if( !m_bThingWasAlreadySelected ){
				
				// OK - the clicked icon wasn't selected, and the ctrl key wasn't down, so
				// deselect everything and reset for this icon

				// 1st De-select everything
				m_cDrawableBag.setCollectiveState( LgbDrawable::k_Selected, false );
				m_cDrawableBag.setCollectiveState( LgbDrawable::k_Master, false );

				m_cSelectionBag.reset();
				m_iNumberIconsCurrentlySelected = 0;

				// Select just the thing that was clicked
				pIcon->m_bIsSelected = true;

				// Push it onto list of selection ( for 'master re-setting' purposess ).
				m_cSelectionBag.push_back( pIcon );
				m_cDrawableBag.setMasterIcon( pIcon );
				m_iNumberIconsCurrentlySelected++;

				// Set the thing as 'last clicked'.  This will be used as the master width and height
				// for %-resizing other selections.
				m_cDrawableBag.setLastClickedIcon( pIcon );

				//m_vMouseActions.push_back( k_SelectionsCleared );
				m_vMouseActions.push_back( k_SelectionSingle );


			} // if( !m_bThingWasAlreadySelected )
			else {

				// Set the thing as 'last clicked'.  This will be used as the master width and height
				// for %-resizing other selections.
				m_cDrawableBag.setLastClickedIcon( pIcon );
			}

		} // if( !m_bCtrlKeyDown )

	} // endif { // if(m_bClickedOnSomething)


	// Reload the contents of the outlines of the rectangles.
	//m_vSelRects.clear();
	//m_cDrawableBag.loadSelectedOutlines( m_vSelRects );

	//BlitCompo();

	CView::OnLButtonDown(nFlags, point);
}

CString CDrawGUIView::getBestPrompt( const std::vector< MouseActionEnum > vMouseActions )
{

	if( vMouseActions.front() == k_SelectionsCleared )
		return "Clear Selections";
	else if( vMouseActions.front() == k_SelectionToggled )
		return "Toggle Selections";
	else if( vMouseActions.front() == k_SelectionSingle )
		return "Single-Select";
	else
		return "Action Unknown";
}

/**
 * Used to calculate the position of a point that would maintain a given aspect ratio when resizing icons.
 *
 * Given a point and a selection mode (which edge of icon has been grabbed)
 * calculates the newX and newY of a point that would maintain the height to width ratio, dHtoW, passed in as a parameter
 *
 */
void CDrawGUIView::maintainAspectRatioOnResize(const LgbRectSelTypeEnum &eSelnMode, const CPoint point, float dHtoW, long &newX, long &newY)
{
	// if drag out top or bottom edge, adjust width to maintain aspect ratio
	// if drag out left or right edge, adjust height to maintain aspect ratio
	// if drag out a corner, if move in x-axis more then y-axis adjust height, else adjust width to maintain aspect ratio
	if (m_eSelnMode == k_LgbDrawableTop || m_eSelnMode == k_LgbDrawableBtm) {
		long deltaY = point.y - m_cInitialClickPt.y;
		newX = m_cInitialClickPt.x + floor(float(deltaY) / dHtoW);
	} else if (m_eSelnMode == k_LgbDrawableLft || m_eSelnMode == k_LgbDrawableRgt) {
		long deltaX = point.x - m_cInitialClickPt.x;
		newY = m_cInitialClickPt.y + ceil(float(deltaX) * dHtoW);							
	} else {
		long deltaX = point.x - m_cInitialClickPt.x;
		long deltaY = point.y - m_cInitialClickPt.y;
		// if dragging out a corner, if x-axis has greater movement than y-axis, then adjust height, else adjust width to maintain aspect ratio
		if ((deltaX * deltaX) >= (deltaY * deltaY)) {
			deltaY = ceil(float(deltaX) * dHtoW);
			// if dragging top left or bottom right, need to reverse sign of adustment
			if (m_eSelnMode == k_LgbDrawableTopRgt || m_eSelnMode == k_LgbDrawableLwrLft) {
				newY = m_cInitialClickPt.y - deltaY;
			} else {
				newY = m_cInitialClickPt.y + deltaY;
			}
		} else {
			deltaX = floor(float(deltaY) / dHtoW);
			// if dragging top left or bottom right, need to reverse sign of adustment
			if (m_eSelnMode == k_LgbDrawableTopRgt || m_eSelnMode == k_LgbDrawableLwrLft) {
				newX = m_cInitialClickPt.x - deltaX;
			} else {
				newX = m_cInitialClickPt.x + deltaX;
			}
		}
	}
}

void CDrawGUIView::OnLButtonUp(UINT nFlags, CPoint point) 
{

	CString csAction = "";
	int iWidth, iHeight;

	// maintain our own button flag's state.
	m_bMouseIsDown = false;

	bool bDragged;

	if( abs(point.x - m_cInitialClickPt.x) > 2 ||  abs(point.y - m_cInitialClickPt.y) > 2 )
		bDragged = true;
	else
		bDragged = false;


	if(m_eSelnMode==k_LgbDrawableInterior){

		// The initial click was in the centre of an icon - user wanted to translate selected icon(s).

		if( bDragged )
		{
			// The main prompt for the user should be 'move' - even if selections were changed in process of moving

			m_cDrawableBag.moveIcons(point - m_cInitialClickPt);

			csAction = "Move (";
			csAction = csAction + intToString( (point - m_cInitialClickPt).cx );
			csAction += ",";
			csAction = csAction + intToString( (point - m_cInitialClickPt).cy );
			csAction +=  ")";

			//saveUndoAction( csAction );

		}else{
	
			if(m_vMouseActions.size()>0)
				csAction = getBestPrompt( m_vMouseActions );
			else
				csAction = "";

		}

	} else if(m_eSelnMode==k_LgbDrawableOutside){

		// User was doing the marquee-drag
		CClientDC dc(this);

		// If marquee was drawn lower-left -> upper right, get anything at least partly within.
		bool getPartials = point.x < m_cInitialClickPt.x;
		bool m_bCtrlKeyDown = (GetKeyState(VK_CONTROL)<0);

		bool bAnythingChanged = m_cDrawableBag.setSelectedIcons( LgbRect( m_cInitialClickPt, point ), 
			getPartials, m_bCtrlKeyDown );

		if( m_cDrawableBag.size() > 0 && bAnythingChanged ){

			m_cDrawableBag.setCollectiveState(LgbDrawable::k_Master, false );
			//m_cDrawableBag.setSelnState( true, k_LgbAllIconTypes );
			m_cDrawableBag.copySelectedDrawables( m_cSelectionBag );

			// If anything is selected, set up the 'masters'
			if( m_iNumberIconsCurrentlySelected = m_cSelectionBag.size() ){
				LgbDrawable *pNewMasterIcon = m_cSelectionBag.front();
				m_cDrawableBag.setCollectiveState( LgbDrawable::k_Master, false );
				m_cDrawableBag.setMasterIcon( pNewMasterIcon );
			}

			csAction = "Change Selections";
		}



	} else {

		// User clicked on the Edge of a selected item

		if( bDragged ) {

			long newY = point.y;
			long newX = point.x;

			IconSelection< LgbTextIcon >  textIcons;
			IconSelection< LgbPatchIcon >  ptchIcons;
			IconSelection< LgbImageIcon > imageIcons;

			vector< LgbDrawable * > vOrigDrawables;
			vector< LgbRect > vMorphedRects;

			m_cDrawableBag.getSelections( textIcons, ptchIcons, imageIcons );

			for(size_t i=0;i<textIcons.size();i++){
				vOrigDrawables.push_back( textIcons.getItem(i) );
			}

			for(size_t i=0;i<ptchIcons.size();i++){
				vOrigDrawables.push_back( ptchIcons.getItem(i) );
			}

			for(size_t i=0;i<imageIcons.size();i++){
				vOrigDrawables.push_back( imageIcons.getItem(i) );

				// if we are locked to aspect ratio of image, adjust the resize of the image to respect the aspect ratio
				if (imageIcons.getItem(i)->getLockAspect() == 1) {
					float dHtoW = imageIcons.getItem(i)->getImageHtoW();
					maintainAspectRatioOnResize(m_eSelnMode, point, dHtoW, newX, newY);

					// as we are changing both height and width no matter which edge grabbed, change sel mode to drag corner
					if (m_eSelnMode == k_LgbDrawableLft || m_eSelnMode == k_LgbDrawableTop) {
						m_eSelnMode = k_LgbDrawableTopLft;
					} else if (m_eSelnMode == k_LgbDrawableRgt || m_eSelnMode == k_LgbDrawableBtm) {
						m_eSelnMode = k_LgbDrawableLwrRgt;
					}
				}
			}

			const CPoint fixedAspectPoint(newX, newY);

			// getMorphedRectangles uses a divide by the width so can't have zero width.
			if (m_cDrawableBag.getMasterIcon()->m_cRect.Width() == 0) {
				iWidth = 1;
			}
			else {
				iWidth = m_cDrawableBag.getMasterIcon()->m_cRect.Width();
			}

			// getMorphedRectangles uses a divide by the height so can't have zero height.
			if (m_cDrawableBag.getMasterIcon()->m_cRect.Height() == 0) {
				iHeight = 1;
			}
			else {
				iHeight = m_cDrawableBag.getMasterIcon()->m_cRect.Height();
			}

			m_cDrawableBag.getMorphedRectangles(
				m_eSelnMode, 
//				point - m_cInitialClickPt, 
				fixedAspectPoint - m_cInitialClickPt, 
				iWidth, 
				iHeight, 
				true,
				vOrigDrawables, 
				vMorphedRects );

			m_cDrawableBag.setMorphedRectangles(
						vOrigDrawables,
						vMorphedRects 
						);

			csAction = "Resize (";
			csAction = csAction + intToString( (fixedAspectPoint - m_cInitialClickPt).cx );
			csAction += ",";
			csAction = csAction + intToString( (fixedAspectPoint - m_cInitialClickPt).cy );
			csAction +=  ")";

		} else {
			if(m_vMouseActions.size()>0) {
				csAction = getBestPrompt( m_vMouseActions );
			}
			else {
				csAction = "";
			}
		}
	}


	saveUndoAction( csAction );

	// InvalidateRect(LgbRect( m_cInitialClickPt, point )); // need to maintain 
	// Reset flags ready for next click
	BlitCompo();


	m_eSelnMode=k_LgbDrawableOutside;
	pDoc->uptodate=0;
	pDoc->SetModifiedFlag();
	CView::OnLButtonUp(nFlags, point);
}


void CDrawGUIView::OnMouseMove( UINT nFlags, CPoint point ) 
{

	if(m_bMouseIsDown){

		if(k_LgbDrawableOutside  == m_eSelnMode){

			// Assume user is dragging a selection marquee
			CClientDC dc(this);
			CPen pen( PS_SOLID, 2, RGB( 200, 80, 80 ) );
			dc.SelectObject(pen);
			dc.SetROP2( R2_XORPEN );

			// Draw an xor rect between initial clickPt and latest dragPt, and between 
			// initial clickPt and last-but-1 dragPt.  then the lst-but-1 rect reverts back to the original
			// screen pixels!
			drawGhostRectangles(	LgbRect( m_cInitialClickPt, point ),
									LgbRect( m_cInitialClickPt, m_cPreviousPt ),
									&dc );

			//InvalidRect.bottom=m_cInitialClickPt.y);
			// Record this point as 'last point for next time'.  This enables the rectangle from last time to
			// be redrawn (in XOR mode ) so that the pixels underneath it return to their as-drawn state.
			m_cPreviousPt = point;

		} else {
			// User is dragging positions of, or resizing, icons
			CClientDC dc(this);
			CPen pen(PS_SOLID, 2, RGB( 255, 0, 0 ));
			dc.SetROP2( R2_XORPEN );

			long newX = point.x;
			long newY = point.y;
			LgbRectSelTypeEnum origSelMode = m_eSelnMode;

			// if an edge has been grabbed, apply aspect ratio to resizing of image icons
			if (m_eSelnMode != k_LgbDrawableInterior) {
				IconSelection< LgbTextIcon >  textIcons;
				IconSelection< LgbPatchIcon >  ptchIcons;
				IconSelection< LgbImageIcon > imageIcons;

				m_cDrawableBag.getSelections( textIcons, ptchIcons, imageIcons );

				for(size_t i=0;i<imageIcons.size();i++){

					// if we are locked to aspect ratio of image, adjust the resize of the image to respect the aspect ratio
					if (imageIcons.getItem(i)->getLockAspect() == 1) {
						float dHtoW = imageIcons.getItem(i)->getImageHtoW();
						maintainAspectRatioOnResize(m_eSelnMode, point, dHtoW, newX, newY);

						// as we are changing both height and width no matter which edge grabbed, temporarily change sel mode to drag corner
						if (m_eSelnMode == k_LgbDrawableLft || m_eSelnMode == k_LgbDrawableTop) {
							m_eSelnMode = k_LgbDrawableTopLft;
						} else if (m_eSelnMode == k_LgbDrawableRgt || m_eSelnMode == k_LgbDrawableBtm) {
							m_eSelnMode = k_LgbDrawableLwrRgt;
						}
					}
				}
			}

			const CPoint fixedAspectPoint(newX, newY);


			//Draw in XOR mode the outlines of the selected rects in their current drag position.
			m_cDrawableBag.drawGhostDragOutlines( 
											m_eSelnMode, 
											fixedAspectPoint - m_cInitialClickPt, 
											m_cPreviousPt - m_cInitialClickPt, 
											&dc );

			m_cPreviousPt = fixedAspectPoint;
			// important to restore the sel mode when dragging as needed by buttonUp
			m_eSelnMode = origSelMode;

		//	BlitCompo();

		} 

	} else {  // if!(m_bMouseIsDown)


		

		// The mouse isn't down.
		// Detect if the user has moved over a selected icon.
		// If so, detect if the icon is selected.  If so,
		// we need to hange the mouse to a 'move' cursor.
		// Otherwise there is no way for the user to move a group of selected icons.

		LgbDrawable *pIcon;
		LgbRectSelTypeEnum selMode = m_cDrawableBag.getSelectedIcon( point, pIcon );
		LgbImageIcon *pImageIcon = NULL;
		pImageIcon = (LgbImageIcon*)pIcon;

		if( pIcon!=NULL ){

			if ((pIcon->getClassId() == k_LgbTextIcon) || (pIcon->getClassId() == k_LgbPatchIcon) ||
				(pIcon->getClassId() == k_LgbImageIcon)) {
					
				if( (selMode==k_LgbDrawableLft) || (selMode==k_LgbDrawableRgt) ){

					::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEWE));

				} else if( (selMode==k_LgbDrawableTop) || (selMode==k_LgbDrawableBtm) ){

					::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZENS));

				} else if( (selMode==k_LgbDrawableTopLft) || (selMode==k_LgbDrawableLwrRgt) ){

					::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZENWSE));

				} else if( (selMode==k_LgbDrawableTopRgt) || (selMode==k_LgbDrawableLwrLft) ){

					::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZENESW));

				} else if( selMode==k_LgbDrawableInterior){

					::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEALL));

				}
			}

		} // if(pIcon!=NULL)

	} // if!(m_bMouseIsDown)

	CView::OnMouseMove(nFlags, point);
}


void CDrawGUIView::LoadGUIInfFromGuiFile(CString csFileName)
{
	// Assume that if 1st icon shows it tag, they all do.
	bool bResetTagDisplay = false;
	bool bShowTags;
	if(m_cDrawableBag.size()){
		bResetTagDisplay = true;
		bShowTags = m_cDrawableBag.front()->m_bShowTag;
	}

	m_cDrawableBag.reset();

	std::vector<LgbTextIconEssentialData_t> textIcons;
	std::vector<LgbPatchIconEssentialData_t> ptchIcons;
	std::vector<LgbImageIconEssentialData_t> imageIcons;
	std::vector<LgbTextStyleEssentialData_t> vTextStyles;

	parseGuiFile(csFileName, textIcons, ptchIcons, imageIcons, vTextStyles);

	for (size_t i=0;i<textIcons.size();i++) {
		// Add the text styles to the first textbox only, since text styles is a class variable
		if (i==0) {
			AddTextboxIcon(textIcons[i], vTextStyles);
		}
		else {
			AddTextboxIcon(textIcons[i]);
		}
	}

	for(size_t i=0;i<ptchIcons.size();i++)
		AddPatchIcon( ptchIcons[i] );

	for(size_t i=0;i<imageIcons.size();i++)
		AddBitmapIcon( imageIcons[i] );

	m_cDrawableBag.sortAscending();

	// Set tag display state to original value.
	if(bResetTagDisplay) m_cDrawableBag.setTagShowState( bShowTags );

	// Do this to ensure that z-dlog gets set.  Otherwise, if project is
	// opened by MRU, and there is only one layout opened at start, the dlog gets
	// set to 0-1, and if you touch it, the icons may get hidden (if they all lie at 
	// (say) z 5-9, and then the only workaround is to give focus to another app, then back 
	// to LGB.  This is because getting the focus sets the z-dlog
	refreshZDialog(); 



	BlitCompo();
}

void CDrawGUIView::resetUndoStore()
{
	CDrawGUIViewStore  tmp;
	tmp.copyFrom( this );
	m_cLgbUndoStore.reset( m_bEnableUndo, m_bEnableRedo, m_csUndoPrompt, m_csRedoPrompt, tmp );
	//SaveGUIInf( csUndoFile );
}

void CDrawGUIView::SaveGUIInf(CString fileName)
{
	m_cDrawableBag.saveToFile(fileName);
}


void CDrawGUIView::UpdateProjectMetaData()
{
	m_cDrawableBag.UpdateProjectMetaData();
}

void CDrawGUIView::ResetAll() {
	m_cDrawableBag.reset();
	init();
}

void CDrawGUIView::AddBitmapIcon( const LgbImageIcon &imageIcon )
{
	LgbImageIcon	*pBmpIcon = NULL;

	pBmpIcon = new LgbImageIcon( imageIcon );

	assert( NULL != pBmpIcon );

	m_cDrawableBag.push_back(pBmpIcon);

}

void CDrawGUIView::AddBitmapIcon( const LgbImageIconEssentialData_t &imageIcon )
{
	LgbImageIcon	*pBmpIcon = NULL;

	CString projDir;
	CDrawGUIApp *pApp = ( CDrawGUIApp *  )AfxGetApp();
	pApp->m_ProjectMetaData.getProjectDir(projDir);

	CRect rect(		imageIcon.basics.xTopLft, 
					imageIcon.basics.yTopLft,
					imageIcon.basics.xTopLft+imageIcon.basics.width,
					imageIcon.basics.yTopLft+imageIcon.basics.height );

	pBmpIcon = new LgbImageIcon(	rect, 
									imageIcon.basics.type,
									imageIcon.basics.tag,
									imageIcon.basics.zPos,
									imageIcon.alpha,
									projDir,
									imageIcon.bitmapFileName,
									imageIcon.lockAspect
									);

	assert( NULL != pBmpIcon );

	m_cDrawableBag.push_back(pBmpIcon);

}



void CDrawGUIView::AddBitmapIcon(
						const CString	&type,
						const CString	&tag,
						const CRect		&rect,
						const int		&zPos,
						const int		&alpha,
						const CString	&bitmapFileName,
						const int			&lockAspect
						)
{

	assert( type == "GUI_Bitmap");

	LgbImageIcon	*pBmpIcon = NULL;

	CString projDir;
	CDrawGUIApp *pApp = ( CDrawGUIApp *  )AfxGetApp();
	pApp->m_ProjectMetaData.getProjectDir(projDir);

	pBmpIcon = new LgbImageIcon( rect, type, tag, zPos, alpha, projDir, bitmapFileName, lockAspect );
	assert( NULL != pBmpIcon );

	pBmpIcon->setAlpha( alpha );

	m_cDrawableBag.push_back(pBmpIcon);

}


void CDrawGUIView::AddTextboxIcon( const LgbTextIcon &textIcon )
{

	LgbTextIcon	*pTxtIcon = NULL;

	pTxtIcon = new LgbTextIcon( textIcon );
	assert( NULL != pTxtIcon );

	m_cDrawableBag.push_back(pTxtIcon);

}

void CDrawGUIView::AddTextboxIcon( const LgbTextIconEssentialData_t &icon )
{

	CRect rect(	icon.basics.xTopLft, 
				icon.basics.yTopLft,
				icon.basics.xTopLft+icon.basics.width,
				icon.basics.yTopLft+icon.basics.height );

	LgbTextIcon	*pTxtIcon = NULL;

	LgbColorsDef tmpCols;

	tmpCols.m_iBgAlpha = (unsigned char ) icon.bgAlpha;
	tmpCols.m_iBgRed = (unsigned char )icon.bgRed;
	tmpCols.m_iBgGreen = (unsigned char )icon.bgGreen;
	tmpCols.m_iBgBlue = (unsigned char )icon.bgBlue;

	tmpCols.m_iFgAlpha = (unsigned char )icon.fgAlpha;
	tmpCols.m_iFgRed = (unsigned char )icon.fgRed;
	tmpCols.m_iFgGreen = (unsigned char )icon.fgGreen;
	tmpCols.m_iFgBlue = (unsigned char )icon.fgBlue;


	pTxtIcon = new LgbTextIcon(	rect, 
								icon.basics.type,
								icon.basics.tag,
								icon.basics.zPos,
								tmpCols
									);

	assert( NULL != pTxtIcon );

	pTxtIcon->setFont(icon.csFont);
	pTxtIcon->setLeftIndent(icon.leftIndent);
	pTxtIcon->setRightIndent(icon.rightIndent);
	pTxtIcon->setTopIndent(icon.topIndent);
	pTxtIcon->setBottomIndent(icon.bottomIndent);
	pTxtIcon->setLineSpacing(icon.lineSpacing);

	m_cDrawableBag.push_back(pTxtIcon);

}

void CDrawGUIView::AddTextboxIcon(const LgbTextIconEssentialData_t &icon, const vector<LgbTextStyleEssentialData_t> vTextStyles)
{
	vector<InlineText> vTextboxTextStyles;

	CRect rect(	icon.basics.xTopLft, 
				icon.basics.yTopLft,
				icon.basics.xTopLft+icon.basics.width,
				icon.basics.yTopLft+icon.basics.height );

	LgbTextIcon	*pTxtIcon = NULL;

	LgbColorsDef tmpCols;

	tmpCols.m_iBgAlpha = (unsigned char ) icon.bgAlpha;
	tmpCols.m_iBgRed = (unsigned char )icon.bgRed;
	tmpCols.m_iBgGreen = (unsigned char )icon.bgGreen;
	tmpCols.m_iBgBlue = (unsigned char )icon.bgBlue;

	tmpCols.m_iFgAlpha = (unsigned char )icon.fgAlpha;
	tmpCols.m_iFgRed = (unsigned char )icon.fgRed;
	tmpCols.m_iFgGreen = (unsigned char )icon.fgGreen;
	tmpCols.m_iFgBlue = (unsigned char )icon.fgBlue;


	pTxtIcon = new LgbTextIcon(	rect, 
								icon.basics.type,
								icon.basics.tag,
								icon.basics.zPos,
								tmpCols
									);

	assert( NULL != pTxtIcon );

	// create a vector of text styles
	for (size_t i=0; i<vTextStyles.size(); i++) {
		tmpCols.m_iFgAlpha = (unsigned char )vTextStyles[i].alpha;
		tmpCols.m_iFgRed = (unsigned char )vTextStyles[i].red;
		tmpCols.m_iFgGreen = (unsigned char )vTextStyles[i].green;
		tmpCols.m_iFgBlue = (unsigned char )vTextStyles[i].blue;
		InlineText xTextStyle(vTextStyles[i].csClass, tmpCols, vTextStyles[i].csFont);
		vTextboxTextStyles.push_back(xTextStyle);
	}
	pTxtIcon->c_vInlineTextVec = vTextboxTextStyles;

	pTxtIcon->setFont(icon.csFont);
	pTxtIcon->setLeftIndent(icon.leftIndent);
	pTxtIcon->setRightIndent(icon.rightIndent);
	pTxtIcon->setTopIndent(icon.topIndent);
	pTxtIcon->setBottomIndent(icon.bottomIndent);
	pTxtIcon->setLineSpacing(icon.lineSpacing);

	m_cDrawableBag.push_back(pTxtIcon);

}

void CDrawGUIView::AddTextboxIcon(
						const CString		&type,
						const CString		&tag,			
						const CRect			&rect,
						const int			&zPos,
						const LgbColorsDef	&colors
						)
{

	LgbTextIcon					*pTxtIcon		= NULL;
	assert( type=="GUI_TextBox2");

	pTxtIcon = new LgbTextIcon( rect, type, tag, zPos, colors );
	assert( NULL != pTxtIcon );

	m_cDrawableBag.push_back(pTxtIcon);

}





















void CDrawGUIView::AddPatchIcon( const LgbPatchIcon &patchIcon )
{

	LgbPatchIcon	*pPtchIcon = NULL;

	pPtchIcon = new LgbPatchIcon( patchIcon );
	assert( NULL != pPtchIcon );

	m_cDrawableBag.push_back(pPtchIcon);

}




void CDrawGUIView::AddPatchIcon( const LgbPatchIconEssentialData_t &icon )
{

	CRect rect(	icon.basics.xTopLft, 
				icon.basics.yTopLft,
				icon.basics.xTopLft+icon.basics.width,
				icon.basics.yTopLft+icon.basics.height );

	LgbPatchIcon	*pPatchIcon = NULL;

	LgbColorsDef tmpCols;

	tmpCols.m_iBgAlpha = (unsigned char ) icon.bgAlpha;
	tmpCols.m_iBgRed = (unsigned char )icon.bgRed;
	tmpCols.m_iBgGreen = (unsigned char )icon.bgGreen;
	tmpCols.m_iBgBlue = (unsigned char )icon.bgBlue;

	tmpCols.m_iFgAlpha = 0;
	tmpCols.m_iFgRed = 0;
	tmpCols.m_iFgGreen = 0;
	tmpCols.m_iFgBlue = 0;


	pPatchIcon = new LgbPatchIcon(	rect, 
								icon.basics.type,
								icon.basics.tag,
								icon.basics.zPos,
								tmpCols
									);

	assert( NULL != pPatchIcon );

	m_cDrawableBag.push_back(pPatchIcon);

}

void CDrawGUIView::AddPatchIcon(
						const CString		&type,
						const CString		&tag,			
						const CRect			&rect,
						const int			&zPos,
						const LgbColorsDef	&colors
						)
{

	LgbPatchIcon					*pPatchIcon		= NULL;
	assert( type=="GUI_Patch");

	pPatchIcon = new LgbPatchIcon( rect, type, tag, zPos, colors );
	assert( NULL != pPatchIcon );

	m_cDrawableBag.push_back(pPatchIcon);

}


void CDrawGUIView::OnInitialUpdate() 
{
	CString Info;

	CView::OnInitialUpdate();
	pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	//CMainFrame *pMainFrm = ( CMainFrame * ) GetParentFrame();
	//pMainFrm->resetChildTitles();
}


void CDrawGUIView::LoadSODL() {

	const CString INITIAL_DESCR = "";

	const int INITIAL_ZPOS = 1; // One must start counting from somewhere

	int currentZPos = INITIAL_ZPOS;

	CString dummyCs;

	const CPoint posIncr(50,20);

	CString widgetTag = "";
	CString bmpPath;
	CString copyBMP;
	CString descript;

	// (MSR) - I don't know what this does.
	_chdir(IPICPROGSDIR);


	// Build up path to sodl file.
	CString projDir;
	CString sodlPath;

	CDrawGUIApp *pApp = ( CDrawGUIApp *  )AfxGetApp();
	pApp->m_ProjectMetaData.getProjectDir(projDir);

	sodlPath = projDir  + SODLDIR + SODLFILENAME;

	CDocTemplate *pDocTemplate = pApp->m_pDocTemplate;

	bool iconAdded = false; // Did loading sodl change contents?

	CFileOperation fileOp;

	if( fileOp.CheckPath(sodlPath)==PATH_NOT_FOUND){

		CString cStr1 = "The sodl file\n(= " + sodlPath +") wasn't found:\n";
		cStr1 += "You may need to write-out the sodl file via\nLucidApplicationBuilder";
		AfxMessageBox(cStr1);

	} else {

		CRect posRect(50,50,50+110,50+60);

		ifstream datafile(sodlPath);

		char ctype[1024];
		char tmp1[1024], tmp2[1024];

		pDoc = GetDocument();
		ASSERT_VALID(pDoc);


		// set the exists flag in all the gui items to false. When the gui items are in the
		// sodl the flag is set to true. All the gui items that are false after the sodl is read
		// in can be deleted.

		m_cDrawableBag.setDeletionTags(true);

		CString type;
		CString targetFileName;
		CString thisTargetFileName = GetDocument()->m_csTargetFileName;
		
		if (datafile.bad()) {  // just to test
			CString cStr1 = "Problem reading the sodl file\n(= " + sodlPath +")\n";
		cStr1 += "You may need to write-out the sodl file via\nLucidApplicationBuilder";
		AfxMessageBox(cStr1);

		}

		while ((!datafile.eof()) && (!datafile.bad())) {
			datafile.getline(ctype,1023);
			if (!datafile.good()) break; //just in case
			
			if ( //@todo this should be a generic list got from a target specific module database
				//(strstr(ctype,"BEGIN gui_viewport")==ctype) ||//@todo these need to be removed - these are causing the viewports to look like text boxes
				//(strstr(ctype,"BEGIN DtvPvrPlay2")==ctype)	|| //@todo these need to be removed - these are causing the viewports to look like text boxes
				(strstr(ctype,"BEGIN GUI_OutputTextBoxBool")==ctype)	||
				(strstr(ctype,"BEGIN GUI_OutputTextBoxInt")==ctype)		||
				(strstr(ctype,"BEGIN GUI_OutputTextBoxString")==ctype)	||
				(strstr(ctype,"BEGIN GUI_OutputTextBoxReal")==ctype)	||
				(strstr(ctype,"BEGIN GUI_InputTextBoxInt")==ctype)		||
				(strstr(ctype,"BEGIN GUI_InputTextBoxReal")==ctype)		||
				(strstr(ctype,"BEGIN GUI_InputTextBoxString")==ctype)	||
				(strstr(ctype,"BEGIN gui_text_bool")==ctype)		||
				(strstr(ctype,"BEGIN gui_text_int")==ctype)		||
				(strstr(ctype,"BEGIN gui_text_string")==ctype)		||
				(strstr(ctype,"BEGIN gui_text_real")==ctype)  )
			{

				// first line after BEGIN contains tag
				datafile >> tmp1 >> tmp2;
				widgetTag = tmp1;
				widgetTag.Delete(0,4);
				targetFileName = tmp2;

				if(targetFileName == thisTargetFileName){

					// The widget belongs to the current file's wigdet-group.

					LgbDrawableIt_t it;
					type = "GUI_TextBox2";

					// if the gui item does not exist then add it
					if ( m_cDrawableBag.isAlreadyInList(type, widgetTag,  it) ) {

						LgbDrawable *pDraw = *it;
						pDraw->m_bIsToBeDeleted = false;

					}else{

						iconAdded = TRUE;
						posRect.OffsetRect( posIncr );
						if (posRect.bottom > 600) {
							posRect.MoveToXY(140, 50 );
						}
						LgbColorsDef cols;
						AddTextboxIcon(type, widgetTag, posRect, currentZPos++ , cols );
					}
				} 

			//} else if (strcmp(ctype,"BEGIN GUI_Image1")==0) {
			// The string may be BEGIN GUI_Image1, BEGIN GUI_Image2 in future, so just search without the integer.

			} else if ((strstr(ctype,"BEGIN gui_Patch")==ctype) || (strstr(ctype,"BEGIN gui_patch")==ctype) || (strstr(ctype,"BEGIN DtvPvrPlay2")==ctype) || (strstr(ctype,"BEGIN gui_viewport")==ctype)) {
				// first line after BEGIN contains tag
				datafile >> tmp1 >> tmp2;
				widgetTag = tmp1;
				widgetTag.Delete(0,4);
				targetFileName = tmp2;

				if(targetFileName == thisTargetFileName){

					LgbDrawableIt_t it;

					// NB. The gui file's 'type' string IS different from the sodl file equivalent string
					//type = "";
					type = "GUI_Patch"; 

					// if the gui item does not exist then add it
					if ( m_cDrawableBag.isAlreadyInList(type, widgetTag,  it) ) {
						LgbDrawable *pDraw = *it;
						pDraw->m_bIsToBeDeleted = false;
					}else{
						iconAdded = TRUE;
						posRect.OffsetRect( posIncr );
						if (posRect.bottom > 600) {//@todo neds the current window size here 
							posRect.MoveToXY(140, 50 );
						}
						LgbColorsDef cols;
						AddPatchIcon(type, widgetTag, posRect, currentZPos++ , cols );

					}
				}
			//} else if (strcmp(ctype,"BEGIN GUI_Image1")==0) {
			// The string may be BEGIN GUI_Image1, BEGIN GUI_Image2 in future, so just search without the integer 
			} else if ((strstr(ctype,"BEGIN GUI_Image")==ctype)||(strstr(ctype,"BEGIN gui_image")==ctype)||
					(strstr(ctype,"BEGIN GUI_Image_File") == ctype)) {

				// first line after BEGIN contains tag
				datafile >> tmp1 >> tmp2;
				widgetTag = tmp1;
				widgetTag.Delete(0,4);
				targetFileName = tmp2;

				if(targetFileName == thisTargetFileName){

					LgbDrawableIt_t it;

					// NB. The gui file's 'type' string IS different from the sodl file equivalent string
					type = "GUI_Bitmap";

					// if the gui item does not exist then add it
					if ( m_cDrawableBag.isAlreadyInList(type, widgetTag,  it) ) {
						LgbDrawable *pDraw = *it;
						pDraw->m_bIsToBeDeleted = false;
					}else{
						iconAdded = TRUE;
						posRect.OffsetRect( posIncr );
						if (posRect.bottom > 600) {
							posRect.MoveToXY(140, 50 );
						}
						AddBitmapIcon(type, widgetTag, posRect, currentZPos++, 
							IMAGE_ICON_DEFAULT_OPACITY, ICON_PLACEHOLDER_FILE, IMAGE_ICON_DEFAULT_LOCK_ASPECT_RATIO);

					}
				}
			}

		} // while ((!datafile.eof()) && (!datafile.bad()))
		
		int nDeleted = m_cDrawableBag.doDeletions();

		if(iconAdded || nDeleted){
			pDoc->SetModifiedFlag(TRUE);
		}

		_chdir(IPICGUIS);

		//m_cDrawableBag.update();
		m_cDrawableBag.sortAscending();

		BlitCompo();

		datafile.close();
		
		// Don't allow undo when SODL is loaded.
		m_cSelectionBag.reset();
		this->resetUndoStore();
		pApp->m_ProjectMetaData.populateBuildNumFromFile();

		//saveUndoAction( _T("Parse SODL") );
	} // if( (err=fileOp.CheckPath(sodlPath))==PATH_NOT_FOUND)
}


void CDrawGUIView::OnLOADAFXSODL() 
{
	LoadSODL();
}


CDrawGUIView * CDrawGUIView::GetView()
{
	CMDIChildWnd * pChild = ((CMDIFrameWnd*)(AfxGetApp()->m_pMainWnd))->MDIGetActive();

    if ( !pChild )
		return NULL;

    CView * pView = pChild->GetActiveView();

    if ( !pView )
		return NULL;

    // Fail if view is of wrong kind
    if ( ! pView->IsKindOf( RUNTIME_CLASS(CDrawGUIView) ) )
		return NULL;

	return (CDrawGUIView *) pView;
}


void CDrawGUIView::OnIconProperties() 
{

	CString projDir; 
	CDrawGUIApp *pApp = ( CDrawGUIApp *  )AfxGetApp();
	
	// holder for text box selections, that can process whether corresponding fields 
	// have common values across the selected icons of that type.
	IconSelection< LgbTextIcon > txtSelections;

		// Similarly, a holder for bitmap icons
	IconSelection< LgbPatchIcon > ptchSelections;

	// Similarly, a holder for bitmap icons
	IconSelection< LgbImageIcon > bmpSelections;

	// Load selected items from dbag into the respective processor holders
	m_cDrawableBag.getSelections( txtSelections, ptchSelections, bmpSelections );

	// Initialise result of dialog 'show' to be anything but IDOK
	const int ANY_NUM = -1000;
	int res = IDOK - ANY_NUM;

	if(!pApp->m_ProjectMetaData.getLock()){

		AfxMessageBox( PMD_LOCK_FAILURE_MESSAGE );

	}else{

		pApp->m_ProjectMetaData.readProjectFile();

		int iTypeCount = 0;

		iTypeCount += (txtSelections.size()>0) ? 1 : 0;
		iTypeCount += (ptchSelections.size()>0) ? 1 : 0;
		iTypeCount += (bmpSelections.size()>0) ? 1 : 0;

		if( iTypeCount > 1){

			// Icons of more than  type are selected.
			// Show a dialog of properties common for text , patches & bmp's

			CProperties_Drawable dlog( &(pApp->m_ProjectMetaData), txtSelections, ptchSelections, bmpSelections  );
			res = dlog.DoModal();

		}else if( iTypeCount == 1){

			if(  txtSelections.size()>0  ){

				// Only textBox's selected
				CProperties_textbox dlog( &(pApp->m_ProjectMetaData),	txtSelections );
				res = dlog.DoModal();

			} else if(ptchSelections.size() > 0){

				// Only Patch icons are selected
				CProperties_Patch dlog( &(pApp->m_ProjectMetaData),	ptchSelections );
				res = dlog.DoModal();

			} else if( bmpSelections.size() > 0 ){

				// Only Bitmap icons are selected
				CProperties_Image dlog( &(pApp->m_ProjectMetaData),	bmpSelections );
				res = dlog.DoModal();

			}

		}else{

			assert(1==0);
		}


		if(res ==  IDOK ){

			m_cDrawableBag.sortAscending();

			saveUndoAction( _T("Dialog-Edit") );

			BlitCompo();

			pApp->m_ProjectMetaData.writeProjectFile();

			// Update the z-dialog for new min max z-pos's etc.
			refreshZDialog();
		}

	
		pApp->m_ProjectMetaData.releaseLock();

	} // if(!getLock())

}

void CDrawGUIView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
	CDrawGUIView *pDum = NULL;
	pDum = (CDrawGUIView *)pActivateView;
	CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void CDrawGUIView::OnActivateFrame(UINT nState, CFrameWnd* pDeactivateFrame)
{
	CView::OnActivateFrame(nState, pDeactivateFrame);
}

void CDrawGUIView::PostNcDestroy()
{
	CMainFrame *pMainFrm = ( CMainFrame * ) GetParentFrame();
	pMainFrm->resetChildTitles();

	CLabLgbBaseApp *pApp = (CLabLgbBaseApp *) AfxGetApp();

	// If there is 1 doc remaining at this point, it means that there about to be
	// (when windows has done its stuff) 0 docs open.
	// So set the z-order dlog ptr to null so that moving the slider doesn't crash the App.
	if(pApp->getOpenDocCount() == 1){

		// Set the view pointer of the z-order dialog bar to null.
		CMainFrame *pMnFrm = ( CMainFrame * ) AfxGetMainWnd();
		LgbZOrderDlogBar *pDum = pMnFrm->getZOrderDlogBarPtr();
		pDum->m_pCDrawGuiView = NULL;
	}
		
	CView::PostNcDestroy();
}

void CDrawGUIView::OnAlignmentLeftEdges()
{
	m_cDrawableBag.alignLft();

	saveUndoAction( _T("Align Lft Edges") );

	BlitCompo();
}

void CDrawGUIView::OnAlignmentRightEdges()
{
	m_cDrawableBag.alignRgt();

	saveUndoAction( _T("Align Rgt Edges") );

	BlitCompo();
}

void CDrawGUIView::OnAlignmentLeftRightCentres()
{
	m_cDrawableBag.alignLftRgtCntrs();

	saveUndoAction( _T("Align Lft/Rgt Cntrs"));

	BlitCompo();
}

void CDrawGUIView::OnAlignmentTopEdges()
{
	m_cDrawableBag.alignTop();

	saveUndoAction( _T("Align Top Edges"));

	BlitCompo();
}

void CDrawGUIView::OnAlignmentBottomEdges()
{
	m_cDrawableBag.alignBtm();

	saveUndoAction( _T("Align Btm Edges"));

	BlitCompo();
}

void CDrawGUIView::OnAlignmentTopBottomCentres()
{
	m_cDrawableBag.alignTopBtmCntrs();

	saveUndoAction( _T("Align Cntrs Vertically"));

	BlitCompo();
}

void CDrawGUIView::OnResizeWidth()
{
	m_cDrawableBag.equaliseWidths();

	saveUndoAction( _T("Equalize Widths"));

	BlitCompo();
}

void CDrawGUIView::OnResizeHeight()
{
	m_cDrawableBag.equaliseHeights();

	saveUndoAction( _T("Equalize Heights"));

	BlitCompo();
}

void CDrawGUIView::drawGhostRectangles(const LgbRect & rect1, const LgbRect & rect2, CClientDC *pDC ) const
{
	pDC->SetROP2( R2_XORPEN );
	rect1.Draw( 0, pDC );
	rect2.Draw( 0, pDC );

}

void CDrawGUIView::OnIconBringTofront()
{
	// The upper and lower bounding values of selected icon's zpos's.
	LgbZBounds_t zBoundsSelected;

	// The upper and lower bounding values of unselected icon's zpos's.
	LgbZBounds_t zBoundsUnselected;

	// load up the zbound positions
	LucidErrEnum err1, err2;
	err1 = m_cDrawableBag.getZBounds( zBoundsSelected, LgbDrawableBag::k_SelectedOnly );
	assert(  (err1 == kErr_NoErr) || (err1 == kErr_NoneSelected) );

	err2 = m_cDrawableBag.getZBounds( zBoundsUnselected, LgbDrawableBag::k_UnselectedOnly );
	assert(  (err2 == kErr_NoErr) || (err2 == kErr_NoneSelected) );

	// Only do anything if rearmost of current selections are not already in front of,
	// or at same level as, frontmost of non-selections.
	//NB.  If the rearmost / frontmost are at the same z-pos, do the move, as at the same z
	// apparent order is random, and the user will expect to see the thing he sent forwards
	// to appear to be forwards.
	if( (zBoundsSelected.rearMost <= zBoundsUnselected.frontMost) &&
		(err1 != kErr_NoneSelected  ) &&
		(err2 != kErr_NoneSelected  ) )
	{

		int offSet = zBoundsUnselected.frontMost  - zBoundsSelected.rearMost + 1;
		int newMaxZ = zBoundsSelected.frontMost + offSet;

		m_cDrawableBag.incrementSelectedZPos( offSet );

		// The new max z-level will be higher than 'max scaale' was before.
		// therefore the icon(s) just moved forward will seem to disappear.
		// To prevent this, refresh Z-dialog (so its new max is set to current max)
		refreshZDialog(true);

		saveUndoAction( _T("Bring to Front"));


		setUpperZActiveLevel( newMaxZ );
		BlitCompo();
	}

}

void CDrawGUIView::OnIconSendToRear()
{
	// ( See OnIconBringTofront for similar ).

	LgbZBounds_t zBoundsSelected;

	LgbZBounds_t zBoundsUnselected;

	LucidErrEnum err1, err2;
	err1 = m_cDrawableBag.getZBounds( zBoundsSelected, LgbDrawableBag::k_SelectedOnly );
	assert(  (err1 == kErr_NoErr) || (err1 == kErr_NoneSelected) );

	err2 = m_cDrawableBag.getZBounds( zBoundsUnselected, LgbDrawableBag::k_UnselectedOnly );
	assert(  (err2 == kErr_NoErr) || (err2 == kErr_NoneSelected) );


	// Only do anything if frontmost of current selections is not already behind rearmost
	// of non-selections.
	//NB.  If the rearmost / frontmost are at the same z-pos, do the move, as at the same z
	// apparent order is random, and the user will expect to see the thing he sent forwards
	// to appear to be forwards.
	if( (zBoundsSelected.frontMost >= zBoundsUnselected.frontMost) &&
		(err1 != kErr_NoneSelected  ) &&
		(err2 != kErr_NoneSelected  ) )
	{
		m_cDrawableBag.incrementSelectedZPos( zBoundsUnselected.rearMost - zBoundsSelected.frontMost - 1);

		saveUndoAction( _T("Send To Rear"));


		refreshZDialog();
		BlitCompo();
	}

}

void CDrawGUIView::OnIconMoveForward()
{
	const int FORWARDS_INCR = 1;
	m_cDrawableBag.incrementSelectedZPos(FORWARDS_INCR);
	refreshZDialog();

	saveUndoAction( _T("Move Forward"));

	BlitCompo();
}

void CDrawGUIView::OnIconMoveBackward()
{
	const int BACKWARDS_INCR = -1;
	m_cDrawableBag.incrementSelectedZPos(BACKWARDS_INCR);
	refreshZDialog();

	saveUndoAction( _T("Move Backward"));

	BlitCompo();
}

void CDrawGUIView::OnIconEqualiseToFrontmost()
{
	LgbZBounds_t zBounds;

	LucidErrEnum err = m_cDrawableBag.getZBounds( zBounds, LgbDrawableBag::k_Any );

	if(err==kErr_NoErr){
		m_cDrawableBag.setSelectedToZPos( zBounds.frontMost );
		refreshZDialog();

		saveUndoAction( _T("Equalize to Frontmost"));

		BlitCompo();
	}

}

void CDrawGUIView::OnIconEqualiseToRearmost()
{
	LgbZBounds_t zBounds;

	LucidErrEnum err = m_cDrawableBag.getZBounds( zBounds, LgbDrawableBag::k_Any );

	if(err==kErr_NoErr){
		m_cDrawableBag.setSelectedToZPos( zBounds.rearMost );
		refreshZDialog();

		saveUndoAction( _T("Equalize to Rearmost"));

		BlitCompo();
	}

}

void CDrawGUIView::OnOptionsDisplayWidgetLabels()
{
	m_bShowTags = !m_bShowTags;
	m_cDrawableBag.setTagShowState( m_bShowTags );

	saveUndoAction( _T("Toggle Label Display"));
	BlitCompo();
}

void CDrawGUIView::setUpperZActiveLevel(const int & val, bool bSave )
{
	m_cZDatVals.zClipVal = val;

#ifdef DEBUG
	char buff[100];
	sprintf_s( buff, 100, "%s %d, %d\n", "In CDrawGuiView ZLean, ZClip vals set to: ", m_cZDatVals.zLeanVal, m_cZDatVals.zClipVal );
	OutputDebugString(buff);
#endif

	if(m_bZSliderNeverMoved)m_bZSliderNeverMoved = false;

	m_cDrawableBag.setUpperZActiveLimit( val );

	if(bSave){
		CString csDum = "Z-Level -> " + intToString(val);
		saveUndoAction( _T(csDum));
	}

	BlitCompo();
}

void CDrawGUIView::setZLeanLevel(const int & val, bool bSave )
{
	m_cZDatVals.zLeanVal = val;

#ifdef DEBUG	
	char buff[100];
	sprintf_s( buff, 100, "%s %d, %d\n", "In CDrawGuiView ZLean, ZClip vals set to: ", m_cZDatVals.zLeanVal, m_cZDatVals.zClipVal );
	OutputDebugString(buff);
#endif

	m_cDrawableBag.setZlean(val);

	if(bSave){
		CString csDum = "Z-Lean Level -> " + intToString(val);
		saveUndoAction( _T(csDum));
	}

	BlitCompo();
}


void CDrawGUIView::OnSetFocus(CWnd* pOldWnd)
{
	CView::OnSetFocus(pOldWnd);


	// The 1st time a view gets focused, set the z-clip to max, so the user can see
	// everything.
	// Afterwards, the user will have set the zclip herself, and the view will
	// have been updated to whatever this value was.

	refreshZDialog();

	BlitCompo();

	if (!isFocusEventStarted) {
		isFocusEventStarted = true;
		// test for presence of Update SODL file
		// if present indicates that SODL needs to written in IAB and then loaded into IGB - inform user accordingly
		CLabLgbBaseApp *pApp = ( CLabLgbBaseApp * ) AfxGetApp();
		ProjectMetaData *pPMD = pApp->m_pProjMetaData;

		// check if SODL has been updated since the project has been opened
		if(pPMD->checkNewerSODLAvailable()){
			// just update the SODL, don't prompt
			LoadSODL();
		}
		isFocusEventStarted = false;
	}

	// update target location from registry
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CString csLocation = getLucidRegValue(_T(REG_TARGET_KEY),_T(REG_TARGET_LOCATION_VALUE),_T(DEFAULT_TARGET_LOCATION));
	((CLabLgbBaseApp *) AfxGetApp())->csCurrentTarget = csLocation;
	// update target combo box with remote ip address
	CString csRemoteIP = getLucidRegValue(_T(REG_TARGET_KEY),_T(REG_TARGET_REMOTE_IP_VALUE),_T(DEFAULT_TARGET_REMOTE_IP));
	pFrame->m_combo.DeleteString(TARGET_COMBO_INDEX_REMOTE);
	pFrame->m_combo.InsertString(TARGET_COMBO_INDEX_REMOTE,csRemoteIP);

	if (csLocation == REG_TARGET_LOCATION_DATA_APPSERVER) {
		pFrame->m_combo.SetCurSel(TARGET_COMBO_INDEX_APPSERVER);
	} else 	if (csLocation == REG_TARGET_LOCATION_DATA_REMOTE) {
		pFrame->m_combo.SetCurSel(TARGET_COMBO_INDEX_REMOTE);
	} else {
		pFrame->m_combo.SetCurSel(TARGET_COMBO_INDEX_LOCAL);
	}

}

void CDrawGUIView::refreshZDialog(const bool &setClipZToMax /*= true*/ )
{

	bool bCopySetClipZToMax = setClipZToMax;

	int nIcons = m_cDrawableBag.size();

	// Setup the zlean dialog ( which is shared betwen all views ) for this view.
	// Don't set the slider values - these are set in 'init', but thereafter
	// are got from the z dialog.

	std::vector<int> tics;// The z-levels which are occupied by an icon haave a tick-mark on the scale

	// load up these tic-mark positions
	m_cDrawableBag.loadTicMarks(tics);

	// Initialise the z-clip posn to 'max scale'
	if(m_cZDatVals.zClipVal == FLAG_NOT_YET_SET){
		m_cZDatVals.zClipVal = tics.back();
	}

	// Arbitrary values ....
	m_cZDatMaxMins.zLeanMax = 10;
	m_cZDatMaxMins.zLeanMin = 0;

	// nice for the user to have the zz-dlog echo the currently-focused view
	CString fileName = GetDocument()->m_csFullHostFileName;

	// If the user has never touched the z-clipping slider, make sure it is set
	// to max (to show everything!).

	if(m_bZSliderNeverMoved){
		bCopySetClipZToMax = true;
		m_cZDatVals.zClipVal = tics.back();
	} else
		bCopySetClipZToMax = false;


	m_pLgbZOrderDlogBar->syncWithView(	this,
									fileName,
									tics,
									bCopySetClipZToMax,
									m_cZDatMaxMins,
									m_cZDatVals
								); 

}

void CDrawGUIView::OnZRenumberConsectively()
{
	m_cDrawableBag.renumberConsec();
	refreshZDialog();

	saveUndoAction( _T("Z-Renumber consec"));

	BlitCompo();
}

void CDrawGUIView::OnZRenumberKeepGaps()
{
	m_cDrawableBag.renumberKeepGaps();
	refreshZDialog();

	saveUndoAction( _T("Z-Renumber Keeping gaps"));

	BlitCompo();
}

void CDrawGUIView::OnSelectionSelectAllBitmaps()
{
	// Maybe no bitmaps are present in sodl ...

	if( m_cDrawableBag.size() == 0 ){

		return;

	}else{

		m_cDrawableBag.setCollectiveState(LgbDrawable::k_Master, false );
		m_cDrawableBag.setCollectiveState( false, LgbDrawable::k_Selected, k_LgbAllIconTypes );
		m_cDrawableBag.setCollectiveState( true, LgbDrawable::k_Selected,  k_LgbBitmapOnly );

		// Copy the selecetd icons into the 'master-selection' list.
		m_cDrawableBag.copySelectedDrawables( m_cSelectionBag );

		// If anything is selected, set up the 'masters'
		if( m_iNumberIconsCurrentlySelected = m_cSelectionBag.size() ){
			LgbDrawable *pNewMasterIcon = m_cSelectionBag.front();
			m_cDrawableBag.setCollectiveState( LgbDrawable::k_Master, false );
			m_cDrawableBag.setMasterIcon( pNewMasterIcon );
		}

	}

	saveUndoAction( _T("Select All Bitmaps"));

	BlitCompo();
}

void CDrawGUIView::OnSelectionSelectAllTextBoxes()
{
	// See OnSelectionSelectAllBitmaps for similar.
	if( m_cDrawableBag.size() == 0 ){

		return;

	}else{
		// set nothing to be master
		m_cDrawableBag.setCollectiveState(LgbDrawable::k_Master, false );

		// set nothing to be selected
		m_cDrawableBag.setCollectiveState( false, LgbDrawable::k_Selected ,k_LgbAllIconTypes );

		// set all text boxes to be selected
		m_cDrawableBag.setCollectiveState( true, LgbDrawable::k_Selected , k_LgbTextBoxOnly );

		// Copy selections into 'masters' list
		m_cDrawableBag.copySelectedDrawables( m_cSelectionBag );

		// If anything is selected, (there may be no textboxes anyway!) set up the 'masters'
		// Do this cos otherwise the align / resize etc  has no master, and crashes.
		if( m_iNumberIconsCurrentlySelected = m_cSelectionBag.size() ){

			// The new master is whatever happened to go in 1st
			LgbDrawable *pNewMasterIcon = m_cSelectionBag.front();
			m_cDrawableBag.setCollectiveState( LgbDrawable::k_Master, false );
			m_cDrawableBag.setMasterIcon( pNewMasterIcon );
		}

	}
	saveUndoAction( _T("Select All Text Boxes"));
	BlitCompo();
}

void CDrawGUIView::OnSelectionSelectAllPatches()
{
	// See OnSelectionSelectAllBitmaps for similar.
	if( m_cDrawableBag.size() == 0 ){

		return;

	}else{
		// set nothing to be master
		m_cDrawableBag.setCollectiveState(LgbDrawable::k_Master, false );

		// set nothing to be selected
		m_cDrawableBag.setCollectiveState( false, LgbDrawable::k_Selected ,k_LgbAllIconTypes );

		// set all text boxes to be selected
		m_cDrawableBag.setCollectiveState( true, LgbDrawable::k_Selected , k_LgbPatchOnly );

		// Copy selections into 'masters' list
		m_cDrawableBag.copySelectedDrawables( m_cSelectionBag );

		// If anything is selected, (there may be no textboxes anyway!) set up the 'masters'
		// Do this cos otherwise the align / resize etc  has no master, and crashes.
		if( m_iNumberIconsCurrentlySelected = m_cSelectionBag.size() ){

			// The new master is whatever happened to go in 1st
			LgbDrawable *pNewMasterIcon = m_cSelectionBag.front();
			m_cDrawableBag.setCollectiveState( LgbDrawable::k_Master, false );
			m_cDrawableBag.setMasterIcon( pNewMasterIcon );
		}

	}
	saveUndoAction( _T("Select All Patches"));
	BlitCompo();
}

void CDrawGUIView::OnOptionsSelectAllWidgets()
{
	if( m_cDrawableBag.size() == 0 ){

		return;

	}else{
		m_cDrawableBag.setCollectiveState(LgbDrawable::k_Master, false );
		m_cDrawableBag.setCollectiveState( true, LgbDrawable::k_Selected, k_LgbAllIconTypes );
		m_cDrawableBag.copySelectedDrawables( m_cSelectionBag );

		// If anything is selected, set up the 'masters'
		if( m_iNumberIconsCurrentlySelected = m_cSelectionBag.size() ){
			LgbDrawable *pNewMasterIcon = m_cSelectionBag.front();
			m_cDrawableBag.setCollectiveState( LgbDrawable::k_Master, false );
			m_cDrawableBag.setMasterIcon( pNewMasterIcon );
		}

	}
	saveUndoAction( _T("Select All"));
	BlitCompo();
}

void CDrawGUIView::OnUpdateOptionsDisplayWidgetLabels(CCmdUI *pCmdUI)
{
	/*
	if(m_bShowTags){
		pCmdUI->SetText("Labels -> Off");
	}else{
		pCmdUI->SetText("Labels -> On");
	}
	*/
	pCmdUI->SetCheck( m_bShowTags );
}

void CDrawGUIView::OnUpdateAlignment(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( m_cDrawableBag.getSelectionCount() > 1);
}

void CDrawGUIView::OnViewZdialog()
{
	if(  (m_pLgbZOrderDlogBar->GetStyle() & WS_VISIBLE) ){
		m_pLgbZOrderDlogBar->ShowWindow( SW_HIDE );

	}else {

		m_pLgbZOrderDlogBar->ShowWindow( SW_NORMAL );
	}

}

void CDrawGUIView::OnUpdateViewZdialog(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( m_pLgbZOrderDlogBar->GetStyle() & WS_VISIBLE );
}

void CDrawGUIView::OnOptionsNativeviewbground()
{
	// Change background colors for this view only!

	m_bNativeBackgroundColors = !m_bNativeBackgroundColors;
	saveUndoAction( _T("Toggle Background"));

	BlitCompo();
}

void CDrawGUIView::OnUpdateOptionsNativeviewbground(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( m_bNativeBackgroundColors );
}

void CDrawGUIView::BlitCompo(void)
{
	CRect clientRect;
	GetClientRect( &clientRect );
	if (m_bWarningBackgroundColors) 
		m_cDrawableBag.Draw( GetDC(), clientRect, m_cStdWarningBackgroundColors );
	else if( m_bNativeBackgroundColors)
		m_cDrawableBag.Draw( GetDC(), clientRect, m_cStdNativeBackgroundColors );
	else
		m_cDrawableBag.Draw( GetDC(), clientRect, m_cStdEditingBackgroundColors );
}


BOOL CDrawGUIView::OnEraseBkgnd(CDC* pDC)
{
	return true;
}

void CDrawGUIView::OnIconSetfullyopaque()
{
	IconSelection< LgbTextIcon > textIcons;
	IconSelection< LgbPatchIcon > ptchIcons;
	IconSelection< LgbImageIcon > imageIcons;
	LgbTextIcon *pTxtIcon = NULL;
	LgbPatchIcon *pPtchIcon = NULL;
	LgbImageIcon *pImgIcon = NULL;

	m_cDrawableBag.getSelections( textIcons, ptchIcons, imageIcons );

	for( size_t i=0; i<textIcons.size(); i++ )
	{
		pTxtIcon = textIcons.getItem(i);
		pTxtIcon->setAlpha(255, 
			LgbTextIcon::LgbTextIcon_FlagText | LgbTextIcon::LgbTextIcon_FlagBackground );
	}

	for( size_t i=0; i<ptchIcons.size(); i++ )
	{
		pPtchIcon = ptchIcons.getItem(i);
		pPtchIcon->setAlpha(255, 
			LgbTextIcon::LgbTextIcon_FlagText | LgbTextIcon::LgbTextIcon_FlagBackground );
	}

	for( size_t i=0; i<imageIcons.size(); i++ )
	{
		pImgIcon = imageIcons.getItem(i);
		pImgIcon->setAlpha(255);
	}

	saveUndoAction( _T("Set Fully Opaque"));

	BlitCompo();
}

void CDrawGUIView::OnIconDecrementOpacity()
{
	IconSelection< LgbTextIcon > textIcons;
	IconSelection< LgbPatchIcon > ptchIcons;
	IconSelection< LgbImageIcon > imageIcons;

	LgbTextIcon *pTxtIcon = NULL;
	LgbPatchIcon *pPtchIcon = NULL;
	LgbImageIcon *pImgIcon = NULL;

	m_cDrawableBag.getSelections( textIcons, ptchIcons, imageIcons );

	for( size_t i=0; i<textIcons.size(); i++ )
	{
		pTxtIcon = textIcons.getItem(i);
		pTxtIcon->changeAlpha(-26 );
	}

	for( size_t i=0; i<ptchIcons.size(); i++ )
	{
		pPtchIcon = ptchIcons.getItem(i);
		pPtchIcon->changeAlpha(-26 );
	}

	for( size_t i=0; i<imageIcons.size(); i++ )
	{
		pImgIcon = imageIcons.getItem(i);
		pImgIcon->changeAlpha(-26);
	}

	saveUndoAction( _T("Decrement Opacity"));

	BlitCompo();
}

void CDrawGUIView::OnLgbShowTransferManager()
{
	CDrawGUIApp *pApp = ( CDrawGUIApp *) AfxGetApp();
	CString csProjectDir;
}


void CDrawGUIView::OnEditUndo()
{
	CDrawGUIViewStore store;
	m_cLgbUndoStore.undo( m_bEnableUndo, m_bEnableRedo, m_csUndoPrompt, m_csRedoPrompt, store );
	store.copyTo( this );
	OnSetFocus(NULL);
}

void CDrawGUIView::OnEditRedo()
{
	CDrawGUIViewStore store;
	m_cLgbUndoStore.redo( m_bEnableUndo, m_bEnableRedo, m_csUndoPrompt, m_csRedoPrompt, store );
	store.copyTo( this );
	OnSetFocus(NULL);
}


void CDrawGUIView::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	pCmdUI->SetText( m_csUndoPrompt  + "  Ctrl-Z");
	pCmdUI->Enable( m_bEnableUndo );
}

void CDrawGUIView::OnUpdateEditRedo(CCmdUI *pCmdUI)
{
	pCmdUI->SetText( m_csRedoPrompt + " Ctrl-Y");
	pCmdUI->Enable( m_bEnableRedo );
}

void CDrawGUIView::saveUndoAction( char *pszDesriptionOfAction )
{
	saveUndoAction( CString(pszDesriptionOfAction) );
}

void CDrawGUIView::saveUndoAction( CString &csDescriptionOfAction )
{
	// Because mouse clicks are Posted/ pumped rather than sent, you can get
	// apparently out-of-sequence clicks coming through.  These won't
	// be handled properly in terms of getting the 'action descrip'
	// correct.  easiest way to fix this is as below!

	if( csDescriptionOfAction.GetLength() > 0){
		CDrawGUIViewStore tmp;
		tmp.copyFrom( this );

		m_cLgbUndoStore.addAction( csDescriptionOfAction,
				m_bEnableUndo, m_bEnableRedo, m_csUndoPrompt, m_csRedoPrompt, tmp );
	}
}

void CDrawGUIView::OnLgbTransferAll()
{ transferToTarget( false ); }


void CDrawGUIView::OnLgbSendDataChanged()
{ transferToTarget( true ); }


void CDrawGUIView::transferToTarget(const bool &bUpdatedOnly )
{

	CLabLgbBaseApp *pApp = ( CLabLgbBaseApp * ) AfxGetApp();

	// start EHS - if starts successfully or is already running, send SODL (which also reloads app in EHS)
	if (pApp->startEHS(true)) {

		// force all GUIs to be saved
		CString csPathName;
		CDrawGUIApp *pGuiApp = ( CDrawGUIApp * ) AfxGetApp();
		POSITION pos = pGuiApp->m_pDocTemplate->GetFirstDocPosition();
		CDrawGUIDoc* pDoc = NULL;

		while (pos) {
			pDoc = (CDrawGUIDoc*) pGuiApp->m_pDocTemplate->GetNextDoc(pos);
			pDoc->SetModifiedFlag(true);
			csPathName = pDoc->GetPathName();
			pDoc->OnSaveDocument(csPathName);
		}

		pApp->c_pTgtTransProgressDlog->ShowWindow(SW_NORMAL);

		CString *pcsDum = new CString( "Tabulating Transferrables ..." );
		pApp->c_pTgtTransProgressDlog->SendMessage( UWM_SET_OVERALL_PROMPT, 0, (LPARAM)pcsDum  );

		Sleep(500);

		// read project file first to avoid overwriting changes made by LGB
		ProjectMetaData *pPMD = pApp->m_pProjMetaData;

		if( !pPMD->getLock() ){

			AfxMessageBox( PMD_LOCK_FAILURE_MESSAGE );

		}else{
			pApp->transferToTarget( bUpdatedOnly );

			// Write-out the latest transfer time.
			pPMD->updateTransferTime();
			pPMD->writeProjectFile();

			pPMD->releaseLock();

		}
	}
}


void CDrawGUIView::OnUpdateLgbTransferAll(CCmdUI *pCmdUI)
{
	CLabLgbBaseApp *pApp = ( CLabLgbBaseApp * ) AfxGetApp();
	ProjectMetaData *pPMD = pApp->m_pProjMetaData;
	m_bIsDirtySODL = false;
	bool bIsWarning = false;

	setStatusBarText("Ready"); // ready message

	// will always have dirty SODL if have dirty widgets
	if(pPMD->checkDirtyWidgets()){
		bIsWarning = true;
		m_bIsDirtySODL = true;
		setStatusBarText("Write SODL for this project in IAB: widgets updated in IAB");
		// NOTE - using status bar instead of modal dialog box as in WINE modal dialog box on window focus causes IGB to freeze
	} else if (pPMD->checkDirtySODL()) {
		m_bIsDirtySODL = true;
		setStatusBarText("Transfer of SODL disabled, write SODL for this project in IAB");
		// NOTE - using status bar instead of modal dialog box as in WINE modal dialog box on window focus causes IGB to freeze
	}
	// if there is a change in warning status, update background
	if (bIsWarning != m_bWarningBackgroundColors) {
		m_bWarningBackgroundColors = bIsWarning; // use warning colour for background
		BlitCompo();
	}
	pCmdUI->Enable((pApp->csCurrentTarget != REG_TARGET_LOCATION_DATA_APPSERVER) && !m_bIsDirtySODL);
}

void CDrawGUIView::OnUpdateLgbTransferChanged(CCmdUI *pCmdUI)
{
	CLabLgbBaseApp *pApp = ( CLabLgbBaseApp * ) AfxGetApp();
	ProjectMetaData *pPMD = pApp->m_pProjMetaData;
	pCmdUI->Enable( (pApp->csCurrentTarget != REG_TARGET_LOCATION_DATA_APPSERVER) && pApp->c_bSendAllToTargetHasOccurred && !m_bIsDirtySODL );
}

void CDrawGUIView::OnEHSInitParams(){
	((CLabLgbBaseApp *) AfxGetApp())->openEHSInitParamsDialog();	
}

void CDrawGUIView::OnEHSStartRestart(){
	((CLabLgbBaseApp *) AfxGetApp())->startEHS(false);	
}

void CDrawGUIView::OnEHSStop(){
	LucidTcpipClient tcpClient;
	LtsStatusType ltsStatusType;

	// connect to tcpip client
	if (( ltsStatusType = tcpClient.Connect()) != 0){
		AfxMessageBox("Unable to establish a TCPIP connection.");
	} else {

		if (( tcpClient.SendText("E\n")) != 0)	{
			AfxMessageBox("Unable to send command over TCPIP connection.");
		}
		// tidy up, close the port at this end
		tcpClient.DisConnect();
	}
}

void switchTarget(int iSelInd) {
	LucidTcpipClient tcpClient;

	CString csLocalIpAddress = DEFAULT_TARGET_LOCAL_IP;
	CString csLocalPort = getLucidRegValue(_T(REG_TARGET_KEY),_T(REG_TARGET_LOCAL_PORT_VALUE),_T(DEFAULT_TARGET_PORT));
	CString csRemoteIpAddress = getLucidRegValue(_T(REG_TARGET_KEY),_T(REG_TARGET_REMOTE_IP_VALUE),_T(DEFAULT_TARGET_REMOTE_IP));
	CString csRemotePort = getLucidRegValue(_T(REG_TARGET_KEY),_T(REG_TARGET_REMOTE_PORT_VALUE),_T(DEFAULT_TARGET_PORT));

	if (iSelInd == TARGET_COMBO_INDEX_LOCAL) {
		// local target selected
		tcpClient.SetIPAddress(csLocalIpAddress);
		tcpClient.SetPort(atoi(csLocalPort));
		setLucidRegValue(_T(REG_TARGET_KEY),_T(REG_TARGET_LOCATION_VALUE),_T(REG_TARGET_LOCATION_DATA_LOCAL));
		((CLabLgbBaseApp *) AfxGetApp())->csCurrentTarget = REG_TARGET_LOCATION_DATA_LOCAL;
	}
	else if (iSelInd == TARGET_COMBO_INDEX_REMOTE) {
		// remote target selected
		tcpClient.SetIPAddress(csRemoteIpAddress);
		tcpClient.SetPort(atoi(csRemotePort));
		setLucidRegValue(_T(REG_TARGET_KEY),_T(REG_TARGET_LOCATION_VALUE),_T(REG_TARGET_LOCATION_DATA_REMOTE));
		((CLabLgbBaseApp *) AfxGetApp())->csCurrentTarget = REG_TARGET_LOCATION_DATA_REMOTE;
	} 
	else {
		// app server target selected
		setLucidRegValue(_T(REG_TARGET_KEY),_T(REG_TARGET_LOCATION_VALUE),_T(REG_TARGET_LOCATION_DATA_APPSERVER));
		((CLabLgbBaseApp *) AfxGetApp())->csCurrentTarget = REG_TARGET_LOCATION_DATA_APPSERVER;
	}
}

void CDrawGUIView::OnSelChangeEHSHostCombo() {
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	int selInd = pFrame->m_combo.GetCurSel();
	switchTarget(selInd);
}

void CDrawGUIView::OnEHSManageLocally() {
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	pFrame->m_combo.SetCurSel(TARGET_COMBO_INDEX_LOCAL);
	switchTarget(TARGET_COMBO_INDEX_LOCAL);
}

void CDrawGUIView::OnEHSManageRemotely() {
	//@todo validate remote IP address before allow user to switch to managing EHS remotely
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	pFrame->m_combo.SetCurSel(TARGET_COMBO_INDEX_REMOTE);
	switchTarget(TARGET_COMBO_INDEX_REMOTE);
}

void CDrawGUIView::OnUpdateEHSManageLocally(CCmdUI *pCmdUI) {
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(((CLabLgbBaseApp *) AfxGetApp())->csCurrentTarget != REG_TARGET_LOCATION_DATA_LOCAL);
}

void CDrawGUIView::OnUpdateEHSManageRemotely(CCmdUI *pCmdUI) {
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(((CLabLgbBaseApp *) AfxGetApp())->csCurrentTarget != REG_TARGET_LOCATION_DATA_REMOTE);
}

void CDrawGUIView::OnUpdateEHSStartRestart(CCmdUI *pCmdUI) {
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(((CLabLgbBaseApp *) AfxGetApp())->csCurrentTarget != REG_TARGET_LOCATION_DATA_APPSERVER);
}

void CDrawGUIView::OnUpdateEHSStop(CCmdUI *pCmdUI) {
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(((CLabLgbBaseApp *) AfxGetApp())->csCurrentTarget != REG_TARGET_LOCATION_DATA_APPSERVER);
}

void CDrawGUIView::OnUpdateEHSInitParams(CCmdUI *pCmdUI) {
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable((((CLabLgbBaseApp *) AfxGetApp())->csCurrentTarget == REG_TARGET_LOCATION_DATA_LOCAL) && (((CLabLgbBaseApp *) AfxGetApp())->isEHSLocalInstallPathKnown));
}

void CDrawGUIView::OnEHSTopmost(){
	LucidTcpipClient tcpClient;
	LtsStatusType ltsStatusType;

	// connect to tcpip client
	if (( ltsStatusType = tcpClient.Connect()) != 0){
		AfxMessageBox("Unable to establish a TCPIP connection.");
	} else {

		if (( tcpClient.SendText("Z2\n")) != 0)	{
			AfxMessageBox("Unable to send command over TCPIP connection.");
			tcpClient.DisConnect();
			return;
		}
	}
}

void CDrawGUIView::OnEHSBottommost(){
	LucidTcpipClient tcpClient;
	LtsStatusType ltsStatusType;

	// connect to tcpip client
	if (( ltsStatusType = tcpClient.Connect()) != 0){
		AfxMessageBox("Unable to establish a TCPIP connection.");
	} else {

		if (( tcpClient.SendText("Z0\n")) != 0)	{
			AfxMessageBox("Unable to send command over TCPIP connection.");
			tcpClient.DisConnect();
			return;
		}
	}
}

void CDrawGUIView::OnEHSNormalZOrder(){
	LucidTcpipClient tcpClient;
	LtsStatusType ltsStatusType;

	// connect to tcpip client
	if (( ltsStatusType = tcpClient.Connect()) != 0){
		AfxMessageBox("Unable to establish a TCPIP connection.");
	} else {

		if (( tcpClient.SendText("Z1\n")) != 0)	{
			AfxMessageBox("Unable to send command over TCPIP connection.");
			tcpClient.DisConnect();
			return;
		}
	}
}








void CDrawGUIView::copyDrawables( std::vector< LgbDrawable *> &rCopiedDrawables, 
								  std::vector< LgbDrawable *> &rCopiedMasters ) const
{

	rCopiedDrawables.clear();
	rCopiedMasters.clear();

	std::list< LgbDrawablePtr >::const_iterator it = m_cDrawableBag.m_lstDrawables.begin();

	//bool bInMasters = false;

	while( it != m_cDrawableBag.m_lstDrawables.end() )
	{

		// Create a copy of the actual drawable.
		if( (*it)->getClassId() ==  k_LgbImageIcon ) {

			LgbImageIcon *pIcon = new LgbImageIcon( *( (LgbImageIcon *)  *it) );
			rCopiedDrawables.push_back( pIcon );

		} else if( (*it)->getClassId() ==  k_LgbTextIcon ) {

			LgbTextIcon *pIcon = new LgbTextIcon( *( (LgbTextIcon *)  *it) );
			rCopiedDrawables.push_back( pIcon );

		} else if( (*it)->getClassId() ==  k_LgbPatchIcon ) {

			LgbPatchIcon *pIcon = new LgbPatchIcon( *( (LgbPatchIcon *)  *it) );
			rCopiedDrawables.push_back( pIcon );
		
		}else{

			assert(1==0);
		}

		// Now handle the list of masters.
		// If the original drawable ptr is in master bag, push the pointer
		// to its copy into copy list.

		it++;
	}


	LgbDrawable *pOrigSel;

	std::list< LgbDrawablePtr >::const_iterator itCopiedDrawable;

	std::list< LgbDrawablePtr >::const_iterator itOrigSeln;



	itOrigSeln = m_cSelectionBag.m_lstDrawables.begin();

	while( itOrigSeln != m_cSelectionBag.m_lstDrawables.end() )
	{
		pOrigSel = *itOrigSeln;


		for( size_t i=0;i<rCopiedDrawables.size();i++ )
		{
			//pDrawableInner = *itInner;
			if( *pOrigSel == *(rCopiedDrawables[i]) )
				rCopiedMasters.push_back( rCopiedDrawables[i] );
		}

		itOrigSeln++;
	}

	return;
}


void CDrawGUIView::loadDrawables( const std::vector< LgbDrawable *> &rCopiedDrawables,
								  const	std::vector< LgbDrawable *> &rCopiedMasters )
{

	m_cDrawableBag.reset();
	m_cSelectionBag.reset();

	for( size_t i=0;i<rCopiedDrawables.size();i++ )
	{

		// Create a copy of the actual drawable.
		if( rCopiedDrawables[i]->getClassId() ==  k_LgbImageIcon ) {

			AddBitmapIcon( *( ( LgbImageIcon *   )rCopiedDrawables[i]) );

		} else if( rCopiedDrawables[i]->getClassId() ==  k_LgbTextIcon ) {

			AddTextboxIcon( *( ( LgbTextIcon *   ) rCopiedDrawables[i]) );

		} else if( rCopiedDrawables[i]->getClassId() ==  k_LgbPatchIcon ) {

			AddPatchIcon( *( ( LgbPatchIcon *   ) rCopiedDrawables[i]) );
		}else{

			assert(1==0);
		}
	}


	for( size_t i=0;i<rCopiedMasters.size();i++ )
	{

		bool bKeepGoing = true;
		size_t j=0;

		while( j<rCopiedDrawables.size() && bKeepGoing )
		{
			if( *(rCopiedMasters[i]) == *(rCopiedDrawables[j]) ){

				m_cSelectionBag.push_back( rCopiedDrawables[j] );
				bKeepGoing = false;
			}
			j++;

		}
	}

	return;

}
