// InterfaceDropTarget.cpp: Implementierung der Klasse CInterfaceDropTarget.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DrawProgView.h"
#include "InterfaceDropTarget.h"
#include "GlobalFuncs_2.h"
#include <cassert>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////
#ifdef LEGACYREMOVE
CInterfaceDropTarget::CInterfaceDropTarget()
{
}

CInterfaceDropTarget::~CInterfaceDropTarget()
{
}

DROPEFFECT CInterfaceDropTarget::OnDragOver(CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, INXPoint point )
{
	// this time we have to check every time what' our format
	// because in this sample the format may change dynamically
	UINT DragDropFormat;
	CDrawProgView *pView = (CDrawProgView *) pWnd;
	INXRect invalidRect;
	INXRect extra(9,9,9,9);

	m_csBlockName = "";
	m_csIconType = "";


	CString format = AfxGetApp()->GetProfileString("DragDrop", "Clipformat", "Common");
	if (format == "Private")
		DragDropFormat = ::RegisterClipboardFormat("InterfaceClipboardFormat");
	else
		DragDropFormat = CF_TEXT;

	CFile *pFile = pDataObject->GetFileData(DragDropFormat);		
	if (pFile != NULL) {
			// perhaps some point checking first?
			TRY
			{
				CArchive ar(pFile, CArchive::load);
				TRY
				{
					if (DragDropFormat != CF_TEXT)
					{
						// "Serialize" your data object from the archive
						// (yes, you may use YourObject.Serialize(ar) here!)
						ar >> m_csIconType;
						ar >> m_csBlockName;

					} else {

						CString t;

						TRY
						{
							int count = 0;
							while(ar.ReadString(t))
							{
								if(t != ""){
									if(count == 0)
										m_csIconType = t;
									if(count == 1)
										m_csBlockName = t;

									count++;
								}
							}
						}
						CATCH_ALL(eInnerMost)
						{
#ifdef _DEBUG
							TCHAR   szCause[255];
							CString strFormatted;
							eInnerMost->GetErrorMessage(szCause, 255);
							strFormatted = _T("Exception: ");
							strFormatted += szCause;
							AfxMessageBox(strFormatted);   
#endif //_DEBUG
							ASSERT(FALSE);
						}
						END_CATCH_ALL;
				//		if (pWnd->IsKindOf(RUNTIME_CLASS(CDropDialog)))
				//			((CDropDialog*)pWnd)->ProcessData(Data);
					}
					ar.Close();
				}
				CATCH_ALL(eInner)
				{
					// exception while reading from or closing the archive
					ASSERT(FALSE);
				}
				END_CATCH_ALL;
			}
			CATCH_ALL(eOuter)
			{
				// exception in the destructor of ar
				ASSERT(FALSE);
			}
			END_CATCH_ALL;
		
		// Functionality for function block substitution
		CClientDC aDC(pView); // create device context
		pView->OnPrepareDC(&aDC); // adjust origin
		aDC.DPtoLP(&point); // convert point to Logical

		pView->m_FBSubstitute.createInitDraggee(m_csIconType, m_csBlockName);
		ConData* fb = pView->pDEP->getIconAtPoint(point);
		// if over function block highlight it if it is replaceable
		if (fb) {

			// if it is an XPORT, don't allow FB Substitution
			//@todo - this is because we haven't coded for reconnecting the new XPORT to the old XPORT connections in the parent DEP
			if (fb->m_csIconType == "XSTART" || fb->m_csIconType == "XFINISH" || fb->m_csIconType.Find("XINPUT") != -1 ||
					fb->m_csIconType.Find("XOUTPUT") != -1) {
				pView->m_FBSubstitute.setDroppee(NULL);
			} else if (pView->m_FBSubstitute.isReplaceable(fb)) {
				pView->m_FBSubstitute.setDroppee(fb);
				fb->selected = 1;
				// Couldn't get InvalidateRect to work with the DC, so adjust invalidate rectangle
				// for scroll and zoom
				INXPoint scrollPos = pView->GetScrollPosition();
				invalidRect = fb->rectangle;
				invalidRect+=extra;
				INXPoint topLeft = invalidRect.TopLeft();
				topLeft.x = (topLeft.x * pView->scale)/100;
				topLeft.y = (topLeft.y * pView->scale)/100;
				INXPoint bottomRight = invalidRect.BottomRight();
				bottomRight.x = (bottomRight.x * pView->scale)/100;
				bottomRight.y = (bottomRight.y * pView->scale)/100;
				invalidRect.SetRect(topLeft, bottomRight);
				invalidRect.OffsetRect(-scrollPos);
				pView->InvalidateRect(invalidRect, FALSE);
			}
			else {
				pView->m_FBSubstitute.setDroppee(NULL);
			}
		}
		else {
			if (pView->m_FBSubstitute.getDroppee()) {
				pView->RemoveHighlight();
			}
			pView->m_FBSubstitute.setDroppee(NULL);
		}

		return DROPEFFECT_COPY; // data fits
	}
	else {
		return DROPEFFECT_NONE; // data won't fit
	}
}

