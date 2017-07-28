#include "DrawProgView.h"
#include <wx/dcclient.h>
#include <wx/app.h>
#include <wx/dir.h>
#include "Porting_Classes/INXGLFont.h"
#include "Porting_Classes/INXRect.h"

/* Accessing the rest of the App */

/*

  This class contains a CObject typed list of all icons in the display.Currently all other displayed data
  is a child of an icon. All programme data is held in this view, rather than the Document Class, because the data is spcific to this view.
  	Displaying manipulating etc is all done via access through icon objects (ConDat)
  Temporary attributes are provided for storing information such as user connection actions etc. to interpret
  what a GUI user is doing.
  */

#include "Resource.h"
#include "DrawProg.h"
#include "DrawProgDoc.h"

#include "../common/Userconfig.h"
#include "bmpfile.h"
#include "Condat.h"
#include "IconParams.h"
#include "LucidConstants.h"
#include "FileOperations.h"
#include "ProjectDialog.h"
#include "LucidTcpipClient.h"
#include "LucidEnums.h"
#include "LucidTcpipClient.h"
#include "BlockOperations.h"
//#include "RJMFileFind2.h"
#include "GlobalFuncs_2.h"


using namespace std;
#include <sys/stat.h>
//#include <sys/types.h>

#include <math.h>
#include <curl/curl.h>
#include <archive.h>
#include <archive_entry.h>

/* Dialogs - todo
#include "Tags.h"
#include "MenuNameDialog.h"
#include "ProjectDescriptionDialog.h"
#include "delims.h"
#include "Datsrc.h"
#include "Encapsulation.h"
#include "colourKey.h"
#include "AddPortDialog.h"
#include "BlockNameDialog.h"
#include "PortLabelDialog.h"
#include "TagDialog.h"
#include "PrintData.h"
#include "ZoomDialog.h"
#include "SelectGroupDialog.h"
#include "LucidStateMachine.h"
#include "TransferToTargetDialog.h"

#include "ExportDialog.h"
*/


BEGIN_EVENT_TABLE(DrawProgView, wxGLCanvas)
    EVT_SIZE(DrawProgView::OnSize)
    EVT_PAINT(DrawProgView::OnPaint)
	EVT_MOUSE_EVENTS(DrawProgView::OnWxMouseEvents)
	EVT_LEFT_UP(DrawProgView::OnWxLeftMouse)
END_EVENT_TABLE()


///\todo remove this? global variable declared in CDrawProgApp
extern wxChar workDir[WORK_DIR_SIZE];

bool DrawProgView::bHasConnectionToEHS; ///\todo this should be a singleton ... static?


DrawProgView::DrawProgView(wxWindow *parent, const wxPoint& pos,
        const wxSize& size, long style):wxGLCanvas(parent, (wxGLCanvas*) NULL, wxID_ANY,
		pos, size, style/*|wxFULL_REPAINT_ON_RESIZE|wxVSCROLL|wxHSCROLL*/)
{
	pDEP = NULL;
}

DrawProgView::~DrawProgView(void)
{
	delete pDEP;
}


/* Legacy compatability \todo consider removing and calling render instead? */
void DrawProgView::RedrawWindow() {
	Render();
}

void DrawProgView::OnPaint(wxPaintEvent& WXUNUSED(event)){
	Render();
}
void DrawProgView::OnSize(wxSizeEvent& event){
	  // this is also necessary to update the context on some platforms
    wxGLCanvas::OnSize(event);

    // set GL viewport (not called by wxGLCanvas::OnSize on all platforms...)
 /*   int w, h;
    GetClientSize(&w, &h);

    SetCurrent();
	glOrtho(0,w,h,0,0.0f,100.0f);*/
}
void DrawProgView::OnEraseBackground(wxEraseEvent& WXUNUSED(event)){

}
void DrawProgView::Render(){

	SetCurrent();
 //   wxPaintDC(this);
	InitGL();
	//set background
	glClearColor(1.0, 1.0, 1.0, 0.0);
    /* clear color and depth buffers */
    glClear(GL_COLOR_BUFFER_BIT);
	
    // gl drawing code
    if(pDEP != NULL){
    	pDEP->DrawGL();
    }else{ /* this is just for debugging purposes @todo - move to a private funcion */
    	INXGLFont newViewText;
    	newViewText.setFontSize(18);
    	newViewText.textOut(25,100,"Couldn't read DEP file");
    	newViewText.setFontSize(14);
    	newViewText.textOut(80,100 + 25,"Old version?");
    }
    glFlush();
    SwapBuffers();
}

