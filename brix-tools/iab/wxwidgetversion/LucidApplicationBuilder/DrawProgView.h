
#ifndef DRAWPROGVIEW_H_
#define DRAWPROGVIEW_H_

#include <wx/wx.h>
#include "wx/glcanvas.h"
#include <GL/gl.h>
#include "DEP.h"

/* Rest of iAB Views */
//#include "DrawProgDoc.h"
#include "Encapsulate.h"
//#include "colourKey.h"
//#include "FTP.h"
#include "TypeConversion.h"
#include "CanvasSupport.h"
//#include "EditList.h"
//#include "DbgMsgDialog.h"

/* Refactoring functions - @todo should be elsewhere */
//#include "InterfaceDropTarget.h"
//#include "FunctionBlockSubstitution.h"

#include "../common/EHSInitParams.h"
#include "../common/LabLgbBaseApp.h"
#include "Porting_Classes/INXString.h"

class CCmdUI {
	 /// \todo temporary compile hack
public:
	void Enable(bool a) {

	}
	void SetCheck(bool a) {

		}
};

class DrawProgView: public wxGLCanvas{


public:
	DrawProgView(wxWindow *parent , const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize, long style = 0);
public:

	/* Rendering Functions */
	~DrawProgView(void);
	void OnPaint(wxPaintEvent& event);
    void OnSize(wxSizeEvent& event);
    void OnEraseBackground(wxEraseEvent& event);
    void Render();
    void RedrawWindow();
    void InitGL();

    /* Logical Functions - @todo should be refactored to entry points only and no business logic */

    /* Attributes */



public:
	DEP* pDEP;
private:


public:
	void init();
	void initUndo();
	void SetToMovingRectangle(INXPOSITION selected);
	void RemoveHighlight();
	void StartLine(INXPOSITION selectedIcon, int PortSelected, int portType );
	void SaveUndo();
	void ViewInstance(INXPOSITION selectedIcon);
	//ConData* SelectIcon(INXPoint point);  // selects a new icon
	INXRect GetViewExtent();
	void ResetScrollSizes();
	void SaveHierName();
	bool LibExist(INXString libName);
	void SetIconID();
	bool XportNameExist(INXObjList* list);
	void SetPointToTestAgainst(INXRect rect); //needed for canvas support
	void RedrawZoom();
	void readProjectFile();
	void SubsetEncapsulate();
	void setStatusBarText(INXString csText);
	void toggleMonitoredLine(ConData* pBlob);
	void startTraceTimer();
	void stopTraceTimer();
	static unsigned int checkForEHSConnection( void * ptr );
	static bool getConnectionState();
	bool appUploader_ExportTransferables();
	bool appUploader_TarExportFiles();

//void DebugThread(void *param);

// UI message map functions
protected:

public:
	void OnWxMouseEvents( wxMouseEvent& event);// wx specific used to fire all the generic options below
	void OnWxLeftMouse( wxMouseEvent& event);

	void OnLButtonDown(unsigned int nFlags, INXPoint _point);
	void OnLButtonUp(unsigned int nFlags, INXPoint _point);
	void OnRButtonDown(unsigned int nFlags, INXPoint _point);
	void OnRButtonUp(unsigned int nFlags, INXPoint _point);
	void OnMouseMove(unsigned int nFlags, INXPoint _point);
	void OnDelete();
	void OnProperties();
	void OnDeleteLine();
	void OnDeleteNode();
	void OnStraighten();
	void OnReRoute();
	void OnAddNode();
	void OnReRouteAll();
	void OnIconShowDesc();
	void OnSubset();
	void OnTopdown();
//	void OnFtpOptions();
//	void OnFtpSodl();
	void OnPortInitialise();
	void OnKey();
	void OnCreateInstance();
	void OnUpLevel();
	void OnDebugStart();
	void OnDebugStop();
	void OnEditCut();
	void OnEditCopy();
	void OnEditPaste();
	void OnDebugPause();
	void OnDebugStep();
	void OnDebugForce();
	void OnDbgHistStart();
	void OnDbgHistStep();
	void OnDbgHistTime();
	void OnDbgHistStop();
	void OnUpdateDebugStop(CCmdUI* pCmdUI);
	void OnUpdateDebugForce(CCmdUI* pCmdUI);
	void OnUpdateDebugPause(CCmdUI* pCmdUI);
	void OnUpdateDebugStep(CCmdUI* pCmdUI);
	void OnUpdateDbgHistStart(CCmdUI* pCmdUI);
	void OnUpdateDbgHistStep(CCmdUI* pCmdUI);
	void OnUpdateDbgHistStop(CCmdUI* pCmdUI);
	void OnUpdateDbgHistTime(CCmdUI* pCmdUI);
	void OnUpdateDebugStart(CCmdUI* pCmdUI);
	void OnDestroy();
	void OnUpdateEditPaste(CCmdUI* pCmdUI);
	void OnUpdateEditCopy(CCmdUI* pCmdUI);
	void OnUpdateEditCut(CCmdUI* pCmdUI);
	void OnDebugRestart();
	void OnUpdateDebugRestart(CCmdUI* pCmdUI);
	void OnTimer(UINT nIDEvent);
	bool OnEraseBkgnd(); // probably not needed in wx
	void OnUpdateUpLevel(CCmdUI* pCmdUI);
	void OnEditUndo();
	void OnUpdateEditUndo(CCmdUI* pCmdUI);
	void OnEditRedo();
	void OnUpdateEditRedo(CCmdUI* pCmdUI);
	void OnUpdateFtpSodl(CCmdUI* pCmdUI);
	void OnAddPort();
	void OnUpdateAddPort(CCmdUI* pCmdUI);
	void OnDeletePort();
	void OnTagLine();
	void OnShowLine();
	void OnDeleteTag();
	void OnAddTag();
	void OnViewZoom();
	void OnWriteSodl();
	void OnUpdateWriteSodl(CCmdUI* pCmdUI);
	void OnGroupSetup();
	void OnAddIconToGroup();
	void OnAddPortToGroup();
	void OnAddToGroup();
	void OnSaveProject();
	void OnLibrary();
	void OnImportLib();
	void OnExportLib();
	void OnCloseProject();
	void OnUpdateCloseProject(CCmdUI* pCmdUI);
	void OnSelectAll();
	void OnLButtonDblClk(UINT nFlags, INXPoint _point);
	void OnUpdateGroupSetup(CCmdUI* pCmdUI);

public:
	/* Windowing Handlers */
	void OnImportDataFile();
	void OnSaveProjectAs();
	void OnEditProjectDesc();
	void OnEditDelete();
	bool OnScroll(unsigned int nScrollCode, unsigned int nPos, bool bDoScroll = true);
	void OnSize(UINT nType, int cx, int cy);
	bool OnMouseWheel(unsigned nFlags, short zDelta, INXPoint pt);
	void OnTransferOptions();
	void OnZoomIn();
	void OnZoomOut();
	void OnUpdateZoomIn(CCmdUI *pCmdUI);
	void OnUpdateZoomOut(CCmdUI *pCmdUI);
	void OnViewRefresh();
		void OnUpdateViewRefresh(CCmdUI *pCmdUI);
		void setLftBtnDownState(const int &val);