BOOL CInterfaceDropTarget::OnDrop(
								  CWnd* pWnd, 
								  COleDataObject* pDataObject, 
								  DROPEFFECT dropEffect, 
								  INXPoint point )
{

	CDrawProgView *pView = (CDrawProgView *) pWnd;
	assert(  pWnd->IsKindOf( RUNTIME_CLASS(CDrawProgView) ) );
	ConData *droppee, *draggee;
	INXPOSITION droppeePos, draggeePos;
	INXPoint droppeePoint, draggeePoint;
	bool bContinue = TRUE;
	set<CString> sWidgetGroupSet;
	vector<pair<CString, CString> > vWidgetGroupPairVec;
	CString csWidgetGroupName;

	if( !pView->pProject->pProjMData->getLock() ){

		AfxMessageBox( PMD_LOCK_FAILURE_MESSAGE );

	} else {

		pView->pProject->pProjMData->readProjectFile();

		// this time we have to check every time what' our format
		// because in this sample the format may change dynamically
		UINT DragDropFormat;

		CString format = AfxGetApp()->GetProfileString("DragDrop", "Clipformat", "Common");
		if (format == "Private")
			DragDropFormat = ::RegisterClipboardFormat("InterfaceClipboardFormat");
		else
			DragDropFormat = CF_TEXT;

		CFile *pFile = pDataObject->GetFileData(DragDropFormat);
		if (pFile != NULL)
		{
			// Process the drop data into the project....
			CClientDC aDC(pView); // create device context
			pView->OnPrepareDC(&aDC); // adjust origin
			aDC.DPtoLP(&point); // convert point to Logical

			ConData* blob =
				pView->processComponentDrop(SnapToGrid(point), m_csIconType, m_csBlockName );

			if (blob) {
				if (blob->m_iUserDefined) {
					// add this instance to the project tree
					pView->pFrame->m_wndProjectBar.m_cProjTree.AddItem2ProjectTree(
						blob, pView->pProject, pView->pDEP->hItem);
					// Make sure gui widget tags are unique
					// add any gui widgets to the project meta data
					HTREEITEM hUserDefItem = 
						pView->pFrame->m_wndProjectBar.m_cProjTree.GetUserDefChildItem(
						blob, pView->pDEP->hItem);

					pView->pProject->getWidgetGroupNames(hUserDefItem, sWidgetGroupSet);
					pView->pProject->setWidgetGroupNames(sWidgetGroupSet, vWidgetGroupPairVec);
					pView->pProject->updateWidgetGroupNames(hUserDefItem, vWidgetGroupPairVec);
				}
				// Add Gui widgets to project file
				else if (blob->isGuiWidget()) {
					pView->pProject->addGuiWidget(blob);
				}
				
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
							if (AfxMessageBox("Substitution will cause your parameters to be lost. Do you want to continue?",MB_YESNO|MB_ICONEXCLAMATION)==IDNO) {
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
						pView->pFrame->m_wndProjectBar.m_cProjTree.DeleteIcon(droppeePos, pView->pProject, pView->pDEP, 0);
					}
					else {
						draggeePos = pView->pDEP->getPosFromIcon(draggee);
						pView->pFrame->m_wndProjectBar.m_cProjTree.DeleteIcon(draggeePos, pView->pProject, pView->pDEP, 0);
					}
				}
				
				if (bContinue) {
					// if adding xport then don't allow undo
					if (!(blob->m_csIconType.Find("XINPUT") != -1 || blob->m_csIconType.Find("XOUTPUT") != -1 || blob->m_csIconType == "XSTART" 
						|| blob->m_csIconType == "XFINISH")) {
						pView->SaveUndo();
					}
					else {
						//@todo - currently can't undo adding an xport
						pView->initUndo();
					}

					pView->pProject->SaveProject();
					pView->pProject->pProjMData->writeProjectFile();
					pView->RedrawWindow();
				}

			}

			//return TRUE;
		}

		pView->pProject->pProjMData->releaseLock();
		return COleDropTarget::OnDrop(pWnd, pDataObject, dropEffect, point);
	}
}
#endif