void DrawProgView::InitGL(){
	int w, h;
    GetClientSize(&w, &h);
	glOrtho(0,w,h,0,0.0f,100.0f);
	glClearDepth(1);
	glClear(GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}


/* Imported from MFC */


/**
 * @brief Called after the user has dragged-and-dropped a component from
 * the component palette onto the view, to do the data processing / adding
 * to the project etc.
 *
 * \param [in] point - the coordinates to drop
 * \param [in] csIconType is the name if the component (and filename).
 * \param [in] csBlock is type of component (e.g. subsystem, native, Xport,...)
 * \return returns a Condata Pointer, which needs to be added to DEP.
 **/
ConData* DrawProgView::processComponentDrop(
			INXPoint point, INXString &csIconType, INXString &csBlock )
{
	INXString csBlockName = "";// This is only set (by a dlgbox) if the icon is a new subsystem component
	ConData* blob = NULL;
	//CPortLabelDialog portDlg(pDEP);
	INXString parentName;
	int dataType = -1, portType = -1;

	// block is defined if it is an encapsulated icon
	// get block name for new blocks
	if (csBlock == "NewComponent") {
#if 0
		CBlockNameDialog blockDlg;

		// SDG: This is a fudge for now. Needs fixing properly.
		// Makes User Components appear at top of tree in component bar
		csBlock = "aaaNewComponent";
		if (blockDlg.DoModal() == IDOK) {
			csBlockName = blockDlg.m_BlockName;
		}
		else {
			return NULL;
		}
#else
		INX_MessageBox("Not implemented NewComponent");
		return NULL;
#endif
	}
	if (csIconType.Find("XINPUT") != -1 || csIconType.Find("XOUTPUT") != -1 || csIconType == "XSTART" || csIconType == "XFINISH") {

		// only allow xports to be added to subsytems
#if 0
		if (pDEP->IsSubsystem()) {
			if (portDlg.DoModal() == IDOK) {
				return pFrame->m_wndProjectBar.m_cProjTree.AddXPort(csIconType, portDlg.m_PortLabel.MakeLower(), point, pProject, pDEP);
				//((CDrawProgApp*)wxGetApp())->AddBlockPort(parentName, pDEP->depFilename, dataType, portType, portDlg.m_PortLabel);
				// don't run rest of function as DeleteBlockPort runs DeleteIcon
				// this should return the xport added, not NULL
			}
			return NULL;
		} else {
			INX_MessageBox("Can only add External Ports to Subsytems");
			return NULL;
		}
#else
		INX_MessageBox("Not implemented XPorts");
		return NULL;
#endif
	}
/* Add the Icon */
	INXPOSITION selected = pDEP->AddIcon(csIconType, csBlock, point);  //create the block and set point in pDEP component list
	blob = (ConData *) pDEP->condata->GetAt(selected);

	// the class name for a new block is the block name
	if (csIconType == "SUBSYSTEM") { // this means it's a subsystem block not a native
		blob->className = csBlockName;
		// create an instance name for this new block
		//CreateDirectory(workDir + USERDEFDIR + blockName, NULL);
		pDEP->CreateInstance(blob, 4); // THIS Will delete IDF
	}
	// create an instance for a new component library components
	else if (csBlock != "" && csBlockName == "") {
		//system("copy " + (INXString)workDir + USERDEFDIR + block + ".prg " + projectDir + DEPDIR + block + ".prg");
		pDEP->CreateInstance(blob, 1);
	}

#if 0
	if((blob->className == "TRANSITIONACTION")||(blob->className  == "ENTRYACTION"))
	{

			CBlockNameDialog blockDlg;

			if (blockDlg.DoModal() == IDOK) {
				blob->description = blockDlg.m_BlockName;

				CLucidStateMachine::AddActionPortsBelow(blob,pDEP,pProject);
				return blob;

			}
			else {
				return NULL;
			}

			/*				CLucidStateMachine::AddActionPortsBelow(blob,pDEP,pProject);
			return blob;
*/

	}

	if(blob->className  == "CONDITIONLOGIC")
	{
		CBlockNameDialog blockDlg;

		if (blockDlg.DoModal() == IDOK) {
			blob->description = blockDlg.m_BlockName;

			CLucidStateMachine::AddConditionLogicPortsBelow(blob,pDEP,pProject);
			return blob;

		}
		else {
			return NULL;
		}

	}
#endif
	return blob;
}

// removes highlighting from icons
void DrawProgView::RemoveHighlight()
{
	INXPOSITION pos;
	ConData* blob;

	pos = pDEP->condata->GetHeadPosition();
	while(pos) {
		blob = (ConData *) (pDEP->condata->GetNext(pos));
		blob->selected = 0;
	}
	RedrawWindow();
}

void DrawProgView::SaveHierName() {
#if 0
	INXPOSITION pos;
	ConData* blob;
	HTREEITEM childItem;
	INXString csProjectDir;

	pProject->pProjMData->getProjectDir(csProjectDir);
	pos = pDEP->condata->GetHeadPosition();
	while (pos) {
		blob = (ConData*) pDEP->condata->GetNext(pos);
		if (blob->m_iUserDefined) {
			blob->hierarchyName = pDEP->depFilename + "\\";
			childItem = pFrame->m_wndProjectBar.m_cProjTree.GetUserDefChildItem(blob, pDEP->hItem);
			pFrame->m_wndProjectBar.m_cProjTree.SaveHierName(childItem, csProjectDir, pProject);
		}
	}
	pDEP->SaveProg(csProjectDir + DEPDIR + pDEP->depFilename + ".prg");
#endif
}


/*
This is called when a user clicks a port to start making a connection.
It is called after the icon and selected port has been identified with ::OnPort(..)
It stores a copy of this information for when the other end of the line has been selected
  */
void DrawProgView::StartLine(INXPOSITION selectedIcon, int PortSelected, int portType) {
	ConData* icon;

	icon = (ConData*)(pDEP->condata->GetAt(selectedIcon));
	selectedControl = selectedIcon;
	selectedPort = PortSelected;
	selectedPortType = portType;
	INXPoint conpoint=icon->GetPortPoint(PortSelected, portType);
	conpoint.x = (conpoint.x * scale)/100;
	conpoint.y = (conpoint.y * scale)/100;

	// set some flags identifying the user's activity
	lastlinepoint = conpoint;
	lastmovingline = conpoint;
	pDEP->depFSM.drawingline = 1;
}

// returns true if library component imported already exists in userdefined directory
bool DrawProgView::LibExist(INXString libName) {
	wxDir finder;
	INXString fileName;

	int bWorking = finder.GetFirst(&fileName ,workDir + USERDEFDIR + "*.prg");
	while (bWorking)
	{
		if (fileName == libName) {
			return true;
		}
		bWorking = finder.GetNext(&fileName );
	}

	return FALSE;
}

/// \brief Sets the unique icon id to be greater than the largest id in the current view
/// \todo move this to be a service provided by DEP or condata (i.e. DEP::getMaxId()) Condata@@SetId().
void DrawProgView::SetIconID() {
	ConData* blob;
	INXPOSITION pos;
	long id = 0;

	pos = pDEP->condata->GetHeadPosition();
	while (pos) {
		blob = (ConData*) pDEP->condata->GetNext(pos);
		if (blob->identnum > id) {
			id = blob->identnum;
		}
	}
	id++;
	ConData::uniqueidgenerator = id;
}

/// \brief  returns true if an xport label in list already exists in the DEP
/// \todo move to DEP
bool DrawProgView::XportNameExist(INXObjList* list) {
	INXPOSITION depPos, listPos;
	ConData *depBlob, *listBlob;

	listPos = list->GetHeadPosition();
	while (listPos) {
		listBlob = (ConData*)(list->GetNext(listPos));
		if (listBlob->m_FbName.Find("XINPUT") != -1 || listBlob->m_FbName.Find("XOUTPUT") != -1 ||
			listBlob->m_FbName == "XSTART" || listBlob->m_FbName == "XFINISH") {
			depPos = pDEP->condata->GetHeadPosition();
			while (depPos) {
				depBlob = (ConData*)(pDEP->condata->GetNext(depPos));
				if (depBlob->m_FbName == listBlob->m_FbName && depBlob->description == listBlob->description) {
					return true;
				}
			}
		}
	}
	return FALSE;
}
void DrawProgView::SubsetEncapsulate()
{

		ConData* encapsulatedIcon;

		if (selectRect.IsRectEmpty()) {
			INX_MessageBox("First select the icons you wish to encapsulate.");
			return;
		}
		if (pDEP->IsRectEmpty(selectRect)) {
			if (INX_MessageBox("You haven't selected any icons. Do you want to create an empty subsytem?")) {
/// \todo
				return;
			}
		}

		selectRect.NormalizeRect();
		encapsulatedIcon = pDEP->SubsetEncapsulate(selectRect, lib);
		if (encapsulatedIcon) {
#if 0
			if (encapsulatedIcon->m_iUserDefined) {
				// add this instance to the project tree

				pFrame->m_wndProjectBar.m_cProjTree.AddItem2ProjectTree(encapsulatedIcon, pProject, pDEP->hItem);

			}

			// only update function block bar if encapsualting a library component
			if (lib) {
				pFrame->updateFunctionBlockBar();
			}
#else
///\todo #warning todo
#endif
			SaveUndo();
		}
		else {
			RemoveHighlight();
		}
		selectRect.SetRectEmpty();
		pProject->SaveProjectDep();
		//RedrawWindow();
}

// Method that toggles lines when define monitoring is turned on
void DrawProgView::toggleMonitoredLine(ConData *pBlob)
{
	TypeConversion tc;
	INXString csRtaFilePath = (INXString)"localhost.Generic-Debugger:" + workDir + TRACEDIR + TRACE_CONFIG_FILE;

	if (selectedPortType == INPUTPORT) {
		//pBlob->inputport[selectedPort]->line.toggleDbgMonitor();
		pDEP->toggleMonitoredLine(INPUTPORT, pBlob->inputport[selectedPort]->line.othericonid, pBlob->inputport[selectedPort]->line.otherportno);
		if (pProject->debug.debugMode != DBGSTOP) {
			pProject->debug.sendMonitor(pBlob->inputport[selectedPort]->line.getDbgMonitor(),
			pBlob->inputport[selectedPort]->line.idNum, tc.DataType2Char(pBlob->inputport[selectedPort]->datatype));
#if 0
			if (pProject->debug.m_RtaTraceSupport.getRtaTrace()) {
				pProject->debug.m_RtaTraceSupport.terminateRtaTraceProc();
				pProject->debug.m_RtaTraceSupport.createRtaConfigFile();
				ShellExecute(NULL, "open", RTA_TRACE_PATH, csRtaFilePath, NULL, SW_SHOWNORMAL);
			}
#endif
		}
	}
	else if (selectedPortType == STARTPORT) {
		//pBlob->startport[selectedPort]->line.toggleDbgMonitor();
		pDEP->toggleMonitoredLine(STARTPORT, pBlob->startport[selectedPort]->line.othericonid, pBlob->startport[selectedPort]->line.otherportno);
		if (pProject->debug.debugMode != DBGSTOP) {
			pProject->debug.sendMonitor(pBlob->startport[selectedPort]->line.getDbgMonitor(),
			pBlob->startport[selectedPort]->line.idNum, "E");
#if 0
			if (pProject->debug.m_RtaTraceSupport.getRtaTrace()) {
				pProject->debug.m_RtaTraceSupport.terminateRtaTraceProc();
				pProject->debug.m_RtaTraceSupport.createRtaConfigFile();
				ShellExecute(NULL, "open", RTA_TRACE_PATH, csRtaFilePath, NULL, SW_SHOWNORMAL);
			}
#endif
		}
	}
}

void DrawProgView::startTraceTimer()
{
#if 0
	SetTimer(TRACE_TIMER_ID, TRACE_PERIOD, 0);
#endif
}

void DrawProgView::stopTraceTimer()
{
#if 0
	KillTimer(TRACE_TIMER_ID);
#endif
}


/*
 * ~brief Handle All Mouse events (iniiated in the workspace window)
 *
 */

void DrawProgView::OnWxMouseEvents( wxMouseEvent& event) {

	INXPoint point(event.GetPosition());
	if (event.LeftDown()) {
	//	OnLButtonDown(0,point);

	}
	else if (event.LeftUp()) {
		OnLButtonUp(0,point);
	}
	else if (event.RightDown()) {
		OnRButtonDown(0,point);
	}
	else if (event.LeftUp()) {
		OnLButtonUp(0,point);
	}
	else if (event.RightUp()) {
		OnRButtonUp(0,point);
	}
	else if (event.Moving()){
		OnRButtonUp(0,point);
	}
	else {
		event.Skip(true); // pass the event up if we don't handle it
	}
}


void DrawProgView::OnWxLeftMouse( wxMouseEvent& event) {
	if (event.GetClassInfo()) {

	}
}

void DrawProgView::OnRButtonUp(unsigned int nFlags, INXPoint _point) {

}
/*
*/
void DrawProgView::OnLButtonDown(unsigned int nFlags, INXPoint _point)
{	// @todo
	INXPoint point(_point.x, _point.y);
	// kwhite:canvassupport
	// case 1: ?
	// case 2: capture selection of function or encap block
	// case 3: capture line selection
	// case 4: rubber band for encapsulation block
	// case 5: creation of rubber band
	// case 6: Multiple objects selected with rubberband

	running=1;
	int portConnected=0;
	int portType=0;
	/// \todo pDoc->SetModifiedFlag();
	//point+=GetScrollPosition( ) ;
	INXPOSITION selectedIcon;
	int PortSelected;
	ConData* blob;
	TypeConversion tc;

	//point.x = (point.x * 100)/scale;
	//point.y = (point.y * 100)/scale;
#if 0
	CClientDC aDC(this); // create device context
	OnPrepareDC(&aDC); // adjust origin
	aDC.DPtoLP((LPPOINT)point); // convert point to Logical
	if (!selectRect.PtInRect(point)) {
		selectRect.SetRectEmpty();
	}
#endif

	if (pDEP->depFSM.drawingline!=1){
		//LineSelected=online(point); // todo
		PortSelected = pDEP->OnConnect(point,&selectedIcon,&portType,&portConnected); // return -ve if an already connected input for deletion

		// if within selection box
		if (selectRect.PtInRect(point)) {
			m_iLftBtnDownState = 6;
			oldpoint = SnapToGrid(point);
			firstpoint = SnapToGrid(point);
		}
		else if ((PortSelected>-1)) {
			RemoveHighlight();
			StartLine(selectedIcon,PortSelected,portType);
		}
		else { // if not a port then check on a line
			RemoveHighlight();
			// if the point is on a line then return the port number the line is connected to
			bool INTERROGATE_ONLY = false;
			// when defining monitors don't add nodes
			if (pProject->getDefineMonitors()) {
				INTERROGATE_ONLY = true;
			}

			selectedPort = pDEP->OnLine(point, &nodeIcon, &nodeSelected, &selectedPortType, INTERROGATE_ONLY);
			// if on a node
			if (nodeSelected) {
				blob = (ConData*) pDEP->condata->GetAt(nodeIcon);
				if (pProject->getDefineMonitors()) {
					toggleMonitoredLine(blob);
				}
				else {
					if (selectedPortType == INPUTPORT) {
						blob->inputport[selectedPort]->line.editNode(point);
					}
					else if (selectedPortType == STARTPORT) {
						blob->startport[selectedPort]->line.editNode(point);
					}
				}
				m_iLftBtnDownState = 3;
			}
			// if on a line
			else if (selectedPort > -1) {
				/* @todo PP: Create the variables for this function
				blob = (ConData*) pDEP->condata->GetAt(nodeIcon);
				// Record Position for move
				m_iLftBtnDownState=XXX;
				oldpoint = pDEP->SnapToGrid(point);
				firstpoint = pDEP->SnapToGrid(point);
				SetToMovingLine(selectedLine);
				moveselectedLine = selectedLine;
				*/
				// remove the following when above is done...
				blob = (ConData*) pDEP->condata->GetAt(nodeIcon);
				if (pProject->getDefineMonitors()) {
					toggleMonitoredLine(blob);
				}
				else {
					// SDG: If left click on a line drag the segment for Gila.
					// Prior to Gila a node was added
					m_iLftBtnDownState = 8;  // set the mode that a line segment is being moved
				}
			}
			else { // if not a line/node then check on an icon
				selectedControl = pDEP->Incontrol(point);
				if (selectedControl) {
					pDEP->setFBHighlight(selectedControl);
					m_iLftBtnDownState=2;
					oldpoint = SnapToGrid(point);
					firstpoint = SnapToGrid(point);
					SetToMovingRectangle(selectedControl);
					moveselected = selectedControl;
				}
				// if on background allow user to select several icons
				else {
					m_iLftBtnDownState = 5;
					selectRect.TopLeft() = point;
					selectRect.BottomRight() = point;
					//removeHighlight();
				}
			}
		}
	}
/// \todo 0 DEP FSM has lots of UI stuff in like drawing line flag - that should really be a flag in this (DrawProgView) class
	if ( /** \todo cs.ValidLeftButtonEvent(m_iLftBtnDownState)  ||*/ pDEP->depFSM.drawingline || m_iLftBtnDownState==5)
	{
		SaveUndo();					//must come first.
		pProject->SaveProjectDep();

		undoFlag = true;
		//SetCapture();				//prevent mouse events disapearing if pointer past boundary
		if(m_iLftBtnDownState == 2)			//Single item selected
		{
			cs.SetTempStore(point);	//Needed to remember first point before mouse move.
									//Used by MouseUp when calling ConData::RenewPosition(..,oldpoint)
			INXPOSITION hideSelected;
			hideSelected = pDEP->Incontrol(point);
			pDEP->setFBHighlight(hideSelected);
			pDEP->HideSelected(hideSelected);
		}
		if(m_iLftBtnDownState == 6)			//Multiple items selected
		{
			cs.SetTempStore(point);	//Needed to remember first point before mouse move.
									//Used by MouseUp when calling ConData::RenewPosition(..,oldpoint)
			pDEP->HideSelectedPositions();
		}
	}
//	CScrollView::OnLButtonDown(nFlags, (INXPoint)point);
	//Skip();
	running=0;
}

/*
	Get the event of the user releasing the mouse button which may mean any of the following,
	depending on the user's previous activity. . e.g. finished drawing a line
*/
void DrawProgView::OnLButtonUp(unsigned int nFlags, INXPoint _point)
{
	INXPoint point(_point.x, _point.y);
	running=1;
	//point+=GetScrollPosition( ) ;
	int selectedPort2;
	INXPOSITION selectedControl2;
	int selectedPortType2 = 0;
	int selectedPortConnected2 = 0;
	int iSelSegNum = -1;
	ConData* pBlob;

	//point.x = (point.x * 100)/scale;
	//point.y = (point.y * 100)/scale;

	switch (m_iLftBtnDownState) {

	case 1:

		break;

	case 2:// this moves an icon around if not drawing a line -
		{
		cs.SetDebugTrace(false);
		if (pDEP->depFSM.drawingline) break;
		if(cs.TopLeftBoundaryHit())
		{
			cs.DebugTrace("kwhite:canvassupport:OnLButtonUp:cs.TopLeftBoundaryHit\n");
			pDEP->RenewPosition(moveselected, SnapToGrid(point), SnapToGrid(cs.GetTempStore()));
			cs.SetTopLeftBoundaryHit(false);
		}
		else
		{
			cs.DebugTrace("kwhite:canvassupport:OnLButtonUp:!cs.TopLeftBoundaryHit()\n");
			pDEP->RenewPosition(moveselected, SnapToGrid(point), SnapToGrid(firstpoint));
		}
		pDEP->SnapIconToGrid(moveselected);
		pDEP->ShowSelected(moveselected); //Im relying on moveselected
		m_iLftBtnDownState=0;
		SaveUndo();
		undoFlag = true; //kwhite:canvassupport added
		copyFlag = true;
		break;
		}
	case 3:
		SaveUndo();
		break;
	case 4:
		{
			// This used to be encapsulation
		}
		break;
	case 5:
		{
			selectRect.NormalizeRect();
			// if there is at least 1 icon slected then display cut and copy buttons and menu items
			if (pDEP->HighlightSelected(selectRect)) {
				copyFlag = true;
			}
			else {
				copyFlag = FALSE;
			}
		}
		break;
	case 6:
		{
			if(cs.TopLeftBoundaryHit())
			{
				cs.DebugTrace("kwhite:canvassupport:OnLButtonUp:if MoveObjects() Y %d\n", SnapToGrid(point).y, cs.GetTempStore().y);
				pDEP->RenewSelectedPos(SnapToGrid(point), SnapToGrid(cs.GetTempStore()), selectRect);
				selectRect = (selectRect)+(oldpoint-firstpoint);
				cs.SetTopLeftBoundaryHit(false);
			}
			else
			{
				cs.DebugTrace("kwhite:canvassupport:OnLButtonUp:            Y %d\n", SnapToGrid(point).y, firstpoint.y);
				selectRect = pDEP->RenewSelectedPos(SnapToGrid(point), SnapToGrid(firstpoint), selectRect);
			}
			pDEP->ShowSelectedPositions();
			SaveUndo();
			undoFlag = true; //kwhite:canvassupport added
		}
		break;
	case 7:// this moves an Line around if not drawing a line -
		{
		cs.SetDebugTrace(false);
		if (pDEP->depFSM.drawingline) break;
		if(cs.TopLeftBoundaryHit())
		{
			cs.DebugTrace("kwhite:canvassupport:OnLButtonUp:cs.TopLeftBoundaryHit\n");
			pDEP->RenewPosition(moveselected, SnapToGrid(point), cs.GetTempStore());
			cs.SetTopLeftBoundaryHit(false);
		}
		else
		{
			cs.DebugTrace("kwhite:canvassupport:OnLButtonUp:!cs.TopLeftBoundaryHit()\n");
			pDEP->RenewPosition(moveselected, SnapToGrid(point), firstpoint);
		}
		/* @todo PP: Create this function for moving a line
		pDEP->ShowSelected(lineselected); //Im relying on moveselected
		*/
		m_iLftBtnDownState=0;
		SaveUndo();
		undoFlag = true; //kwhite:canvassupport added
		copyFlag = true;
		break;
		}
	case 8: // line segements
		{
		//TO DO: check if segments are aligned. If they are delete node.
		pBlob = (ConData*) pDEP->condata->GetAt(nodeIcon);
		if (selectedPortType == INPUTPORT) {
			iSelSegNum = pBlob->inputport[selectedPort]->line.GetSelectedSegment();
			if (iSelSegNum >= 0) {
				if (iSelSegNum+2 <= pBlob->inputport[selectedPort]->line.points.GetUpperBound()) {
					if (pBlob->inputport[selectedPort]->line.IsSegmentsAligned(iSelSegNum, iSelSegNum+2)) {
						pBlob->inputport[selectedPort]->line.DeleteNode(iSelSegNum+1);
						pBlob->inputport[selectedPort]->line.DeleteNode(iSelSegNum+1);
					}
				}
				if (iSelSegNum >= 2) {
					if (pBlob->inputport[selectedPort]->line.IsSegmentsAligned(iSelSegNum, iSelSegNum-2)) {
						pBlob->inputport[selectedPort]->line.DeleteNode(iSelSegNum-1);
						pBlob->inputport[selectedPort]->line.DeleteNode(iSelSegNum-1);
					}
				}
			}
		}
		else if (selectedPortType == STARTPORT) {
			iSelSegNum = pBlob->startport[selectedPort]->line.GetSelectedSegment();
			if (iSelSegNum >= 0) {
				if (iSelSegNum+2 <= pBlob->startport[selectedPort]->line.points.GetUpperBound()) {
					if (pBlob->startport[selectedPort]->line.IsSegmentsAligned(iSelSegNum, iSelSegNum+2)) {
						pBlob->startport[selectedPort]->line.DeleteNode(iSelSegNum+1);
						pBlob->startport[selectedPort]->line.DeleteNode(iSelSegNum+1);
					}
				}
				if (iSelSegNum >= 2) {
					if (pBlob->startport[selectedPort]->line.IsSegmentsAligned(iSelSegNum, iSelSegNum-2)) {
						pBlob->startport[selectedPort]->line.DeleteNode(iSelSegNum-1);
						pBlob->startport[selectedPort]->line.DeleteNode(iSelSegNum-1);
					}
				}
			}		}

		SaveUndo();
		break;
		}
	}
#if 0
	if (pDEP->depFSM.drawingline) { //if drawing a line find the other end and test if it is another port
		CClientDC dc(this);
		// to change the colour for a drawn line the pen needs to be set in IconLines::Draw
		dc.SelectObject(blackpen);
		//dc.MoveTo(lastlinepoint+GetScrollPosition( ) );
		//dc.LineTo(lastmovingline+GetScrollPosition( ) );
		selectedPort2 = pDEP->OnConnect(point,&selectedControl2,&selectedPortType2,&selectedPortConnected2);
		if (selectedPort2 > -1) {
			// check if connection dragging or drawing
			// connection dragging
			if (selectedPortType == selectedPortType2) {
				pDEP->dragConnections(selectedControl, selectedPort, selectedPortType, selectedControl2, selectedPort2, selectedPortType2);
				SaveUndo();
			}
			// connection drawing
			else {
				// Only add nodes and save undo file, if the line was added successfully
				if (pDEP->AddLine(selectedControl, selectedPort, selectedPortType, selectedControl2, selectedPort2, selectedPortType2)) {
					pDEP->AddNodes(selectedControl, selectedPort, selectedPortType, selectedControl2, selectedPort2, selectedPortType2);
					SaveUndo();
				}
			}
		}
		pDEP->depFSM.drawingline = 0;
		ReleaseDC(&dc);
	}
#endif

	if (this == GetCapture())	//kwhite:canvassupport - prevent mouse events disapearing if pointer past boundary
	{
		cs.DebugTrace("kwhite:canvassupport:OnLButtonUp:ReleaseCapture,SetMoveObjects(false)\n");
		//ReleaseCapture();		//release the mouse capture otherwise other apps wont work
	}

//	CScrollView::OnLButtonUp(nFlags, point);
	m_iLftBtnDownState=0;
	running = 0;
	pProject->SaveProjectDep();
	RedrawWindow();
}



/*
	When the right button is clicked on an icon then bring up a popup menu
*/
void DrawProgView::OnRButtonDown(unsigned int nFlags, INXPoint _point)
{
	INXPoint point(_point.x, _point.y);
#if 0
	CMenu iconMenu;
	ConData* blob;
	int portConnected=0;
	INXPoint menuPoint = point;
	//point.x = (point.x * 100)/scale;
	//point.y = (point.y * 100)/scale;
	CClientDC aDC(this); // create device context
	OnPrepareDC(&aDC); // adjust origin
	aDC.DPtoLP((LPPOINT)point); // convert point to Logical
	m_cpRButtonDown = point;

	ClientToScreen((LPPOINT)menuPoint);	// Convert to screen coordinates
	RemoveHighlight();
	// TODO: Add your message handler code here and/or call default
	pDoc->SetModifiedFlag();
	//point+=GetScrollPosition( ) ;
	running=1;
	selectRect.SetRectEmpty();

	selectedPort = pDEP->OnConnect(point,&selectedControl,&selectedPortType,&portConnected);
	// load the port menu if an unconnected start port is selected
	if (selectedPort>-1) {
		blob = (ConData*) pDEP->condata->GetAt(selectedControl);
		/*@todo MIGRATION_ISSUES // iconMenu.LoadMenu
		iconMenu.LoadMenu(IDR_ICON_MENU); // Load the icon menu
		*/
		// Check initialise item
		if (selectedPortType == STARTPORT && !blob->startport[selectedPort]->line.exist) {
			iconMenu.GetSubMenu(7)->CheckMenuItem(ID_PORT_INITIALISE,(blob->startport[selectedPort]->initialise==1?MF_CHECKED:MF_UNCHECKED)|MF_BYCOMMAND);
			iconMenu.GetSubMenu(8)->CheckMenuItem(ID_PORT_INITIALISE,(blob->startport[selectedPort]->initialise==1?MF_CHECKED:MF_UNCHECKED)|MF_BYCOMMAND);
		}

		// Enable Tag menu items appropriately
		switch (selectedPortType) {
			case STARTPORT:
			{
				iconMenu.GetSubMenu(7)->EnableMenuItem(ID_ADD_TAG, blob->startport[selectedPort]->tag != "");
				iconMenu.GetSubMenu(7)->EnableMenuItem(ID_DELETE_TAG, blob->startport[selectedPort]->tag == "");
				iconMenu.GetSubMenu(7)->EnableMenuItem(ID_SHOW_LINE, !(blob->startport[selectedPort]->tag != "" &&
					blob->startport[selectedPort]->line.exist));
				iconMenu.GetSubMenu(8)->EnableMenuItem(ID_ADD_TAG, blob->startport[selectedPort]->tag != "");
				iconMenu.GetSubMenu(8)->EnableMenuItem(ID_DELETE_TAG, blob->startport[selectedPort]->tag == "");
				iconMenu.GetSubMenu(8)->EnableMenuItem(ID_SHOW_LINE, !(blob->startport[selectedPort]->tag != "" &&
					blob->startport[selectedPort]->line.exist));
				break;
			}
			case INPUTPORT:
			{
				iconMenu.GetSubMenu(1)->EnableMenuItem(ID_ADD_TAG, blob->inputport[selectedPort]->tag != "");
				iconMenu.GetSubMenu(1)->EnableMenuItem(ID_DELETE_TAG, blob->inputport[selectedPort]->tag == "");
				iconMenu.GetSubMenu(1)->EnableMenuItem(ID_SHOW_LINE, !(blob->inputport[selectedPort]->tag != "" &&
					blob->inputport[selectedPort]->line.exist));
				iconMenu.GetSubMenu(6)->EnableMenuItem(ID_ADD_TAG, blob->inputport[selectedPort]->tag != "");
				iconMenu.GetSubMenu(6)->EnableMenuItem(ID_DELETE_TAG, blob->inputport[selectedPort]->tag == "");
				iconMenu.GetSubMenu(6)->EnableMenuItem(ID_SHOW_LINE, !(blob->inputport[selectedPort]->tag != "" &&
					blob->inputport[selectedPort]->line.exist));
				break;
			}
			case OUTPUTPORT:
			{
				iconMenu.GetSubMenu(1)->EnableMenuItem(ID_ADD_TAG, blob->outputport[selectedPort]->tag != "");
				iconMenu.GetSubMenu(1)->EnableMenuItem(ID_DELETE_TAG, blob->outputport[selectedPort]->tag == "");
				iconMenu.GetSubMenu(1)->EnableMenuItem(ID_SHOW_LINE, !(blob->outputport[selectedPort]->tag != "" &&
					pDEP->IsOutputPortConnected(blob, selectedPort)));
				iconMenu.GetSubMenu(6)->EnableMenuItem(ID_ADD_TAG, blob->outputport[selectedPort]->tag != "");
				iconMenu.GetSubMenu(6)->EnableMenuItem(ID_DELETE_TAG, blob->outputport[selectedPort]->tag == "");
				iconMenu.GetSubMenu(6)->EnableMenuItem(ID_SHOW_LINE, !(blob->outputport[selectedPort]->tag != "" &&
					pDEP->IsOutputPortConnected(blob, selectedPort)));
				break;
			}
			case FINISHPORT:
			{
				iconMenu.GetSubMenu(1)->EnableMenuItem(ID_ADD_TAG, blob->finishport[selectedPort]->tag != "");
				iconMenu.GetSubMenu(1)->EnableMenuItem(ID_DELETE_TAG, blob->finishport[selectedPort]->tag == "");
				iconMenu.GetSubMenu(1)->EnableMenuItem(ID_SHOW_LINE, !(blob->finishport[selectedPort]->tag != "" &&
					pDEP->IsFinishPortConnected(blob, selectedPort)));
				iconMenu.GetSubMenu(6)->EnableMenuItem(ID_ADD_TAG, blob->finishport[selectedPort]->tag != "");
				iconMenu.GetSubMenu(6)->EnableMenuItem(ID_DELETE_TAG, blob->finishport[selectedPort]->tag == "");
				iconMenu.GetSubMenu(6)->EnableMenuItem(ID_SHOW_LINE, !(blob->finishport[selectedPort]->tag != "" &&
					pDEP->IsFinishPortConnected(blob, selectedPort)));
				break;
			}
		}


		// display port menu pop-up
		if (blob->m_iUserDefined && selectedPortType != STARTPORT) {
			iconMenu.GetSubMenu(6)->EnableMenuItem(ID_ADD_PORT_TO_GROUP, 1);
			iconMenu.GetSubMenu(6)->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, menuPoint.x, menuPoint.y, this);
		}
		else if (!blob->m_iUserDefined && selectedPortType == STARTPORT) {
			iconMenu.GetSubMenu(7)->EnableMenuItem(ID_ADD_PORT_TO_GROUP, 1);
			iconMenu.GetSubMenu(7)->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, menuPoint.x, menuPoint.y, this);
		}
		else if (blob->m_iUserDefined && selectedPortType == STARTPORT) {
			iconMenu.GetSubMenu(8)->EnableMenuItem(ID_ADD_PORT_TO_GROUP, 1);
			iconMenu.GetSubMenu(8)->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, menuPoint.x, menuPoint.y, this);
		}
		else {
			iconMenu.GetSubMenu(1)->EnableMenuItem(ID_ADD_PORT_TO_GROUP, 1);
			iconMenu.GetSubMenu(1)->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, menuPoint.x, menuPoint.y, this);
		}
	}
	else {

		const bool INTERROGATE_ONLY = true;
		selectedPort = pDEP->OnLine(point, &nodeIcon, &nodeSelected, &selectedPortType, INTERROGATE_ONLY );
		selectedControl = pDEP->Incontrol(point);
		if (nodeSelected) {
			/*@todo MIGRATION_ISSUES // iconMenu.LoadMenu
			iconMenu.LoadMenu(IDR_ICON_MENU); // Load the icon menu
	*/
			// display node menu pop-up
			iconMenu.GetSubMenu(3)->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, menuPoint.x, menuPoint.y, this);
		}
		else if (selectedPort > -1) {
				/*@todo MIGRATION_ISSUES // iconMenu.LoadMenu
			iconMenu.LoadMenu(IDR_ICON_MENU); // Load the icon menu
			*/
			// display line menu pop-up
			iconMenu.GetSubMenu(2)->EnableMenuItem(ID_DEBUG_FORCE, 1);
			iconMenu.GetSubMenu(2)->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, menuPoint.x, menuPoint.y, this);
		} else if (selectedControl) {
			// highlight icon
			pDEP->setFBHighlight(selectedControl);
			RedrawWindow();

			blob = (ConData *) pDEP->condata->GetAt(selectedControl);
		/*@todo MIGRATION_ISSUES  //	iconMenu.LoadMenu
			iconMenu.LoadMenu(IDR_ICON_MENU); // Load the icon menu
			*/
			// Check show description item
			/// \todo  iconMenu.CheckMenuItem(ID_ICON_SHOW_DESC,(blob->showdescript==1?MF_CHECKED:MF_UNCHECKED)|MF_BYCOMMAND);
			// display icon menu pop-up
			if (blob->m_iUserDefined) {
				iconMenu.GetSubMenu(4)->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, menuPoint.x, menuPoint.y, this);
			}
			else if (blob->m_FbName.Find("XINPUT") != -1 || blob->m_FbName.Find("XOUTPUT") != -1 ||
				blob->m_FbName == "XSTART" || blob->m_FbName == "XFINISH") {
				iconMenu.GetSubMenu(5)->EnableMenuItem(ID_ADD_ICON_TO_GROUP, 1);
				iconMenu.GetSubMenu(5)->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, menuPoint.x, menuPoint.y, this);
			}
			else {
				iconMenu.GetSubMenu(5)->EnableMenuItem(ID_ADD_ICON_TO_GROUP, 1);
				iconMenu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, menuPoint.x, menuPoint.y, this);
			}

		} else {

			// Superseded by the dockable, semi-permanent ConInfoBar, which allows picking of
			// components.
			/*
			point = pDEP->SnapToGrid(point);
			readProjectFile();

			//This is where the component-palette comes up.
			blob = SelectIcon(point);
			//blob = SelectIcon(menuPoint);
			if (blob) {
				if (blob->userDefined) {
					// add this instance to the project tree
					pFrame->m_wndProjectBar.m_cProjTree.AddItem2ProjectTree(blob, pProject, pDEP->hItem);
					// Make sure gui widget tags are unique
					// add any gui widgets to the project meta data
					HTREEITEM hUserDefItem = pFrame->m_wndProjectBar.m_cProjTree.GetUserDefChildItem(blob, pDEP->hItem);
					pProject->uniquifyWidgetsInUserDefBlock(hUserDefItem);
				}
				// Add Gui widgets to project file
				else if (blob->isGuiWidget()) {
					pProject->addGuiWidget(blob);
				}
				// if adding xport then don't allow undo
				if (!(blob->m_csIconType.Find("XINPUT") != -1 || blob->m_csIconType.Find("XOUTPUT") != -1 || blob->m_csIconType == "XSTART"
					|| blob->m_csIconType == "XFINISH")) {
					SaveUndo();
				}
				pProject->SaveProject();
				RedrawWindow();
			}
			*/

		}
	}

	CScrollView::OnRButtonDown(nFlags, point);
	running=0;