	/* Funcional Feature operations */
	void OnUpdateImportLib(CCmdUI *pCmdUI);
	void OnUpdateExportLib(CCmdUI *pCmdUI);
	void OnUpdateTransferManager(CCmdUI *pCmdUI);
	void OnUpdateLaunchTransfer(CCmdUI *pCmdUI);
	//void OnTransferManager();
		//void OnLaunchTransfer();


	//virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, INXPoint point);
	//virtual bool OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, INXPoint point);
	ConData* processComponentDrop(INXPoint point, INXString &csIconType, INXString &csBlock );
	void OnRenamePort();
	void OnRenameXport();
	void OnAddToLibrary();
	void OnUpdateAddToGroup(CCmdUI *pCmdUI);
	void OnUpdateTransferChanged(CCmdUI *pCmdUI);
	void OnLabTransferAll();
	void OnLabTransferChanged();
	void OnDefineMonitors();
	void OnSelectAllMonitors();
	void OnClearAllMonitors();
	void OnUpdateSelectAllMonitors(CCmdUI *pCmdUI);
	void OnUpdateClearAllMonitors(CCmdUI *pCmdUI);
	void OnUpdateDefineMonitors(CCmdUI *pCmdUI);
	void OnTrace();
	void OnUpdateTrace(CCmdUI *pCmdUI);
	void OnUpdateTransferAll(CCmdUI *pCmdUI);
	void OnNationalLanguageSupport();
	void OnEHSStartRestart();
	void OnEHSStop();
//	void OnEHSUpdate();
	void OnEHSTopmost();
	void OnEHSBottommost();
	void OnEHSNormalZOrder();
	void OnEHSInitParams();
	void OnEHSManageLocally();
	void OnEHSManageRemotely();
	void OnSelChangeEHSHostCombo();
	void OnUpdateEHSManageLocally(CCmdUI *pCmdUI);
	void OnUpdateEHSManageRemotely(CCmdUI *pCmdUI);
	void OnUpdateEHSStartRestart(CCmdUI *pCmdUI);
	void OnUpdateEHSStop(CCmdUI *pCmdUI);
	void OnUpdateEHSInitParams(CCmdUI *pCmdUI);
	void OnUpdateLocalHost(CCmdUI *pCmdUI);
	void OnImportResourceFile();
	void OnDebugStartwithrestart();
	void OnUpdateDebugStartwithrestart(CCmdUI *pCmdUI);


/* Attributes */
	wxSize windowSize;
    bool   m_init;
    unsigned int m_gllist;

    /* UI State */
    int running;
    int showfixed;
	// to restrict draw to animated things - specifically flashing ports to indicate an unconnected mandatory port
	bool onlyDrawAnimatedStuff;
	bool otherDrawEvent;
	int toggleAnimation; // 0 - toggle off, 1 - toggle on

	/* Canvas remapping (if we need it?) */
	CanvasSupport cs;

    //Line sketching
    INXPoint oldpoint,firstpoint;
    INXPoint lastmovingline;
    INXPoint lastlinepoint;

	INXRect RectangleSite, encapsulate, selectRect;
	INXPOSITION moveselected;
	INXPOSITION nodeIcon;
	// These 3 variables are defined by onlbuttondown and onrbuttondown
	INXPOSITION selectedControl;
	int selectedPortType;
	int selectedPort;

	int m_iLftBtnDownState;
	int enableSubset; //flags for drawing stuff
	long otherend;  // id of other icon
	bool nodeSelected;

	// debug variables

	bool lock;

	// edit variables
	bool pasteFlag;
	bool copyFlag;
	bool undoFlag;
	bool redoFlag;
	bool wrapFlag;
	int iUndoFileNum;
	int maxUndoFileNum;
	int iUndoFlagNum;
//	EditList edit;

	// print variables
	INXSize viewSize;
	int xViewSize;
	int yViewSize;
	int scale;


	static bool bHasConnectionToEHS; ///\todo this should be a singleton ... static?

	int lib; //0 - sub-function, 1 - library function, 2 - paste sub-block

	//CMainFrame *pFrame;
	Project* pProject;

	TypeConversion converter;


// wxwidgets
DECLARE_EVENT_TABLE()
};

#endif /* DRAWPROGVIEW_H_ */