#endif
}



/*
Used to draw the trace line when new lines are beig drawn, or icons are being moved
  */
void DrawProgView::OnMouseMove(unsigned int nFlags, INXPoint _point)
{
	INXPoint point(_point.x, _point.y);
	/// \todo create an enum for this
	// case 1: ?
	// case 2: capture selection of function or encap block
	// case 3: capture line selection
	// case 4: rubber band for encapsulation block
	// case 5: creation of rubber band
	// case 6: Multiple objects selected with rubberband
	// case 8: Dragging line segments
	// or Drawing line

	//CScrollView::OnMouseMove(nFlags, (INXPoint)point);

	char buffx[200];
	sprintf(buffx, "%d= m_iLftBtnDownState\n", m_iLftBtnDownState );
	///TRACE( buffx );

	if(pDEP->depFSM.drawingline)
		sprintf(buffx, "pDEP->depFSM.drawingline==true\n" );
	else
		sprintf(buffx, "pDEP->depFSM.drawingline==false\n" );

	//TRACE( buffx );

	if (!running) {

	INXPoint linePoint = point;
	INXSize topleftpnt(0,0); /// \todo GetScrollPosition( ).x, GetScrollPosition( ).y);

	linePoint+=topleftpnt ;
	sleep(20);
	running=1;
#if 0
	CClientDC dc(this); // create device context
	OnPrepareDC(&dc); // adjust origin
	dc.DPtoLP((LPPOINT)point); // convert point to Logical
#endif


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// When the user is not 'doing anything' ie not drawing a line, dragging a connection etc
	// adjust cursor according to what it is over

	if( m_iLftBtnDownState == 0 && !pDEP->depFSM.drawingline ){

		//if (pDEP->depFSM.drawingline)
		INXPoint pnt = point;

		// Over a port?
		int iTmpPortConnected=0;
		int iTmpPortType=0;
		INXPOSITION cTmpSelectedThing;

		int iTmpPortSelected = 0;

		iTmpPortSelected = pDEP->OnConnect(pnt,&cTmpSelectedThing,&iTmpPortType,&iTmpPortConnected);

		if (iTmpPortSelected >= 0) {
			/// \todo ::SetCursor(wxGetApp()->LoadCursor(IDC_CURSOR_LABPORT) );
		} else {
			cTmpSelectedThing = pDEP->Incontrol(pnt);

			bool bTmpNodeSelected;
			int iTmpSelectedPortType;

			const bool INTERROGATE_ONLY = true;
			iTmpPortSelected = pDEP->OnLine(pnt, &cTmpSelectedThing, &bTmpNodeSelected, &iTmpSelectedPortType, INTERROGATE_ONLY);

			// Over a line?
			if(iTmpPortSelected >= 0) {
				if (bTmpNodeSelected) {
					/// \todo ::SetCursor(wxGetApp()->LoadCursor(IDC_CURSOR_LABNODE) );
				} else {
					/// \todo ::SetCursor(wxGetApp()->LoadCursor(IDC_CURSOR_LABLINE) );
				}
			//Over a f-block?
			} else if (cTmpSelectedThing) {
				/// \todo ::SetCursor(wxGetApp()->LoadCursor(IDC_CURSOR_LABBLOCK) );
			} else {
				/// \todo ::SetCursor(wxGetApp()->LoadStandardCursor(IDC_ARROW) );
			}
		}
	} else if (m_iLftBtnDownState == 0 && pDEP->depFSM.drawingline) {
		INXPoint pnt = point;

		// Over a port?
		int iTmpPortConnected=0;
		int iTmpPortType=0;
		INXPOSITION cTmpSelectedThing;

		int iTmpPortSelected = 0;

		iTmpPortSelected = pDEP->OnConnect(pnt,&cTmpSelectedThing,&iTmpPortType,&iTmpPortConnected);

		if( iTmpPortSelected >=0 ){

			/// \todo ::SetCursor(wxGetApp()->LoadCursor(IDC_CURSOR_LABPORT) );

		} else{

			/// \todo ::SetCursor(wxGetApp()->LoadStandardCursor(IDC_ARROW) );

		}
	}

	switch (m_iLftBtnDownState)
	{	// horrible code - sorry
		// lbutton down describes what activity is being done
		// 0 i think is nothing,
		// 2 is moving an icon. drawing a line is seperately indicated for some reason in  'drawingline'
	case 0:
	{

		if( !pDEP->depFSM.drawingline ){

			//if (pDEP->depFSM.drawingline)
			INXPoint pnt = point;

			// Over a port?
			int iTmpPortConnected = 0;
			int iTmpPortType = 0;
			INXPOSITION cTmpSelectedThing;

			int iTmpPortSelected = 0;

			iTmpPortSelected = pDEP->OnConnect(pnt,&cTmpSelectedThing,&iTmpPortType,&iTmpPortConnected);

			if ( iTmpPortSelected >= 0 ) {

				/// \todo ::SetCursor(wxGetApp()->LoadCursor(IDC_CURSOR_LABPORT) );

			} else {
				cTmpSelectedThing = pDEP->Incontrol(pnt);

				bool bTmpNodeSelected;
				int iTmpSelectedPortType;

				const bool INTERROGATE_ONLY = true;
				iTmpPortSelected = pDEP->OnLine(pnt, &cTmpSelectedThing, &bTmpNodeSelected, &iTmpSelectedPortType, INTERROGATE_ONLY);

				// Over a line?
				if(iTmpPortSelected >= 0) {
					if (bTmpNodeSelected) {
						/// \todo ::SetCursor(wxGetApp()->LoadCursor(IDC_CURSOR_LABNODE) );
					} else {
						/// \todo ::SetCursor(wxGetApp()->LoadCursor(IDC_CURSOR_LABLINE) );
					}
				//Over a f-block?
				} else if (cTmpSelectedThing) {
					/// \todo ::SetCursor(wxGetApp()->LoadCursor(IDC_CURSOR_LABBLOCK) );
				} else {
					/// \todo ::SetCursor(wxGetApp()->LoadStandardCursor(IDC_ARROW) );
				}
			}

		} 	else if( pDEP->depFSM.drawingline ) {

			//if (pDEP->depFSM.drawingline)
			INXPoint pnt = point;

			// Over a port?
			int iTmpPortConnected=0;
			int iTmpPortType=0;
			INXPOSITION cTmpSelectedThing;

			int iTmpPortSelected = 0;

			iTmpPortSelected = pDEP->OnConnect(pnt,&cTmpSelectedThing,&iTmpPortType,&iTmpPortConnected);

			if( iTmpPortSelected >=0 ){

				/// \todo ::SetCursor(wxGetApp()->LoadCursor(IDC_CURSOR_LABPORT) );

			} else{

				/// \todo ::SetCursor(wxGetApp()->LoadStandardCursor(IDC_ARROW) );

			}
		}

		break;
	}
	case 2:
	{
		/// \todo
#if 0
		//CClientDC dc(this); //this is the client area only so compensate for scroll offset
		dc.SelectObject(nullpen);
		INXRect extra(2,2,2,2);INXPoint bacabit(1,1);
		INXRect dooby = (RectangleSite)+(oldpoint-firstpoint);
		dooby+=extra;
 		dc.Rectangle(dooby);
		InvalidateRect(dooby,FALSE);
		//oldpoint=point-bacabit;
		dc.SelectObject(dashkpen);
		dooby = RectangleSite+(point-firstpoint);
		dc.Rectangle(dooby);
		//ReleaseDC(&dc); //kwhite this is badly managed
		oldpoint = point;
		if (cs.StretchCanvas(dooby, viewSize))
		{
			SetScrollSizes(MM_TEXT, viewSize);
			pDEP->setCanvasSize(viewSize);
		}
		SetPointToTestAgainst(dooby); //Needed for boundary check on item rather than mouse cursor
		break;
#endif
	}
	// update view with line node being dragged
	case 3:
		{
		if (!pProject->getDefineMonitors()) {
			ConData* blob;

			blob = (ConData*) pDEP->condata->GetAt(nodeIcon);
			// snap nodes to grid.
			point = SnapToGrid(point);
			if (selectedPortType == INPUTPORT) {
				blob->inputport[selectedPort]->line.editNode(point);
			}
			else if (selectedPortType == STARTPORT) {
				blob->startport[selectedPort]->line.editNode(point);
			}

			/// \todo ::SetCursor(wxGetApp()->LoadCursor(IDC_CURSOR_LABNODE) );

			RedrawWindow();
		}
		break;
		}
	// update view with encapsulation box being dragged
	case 4:
		{
		encapsulate.BottomRight() = point;
		/// \todo dc.Rectangle(encapsulate);
		RedrawWindow();
		break;
		}
	// update view with selection box being dragged
	case 5:
		{
		selectRect.BottomRight() = point;
		RedrawWindow();
		break;
		}
	case 6:
	{
		/// \todo
		#if 0
		//CClientDC dc(this); //this is the client area only so compensate for scroll offset
		dc.SelectObject(nullpen);
		INXRect extra(2,2,2,2);
		INXRect dooby = (selectRect)+(oldpoint-firstpoint);
		dooby+=extra;
 		dc.Rectangle(dooby);
		InvalidateRect(dooby,FALSE);
		dc.SelectObject(dashkpen);
		dooby = selectRect+(point-firstpoint);
		dc.Rectangle(dooby);
		//ReleaseDC(&dc); //kwhite this is badly managed
		oldpoint = point;
		if (cs.StretchCanvas(dooby, viewSize))
		{
			SetScrollSizes(MM_TEXT, viewSize);
			pDEP->setCanvasSize(viewSize);
		}
		SetPointToTestAgainst(dooby); //Needed for boundary check on items rather than mouse curser
		break;
#endif
	}
	// update view with line segement being dragged
	case 8:
		{
		if (!pProject->getDefineMonitors()) {
			ConData* blob;

			blob = (ConData*) pDEP->condata->GetAt(nodeIcon);
			// snap nodes to grid.
			point = SnapToGrid(point);
			if (selectedPortType == INPUTPORT) {
				blob->inputport[selectedPort]->line.MoveSegment(point);
			}
			else if (selectedPortType == STARTPORT) {
				blob->startport[selectedPort]->line.MoveSegment(point);
			}

			/// \todo  ::SetCursor(wxGetApp()->LoadCursor(IDC_CURSOR_LABLINE) );

			RedrawWindow();
		}
		break;
		}

	}
#if 0
	// line drawing
		if (pDEP->depFSM.drawingline) {

			INXRect invalided;
			CClientDC dc(this);	//kwhite this is badly managed

			cs.DebugTrace("drawing line\n");
			dc.MoveTo(lastlinepoint-topleftpnt);
			dc.SelectObject(nullpen);
			dc.LineTo(lastmovingline-topleftpnt);
			dc.MoveTo(lastlinepoint-topleftpnt);
			if (lastlinepoint.x>lastmovingline.x) {
				invalided.TopLeft().x = lastmovingline.x;
				invalided.BottomRight().x = lastlinepoint.x;
			}
			else {
				invalided.BottomRight().x=lastmovingline.x;invalided.TopLeft().x=lastlinepoint.x;}
			if (lastlinepoint.y>lastmovingline.y) {
				invalided.TopLeft().y=lastmovingline.y;invalided.BottomRight().y=lastlinepoint.y;}
			else {
				invalided.BottomRight().y=lastmovingline.y;invalided.TopLeft().y=lastlinepoint.y;}

			InvalidateRect(invalided,FALSE);
			// When drawing a line the colour is defined here
			dc.SelectObject(greenpen);
			dc.LineTo(linePoint-topleftpnt);
			lastmovingline=linePoint;
			ReleaseDC(&dc);
		}

	}
	running=0;

	cs.SetDebugTrace(false);

	if (cs.ValidLeftButtonEvent(m_iLftBtnDownState) || pDEP->depFSM.drawingline || m_iLftBtnDownState==5)
	{
		//Mouse over point  -  needs to look at the logical area
		CClientDC dc(this); // create device context
		OnPrepareDC(&dc);   // adjust origin
		dc.LPtoDP((LPPOINT)point);  // convert point to Logical - confused but it works.

		// When line hits (0,0) don't shift rest of diagram, because there aren't any
		// icons above or to the left of this point
		if (pDEP->depFSM.drawingline || m_iLftBtnDownState==5) {
			if (cs.NearTopLeftBoundary(point)) {
				INXPoint ScrollPos = cs.AdjustPositionOfScrollUpwards();
				ScrollToPosition(ScrollPos);
				RedrawWindow();
				Sleep(10);
			}
		}
		else {
			if (cs.NearTopLeftBoundary(cs.GetPointToTestAgainst())) {
				INXPoint adjust;
				adjust = cs.AdjustPositionOfObjects(firstpoint);

				//Ensure items dont dissappear from the bottom/right of the screen
				cs.StretchCanvas(adjust - firstpoint, viewSize);
				SetScrollSizes(MM_TEXT, viewSize);
				pDEP->setCanvasSize(viewSize);

				//Move currently selected objects first, and externally connected lines
				pDEP->MoveObjectsWithinSelectedBox(adjust, firstpoint);
				pDEP->MoveExternallyConnectedLines( adjust, firstpoint);

				//Now we can move other objects, in essence we are moving everything
				pDEP->InvertSelected();									//flip selection
				pDEP->MoveObjectsWithinSelectedBox(adjust, firstpoint);
				pDEP->MoveExternallyConnectedLines( adjust, firstpoint);
				pDEP->InvertSelected();									//flip selection back

				adjust = cs.AdjustPositionOfObjects(cs.GetTempStore()); //alter stored point to reflect scrolling effect
				cs.SetTempStore(adjust);
				cs.SetTopLeftBoundaryHit(true);
				RedrawWindow();
				sleep(10); /// \todo
			}
		}	//INXPoint

		if (cs.NearBottomRightBoundary(point))
		{
			//INXString tmp;
			//unsigned int nScrollCode = 0;
			INXPoint ScrollPosition = cs.AdjustPositionOfScrollDownwards();
			ScrollToPosition(ScrollPosition);
			RedrawWindow();
			sleep(10); /// \todo
		}
		ReleaseDC(&dc);
#endif
	}

}

void DrawProgView::SetPointToTestAgainst(INXRect rect)
{
	INXPoint temp;
	temp.x = rect.left;
	temp.y = rect.top;

	//must take account of scroll position
	INXSize topleft = {0,0}; /// \todo GetThumbPosition( );
	temp.x = temp.x - topleft.cx;
	temp.y = temp.y - topleft.cy;

	//record in canvas object for boundary hit test
	cs.SetPointToTestAgainst(temp);
}

///\todo this doesn't need implementing , but there is some threads started here that need doing elsewhare instead
#if 0
// this assigns the view to a document for file handling
void DrawProgView::OnInitialUpdate()
{
	// Set up the scrollbars
	ResetScrollSizes();
	INXRect clientRect;
	this->GetClientRect(clientRect);
	INXPoint point = pDEP->getInitScrollPos(clientRect);
	this->ScrollToPosition(point);
	cs.SetScrollPosition(point);

	CScrollView::OnInitialUpdate();

	//m_DT.Register(this);

	// TODO: Add your specialized code here and/or call the base class
	pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	onlyDrawAnimatedStuff = false;
//	otherDrawEvent = false;
	toggleAnimation = 0;

	// note - it is currently not possible to start IAB in debug mode, but this is future proofing
	if (pProject->debug.debugMode == DBGSTOP) {
		SetTimer(TIMER_IDS_DRAWANIMATEDSTUFF,TIMER_WAITMS_DRAWANIMATEDSTUFF,NULL); //fire a timer to animate certain parts of the DEP eg. unconnected mandatory ports
	}
	//todo - this blocks any other process from connecting to EHS, suggest use watchdog pattern where EHS creates a file and watchdog checks for presence of this file
//	AfxBeginThread(checkForEHSConnection, this);
}
#endif

/**
 * \brief What does this do? \todo
 */
void DrawProgView::ViewInstance(INXPOSITION selectedIcon) {
#if 0
	ConData* selectedBlob = NULL;
	HTREEITEM childItem;
	INXString depPath, csProjectDir;

	// open the instance dep
	selectedBlob = (ConData*) pDEP->condata->GetAt(selectedIcon);
	pFrame->m_wndProjectBar.m_cProjTree.openProject = FALSE;
	childItem = pFrame->m_wndProjectBar.m_cProjTree.GetUserDefChildItem(selectedBlob, pDEP->hItem);
	depPath = pFrame->m_wndProjectBar.m_cProjTree.GetDEPPath(childItem);
	pFrame->m_wndProjectBar.m_cProjTree.hSelItem = childItem;
	pProject->pProjMData->getProjectDir(csProjectDir);
	CDocument* Subsystem=wxGetApp( ).OpenDocumentFile(csProjectDir + DEPDIR + depPath +
		"\\" + selectedBlob->description + ".prg");
//@todo there is a crash here that occurs when sub systems are opened (reports that the path doesn't exist - this coid be when two projects are open at the same time.
	// Propagate debug data
	INXPOSITION pos = Subsystem->GetFirstViewPosition();
	DrawProgView* pView = (DrawProgView*) Subsystem->GetNextView(pos);
	if (pView->pProject->debug.debugMode != DBGSTOP) {
		pView->pDEP->ResetAllDbgEvents();
		// To Do: Pass the method select
		pView->pDEP->PropagateDebugDataDown(selectedBlob);
	}
	// Need to initialise undo for case when the view is already open
	// This is done in OnActivateView
	/*
		POSITION pos = Subsystem->GetFirstViewPosition();
		DrawProgView* pView = (DrawProgView*) Subsystem->GetNextView(pos);
		pView->initUndo();
	*/
#endif
}

void DrawProgView::OnDelete()
{
	//ShellExecute(NULL, "open", "ruby", "C:\\work\\webTV\\EHS\\iplayer.dl http://www.bbc.co.uk/iplayer/page/item/b00b24mk.shtml?src=ip_potpw", NULL, SW_HIDE);
	if( !pProject->pProjMData->getLock() ) {

		INX_MessageBox(PMD_LOCK_FAILURE_MESSAGE);
	}else{

		ConData* blob;
		bool undo = true;

		readProjectFile();
		// don't allow an undo when deleting a Xport
		blob = (ConData*) pDEP->condata->GetAt(selectedControl);
		if (blob->m_FbName.Find("XINPUT") != -1 || blob->m_FbName.Find("XOUTPUT") != -1 || blob->m_FbName == "XSTART" ||
			blob->m_FbName == "XFINISH") {
			undo = FALSE;
		}
		///\todo pFrame->m_wndProjectBar.m_cProjTree.DeleteIcon(selectedControl, pProject, pDEP, 1);
		RedrawWindow();
		if (undo) {
			SaveUndo();
		}
		else {
			initUndo();
		}
		pProject->SaveProject();
		pProject->pProjMData->writeProjectFile();
		pProject->pProjMData->releaseLock();
	}
}

void DrawProgView::OnProperties()
{
#if 0
	if( !pProject->pProjMData->getLock() ) {

		INX_MessageBox(PMD_LOCK_FAILURE_MESSAGE);

	}else{

		ConData* blob;

		readProjectFile();
		blob = (ConData*) pDEP->condata->GetAt(selectedControl);
		int * retVal = pDEP->EditControl(selectedControl);

		// remove highlight

		blob->selected = 0;
		if( retVal == IDOK)
			pProject->SaveProject();
		RedrawWindow();

		if( retVal == IDOK)
			pProject->pProjMData->writeProjectFile();

		pProject->pProjMData->releaseLock();

	}
#endif
}



void DrawProgView::OnDeleteLine()
{

	pDEP->DeleteLine(nodeIcon, selectedPort, selectedPortType);
	RedrawWindow();
	SaveUndo();
	pProject->SaveProjectDep();
}

void DrawProgView::OnDeleteNode()
{
	int iSegmentNum = -1;
	ConData* blob;

	blob = (ConData*) pDEP->condata->GetAt(nodeIcon);
	///\todo
	#if 0
	if (selectedPortType == INPUTPORT) {
		iSegmentNum = blob->inputport[selectedPort]->line.GetLineSegment(SnapToGrid(m_cpRButtonDown));
	}
	else if (selectedPortType == STARTPORT) {
		iSegmentNum = blob->startport[selectedPort]->line.GetLineSegment(SnapToGrid(m_cpRButtonDown));
	}

	if (iSegmentNum >= 0) {
		if (selectedPortType == INPUTPORT) {
			blob->inputport[selectedPort]->line.DeleteNode(iSegmentNum);
		}
		else if (selectedPortType == STARTPORT) {
			blob->startport[selectedPort]->line.DeleteNode(iSegmentNum);
		}
		RedrawWindow();
		SaveUndo();
		pProject->SaveProjectDep();
	}
#endif
}

void DrawProgView::OnStraighten()
{
	ConData* blob;

	blob = (ConData*) pDEP->condata->GetAt(nodeIcon);
	if (selectedPortType == INPUTPORT) {
		blob->inputport[selectedPort]->line.deleteAllNodes();
	}
	else if (selectedPortType == STARTPORT) {
		blob->startport[selectedPort]->line.deleteAllNodes();
	}
	RedrawWindow();
	SaveUndo();
	pProject->SaveProjectDep();
}

// This function reroutes all lines of the seldcted icon.
void DrawProgView::OnReRouteAll() {
	ConData* blob;
	blob = (ConData*) pDEP->condata->GetAt(selectedControl);// assume selected is OK!
	blob->ReRouteAll();
	RedrawWindow();
	SaveUndo();
	pProject->SaveProjectDep(); // why do we need these?
}


// This function reroutes the slected line -
// THe port number dependent placement is stil l messy (in allr respects) and spread out over the classes this will need reviewing
// at the next code review. @todo it would be best if this were to be moved into the condata class as the 'reroute all' is there too
// and this knows about port numbers, which can then finally be passed to the line class dogleg function.
void DrawProgView::OnReRoute()
{
	ConData* blob;
	blob = (ConData*) pDEP->condata->GetAt(nodeIcon);
	int y_shift=blob->rectangle.top; // if a loop backward is required go below either block
	if (selectedPortType == INPUTPORT) {
		blob->inputport[selectedPort]->line.AddDogLeg(blob->inputport[selectedPort]->portNum*2+1,y_shift);
	}
	else if (selectedPortType == STARTPORT) {
		blob->startport[selectedPort]->line.AddDogLeg(blob->startport[selectedPort]->portNum*2,y_shift);
	}
	RedrawWindow();
	SaveUndo();
	pProject->SaveProjectDep();
}

void DrawProgView::OnIconShowDesc()
{
	ConData* blob;

	blob = (ConData*) pDEP->condata->GetAt(selectedControl);
	///\todo
#if 0
	if (blob->showdescript == 0) {
		CDC *theDC = GetDC();
		blob->DrawDescription(theDC);
		blob->showdescript = 1;
	}
	else if (blob->showdescript == 1) {
		blob->showdescript = 0;
	}
	// remove highlight
	blob->selected = 0;
	RedrawWindow();
	SaveUndo();
	pProject->SaveProjectDep();
#endif
}

void DrawProgView::OnSubset()
{
	if( !pProject->pProjMData->getLock() ) {

		INX_MessageBox(PMD_LOCK_FAILURE_MESSAGE);
	}else{
		lib = 0;
		SubsetEncapsulate();
		pProject->pProjMData->releaseLock();
	}
}

void DrawProgView::OnTopdown()
{
	if( !pProject->pProjMData->getLock() ) {
		INX_MessageBox(PMD_LOCK_FAILURE_MESSAGE);
	}else{

		pDEP->TopdownEncapsulate();
		///\todo pFrame->updateFunctionBlockBar();
		pProject->pProjMData->releaseLock();
	}
}



void DrawProgView::OnPortInitialise()
{
	ConData* blob;

	blob = (ConData*) pDEP->condata->GetAt(selectedControl);
	if (!(selectedPortType == STARTPORT && !blob->startport[selectedPort]->line.exist)) {
		INX_MessageBox("Can only initialise unconnected start ports.");
		return;
	}

	if (blob->startport[selectedPort]->initialise) {
		blob->startport[selectedPort]->initialise = 0;
		blob->startport[selectedPort]->connected = 0;
	}
	// set the start port to initialised
	else {
		blob->startport[selectedPort]->initialise = 1;
		blob->startport[selectedPort]->connected = 1;
	}
	blob->startport[selectedPort]->init();
	RedrawWindow();
	SaveUndo();
	pProject->SaveProjectDep();

}


void DrawProgView::OnCreateInstance()
{
	ConData* blob;

	blob = (ConData*) pDEP->condata->GetAt(selectedControl);
	if (blob->m_iUserDefined)
	{
		ViewInstance(selectedControl);
	}
	else
	{
		INX_MessageBox("Can only view user defined blocks.");
	}
	// remove highlight
	blob->selected = 0;

	RedrawWindow();
}

void DrawProgView::OnUpLevel()
{
	///\todo  pFrame->m_wndProjectBar.m_cProjTree.OpenParent(pDEP->hItem, pProject);
}

void DrawProgView::OnDebugStart()
{
	///\todo
#if 0
	CLabLgbBaseApp *pApp = ( CLabLgbBaseApp * ) wxGetApp();
	bool ehsRunning = pApp->isConnectionToEHS();
	if (!ehsRunning) {
		ehsRunning = pApp->startEHS(false);
	}

	// if EHS started successfully or already running, start debug
	if (ehsRunning) {
		// display loading debug message
		dbgMsg = new CDbgMsgDialog;
	   //Check if new succeeded and we got a valid pointer to a dialog object
		if(dbgMsg != NULL)
		{
			// Create modeless dialog box
			BOOL ret = dbgMsg->Create(IDD_DEBUG_MSG,this);
			if(!ret)   //Create failed.
				INX_MessageBox("Error creating Dialog");
			//dbgMsg->ShowWindow(SW_SHOW);
		}
		else
			INX_MessageBox("Error Creating Dialog Object");

		pProject->debug.setView(this);
		pProject->DebugStart(0); //switch to debug without restart
	//	if (dbgMsg) delete dbgMsg;
	}
#endif
}

void DrawProgView::OnDebugRestart()
{
	pProject->debug.DebugRestart();
}

void DrawProgView::OnDebugStop()
{
	pProject->debug.DebugStop();
}

void DrawProgView::OnEHSInitParams(){
	///\todo  ((CLabLgbBaseApp *) wxGetApp())->openEHSInitParamsDialog();
}



void DrawProgView::OnEHSStartRestart(){
	///\todo ((CLabLgbBaseApp *) wxGetApp())->startEHS(false);
}

/**
 *
 * Exports transferables to export directory
 * Transferables are sodl, info.xml, images, fonts etc
 *
 */
bool DrawProgView::appUploader_ExportTransferables(){
	bool success = false;

	INXString infoFilePath;
	pProject->pProjMData->getProjectDir(infoFilePath);
	infoFilePath += APP_DESC_DIR;
	infoFilePath += APP_DESC_FILE;

	// make sure the info.xml file has been created before we proceed
	CFileOperation fo;
	int foErr = fo.CheckPath( infoFilePath);
	if (foErr != PATH_IS_FILE) {
		INX_MessageBox("Project Description not found:" + infoFilePath);
	} else {
		/* Set the active project in the UI */
		DrawProg &pApp =  wxGetApp();
		pApp.setProjMetaData( pProject->pProjMData );
		pApp.setProject(pProject);

		if( !pProject->pProjMData->getLock() ){
			INX_MessageBox( PMD_LOCK_FAILURE_MESSAGE );
		}else{
			pApp.copyTransferrablesToExports(pProject->pProjMData, false, true);
			// Write-out the latest transfer time.
			pProject->pProjMData->updateTransferTime();
			pProject->pProjMData->writeProjectFile();
			pProject->pProjMData->releaseLock();
			success = true;
		}
	}
	return success;
}

/**
 *
 * Tars up the files in the export directory
 *
 */
bool DrawProgView::appUploader_TarExportFiles(){
	bool success = false;
#if 0
	/// \todo - part way through converting to wxDir
	FILE * pFile;
	long lSize;
	char * buffer;
	size_t result;

	struct archive *a;
	struct archive_entry *entry;
	struct stat st;
	INXString exportPath;
	pProject->pProjMData->getProjectDir(exportPath);
	exportPath += EXPORTDIR;
	INXString filePath;
	INXString name;

	INXString tarFilePath;
	pProject->pProjMData->getProjectDir(tarFilePath);
	tarFilePath += APP_TAR_FILE;

	a = archive_write_new();
	archive_write_set_compression_gzip(a);
	archive_write_set_format_pax_restricted(a); // tar format that uses pax extensions only when absolutely necessary. Most of the time, it will write plain ustar entries
	archive_write_open_filename(a, tarFilePath);

	// write each file in the export directory to the archive
	wxDir hFile; // todo we should abstract finder from the wx finder for future maintenance
	bool bFound = hFile.GetFirst(&name, exportPath + _T("*.*") );
	success = true;
	while ( bFound && success )
	{
		//bFound = hFile.FindNextFile();
		//name = hFile.GetFileName();
		// don't need this for wxDir - if( (! hFile.Exists(name)) && (! hFile..IsDirectory() ))
		{
			//name = hFile.GetFileName();
			filePath = hFile..GetFilePath();
			stat(filePath, &st);
			entry = archive_entry_new();
			archive_entry_set_pathname(entry, name);
			archive_entry_set_size(entry, st.st_size);
			archive_entry_set_filetype(entry, AE_IFREG);
			archive_entry_set_perm(entry, 0644);
			archive_write_header(a, entry);

			success = false;
			pFile = fopen ( filePath , "rb" );
			if (pFile != NULL) {
				// obtain file size:
				fseek (pFile , 0 , SEEK_END);
				lSize = ftell (pFile);
				rewind (pFile);

				// allocate memory to contain the whole file:
				buffer = (char*) malloc (sizeof(char)*lSize);
				if (buffer != NULL) {
					// copy the file into the buffer:
					result = fread (buffer,1,lSize,pFile);
					if (result == lSize) {
						archive_write_data(a, buffer, result);
						success = true;
						//@todo - log success and failure of archiving each file
					}
				}
				fclose(pFile);
				free(buffer);
			}

			archive_entry_free(entry);
		}
	}

	int arcClsErr = archive_write_close(a);
	int arcFreeErr = archive_write_free(a); // archive_write_finish() in libarchive2.x and 3.x

	// if files archived successfully and close and free were successfull
	if (success && (arcClsErr != 0 || arcFreeErr != 0)) {
		success = false;
	}

	return success;
#else
	return false;
#endif
}

void DrawProgView::OnEHSStop(){
	LucidTcpipClient tcpClient;
	LtsStatusType ltsStatusType;

	// connect to tcpip client
	if (( ltsStatusType = tcpClient.Connect()) != 0){
		INX_MessageBox("Unable to establish a TCPIP connection.");
	} else {

		if (( tcpClient.SendText("E\n")) != 0)	{
			INX_MessageBox("Unable to send command over TCPIP connection.");
		}
		// tidy up, close the port at this end
		tcpClient.DisConnect();
	}
}

/* - don't need to send params via tcpip, now update graphics.nfo
void DrawProgView::OnEHSUpdate(){
	LucidTcpipClient tcpClient;
	LtsStatusType ltsStatusType;

	// connect to tcpip client
	if (( ltsStatusType = tcpClient.Connect()) != 0){
		INX_MessageBox("Unable to establish a TCPIP connection.");
	} else {
		EHSInitParams * pParams = ((CDrawProgApp *) wxGetApp())->pEHSInitParams;
		char cRGB[10];
		sprintf_s(cRGB,"%3d%3d%3d",pParams->nColourRed,pParams->nColourGreen,pParams->nColourBlue);


//		if (( tcpClient.SendText("UX100\nUY200\nUW600\nUH300\nUC200057220\nUA150\nUF1\nUZ1\n")) != 0)	{
		if (( tcpClient.SendText("UX" + intToString(pParams->nXCoord) + "\n"
									"UY" + intToString(pParams->nYCoord) + "\n"
									"UW" + intToString(pParams->nWidth) + "\n"
									"UH" + intToString(pParams->nHeight) + "\n"
									"UC" + cRGB + "\n"
									"UA" + intToString(pParams->nAlpha) + "\n"
									"UF" + intToString(pParams->nHasFrame) + "\n"
									"UZ" + intToString(pParams->nZOrder) + "\n"
									)) != 0)	{

			INX_MessageBox("Unable to send command over TCPIP connection.");
			tcpClient.DisConnect();
			return;
		}
	}
}
*/

void switchTarget(int iSelInd) {
#if 0
	LucidTcpipClient tcpClient;

	INXString csLocalIpAddress = DEFAULT_TARGET_LOCAL_IP;
	INXString csLocalPort = getLucidRegValue(_T(REG_TARGET_KEY),_T(REG_TARGET_LOCAL_PORT_VALUE),_T((INXString)DEFAULT_TARGET_PORT));
	INXString csRemoteIpAddress = getLucidRegValue(_T(REG_TARGET_KEY),_T(REG_TARGET_REMOTE_IP_VALUE),_T((INXString)DEFAULT_TARGET_REMOTE_IP));
	INXString csRemotePort = getLucidRegValue(_T(REG_TARGET_KEY),_T(REG_TARGET_REMOTE_PORT_VALUE),_T((INXString)DEFAULT_TARGET_PORT));

	if (iSelInd == TARGET_COMBO_INDEX_LOCAL) {
		// local target selected
		tcpClient.SetIPAddress((INXString)csLocalIpAddress);
		tcpClient.SetPort(atoi(csLocalPort));
		setLucidRegValue(_T(REG_TARGET_KEY),_T(REG_TARGET_LOCATION_VALUE),_T(REG_TARGET_LOCATION_DATA_LOCAL));
		wxGetApp().csCurrentTarget = REG_TARGET_LOCATION_DATA_LOCAL;
	}
	else if (iSelInd == TARGET_COMBO_INDEX_REMOTE) {
		// remote target selected
		tcpClient.SetIPAddress((INXString)csRemoteIpAddress);
		tcpClient.SetPort(atoi(csRemotePort));
		setLucidRegValue(_T(REG_TARGET_KEY),_T(REG_TARGET_LOCATION_VALUE),_T(REG_TARGET_LOCATION_DATA_REMOTE));
		wxGetApp().csCurrentTarget = REG_TARGET_LOCATION_DATA_REMOTE;
	}
	else {
		// app server target selected
		setLucidRegValue(_T(REG_TARGET_KEY),_T(REG_TARGET_LOCATION_VALUE),_T(REG_TARGET_LOCATION_DATA_APPSERVER));
		wxGetApp().csCurrentTarget = REG_TARGET_LOCATION_DATA_APPSERVER;
	}
#endif
}

void DrawProgView::OnSelChangeEHSHostCombo() {
	///int selInd = pFrame->m_combo.GetCurSel();
	//switchTarget(selInd);
}

void DrawProgView::OnEHSManageLocally() {
	///pFrame->m_combo.SetCurSel(TARGET_COMBO_INDEX_LOCAL);
	//switchTarget(TARGET_COMBO_INDEX_LOCAL);
}

void DrawProgView::OnEHSManageRemotely() {
	//@todo validate remote IP address before allow user to switch to managing EHS remotely
	///pFrame->m_combo.SetCurSel(TARGET_COMBO_INDEX_REMOTE);
	//switchTarget(TARGET_COMBO_INDEX_REMOTE);
}



void DrawProgView::OnUpdateEHSManageLocally(CCmdUI *pCmdUI) {
	// TODO: Add your command update UI handler code here
	/// \todo pCmdUI->Enable(((CLabLgbBaseApp *) wxGetApp())->csCurrentTarget != REG_TARGET_LOCATION_DATA_LOCAL);
}

void DrawProgView::OnUpdateEHSManageRemotely(CCmdUI *pCmdUI) {
	// TODO: Add your command update UI handler code here
	/// \todo pCmdUI->Enable(((CLabLgbBaseApp *) wxGetApp())->csCurrentTarget != REG_TARGET_LOCATION_DATA_REMOTE);
}

void DrawProgView::OnUpdateEHSStartRestart(CCmdUI *pCmdUI) {
	// TODO: Add your command update UI handler code here
	/// \todo pCmdUI->Enable(((CLabLgbBaseApp *) wxGetApp())->csCurrentTarget != REG_TARGET_LOCATION_DATA_APPSERVER);
}

void DrawProgView::OnUpdateEHSStop(CCmdUI *pCmdUI) {
	// TODO: Add your command update UI handler code here
	/// \todo pCmdUI->Enable(((CLabLgbBaseApp *) wxGetApp())->csCurrentTarget != REG_TARGET_LOCATION_DATA_APPSERVER);
}

void DrawProgView::OnUpdateEHSInitParams(CCmdUI *pCmdUI) {
	// TODO: Add your command update UI handler code here
	/// \todo pCmdUI->Enable((((CLabLgbBaseApp *) wxGetApp())->csCurrentTarget == REG_TARGET_LOCATION_DATA_LOCAL) && (((CLabLgbBaseApp *) wxGetApp())->isEHSLocalInstallPathKnown));
}

void DrawProgView::OnEHSTopmost(){
	LucidTcpipClient tcpClient;
	LtsStatusType ltsStatusType;

	// connect to tcpip client
	if (( ltsStatusType = tcpClient.Connect()) != 0){
		INX_MessageBox("Unable to establish a TCPIP connection.");
	} else {

		if (( tcpClient.SendText("Z2\n")) != 0)	{
			INX_MessageBox("Unable to send command over TCPIP connection.");
			tcpClient.DisConnect();
			return;
		}
	}
}

void DrawProgView::OnEHSBottommost(){
	LucidTcpipClient tcpClient;
	LtsStatusType ltsStatusType;

	// connect to tcpip client
	if (( ltsStatusType = tcpClient.Connect()) != 0){
		INX_MessageBox("Unable to establish a TCPIP connection.");
	} else {

		if (( tcpClient.SendText("Z0\n")) != 0)	{
			INX_MessageBox("Unable to send command over TCPIP connection.");
			tcpClient.DisConnect();
			return;
		}
	}
}

void DrawProgView::OnEHSNormalZOrder(){
	LucidTcpipClient tcpClient;
	LtsStatusType ltsStatusType;

	// connect to tcpip client
	if (( ltsStatusType = tcpClient.Connect()) != 0){
		INX_MessageBox("Unable to establish a TCPIP connection.");
	} else {

		if (( tcpClient.SendText("Z1\n")) != 0)	{
			INX_MessageBox("Unable to send command over TCPIP connection.");
			tcpClient.DisConnect();
			return;
		}
	}
}

void DrawProgView::OnUpdateLocalHost(CCmdUI *pCmdUI)
{
/* test to add random text to status bar
    pCmdUI->Enable();
    INXString strPage;
    strPage.Format(_T("Page %d"), 12);
    pCmdUI->SetText(strPage);
*/
}

void DrawProgView::OnDebugStartwithrestart()
{
#if 0
	DrawProg &pApp = wxGetApp();
	bool ehsRunning = pApp.isConnectionToEHS();
	if (!ehsRunning) {
		ehsRunning = pApp.startEHS(false);
	}

	// if EHS started successfully or already running, start debug
	if (ehsRunning) {

		///\todo
		/* We need to restart -> set to debug -> send monitors -> run
		'L' -> 'X' - > send stuff() -> 'R'
		*/
		/* @todo we don't do any explicit state change checking here that current SODL and target is coherent */
	/*	pProject->debug.tcpClient.SendText("Lt.sdl\n"); //@todo shouldn't access the tcpip bits like this really!
		pProject->debug.tcpClient.SendText("Lt.sdl\n"); //@todo shouldn't access the tcpip bits like this really!
		OnDebugStart(); // just it it up then run
		*/
		// display loading debug message
		dbgMsg = new CDbgMsgDialog;
	   //Check if new succeeded and we got a valid pointer to a dialog object
		if(dbgMsg != NULL)
		{
			// Create modeless dialog box
			BOOL ret = dbgMsg->Create(IDD_DEBUG_MSG,this);
			if(!ret)   //Create failed.
				INX_MessageBox("Error creating Dialog");
			//dbgMsg->ShowWindow(SW_SHOW);
		}
		else
			INX_MessageBox("Error Creating Dialog Object");

		pProject->debug.setView(this);
		pProject->DebugStart(1); //switch to debug without restart

	}
#endif
}


void DrawProgView::OnEditCut()
{
#if 0
	ConData *icondata;
	INXPOSITION pos, delPos;
	bool undo = true;

	if( !pProject->pProjMData->getLock() ) {
		INX_MessageBox(PMD_LOCK_FAILURE_MESSAGE);
	}else{
		readProjectFile();
		// keep a copy of the selected box to be deleted
		pDEP->setSaveSelectedFlag(true);
		pDEP->SaveProg(workDir + TEMPDIR + "temp");
		pDEP->setSaveSelectedFlag(FALSE);
		// save project because may have changed sub-blocks but not saved, and want to paste changes
		pProject->SaveProject();
		edit.BufferSelectedIcons(selectRect, pProject, pDEP);
		pasteFlag = true;

		// delete every icon in the selected box
		pos = pDEP->condata->GetHeadPosition();
		while (pos) {
			delPos = pos;
			icondata = (ConData *) (pDEP->condata->GetNext(pos));
			//if (selectRect.PtInRect(icondata->GetIconCentre())) {
			if (icondata->selected) {
				if (icondata->m_FbName.Find("XINPUT") != -1 || icondata->m_FbName.Find("XOUTPUT") != -1 || icondata->m_FbName == "XSTART" ||
					icondata->m_FbName == "XFINISH") {
					undo = FALSE;
				}
				pFrame->m_wndProjectBar.m_cProjTree.DeleteIcon(delPos, pProject, pDEP, 1);
				if (!undo) {
					//@todo - currently can't undo an edit-cut if the selection contains a subsystem
					initUndo();
				}
			}
		}
		selectRect.BottomRight() = selectRect.TopLeft();
		RedrawWindow();
		copyFlag = FALSE;
		if (undo) {
			SaveUndo();
		}
		pProject->SaveProject();
		edit.resetPasteOffset();
		pProject->pProjMData->writeProjectFile();
		pProject->pProjMData->releaseLock();
	}
#endif
}

void DrawProgView::OnEditCopy()
{
#if 0
	if( !pProject->pProjMData->getLock() ) {
		INX_MessageBox(PMD_LOCK_FAILURE_MESSAGE);
	}else{
		readProjectFile();
		// if an icon is selected then want to be able to copy
		// Therefore, need to save the fact that it is selected
		// However, only want to do this when copying and not when saving app.
		pDEP->setSaveSelectedFlag(true);
		pDEP->SaveProg(workDir + TEMPDIR + "temp");
		pDEP->setSaveSelectedFlag(FALSE);
		// save project because may have changed sub-blocks but not saved, and want to paste changes
		pProject->SaveProject();
		edit.BufferSelectedIcons(selectRect, pProject, pDEP);
		pasteFlag = true;
		edit.resetPasteOffset();
		pProject->pProjMData->releaseLock();
	}
#endif
}

void DrawProgView::OnEditPaste()
{
#if 0
	ConData* icondata;
	INXPOSITION pos;
	INXObjList* pasteList;
	INXPoint old(0,0);
	INXPoint topLeft, bottomRight, ScrollPosition;
	HTREEITEM hParent;
	INXString depPath, csProjectDir;
	DEP* pParentDEP;
	INXRect clientRect;

	if( !pProject->pProjMData->getLock() ) {
		INX_MessageBox(PMD_LOCK_FAILURE_MESSAGE);
	}else{

		readProjectFile();
		pProject->pProjMData->getProjectDir(csProjectDir);
		//SaveCopy("tmpcopy.prg");
		RemoveHighlight();
		pasteList = edit.LoadPaste((INXString)workDir + "\\tmpcopy.prg");
		if (pasteList == NULL) {
			pProject->pProjMData->releaseLock();
			return;
		}
		if (XportNameExist(pasteList)) {
			INX_MessageBox("Cannot paste the icons, because one of the Xport labels already exists.");
			pProject->pProjMData->releaseLock();
			return;
		}
		pDEP->ReassignIconIDs(pasteList);

		// initialise the selection box coordinates
		icondata = (ConData*)(pasteList->GetHead());
		topLeft = icondata->GetIconPos();
		bottomRight = icondata->GetIconBottomRight();

		pos = pasteList->GetHeadPosition();
		while (pos) {
			icondata = (ConData*)(pasteList->GetNext(pos));
			// highlight all the icons pasted so that they can be moved
			icondata->selected = 1;
			// adjust selection box coordinates to fit around the pasted icons
			if (icondata->GetIconPos().x < topLeft.x) {
				topLeft.x = icondata->GetIconPos().x;
			}
			if (icondata->GetIconPos().y < topLeft.y) {
				topLeft.y = icondata->GetIconPos().y;
			}
			if (icondata->GetIconBottomRight().x > bottomRight.x) {
				bottomRight.x = icondata->GetIconBottomRight().x;
			}
			if (icondata->GetIconBottomRight().y > bottomRight.y) {
				bottomRight.y = icondata->GetIconBottomRight().y;
			}
			//icondata->RenewPosition(offset, old, firstpoint);
			// add user defined blocks to project tree
			if (icondata->m_iUserDefined) {
				pDEP->CreateInstance(icondata, 2);
				pFrame->m_wndProjectBar.m_cProjTree.AddItem2ProjectTree(icondata, pProject, pDEP->hItem);
			}
			// if we are pasting an xport, test if it is being pasted into a subsystem first
			if (icondata->m_FbName.Find("XINPUT") != -1 || icondata->m_FbName.Find("XOUTPUT") != -1 ||
				icondata->m_FbName == "XSTART" || icondata->m_FbName == "XFINISH") {
				hParent = pFrame->m_wndProjectBar.m_cProjTree.GetParentItem(pDEP->hItem);

				// can only add xports if DEP has a parent (is a subsystem), add ports to parent component and add xport to this DEP
				if ((INXString)pFrame->m_wndProjectBar.m_cProjTree.GetItemText(hParent) != APP) {
					depPath = pFrame->m_wndProjectBar.m_cProjTree.GetDEPPath(hParent);
					pFrame->m_wndProjectBar.m_cProjTree.hSelItem = hParent;
					DrawProgView* pView = pProject->OpenView(csProjectDir + DEPDIR + depPath +
						(INXString)pFrame->m_wndProjectBar.m_cProjTree.GetItemText(hParent) + ".prg");
					pParentDEP = pView->pDEP;
					pParentDEP->AddBlockPort(icondata->m_FbName, icondata->description, pDEP->depFilename);
					// set modified flag in doc
					pView->pDoc->SetModifiedFlag(true);
					pFrame->m_wndProjectBar.m_cProjTree.hSelItem = pDEP->hItem;
					CDocument* Subsystem = wxGetApp( )->OpenDocumentFile(csProjectDir + DEPDIR +
						pFrame->m_wndProjectBar.m_cProjTree.GetDEPPath(pDEP->hItem) + pDEP->depFilename + ".prg");
					pDEP->condata->AddTail(icondata);
				}
			} else {
				pDEP->condata->AddTail(icondata);
			}
		}
		pProject->addPastedGuiWidgets(pDEP->hItem, pasteList);

		selectRect.TopLeft() = topLeft;
		selectRect.BottomRight() = bottomRight;
		selectRect.InflateRect(10,10,10,10);
		// offset for pasted icons
		//selectRect.OffsetRect(offset);

		//pDEP->condata->AddTail(pasteList);
		pDEP->AssignIconLineEndPoints();
		//pasteList->RemoveAll();
		delete pasteList;

		// check that the pasted icons are inside the client rect otherwise paste them in
		// the top left corner of the client rect
		ScrollPosition = this->GetScrollPosition();
		this->GetClientRect(clientRect);
		clientRect.MoveToXY(ScrollPosition);
		if (!clientRect.PtInRect(topLeft)) {
			edit.setPasteOffset(ScrollPosition);
			firstpoint = topLeft - INXPoint(20,30);
		}
		else {
			firstpoint = old;
		}

		selectRect = pDEP->RenewSelectedPos(edit.getPasteOffset(), firstpoint, selectRect);
		// if pasted icons are near bottom right then increase canvas and adjust scroll position
		if (cs.StretchCanvas(selectRect, viewSize)) {
			SetScrollSizes(MM_TEXT, viewSize);
			pDEP->setCanvasSize(viewSize);
		}
		if (cs.NearBottomRightBoundary(selectRect.BottomRight())) {
			cs.AdjustPositionOfScrollDownwards();
			ScrollPosition = cs.AdjustPositionOfScrollDownwards();
			ScrollToPosition(ScrollPosition);
		}
		edit.incPasteOffset();
		RedrawWindow();
		// icons are still highlighted so allow cut and copy
		copyFlag = true;
		SaveUndo();
		pProject->SaveProject();

		pProject->pProjMData->writeProjectFile();
		pProject->pProjMData->releaseLock();
	}
#endif
}

void DrawProgView::OnDebugPause()
{
	pProject->debug.DebugPause();
}

void DrawProgView::OnDebugStep()
{
	pProject->debug.DebugStep();
}

void DrawProgView::OnDebugForce()
{
	pProject->debug.DebugForce(nodeIcon, selectedPortType, selectedPort);
}

void DrawProgView::OnDbgHistStart()
{
	pProject->debug.DbgHistStart();
}

void DrawProgView::OnDbgHistStep()
{
	pProject->debug.waitNxtEvnt = true;
}

void DrawProgView::OnDbgHistTime()
{
	pProject->debug.DbgHistTime();
}

void DrawProgView::OnDbgHistStop()
{
	pProject->debug.dbgHistory = FALSE;
	pProject->debug.waitNxtEvnt = true;
}

void DrawProgView::OnUpdateDebugStartwithrestart(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable((pProject->debug.debugMode == DBGSTOP) && !pProject->debug.dbgHistory && !lock);
}


void DrawProgView::OnUpdateDebugStart(CCmdUI* pCmdUI)
{
	// debugger doesn't work in ehs so disable in dep
	//pCmdUI->Enable(true);
	pCmdUI->Enable((pProject->debug.debugMode == DBGSTOP) && !pProject->debug.dbgHistory && !lock);
}

void DrawProgView::OnUpdateDebugStop(CCmdUI* pCmdUI)
{
	pCmdUI->Enable((pProject->debug.debugMode != DBGSTOP) && !pProject->debug.dbgHistory && !lock);
}

void DrawProgView::OnUpdateDebugForce(CCmdUI* pCmdUI)
{
	// Enable force item when in pause state
	pCmdUI->Enable(FALSE);
	//pCmdUI->Enable((pProject->debug.debugMode == DBGPAUSE) && !pProject->debug.dbgHistory);
}

void DrawProgView::OnUpdateDebugPause(CCmdUI* pCmdUI)
{
	// Enable pause item when in start state and step state
	// Want to be able to pause stepping.
	pCmdUI->Enable(((pProject->debug.debugMode == DBGSTART) || (pProject->debug.debugMode == DBGSTEP)) && !pProject->debug.dbgHistory && !lock);
}

void DrawProgView::OnUpdateDebugStep(CCmdUI* pCmdUI)
{
	// Enable step item when in pause state
	pCmdUI->Enable((pProject->debug.debugMode == DBGPAUSE) && !pProject->debug.dbgHistory);
	// Keep button depressed until event received
	pCmdUI->SetCheck((pProject->debug.debugMode == DBGSTEP));
}

void DrawProgView::OnUpdateDebugRestart(CCmdUI* pCmdUI)
{
	// Enable restart item when in pause state and step state
	pCmdUI->Enable(((pProject->debug.debugMode == DBGPAUSE) || (pProject->debug.debugMode == DBGSTEP)) && !pProject->debug.dbgHistory);
}

void DrawProgView::OnUpdateDbgHistStart(CCmdUI* pCmdUI)
{
	// Enable debug history start item when debug data is available
	pCmdUI->Enable(((pProject->debug.debugMode == DBGPAUSE) || ((pProject->debug.debugMode == DBGSTOP) &&
		pProject->debug.dbgDataRdy)) && !pProject->debug.dbgHistory);
}

void DrawProgView::OnUpdateDbgHistStep(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(pProject->debug.dbgHistory);
}

void DrawProgView::OnUpdateDbgHistStop(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(pProject->debug.dbgHistory);
}

void DrawProgView::OnUpdateDbgHistTime(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(pProject->debug.dbgHistory);
}

void DrawProgView::OnDestroy()
{
	//CScrollView::OnDestroy();

	if (pProject) {
		pProject->debug.DestroyView();
	}
}

void DrawProgView::OnUpdateEditPaste(CCmdUI* pCmdUI)
{
	//pCmdUI->Enable(pasteFlag);
}

void DrawProgView::OnUpdateEditCopy(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(copyFlag);
}

void DrawProgView::OnUpdateEditCut(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(copyFlag);
}

void DrawProgView::OnTimer(unsigned int nIDEvent)
{
	if (nIDEvent == TIMER_IDS_DRAWANIMATEDSTUFF) {
//		KillTimer(TIMER_IDS_DRAWANIMATEDSTUFF);

		//@todo - various performance improvements: currently uses brute force to check every port and only highlight those in state of mandatory & no connection
		// Suggestion is to have a global reference count maintained by the ports that turns the animation timer on/off when > 0 and = 0 respectively
		// As a bootstrap to the reference count could check all ports on a slow timer and kill the animation timer if no ports require highlighting
		onlyDrawAnimatedStuff = false;

		// only do this if not debugging, dragging or selecting rectangle etc
		if ((pProject->debug.debugMode == DBGSTOP) && (m_iLftBtnDownState == 0)) {
			onlyDrawAnimatedStuff = true;
			if (toggleAnimation == 0) {
				toggleAnimation = 1;
			} else {
				toggleAnimation = 0;
			}
			// redraw ports - flag to prevent background from being erased
			wxRect clientRect = GetClientRect();
			//(&clientRect);
			///\todoInvalidateRect( clientRect,false);

#if 0
			///\todo
			HICON hIcon = (HICON)::LoadImage(AfxGetInstanceHandle(), getConnectionState() ? MAKEINTRESOURCE(IDI_LED_ON) : MAKEINTRESOURCE(IDI_LED_OFF), IMAGE_ICON, 16, 16, LR_SHARED);
			if (getConnectionState() && !toggleAnimation) {
				hIcon = NULL;
			}

			//todo - should poll both local and remote not one or the other
			if (((CLabLgbBaseApp *) wxGetApp())->csCurrentTarget == REG_TARGET_LOCATION_DATA_LOCAL) {
				pFrame->m_wndStatusBar.GetStatusBarCtrl().SetIcon(pFrame->m_wndStatusBar.CommandToIndex(ID_INDICATOR_LOCALHOST), hIcon);
				pFrame->m_wndStatusBar.GetStatusBarCtrl().SetIcon(pFrame->m_wndStatusBar.CommandToIndex(ID_INDICATOR_NUM), NULL);
			} else if (((CLabLgbBaseApp *) wxGetApp())->csCurrentTarget == REG_TARGET_LOCATION_DATA_REMOTE) {
				pFrame->m_wndStatusBar.GetStatusBarCtrl().SetIcon(pFrame->m_wndStatusBar.CommandToIndex(ID_INDICATOR_NUM), hIcon);
				pFrame->m_wndStatusBar.GetStatusBarCtrl().SetIcon(pFrame->m_wndStatusBar.CommandToIndex(ID_INDICATOR_LOCALHOST), NULL);
			}
			DestroyIcon(hIcon);

#endif
		}
	} else {
//		pProject->debug.setWriteRtaTrace(true);
	}
//	CScrollView::OnTimer(nIDEvent);
}

bool DrawProgView::getConnectionState() {
	return bHasConnectionToEHS;
}

#if 0
unsigned int DrawProgView::checkForEHSConnection( void* ptr )
{
	//todo - polling of connection should be in a separate thread
	// need to poll local and remote independent of setting csCurrentTarget
	// problem - blocks process if remote IP not found as timeout is too long
	LucidTcpipClient tcpClient;
	LtsStatusType ltsStatusType;

	while (1) {
		// connect to tcpip client
		if (( ltsStatusType = tcpClient.Connect()) != 0){
			bHasConnectionToEHS = false;
			//todo - why does this test never fail in linux env?
		} else {
			// test connection by retrieving state
			if (( tcpClient.SendText("?S\n")) != 0)	{
				bHasConnectionToEHS = false;
			} else {
				bHasConnectionToEHS = true;
			}
		}
		Sleep(2000);
	}
	return 0;
}
#endif


bool DrawProgView::OnEraseBkgnd()
{
#if 0
	if ((pProject->debug.debugMode == DBGSTART) || (m_iLftBtnDownState == 5) || (m_iLftBtnDownState == 4)) {
		return FALSE;
	}
	else {
		return CScrollView::OnEraseBkgnd(pDC);
	}
#endif
}

void DrawProgView::OnUpdateUpLevel(CCmdUI* pCmdUI)
{
#if 0
	HTREEITEM hParent = pFrame->m_wndProjectBar.m_cProjTree.GetParentItem(pDEP->hItem);
	pCmdUI->Enable((INXString)pFrame->m_wndProjectBar.m_cProjTree.GetItemText(hParent) != APP);
#endif
}

void DrawProgView::OnEditUndo()
{

#if 0
	if(!pProject->pProjMData->getLock() ){
		INX_MessageBox( PMD_LOCK_FAILURE_MESSAGE );
	}else{

		char szUndoFileNum[MAX_UNDO_FILE_NUM];
		int iTmp;

		// delete all condata objects
		pDEP->deleteConData();
		pDEP->condata->RemoveAll();
		// decrement the undo file num pointer
		if (iUndoFileNum == 0) {
			iUndoFileNum = (int)pow(10.0, MAX_UNDO_FILE_NUM-1)-1;
		}
		else {
			iUndoFileNum--;
		}
		// Load the previous DEP and project file
		if (iUndoFileNum == 0) {
			iTmp = (int)pow(10.0, MAX_UNDO_FILE_NUM-1)-1;
		}
		else {
			iTmp = iUndoFileNum-1;
		}
		_itoa_s(iTmp, szUndoFileNum, 10);
		pDEP->LoadProg(workDir + TEMPDIR + "undo" + szUndoFileNum + ".prg");
		//pProject->pProjMData->setProjectToNull();
		pProject->pProjMData->readProjectFile(workDir + TEMPDIR + "lpj_undo" + szUndoFileNum);

		if (iUndoFileNum == iUndoFlagNum) {
			undoFlag = FALSE;
		}
		// remove selection box for the case when doing a group move
		selectRect.BottomRight() = selectRect.TopLeft();
		copyFlag = FALSE;

		// update project navigator
		pFrame->m_wndProjectBar.m_cProjTree.UpdateTree(pProject, pDEP);
		pProject->SaveProject();
		pProject->pProjMData->writeProjectFile();

		// remap DEP and resend all monitors in debug mode
		if (pProject->debug.debugMode != DBGSTOP) {
			pDEP->MapLineID(pProject->flattened);
			pProject->debug.sendAllMonitors();
		}

		RedrawWindow();
		redoFlag = true;
		pProject->pProjMData->releaseLock();
	}
#endif
}

void DrawProgView::OnUpdateEditUndo(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(undoFlag);
}

void DrawProgView::OnEditRedo()
{
	if(!pProject->pProjMData->getLock() ){
		INX_MessageBox( PMD_LOCK_FAILURE_MESSAGE );
	}else{

		char szUndoFileNum[MAX_UNDO_FILE_NUM];

		// delete all condata objects
		pDEP->deleteConData();
		pDEP->condata->RemoveAll();
		// Load the DEP and project file prior to undo
		sprintf( szUndoFileNum,"%d",iUndoFileNum);
		pDEP->LoadProg(workDir + TEMPDIR + "undo" + szUndoFileNum + ".prg");
		pProject->pProjMData->readProjectFile(workDir + TEMPDIR + "lpj_undo" + szUndoFileNum);
		if (iUndoFileNum >= (int)pow(10.0, MAX_UNDO_FILE_NUM-1)-1) {
			iUndoFileNum = 0;
		}
		else {
			iUndoFileNum++;
		}
		if (iUndoFileNum == maxUndoFileNum) {
			redoFlag = FALSE;
		}

		// update project navigator
		///\todo pFrame->m_wndProjectBar.m_cProjTree.UpdateTree(pProject, pDEP);
		pProject->pProjMData->writeProjectFile();

		// remap DEP in debug mode
		if (pProject->debug.debugMode != DBGSTOP) {
			pDEP->MapLineID(pProject->flattened);
			pProject->debug.sendAllMonitors();
		}

		RedrawWindow();
		undoFlag = true;
		pProject->pProjMData->releaseLock();
	}
}

void DrawProgView::OnUpdateEditRedo(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(redoFlag);
}

void DrawProgView::OnUpdateFtpSodl(CCmdUI* pCmdUI)
{
	INXString csProjectName;
	pProject->pProjMData->getProjectName(csProjectName);
	pCmdUI->Enable((csProjectName == pDEP->depFilename) && (pProject->debug.debugMode == DBGSTOP));
}

void DrawProgView::OnAddPort()
{
	ConData* blob;
	INXString portLabel;
	INXString portType, dataType;
	int iPortType, iDataType;
	INXPoint point;
	INXString blockFile;

	blob = (ConData*) pDEP->condata->GetAt(selectedControl);
#if 0
	CAddPortDialog dialog(blob);
	if (blob->m_iUserDefined) {
		if (dialog.DoModal() == IDOK) {
			portLabel = dialog.m_PortLabel;
			portLabel.MakeLower();
			portType = dialog.portType;
			dataType = dialog.dataType;
			iPortType = blob->portType2Int(portType);
			// convert data type to an int
			if (dataType == "Boolean") {
				iDataType = 0;
			}
			else if (dataType == "Integer") {
				iDataType = 1;
			}
			else if (dataType == "Real") {
				iDataType = 2;
			}
			else if (dataType == "String") {
				iDataType = 3;
			}
			else {
				iDataType = -1;
			}
			pFrame->m_wndProjectBar.m_cProjTree.openProject = FALSE;
			pProject->AddBlockPort(blob, iDataType, iPortType, portLabel, pDEP);
			pFrame->m_wndProjectBar.m_cProjTree.openProject = true;
			blob->selected = 0;
			RedrawWindow();
			pProject->SaveProjectDep();
			//@todo - currently can't undo addition of ports to a subsystem
			// don't allow undo of ports because can't undo them in the other block
			initUndo();
		}
	}
	else {
		INX_MessageBox("Can only add ports to user defined blocks.");
	}
#endif
}

void DrawProgView::OnUpdateAddPort(CCmdUI* pCmdUI)
{
	//pCmdUI->Enable(FALSE);
}

void DrawProgView::OnDeletePort()
{
	if (INX_MessageBox("Deleting a port will also change the subsystem and the action cannot be undone. Do you want to continue?")) {
		///\todo pFrame->m_wndProjectBar.m_cProjTree.DeleteBlockPort(selectedControl, selectedPort, selectedPortType, pProject, pDEP);
		//SaveUndo();
		pProject->SaveProjectDep();
		//@todo - currently can't undo a delete port on a subsystem but have added a confimation dialog
		// Can't undo delete port currently, because it requires udating 2 deps (.prg)
		initUndo();
	}
}

void DrawProgView::OnTagLine()
{
	pDEP->TagLine(nodeIcon, selectedPort, selectedPortType);
	RedrawWindow();
	SaveUndo();
	pProject->SaveProjectDep();
}

void DrawProgView::OnShowLine()
{
	pDEP->ShowLine(selectedControl, selectedPort, selectedPortType);
	RedrawWindow();
	SaveUndo();
	pProject->SaveProjectDep();
}

void DrawProgView::OnDeleteTag()
{
	pDEP->DeleteTag(selectedControl, selectedPort, selectedPortType);
	RedrawWindow();
	SaveUndo();
	pProject->SaveProjectDep();
}

void DrawProgView::OnAddTag()
{
	if (pDEP->AddTag(selectedControl, selectedPort, selectedPortType)) {
		RedrawWindow();
		SaveUndo();
		pProject->SaveProjectDep();
	}
}
#if 0
void DrawProgView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	int xOrg, yOrg;

	// Output the file name
	pDC->SetTextAlign(TA_CENTER);
	pDC->TextOut(pInfo->m_rectDraw.right/2, -20, (INXString)((CPrintData*)(pInfo->m_lpUserData))->m_ViewTitle);
	pDC->SetTextAlign(TA_LEFT);

	// Calculate the origin point for the current page
	if (((CDrawProgApp*)wxGetApp())->GetOrientation() == 0) {
		xOrg = (int)(((CPrintData*)(pInfo->m_lpUserData))->m_ViewRefPoint.x + PAGE_WIDTH*((pInfo->m_nCurPage - 1)%
		(((CPrintData*)(pInfo->m_lpUserData))->m_nWidths)));
		yOrg = (int)(((CPrintData*)(pInfo->m_lpUserData))->m_ViewRefPoint.y - PAGE_LENGTH*((pInfo->m_nCurPage - 1)/
		(((CPrintData*)(pInfo->m_lpUserData))->m_nWidths)));
	}
	else if (((CDrawProgApp*)wxGetApp())->GetOrientation() == 1) {
		xOrg = (int)(((CPrintData*)(pInfo->m_lpUserData))->m_ViewRefPoint.x + PAGE_LENGTH*((pInfo->m_nCurPage - 1)%
		(((CPrintData*)(pInfo->m_lpUserData))->m_nLengths)));
		yOrg = (int)(((CPrintData*)(pInfo->m_lpUserData))->m_ViewRefPoint.y - PAGE_WIDTH*((pInfo->m_nCurPage - 1)/
		(((CPrintData*)(pInfo->m_lpUserData))->m_nLengths)));
	}

	// Calculate offsets to center drawing area on page as positive values
	//int xOffset = (int)(pInfo->m_rectDraw.right - PAGE_WIDTH)/2;
	//int yOffset = -(int)(pInfo->m_rectDraw.bottom + PAGE_LENGTH)/2;
	int xOffset = 0; int yOffset = 0;

	// Change window origin to correspond to current page & save old origin
	INXPoint oldOrg = pDC->SetWindowOrg(xOrg-xOffset, yOrg+yOffset);

	// Define a clip rectangle the size of the printed area
	//pDC->IntersectClipRect(xOrg,yOrg,xOrg+(int)PAGE_WIDTH,yOrg+(int)PAGE_LENGTH);
	pDC->IntersectClipRect(xOrg,yOrg,xOrg+pInfo->m_rectDraw.right,yOrg+pInfo->m_rectDraw.bottom);

	OnDraw(pDC); // Draw the whole view
	pDC->SelectClipRgn(NULL); // Remove the clip rectangle
	pDC->SetWindowOrg(oldOrg); // Restore old window origin
	//CScrollView::OnPrint(pDC, pInfo);
}
#endif

void DrawProgView::OnViewZoom()
{
#if 0
	CZoomDialog dialog;

	// Initialise the zoom dialog box
	dialog.iScale = scale;
	if (dialog.DoModal() == IDOK) {
		scale = dialog.iScale;
		RedrawZoom();
	}
#endif
}

void DrawProgView::OnWriteSodl()
{
	if(!pProject->pProjMData->getLock() ){
		INX_MessageBox( PMD_LOCK_FAILURE_MESSAGE );
	}else{
		INXString csProjectDir;
		pProject->pProjMData->getProjectDir( csProjectDir );

		//INX_MessageBox( "Get ready to call SaveProject" );
		pProject->SaveProject();

		//INX_MessageBox( "Get ready to call m_cProjTree.SaveHierName" );
		///\todo pFrame->m_wndProjectBar.m_cProjTree.SaveHierName(pProject->pDEP[0]->hItem, csProjectDir, pProject);

		//INX_MessageBox( "Get ready to call WriteSODL" );
		pProject->WriteSODL(csProjectDir + SODLDIR + SODLFILENAME);
		pProject->pProjMData->releaseLock();
	}
}

void DrawProgView::OnUpdateWriteSodl(CCmdUI* pCmdUI)
{
	INXString csProjectName;
	pProject->pProjMData->getProjectName(csProjectName);
	//pCmdUI->Enable((csProjectName == pDEP->depFilename) && (pProject->debug.debugMode == DBGSTOP));
	pCmdUI->Enable(pProject->debug.debugMode == DBGSTOP);
}

void DrawProgView::OnGroupSetup()
{
	pProject->EditGroupSetup();
}

void DrawProgView::OnAddIconToGroup()
{
#if 0
	CSelectGroupDialog dialog(pProject);
	int index;
	vector<Group> vGroups;

	if (dialog.DoModal()==IDOK) {
		// get the corresponding group ID
		pProject->pProjMData->getGroupVec(vGroups);
		for (unsigned int i=0; i<vGroups.size(); i++) {
			if (dialog.selectedGroup == vGroups.at(i).Name) {
				index = i;
			}
		}
		// set the groupID in all the icon start ports
		pProject->AddIconToGroup(selectedControl, vGroups.at(index).ID, pDEP);
	}
	// remove highlight
	ConData* blob = (ConData*) pDEP->condata->GetAt(selectedControl);
	blob->selected = 0;
	RedrawWindow();
#endif
}

void DrawProgView::OnAddPortToGroup()
{
#if 0
	CSelectGroupDialog dialog(pProject);
	ConData* blob;
	vector<Group> vGroups;

	// only set the group ID in start ports
	if (selectedPortType == STARTPORT) {
		if (dialog.DoModal()==IDOK) {
			// get the corresponding group ID
			pProject->pProjMData->getGroupVec(vGroups);
			for (unsigned int i=0; i<vGroups.size(); i++) {
				if (dialog.selectedGroup == vGroups.at(i).Name) {
					// set the groupID in the start port selected
					blob = (ConData*) pDEP->condata->GetAt(selectedControl);
					blob->startport[selectedPort]->groupID = vGroups.at(i).ID;
				}
			}
		}
	}
	else {
		INX_MessageBox("Can only add start ports to a group.");
	}
#endif
}

// Add selected icons to a group
void DrawProgView::OnAddToGroup()
{
#if 0
	INXPOSITION pos, selectedPos;
	CSelectGroupDialog dialog(pProject);
	int selectedCount = 0;
	ConData* icondata;
	vector<Group> vGroups;

	// check if any icons have been selected
	pos = pDEP->condata->GetHeadPosition();
	while (pos) {
		icondata = (ConData *) (pDEP->condata->GetNext(pos));
		if (selectRect.PtInRect(icondata->GetIconCentre())) {
			selectedCount++;
		}
	}
	if (selectedCount) {
		if (dialog.DoModal()==IDOK) {
			// get the corresponding group ID
			pProject->pProjMData->getGroupVec(vGroups);
			for (unsigned int i=0; i<vGroups.size(); i++) {
				if (dialog.selectedGroup == vGroups.at(i).Name) {
					// set the groupID in all the selected icons
					pos = pDEP->condata->GetHeadPosition();
					while (pos) {
						selectedPos = pos;
						icondata = (ConData *) (pDEP->condata->GetNext(pos));
						if (selectRect.PtInRect(icondata->GetIconCentre())) {
							pProject->AddIconToGroup(selectedPos, vGroups.at(i).ID, pDEP);
						}
						// remove highlight
						icondata->selected = 0;
					}
				}
			}
		}
	}
	else {
		INX_MessageBox("First select the icons you want to add to the group.");
	}

	selectRect.SetRectEmpty();
	RedrawWindow();
#endif
}

void DrawProgView::OnSaveProject()
{
	// read project file first to avoid overwriting changes made by LGB
	if(!pProject->pProjMData->getLock() ){

		INX_MessageBox( PMD_LOCK_FAILURE_MESSAGE );

	}else{
		readProjectFile();
		pProject->SaveProject();
		// don't allow undo when save project, because it removes user defined blocks that have been deleted
		undoFlag = FALSE;
		pProject->pProjMData->releaseLock();
	}
#if 0
	///\todo remove this
	/*@todo MIGRATION_ISSUES temporary testing of the
	 openGL view using Save button */
		int temp = 0;
		wxApp* glApp = new MyApp();
		wxApp::SetInstance(glApp);
		wxEntryStart(temp, 0);
		wxTheApp->OnInit();
		wxTheApp->OnRun();
		wxTheApp->OnExit();
		wxEntryCleanup();
#endif
}


#if 0
void DrawProgView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
	INXString csRtaFilePath = (INXString)"localhost.Generic-Debugger:" + workDir + TRACEDIR + TRACE_CONFIG_FILE;
	bool bChangeView = FALSE;

	if (bActivate) {
		if (pProject->debug.debugMode != DBGSTOP) {
				if (pProject->debug.pView != this) {
					bChangeView = true;
				}
			// Only map lines once. Not every time view is activated.
			// Can't do this in OnInitialUpdate because view might not have been opened in debug mode
			if (!pDEP->dbgMappedFlag) {
				pDEP->dbgMappedFlag = true;
				pFrame->m_wndProjectBar.m_cProjTree.OpenDebugDEP(this);
			}
			else {
				pProject->debug.setView(this);
			}
		}

		// Only send monitors and restart trace if a new view is opened
		if (bChangeView) {
			// don't want EHS to send trace data for monitored lines that are in a previous view
			// because event lines may not be displayed
			pProject->debug.ClearAllMonitors();
			pProject->debug.sendAllMonitors();
			if (pProject->debug.m_RtaTraceSupport.getRtaTrace()) {
				pProject->debug.m_RtaTraceSupport.terminateRtaTraceProc();
				pProject->debug.m_RtaTraceSupport.createRtaConfigFile();
				ShellExecute(NULL, "open", RTA_TRACE_PATH, csRtaFilePath, NULL, SW_SHOWNORMAL);
			}
		}

		CChildFrame* viewFrame = (CChildFrame*)GetParentFrame();
		if (pProject->getDefineMonitors()) {
			viewFrame->m_StatusBar.GetStatusBarCtrl().SetText("Define Monitoring", 1, 0);
		}
		else {
			viewFrame->m_StatusBar.GetStatusBarCtrl().SetText("Line Editing", 1, 0);
		}

		// set the unique icon id for the current view
		SetIconID();
		//@todo - undo is initialised when view is first activated which has an unwanted consequence of clearing the cache when LAB moves to background and then foreground
		// REVISIT
		// Don't allow an undo when a view is first activated
		// This isn't ideal because it means if LAB moves to background and then foreground
		// undo is initialised. It is the only way I could think of initialising undo when changing the view
		initUndo();
	}

	// update target location from registry
	INXString csLocation = getLucidRegValue(_T(REG_TARGET_KEY),_T(REG_TARGET_LOCATION_VALUE),_T((INXString)DEFAULT_TARGET_LOCATION));
	((CLabLgbBaseApp *) wxGetApp())->csCurrentTarget = csLocation;
	// update target combo box with remote ip address
	INXString csRemoteIP = getLucidRegValue(_T(REG_TARGET_KEY),_T(REG_TARGET_REMOTE_IP_VALUE),_T((INXString)DEFAULT_TARGET_REMOTE_IP));
	pFrame->m_combo.DeleteString(TARGET_COMBO_INDEX_REMOTE);
	pFrame->m_combo.InsertString(TARGET_COMBO_INDEX_REMOTE,csRemoteIP);

	if (csLocation == REG_TARGET_LOCATION_DATA_APPSERVER) {
		pFrame->m_combo.SetCurSel(TARGET_COMBO_INDEX_APPSERVER);
	} else 	if (csLocation == REG_TARGET_LOCATION_DATA_REMOTE) {
		pFrame->m_combo.SetCurSel(TARGET_COMBO_INDEX_REMOTE);
	} else {
		pFrame->m_combo.SetCurSel(TARGET_COMBO_INDEX_LOCAL);
	}

	// update status bar with remote ip address
	pFrame->m_wndStatusBar.GetStatusBarCtrl().SetText(TARGET_DISPLAY_NAME_LOCAL, pFrame->m_wndStatusBar.CommandToIndex(ID_INDICATOR_CAPS),SBT_NOBORDERS);
	pFrame->m_wndStatusBar.GetStatusBarCtrl().SetText(csRemoteIP, pFrame->m_wndStatusBar.CommandToIndex(ID_INDICATOR_SCRL),SBT_NOBORDERS);


	CScrollView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}
#endif

void DrawProgView::OnLibrary()
{
	if(!pProject->pProjMData->getLock() ){

		INX_MessageBox( PMD_LOCK_FAILURE_MESSAGE );
	}else{

		lib = 1;
		SubsetEncapsulate();
		pProject->pProjMData->releaseLock();
	}
}

void DrawProgView::OnImportLib()
{

#if 0
///\todo
	// rArchive has been removed due to license issues
	//rArchive ra;
	CFileOperation fo;
	INXString m_File_Root = workDir + EXPORTDIR;
	wxDir finder;
	INXString fileName, compName;

	// Create a directory for the archived files to be written to
	fo.SetOverwriteMode(true); // set OverwriteMode flag
	fo.Delete(m_File_Root);
	CreateDirectory(m_File_Root, NULL);
	FileDialog box(1,"r","archive.r",OFN_FILEMUSTEXIST,"Archived Library Files (*.r)|*.r|");
	if (box.DoModal()==IDOK) {
		//extract archive
		/*
		if (!ra.Open(box.GetPathName())) {
			MessageBox(_T("Failed to open import library file."));
			return;
		}
		ra.SetRoot(m_File_Root);
		if (!ra.ResetPointer()) MessageBox(_T("Pointer reset failed."));
		while (ra.WriteNextFile() == true) {
		}
		*/

		// Copy the library components to the userdefined directory unless they already exist in which
		// case prompt the user
		int bWorking = finder.FindFile(workDir + EXPORTDIR + "*.prg");
		while (bWorking)
		{
			bWorking = finder.FindNextFile();
			fileName = finder.GetFileName();
			compName = fileName;
			compName.MakeReverse();
			compName.Delete(0,4);
			compName.MakeReverse();
			if (LibExist(fileName)) {
				if ((INX_MessageBox("The library component " + compName + " already exists. Do you want to overwrite it?",
					MB_YESNO))==IDYES) {
					fo.Copy((INXString)workDir + EXPORTDIR + fileName, (INXString)workDir + USERDEFDIR);
					fo.Copy((INXString)workDir + EXPORTDIR + compName, (INXString)workDir + USERDEFDIR);
					fo.Copy((INXString)workDir + EXPORTDIR + compName + ".idf.ini", (INXString)workDir + USERDEFDIR);
				}
			}
			else {
				fo.Copy((INXString)workDir + EXPORTDIR + fileName, (INXString)workDir + USERDEFDIR);
				fo.Copy((INXString)workDir + EXPORTDIR + compName, (INXString)workDir + USERDEFDIR);
				fo.Copy((INXString)workDir + EXPORTDIR + compName + ".idf.ini", (INXString)workDir + USERDEFDIR);
			}
		}
	}
#endif
}

void DrawProgView::OnExportLib()
{
#if 0
	RJMFileFind2 ff;
	INXObjArray<INXString> csa;
	INXString m_File_Root = workDir + EXPORTDIR;
	INXString csProjectDir;
	pProject->pProjMData->getProjectDir(csProjectDir);
	INXString m_Archive_File_Name = csProjectDir + EXPORTDIR + "archive.r";
	CExportDialog dialog;

	if (dialog.DoModal() == IDOK) {
		ff.FindFiles(true,m_File_Root,_T("*.*"),&csa);

		// Open archive
		// rArchive has been rmoved due to license issues
		/*
		rArchive ra;
		if (!ra.Open(m_Archive_File_Name,true)) {
			MessageBox(_T("Failed to open export library file."));
			return;
		};

		ra.SetRoot(m_File_Root);
		*/

		// Add files to archive
		/*
		INXString tmp;
		for (int c=0;c<csa.GetSize();c++) {
			tmp = csa.GetAt(c);
			tmp = tmp.Right(tmp.GetLength()-m_File_Root.GetLength());
			if (!ra.AddToArchive(tmp)) MessageBox(_T("Failed to add file " + tmp));
		};
		ra.Close();
		*/
		MessageBox(_T("Export library file created in " + csProjectDir + EXPORTDIR));
	}
#endif
}

void DrawProgView::OnCloseProject()
{
	// Save the proj file before losing the proj,
	// bcos otherwise/ afterwards, pProjMData==NULL and the prog crashes.
	if( !pProject->pProjMData->getLock() ) {
		INX_MessageBox(PMD_LOCK_FAILURE_MESSAGE);
	}else{
		pProject->pProjMData->readProjectFile();
		pProject->pProjMData->writeProjectFile();
		pProject->pProjMData->releaseLock();
	}

	//pDoc->OnCloseDocument();
}

void DrawProgView::OnUpdateCloseProject(CCmdUI* pCmdUI)
{
	INXString csProjectName;
	pProject->pProjMData->getProjectName(csProjectName);
	pCmdUI->Enable(csProjectName == pDEP->depFilename);
}

void DrawProgView::OnSelectAll()
{
	INXRect ElementBound;
	INXPOSITION pos;
	ConData* blob;

	pos = pDEP->condata->GetHeadPosition();
	if (pos) {
		blob = (ConData*) pDEP->condata->GetNext(pos);
		selectRect = blob->GetBoundingRectangle();
	}
	while (pos) {
		blob = (ConData*) pDEP->condata->GetNext(pos);
		//dc.LPtoDP(blob->rectangle);
		ElementBound = blob->GetBoundingRectangle();
		// Make coordinates of view extent the outer limits

		selectRect.UnionRect(selectRect, ElementBound);

	}
	selectRect.NormalizeRect();
	selectRect.InflateRect(10,10,10,10);
	if (pDEP->HighlightSelected(selectRect)) {
		copyFlag = true;
	}
	else {
		copyFlag = FALSE;
	}
	RedrawWindow();
}

void DrawProgView::OnLButtonDblClk(unsigned int nFlags, INXPoint _point)
{
	INXPoint point(_point.x, _point.y);
	// TODO: Add your message handler code here and/or call default
	selectRect.SetRectEmpty();
	//CClientDC aDC(this); // create device context
	//OnPrepareDC(&aDC); // adjust origin
	//aDC.DPtoLP((LPPOINT)point); // convert point to Logical
	//point.x = (point.x * 100)/scale;
	//point.y = (point.y * 100)/scale;

	//DrawProg &pApp = wxGetApp();

//	if(!pProject->pProjMData->getLock()){

//		INX_MessageBox( PMD_LOCK_FAILURE_MESSAGE );

///	}else{

	//	pProject->pProjMData->readProjectFile();

		selectedControl = pDEP->Incontrol(point);
		if (selectedControl) {
			ConData* blob;
			blob = (ConData*) pDEP->condata->GetAt(selectedControl);
			pDEP->setFBHighlight(selectedControl);
			if (blob->m_FbType == "") {
				OnProperties();
			}
			else {
				OnCreateInstance();
			}
		}

//		pProject->pProjMData->writeProjectFile();
//		pProject->pProjMData->releaseLock();

//	} // if(!m_ProjectMetaData.getLock())

	//CScrollView::OnLButtonDblClk(nFlags, point);
}

void DrawProgView::OnUpdateGroupSetup(CCmdUI* pCmdUI)
{
	// disable group setup
	//pCmdUI->Enable(FALSE);
}

void DrawProgView::OnImportDataFile()
{
/* dk - Data Items removed from IAB
	ExtDataFile dataFile;
	bool bExists;

	if (!pProject->pProjMData->showAddFileDialog(dataFile, bExists)) {
		// showAddfiledialog saves the pmd file!
		if (!bExists) {
			pFrame->m_wndProjectBar.m_cProjTree.AddDataFile(dataFile, pDEP->hItem);
		}
	}
*/
}

void DrawProgView::OnEditProjectDesc()
{
#if 0
	ProjectDescriptionDialog projDlg(pProject->pProjMData);

	if (projDlg.DoModal()==IDOK) {
		pProject->pProjMData->writeProjectDescriptionFile();
		pFrame->m_wndProjectBar.m_cProjTree.UpdateProjectDescrptionOnTree(pProject, pDEP);
	}
#endif
}

void DrawProgView::OnSaveProjectAs()
{
#if 0
	// We need to replace the getNextDoc stuff in here wxwidgets
	if( !pProject->pProjMData->getLock() ) {

		INX_MessageBox(PMD_LOCK_FAILURE_MESSAGE);

	}else{

		readProjectFile();
		pProject->pProjMData->releaseLock();

		INXString csOldProjectDir, csOldProjectName;
		INXString csNewProjectDir, csNewProjectName, csProjectPathName;
		POSITION pos;
		CDrawProgApp *pApp = ( CDrawProgApp *) wxGetApp();

		pProject->pProjMData->getProjectDir(csOldProjectDir);
		pProject->pProjMData->getProjectName(csOldProjectName);

		if (!pProject->pProjMData->showSaveProjectAsDialog()) {

			pProject->pProjMData->getProjectDir(csNewProjectDir);
			pProject->pProjMData->getProjectName(csNewProjectName);

			pProject->pProjMData->getLock();
			pProject->pProjMData->writeProjectFile();

			pos = ((CDrawProgApp*)wxGetApp())->pDocTemplate->GetFirstDocPosition();
			// The user could do a save as from a sub view therfore:
			// find the top doc object in the project as it needs its name changing
			while (pos) {
				CDrawProgDoc* pDocmnt = (CDrawProgDoc*) ((CDrawProgApp*)wxGetApp())->pDocTemplate->GetNextDoc(pos);
				if (pDocmnt->pDEP->depFilename == csOldProjectName) {
					// Rename project in project window
					pFrame->m_wndProjectBar.m_cProjTree.SaveProjectAs(csNewProjectName, pDocmnt->pDEP->hItem);
					// Update DEP
					pDocmnt->pDEP->depFilename = csNewProjectName;
					pDocmnt->pDEP->projectDir = csNewProjectDir;
					// update title with new name
					pDocmnt->SetTitle(csNewProjectName);
					pDocmnt->SetPathName(csNewProjectDir + DEPDIR + csNewProjectName + ".prg");
					pProject->pProjMData->getFullPathProjectFile(csProjectPathName);
					pApp->addProjectToMRUList(csProjectPathName);
					pFrame->setFrameCaption();
				}
				// Ensure that all open docs have their pathnames updated.
				// This prevents a new doc being opened.
				else if (pDocmnt->pProject == this->pProject) {
					pDocmnt->SetPathName(csNewProjectDir + DEPDIR + pFrame->m_wndProjectBar.m_cProjTree.GetDEPPath(pDocmnt->pDEP->hItem) + pDocmnt->pDEP->depFilename + ".prg");
				}

			}
			pProject->pProjMData->releaseLock();
		}
	}
#endif
}

bool DrawProgView::OnMouseWheel(unsigned int nFlags, short zDelta, INXPoint pt)
{
	// ScrollPosition is used by NearBottomRightBoundary check
	INXSize topleft = {0,0};// todo GetScrollPosition( );
	cs.SetScrollPosition(topleft);

	return true; //CScrollView::OnMouseWheel(nFlags, zDelta, pt);
}

bool DrawProgView::OnScroll(unsigned int nScrollCode, unsigned int nPos, bool bDoScroll)
{

	// ScrollPosition is used by NearBottomRightBoundary check
	INXSize topleft = {0,0};//todo GetScrollPosition( );
	cs.SetScrollPosition(topleft);
	//return CScrollView::OnScroll(nScrollCode, nPos, bDoScroll);
	return true;
}

void DrawProgView::OnSize(unsigned int nType, int cx, int cy)
{
	//CScrollView::OnSize(nType, cx, cy);


	INXPoint max;
	max.x = cx;
	max.y = cy;
	cs.SetMaxBoundary( max);
}

void DrawProgView::OnEditDelete()
{
#if 0
	ConData *icondata;
	INXPOSITION pos, delPos;
	bool undo = true;

	if( !pProject->pProjMData->getLock() ) {

		INX_MessageBox(PMD_LOCK_FAILURE_MESSAGE);

	}else{

		pProject->pProjMData->readProjectFile();
		// delete every icon in the selected box
		pos = pDEP->condata->GetHeadPosition();
		while (pos) {
			delPos = pos;
			icondata = (ConData *) (pDEP->condata->GetNext(pos));
			//if (selectRect.PtInRect(icondata->GetIconCentre())) {
			if (icondata->selected) {
				if (icondata->m_FbName.Find("XINPUT") != -1 || icondata->m_FbName.Find("XOUTPUT") != -1 || icondata->m_FbName == "XSTART" ||
					icondata->m_FbName == "XFINISH") {
					undo = FALSE;
				}
				pFrame->m_wndProjectBar.m_cProjTree.DeleteIcon(delPos, pProject, pDEP, 1);
				if (!undo) {
					//@todo - currently can't undo an edit-delete if the selection contains a subsystem
					initUndo();
				}
			}
		}
		selectRect.BottomRight() = selectRect.TopLeft();
		RedrawWindow();
		if (undo) {
			SaveUndo();
		}
		pProject->SaveProject();
		pProject->pProjMData->writeProjectFile();
		pProject->pProjMData->releaseLock();
	}
#endif

}

void DrawProgView::OnTransferOptions()
{
#if 0
	LucidTcpipClient tcpipClient;
	tcpipClient.ConfigDlg();

	// set the 'all has been transferred already' flag to false, for this new target.
	pProject->m_bTransferAllHasOccurred = false;
	// update the ip address for the target
	int selInd = pFrame->m_combo.GetCurSel();
	INXString csRemoteIP = getLucidRegValue(_T(REG_TARGET_KEY),_T(REG_TARGET_REMOTE_IP_VALUE),_T((INXString)DEFAULT_TARGET_REMOTE_IP));
	pFrame->m_combo.DeleteString(TARGET_COMBO_INDEX_REMOTE);
	pFrame->m_combo.InsertString(TARGET_COMBO_INDEX_REMOTE,csRemoteIP);
	pFrame->m_combo.SetCurSel(selInd);
	// update status bar with remote ip address
	pFrame->m_wndStatusBar.GetStatusBarCtrl().SetText(csRemoteIP, pFrame->m_wndStatusBar.CommandToIndex(ID_INDICATOR_SCRL),SBT_NOBORDERS);
#endif
}

void DrawProgView::OnZoomIn()
{
	scale = scale+ZOOM_DELTA;
	RedrawZoom();
}

void DrawProgView::RedrawZoom()
{
	char szScale[MAX_ZOOM_CHAR] = {'\0'};
#if 0
	// Get the frame window for this view
	CChildFrame* viewFrame = (CChildFrame*)GetParentFrame();
	// Write the zoom value to the status bar
	_itoa_s(scale, szScale, 10);
	viewFrame->m_StatusBar.GetStatusBarCtrl().SetText("Zoom: " + (INXString)szScale + "%", 0, 0);
	// Adjust scrolling to the new scale
		ResetScrollSizes();
#endif

	RedrawWindow();
}

void DrawProgView::OnZoomOut()
{
	scale = scale-ZOOM_DELTA;
	RedrawZoom();
}

void DrawProgView::OnUpdateZoomIn(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(scale<MAX_ZOOM);
}

void DrawProgView::OnUpdateZoomOut(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(scale>MIN_ZOOM);
}

/*
void DrawProgView::OnTransferAll()
{
	CDrawProgApp *pApp = ( CDrawProgApp *) wxGetApp();
	INXString csProjectDir;

	// Write out SODL

// The following line overwrites the contents of the project as seen by LGB.
// This is a problem, as often around this point the user has added some image files to project.
// There doesn't seem to be any particlar need to write the project right now (does there)
// ( MSR 19Sept07 ).
	//pProject->SaveProject();

	pProject->pProjMData->getProjectDir(csProjectDir);
	// Transfer Manager can be called anywhere in the application hierarchy
	// Need to save hierarchy names starting at the top level of the project
	pFrame->m_wndProjectBar.m_cProjTree.SaveHierName(pProject->pDEP[0]->hItem, csProjectDir, pProject);
	pProject->WriteSODL(csProjectDir + SODLDIR + SODLFILENAME);

	// PD says that there shouldn't be 2 places where u find sodl.
	//pProject->WriteSODL(csProjectDir + SODLDIR + SODLFILENAME);

	pApp->setProjectMetaData(pProject->pProjMData);
	//pApp->setProject(pProject);
	pApp->transferToTarget( changedOnly );
}
*/
/*

void DrawProgView::OnTransferManager()
{
	CDrawProgApp *pApp = ( CDrawProgApp *) wxGetApp();
	INXString csProjectDir;

	// Write out SODL

// The following line overwrites the contents of the project as seen by LGB.
// This is a problem, as often around this point the user has added some image files to project.
// There doesn't seem to be any particlar need to write the project right now (does there)
// ( MSR 19Sept07 ).
	//pProject->SaveProject();

	pProject->pProjMData->getProjectDir(csProjectDir);
	// Transfer Manager can be called anywhere in the application hierarchy
	// Need to save hierarchy names starting at the top level of the project
	pFrame->m_wndProjectBar.m_cProjTree.SaveHierName(pProject->pDEP[0]->hItem, csProjectDir, pProject);
	pProject->WriteSODL(csProjectDir + SODLDIR + SODLFILENAME);

	// PD says that there shouldn't be 2 places where u find sodl.
	//pProject->WriteSODL(csProjectDir + SODLDIR + SODLFILENAME);

	pApp->c_pTransferToTargetDialog->setProjectMetaData(pProject->pProjMData);
	pApp->c_pTransferToTargetDialog->setProject(pProject);
	pApp->c_pTransferToTargetDialog->ShowWindow(SW_SHOWNORMAL);
}

void DrawProgView::OnLaunchTransfer()
{
	CDrawProgApp *pApp = ( CDrawProgApp *) wxGetApp();
	INXString csProjectDir;

// Write out SODL
// The following line overwrites the contents of the project as seen by LGB.
// This is a problem, as often around this point the user has added some image files to project.
// There doesn't seem to be any particlar need to write the project right now (does there)
// ( MSR 19Sept07 ).
//pProject->SaveProject();

	pProject->pProjMData->getProjectDir(csProjectDir);
	// Launch Transfer can be invoked anywhere in the application hierarchy
	// Need to save hierarchy names starting at the top level of the project
	pFrame->m_wndProjectBar.m_cProjTree.SaveHierName(pProject->pDEP[0]->hItem, csProjectDir, pProject);
	pProject->WriteSODL(csProjectDir + SODLDIR + SODLFILENAME);

	pApp->c_pTransferToTargetDialog->setProjectMetaData( pProject->pProjMData );
	pApp->c_pTransferToTargetDialog->setProject(pProject);
	pApp->c_pTransferToTargetDialog->ShowWindow(SW_SHOWNORMAL);
	pApp->c_pTransferToTargetDialog->OnBnClickedTransfer();

}
*/
void DrawProgView::readProjectFile()
{
	INXString csProjectPathName;

	pProject->pProjMData->getFullPathProjectFile(csProjectPathName);
	pProject->pProjMData->readProjectFile((INXString)csProjectPathName);
}

// disable import and export library functions, because decompressing is not working for import library
void DrawProgView::OnUpdateImportLib(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(FALSE);
}

void DrawProgView::OnUpdateExportLib(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(FALSE);
}

void DrawProgView::OnUpdateTransferManager(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(pProject->debug.debugMode == DBGSTOP);
}

void DrawProgView::OnUpdateLaunchTransfer(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(pProject->debug.debugMode == DBGSTOP);
}

void DrawProgView::OnViewRefresh()
{
	INXRect clientRect;
#if 0
	this->GetClientRect(clientRect);
	INXPoint point = pDEP->getInitScrollPos(clientRect);
	this->ScrollToPosition(point);
	cs.SetScrollPosition(point);
#endif
}

void DrawProgView::OnUpdateViewRefresh(CCmdUI *pCmdUI)
{
//	TRACE(_T("OnUpdateViewRefresh\n"));
	onlyDrawAnimatedStuff = false; // turn this flag off to ensure that normal calls to paint repaint whole window

	pCmdUI->Enable(scale == 100);
}

void DrawProgView::setLftBtnDownState(const int &val)
{
	m_iLftBtnDownState = val;
}
#if 0
DROPEFFECT DrawProgView::OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, INXPoint point)
{
	//INX_MessageBox("DragOver");

	return CScrollView::OnDragOver(pDataObject, dwKeyState, point);
}
#endif
#if 0
bool DrawProgView::OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, INXPoint point)
{
	//INX_MessageBox("Drop");

	return CScrollView::OnDrop(pDataObject, dropEffect, point);
}
#endif
void DrawProgView::OnRenamePort()
{
	///\todo pFrame->m_wndProjectBar.m_cProjTree.RenameBlockPort(selectedControl, selectedPort, selectedPortType, pProject, pDEP);
	pProject->SaveProjectDep();
	//@todo - currently can't undo a rename port of subsystem
	// Can't undo rename port currently, because it requires udating 2 deps (.prg)
	initUndo();
	RedrawWindow();
}

void DrawProgView::OnRenameXport()
{
	///\todo pFrame->m_wndProjectBar.m_cProjTree.RenameXport(selectedControl, pProject, pDEP);
	pProject->SaveProjectDep();
	//@todo - currently can't undo a rename port of subsystem
	// Can't undo rename xport currently, because it requires udating 2 deps (.prg)
	initUndo();
	RedrawWindow();
}

void DrawProgView::OnAddToLibrary()
{
#if 0
	Encapsulation subsystem;
	CMenuNameDialog dlg;
	INXString csMenuName;
	ConData* blob = (ConData*) pDEP->condata->GetAt(selectedControl);

	if (!blob->m_iUserDefined) {
		INX_MessageBox("Can only add user defined blocks to a library.");
		return;
	}
	else if (!subsystem.IsLibComponentUnique(blob->className)) {
		if (INX_MessageBox("A library component with this name already exists. Do you want to replace it?",MB_YESNO|MB_ICONEXCLAMATION)==IDNO) {
			return;
		}
	}

	// Get menu name
	if (dlg.DoModal()==IDOK) {
		csMenuName = dlg.getMenuName();
	}
	else {
		return;
	}

	pDEP->AddToLibrary(selectedControl, csMenuName);
	// Update the function block chooser
	pFrame->updateFunctionBlockBar();
#endif
}

void DrawProgView::OnUpdateTransferChanged(CCmdUI *pCmdUI)
{
	///\todo  pCmdUI->Enable(wxGetApp()).csCurrentTarget != REG_TARGET_LOCATION_DATA_APPSERVER) && pProject->m_bTransferAllHasOccurred && (pProject->debug.debugMode == DBGSTOP));
}

void DrawProgView::OnUpdateAddToGroup(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(false);
}

/*
void DrawProgView::OnLabTransferAll()
{
	CDrawProgApp *pApp = ( CDrawProgApp *) wxGetApp();
	INXString csProjectDir;

	pProject->pProjMData->getProjectDir(csProjectDir);
	// Transfer Manager can be called anywhere in the application hierarchy
	// Need to save hierarchy names starting at the top level of the project
	pFrame->m_wndProjectBar.m_cProjTree.SaveHierName(pProject->pDEP[0]->hItem, csProjectDir, pProject);
	pProject->WriteSODL(csProjectDir + SODLDIR + SODLFILENAME);

	const bool bUpdatedOnly = false;
	pApp->transferToTarget( pProject->pProjMData, bUpdatedOnly );

}

void DrawProgView::OnLabTransferChanged()
{
	pProject->pProjMData->getProjectDir(csProjectDir);

	// Transfer Manager can be called anywhere in the application hierarchy
	// Need to save hierarchy names starting at the top level of the project
	pFrame->m_wndProjectBar.m_cProjTree.SaveHierName(
			pProject->pDEP[0]->hItem, csProjectDir, pProject);

	pProject->WriteSODL(csProjectDir + SODLDIR + SODLFILENAME);

	const bool bUpdatedOnly = true;
	pApp->transferToTarget( pProject->pProjMData, bUpdatedOnly );
}

*/

void DrawProgView::OnLabTransferAll()
{
	///\todo transferToTarget( false );
}


void DrawProgView::OnLabTransferChanged()
{
	///\todo transferToTarget( true );
}



/* CALLBACK FUNCTION that writes to our data buffer
 *
 * This leaves the string null terminates at each chunk of data
 *
 */
size_t AppUpload_write_data(void *ptr, size_t size, size_t nmemb, void *userdata) {
#if 0
	size_t amount = size * nmemb;
	char * buffer = (char *)userdata;

	strncpy(buffer, (char *)ptr,amount>CURL_WRITE_BUFFER_SIZE?CURL_WRITE_BUFFER_SIZE:amount );
	buffer[amount]='\0'; // terminate if pre-gunged
	return amount;
#else
	return 0;
#endif
}

#if 0
void DrawProgView::uploadAppToServer()
{
	INXString tarFilePath;
	pProject->pProjMData->getProjectDir(tarFilePath);
	tarFilePath += APP_TAR_FILE;

	bool success = false;
	success = appUploader_ExportTransferables();
	if (!success) return;
	//@todo log progress
	success = appUploader_TarExportFiles();
	if (!success) return;
	//@todo log progress

	// 3. upload the app tar file
	// find the app tar file in the main project dir
	CFileOperation fo;
	int foErr = fo.CheckPath( tarFilePath);
	if (foErr != PATH_IS_FILE) {
		INX_MessageBox("App tar file not found:" + tarFilePath);
	} else {
		// perform file upload

		//@todo - replace with the nonblocking version and a progress bar or callback checked from a separate thread
		INX_MessageBox("Uploading commencing... Click OK to continue");

		CURL *curl;
		CURLcode res;

		INXString message;
		long lResponseCode;
//		char * pCharURLEncodedUserName;
//		char * pCharUserName;
		INXString csUserName = getLucidRegValue(_T(REG_TARGET_KEY),_T(REG_TARGET_APPSERVER_USERNAME_VALUE),_T((INXString)DEFAULT_TARGET_APPSERVER_USERNAME));
//		pCharUserName = (char *) (LPCTSTR) csUserName;
		INXString csURL = getLucidRegValue(_T(REG_TARGET_KEY),_T(REG_TARGET_APPSERVER_URL_VALUE),_T((INXString)DEFAULT_TARGET_APPSERVER_URL));
		INXString csPassword = getLucidRegValue(_T(REG_TARGET_KEY),_T(REG_TARGET_APPSERVER_PASSWORD_VALUE),_T((INXString)DEFAULT_TARGET_APPSERVER_PASSWORD));

		struct curl_httppost *formpost=NULL;
		struct curl_httppost *lastptr=NULL;
		struct curl_slist *headerlist=NULL;
		static const char buf[] = "Expect:";

		curl = curl_easy_init();
		// initalize custom header list (stating that Expect: 100-continue is not wanted
		headerlist = curl_slist_append(headerlist, buf);

		if(curl) {
//don't need this, url encoded in form?			pCharURLEncodedUserName = curl_easy_escape(curl, pCharUserName, 0);

			/* Fill in the file upload field. This makes libcurl load data from
				 the given file name when curl_easy_perform() is called. */
			curl_formadd(&formpost,
				   &lastptr,
				   CURLFORM_COPYNAME, "file",
				   CURLFORM_FILE, tarFilePath,
				   CURLFORM_END);

			/* Fill in the username field */
			curl_formadd(&formpost,
				   &lastptr,
				   CURLFORM_COPYNAME, "username",
				   CURLFORM_COPYCONTENTS, csUserName,
				   CURLFORM_END);

			/* Fill in the user password field */
			curl_formadd(&formpost,
				   &lastptr,
				   CURLFORM_COPYNAME, "password",
				   CURLFORM_COPYCONTENTS, csPassword,
				   CURLFORM_END);

			/* what URL that receives this POST */
			curl_easy_setopt(curl, CURLOPT_URL, csURL);
			/* disable 100-continue header if explicitly requested */
			curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);
			curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);

			res = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, AppUpload_write_data);
			if (res != CURLE_OK) {
				INX_MessageBox("libcurl failed to register callback");
			} else {
				char * buffer = new char[CURL_WRITE_BUFFER_SIZE];
				buffer[0] = '\0';
				res = curl_easy_setopt(curl, CURLOPT_WRITEDATA,(void*) buffer); //We'll write XML into a buffer directly
				if (res != CURLE_OK) {
					INX_MessageBox("libcurl to register writedata");
				} else {

					res = curl_easy_perform(curl);
					if (res == CURLE_OK) {
						curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &lResponseCode);
						//@todo - check response code from server

						// check buffer to see if any error xml
						if (buffer != NULL) {
							if (buffer[0] == '\0') {
								INX_MessageBox("App successfully uploaded");
							} else {
								message = buffer;
								//@todo - extract error message from xml
								INX_MessageBox("App uploading failed ...\n" + message);
							}
						} else {
							INX_MessageBox("App successfully uploaded");
						}
					} else if (res == CURLE_COULDNT_RESOLVE_HOST) {
						INX_MessageBox("App failed to upload, couldn't resolve host.\nCheck the URL of the App Server");
					} else {
						INX_MessageBox("App failed to upload, libcurl error code: " + res);
					}
				}
				free(buffer);
			}

			/* then cleanup the formpost chain */
			curl_formfree(formpost);

			/* free slist */
			curl_slist_free_all (headerlist);

			/* always cleanup */
			curl_easy_cleanup(curl);
		}
	}

}
#endif


#if 0
void DrawProgView::transferToTarget(const bool &bUpdatedOnly )
{
	CLabLgbBaseApp *pApp = ( CLabLgbBaseApp * ) wxGetApp();

	// first check which target - if it is App server upload app via http post form, if it is EHS local or remote se tcpip
	INXString csLocation = getLucidRegValue(_T(REG_TARGET_KEY),_T(REG_TARGET_LOCATION_VALUE),_T((INXString)DEFAULT_TARGET_LOCATION));

	if (csLocation == REG_TARGET_LOCATION_DATA_APPSERVER) {
		uploadAppToServer();
	}
	// start EHS - if starts successfully or is already running, send SODL (which also reloads app in EHS)
	else if (pApp->startEHS(true)) {

		// read project file first to avoid overwriting changes made by LGB
		pApp->c_pTgtTransProgressDlog->ShowWindow(SW_NORMAL);
		INXString *pcsDum = new INXString("Writing SODL ...");
		pApp->c_pTgtTransProgressDlog->SendMessage( UWM_SET_OVERALL_PROMPT, 0, (LPARAM)pcsDum  );

		Sleep(500);

		pApp->setProjMetaData( pProject->pProjMData );
		pApp->setProject(pProject);

		INXString csProjectDir;
		pProject->pProjMData->getProjectDir(csProjectDir);

		// Transfer Manager can be called anywhere in the application hierarchy
		// Need to save hierarchy names starting at the top level of the project
		pFrame->m_wndProjectBar.m_cProjTree.SaveHierName(
				pProject->pDEP[0]->hItem, csProjectDir, pProject);

		pProject->WriteSODL(csProjectDir + SODLDIR + SODLFILENAME);



		pcsDum = new INXString("Tabulating Transferrables ...");
		pApp->c_pTgtTransProgressDlog->SendMessage( UWM_SET_OVERALL_PROMPT, 0, (LPARAM)pcsDum  );

		if( !pProject->pProjMData->getLock() ){

			INX_MessageBox( PMD_LOCK_FAILURE_MESSAGE );

		}else{

			pApp->transferToTarget( bUpdatedOnly );
			//pProject->m_bTransferAllHasOccurred = pProject->m_bTransferAllHasOccurred || (!bUpdatedOnly && pApp->getTransferSuccess());

			// Write-out the latest transfer time.
			pProject->pProjMData->updateTransferTime();
			pProject->pProjMData->writeProjectFile();

			pProject->pProjMData->releaseLock();

		}
	}
}
#endif


void DrawProgView::OnDefineMonitors()
{
#if 0
	// Get the frame window for this view
	CChildFrame* viewFrame = (CChildFrame*)GetParentFrame();
	if (pProject->getDefineMonitors()) {
		pProject->setDefineMonitors(FALSE);
		viewFrame->m_StatusBar.GetStatusBarCtrl().SetText("Line Editing", 1, 0);
	}
	else {
		pProject->setDefineMonitors(true);
		viewFrame->m_StatusBar.GetStatusBarCtrl().SetText("Define Monitoring", 1, 0);
	}
#endif
	RedrawWindow();
}

void DrawProgView::OnSelectAllMonitors()
{
	pDEP->setAllMonitors(true);
	SaveUndo();					//must come first.
	pProject->SaveProjectDep();
	RedrawWindow();
}

void DrawProgView::OnClearAllMonitors()
{
	pDEP->setAllMonitors(FALSE);
	SaveUndo();					//must come first.
	pProject->SaveProjectDep();
	RedrawWindow();
}

void DrawProgView::OnUpdateSelectAllMonitors(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(pProject->getDefineMonitors());
}

void DrawProgView::OnUpdateClearAllMonitors(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(pProject->getDefineMonitors());
}

void DrawProgView::OnUpdateDefineMonitors(CCmdUI *pCmdUI)
{
	if (pProject->getDefineMonitors()) {
		pCmdUI->SetCheck(1);
	}
	else {
		pCmdUI->SetCheck(0);
	}
	pCmdUI->Enable(pProject->debug.debugMode == DBGSTOP);
}

void DrawProgView::OnTrace()
{
#if 0
	// ///\todo depricated
	INXString csRtaFilePath = (INXString)"localhost.Generic-Debugger:" + workDir + TRACEDIR + TRACE_CONFIG_FILE;
	CFileOperation fo;

	// Check that RTA-Trace is installed
	if (!fo.CheckPath(RTA_TRACE_PATH)) {
		INX_MessageBox("RTA Trace is not installed");
		return;
	}
	if (!pProject->debug.m_RtaTraceSupport.getRtaTrace()) {
		if (pProject->debug.m_RtaTraceSupport.createRtaConfigFile()) {
			// Launch RTA-TRACE
			ShellExecute(NULL, "open", RTA_TRACE_PATH, csRtaFilePath, NULL, SW_SHOWNORMAL);
			pProject->debug.m_RtaTraceSupport.setRtaTrace(true);
			startTraceTimer();
		}
	}
	else {
		pProject->debug.m_RtaTraceSupport.terminateRtaTraceProc();
		stopTraceTimer();
		pProject->debug.m_RtaTraceSupport.setRtaTrace(FALSE);
	}
#endif
}

void DrawProgView::OnUpdateTrace(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(pProject->debug.debugMode != DBGSTOP);
	///\todo pCmdUI->SetCheck(pProject->debug.m_RtaTraceSupport.getRtaTrace());
}

void DrawProgView::OnUpdateTransferAll(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(pProject->debug.debugMode == DBGSTOP);
}


/* Depricated */
void DrawProgView::OnNationalLanguageSupport()
{
	//if (pProject->RunNlsExec()) {
	//	pProject->OpenNlsFile();
	//}
}

void DrawProgView::OnImportResourceFile()
{
	ExtResourceFile xResourceFile;
	bool bExists;

	if (!pProject->pProjMData->showAddResourceDialog(xResourceFile, bExists)) {
		if (!bExists) {
			///\todo pFrame->m_wndProjectBar.m_cProjTree.AddResourceFile(xResourceFile, pDEP->hItem);
		}
	}
}


// Called when an icon is selected to be moved it is drawn as a rectangle outline
void DrawProgView::SetToMovingRectangle(INXPOSITION selected) {
		ConData *icondata;

		icondata = ((ConData *) pDEP->condata->GetAt(selected));
		RectangleSite.CopyRect(icondata->GetBoundingRectangle());
		// Make sure bounding rectangle is snapped to grid before moving
		//RectangleSite.SetRect(pDEP->SnapToGrid(RectangleSite.TopLeft()),pDEP->SnapToGrid(RectangleSite.BottomRight()));
		// Adjust size of RectangleSite according to scale
		/*double deltaHeight = ((RectangleSite.Height()/2)*(100-scale))/100;
		double deltaWidth = ((RectangleSite.Width()/2)*(100-scale))/100;
		RectangleSite.DeflateRect((int)deltaWidth, (int)deltaHeight);*/
		//RectangleSite.OffsetRect(-RectangleSite.TopLeft()); //make into 0 offset box
}

INXRect DrawProgView::GetViewExtent() {
	INXRect ViewExtent(0,0,1,1); // Initial view extent
	INXRect ElementBound(0,0,0,0); // Space for element bounding rectangle
	INXPOSITION pos;
	ConData* blob;

	//CClientDC dc(this);
	//dc.SetMapMode(MM_LOENGLISH);
	pos = pDEP->condata->GetHeadPosition();
	while (pos) {
		blob = (ConData*) pDEP->condata->GetNext(pos);
		//dc.LPtoDP(blob->rectangle);
		ElementBound = blob->GetBoundingRectangle();
		// Make coordinates of view extent the outer limits

		ViewExtent.UnionRect(ViewExtent, ElementBound);

	}
	ViewExtent.NormalizeRect();
	//dc.SetMapMode(MM_TEXT);
	//ReleaseDC(&dc);
	return ViewExtent;
}



// save DEP and project file so can perform an undo
// project file needs to be undone since it contains a list of all the gui widgets.

void DrawProgView::SaveUndo() {
#if 0
	char szUndoFileNum[MAX_UNDO_FILE_NUM];

	undoFlag = true;
	redoFlag = FALSE;

	_itoa_s(iUndoFileNum, szUndoFileNum, 10);

	pDEP->SaveProg(workDir + TEMPDIR + "undo" + szUndoFileNum + ".prg");
	pProject->pProjMData->writeProjectFileAs(workDir + TEMPDIR + "lpj_undo" + szUndoFileNum);

	if (iUndoFileNum >= (int)pow(10.0, MAX_UNDO_FILE_NUM-1)-1) {
		iUndoFileNum = 0;
		wrapFlag = true;
	}
	else {
		iUndoFileNum++;
	}
	// Need to move the file num at which the undo flag becomes false
	// When file num wraps around need to save the filenum at which the undo function
	// becomes disabled should the user do enough undos
	if (wrapFlag && iUndoFileNum==iUndoFlagNum) {
		if (iUndoFlagNum >= (int)pow(10.0, MAX_UNDO_FILE_NUM-1)-1) {
			iUndoFlagNum = 0;
		}
		else {
			iUndoFlagNum++;
		}
	}
	maxUndoFileNum = iUndoFileNum;
#endif
}

// initialise undo/redo function
void DrawProgView::initUndo() {
#if 0
	undoFlag = FALSE;
	redoFlag = FALSE;
	wrapFlag = FALSE;
	iUndoFileNum = 0;
	maxUndoFileNum = 0;
	iUndoFlagNum = 1;

	// remove all the undo files
	int filenum = 1;
	char szUndoFileNum[MAX_UNDO_FILE_NUM];
	_itoa_s(filenum, szUndoFileNum, 10);
	while (remove(workDir + TEMPDIR + "undo" + szUndoFileNum + ".prg") != -1) {
		remove(workDir + TEMPDIR + "lpj_undo" + szUndoFileNum);
		if (filenum >= (int)pow(10.0, MAX_UNDO_FILE_NUM-1)-1) {
			filenum = 0;
		}
		else {
			filenum++;
		}
		_itoa_s(filenum, szUndoFileNum, 10);
	}

	// save the initial DEP
	SaveUndo();
	undoFlag = FALSE;
#endif
}




#if 0 // this is the windows Ole version - moved relavant bits into DrawProgView::processComponentDrop() call
/* THis is the logic for doing a drop from "InterfaceDropTarget.cpp /
 */
BOOL CInterfaceDropTarget::OnDrop(
								  CWnd* pWnd,
								  COleDataObject* pDataObject,
								  DROPEFFECT dropEffect,
								  INXPoint point )
{

	DrawProgView *pView = (DrawProgView *) pWnd;
	assert(  pWnd->IsKindOf( RUNTIME_CLASS(DrawProgView) ) );
	ConData *droppee, *draggee;
	INXPOSITION droppeePos, draggeePos;
	INXPoint droppeePoint, draggeePoint;
	bool bContinue = true;
	set<INXString> sWidgetGroupSet;
	vector<pair<INXString, INXString> > vWidgetGroupPairVec;
	INXString csWidgetGroupName;

	if( !pView->pProject->pProjMData->getLock() ){

		INX_MessageBox( PMD_LOCK_FAILURE_MESSAGE );

	} else {

		pView->pProject->pProjMData->readProjectFile();

		// this time we have to check every time what' our format
		// because in this sample the format may change dynamically
		unsigned int DragDropFormat;

		INXString format = wxGetApp()->GetProfileString("DragDrop", "Clipformat", "Common");
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
				pView->processComponentDrop(SnapToGrid(point), m_FbName, m_FbType );

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
						pView->pFrame->m_wndProjectBar.m_cProjTree.DeleteIcon(droppeePos, pView->pProject, pView->pDEP, 0);
					}
					else {
						draggeePos = pView->pDEP->getPosFromIcon(draggee);
						pView->pFrame->m_wndProjectBar.m_cProjTree.DeleteIcon(draggeePos, pView->pProject, pView->pDEP, 0);
					}
				}

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

					pView->pProject->SaveProject();
					pView->pProject->pProjMData->writeProjectFile();
					pView->RedrawWindow();
				}

			}

			//return true;
		}

		pView->pProject->pProjMData->releaseLock();
		return COleDropTarget::OnDrop(pWnd, pDataObject, dropEffect, point);
	}
}
#endif



