// DrawProgView.h : interface of the CDrawProgView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWPROGVIEW_H__EC34D26E_981B_11D3_A9AD_00001C21326E__INCLUDED_)
#define AFX_DRAWPROGVIEW_H__EC34D26E_981B_11D3_A9AD_00001C21326E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "DrawProgDoc.h"
#include "Encapsulate.h"
#include "colourKey.h"
#include "FTP.h"
#include "TypeConversion.h"
#include "EditList.h"
#include "DbgMsgDialog.h"
#include "CanvasSupport.h"
#include "InterfaceDropTarget.h"
#include "FunctionBlockSubstitution.h"
#include "../common/EHSInitParams.h"
#include "../common/LabLgbBaseApp.h"
#include "Porting_Classes/INXString.h"


//#include "C:\\downloads\\ZipArchive\\ZipArchive.h"

class CDrawProgView : public CScrollView//CView  
{
protected: // create from serialization only
	
	DECLARE_DYNCREATE(CDrawProgView)

	UINT m_DragDropFormat;

//	CInterfaceDropTarget m_DT;

// Attributes
public:
	CDrawProgDoc* GetDocument();
	CDrawProgView();
// Operations
public:

	//void OnLabTransferAll();

	//bool c_bSendAllToTargetHasOccurred;
	void transferToTarget(const bool &bUpdatedOnly );
	void uploadAppToServer();


	//CObArray icon;  // This is an array of all the icons in the view
	CPen bluepen,greenpen,redpen,nullpen,dashkpen,blackpen;
	CBrush greenbrush;
	CDrawProgDoc* pDoc;
	int running;
	int showfixed;
	
	//Line sketching
	INXPoint oldpoint,firstpoint;
	INXPoint lastmovingline;
	INXPoint lastlinepoint;

	//kwhite:canvassupport
	CanvasSupport cs;

//SOME DRAWING VARIABLES	
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
	ColourKey* colourKeyDialog;
	// debug variables
	CDbgMsgDialog* dbgMsg;
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
	EditList edit;
	
	// print variables
	INXSize viewSize;
	int xViewSize;
	int yViewSize;
	int scale;

	// to restrict draw to animated things - specifically flashing ports to indicate an unconnected mandatory port
	bool onlyDrawAnimatedStuff;
	bool otherDrawEvent;
	int toggleAnimation; // 0 - toggle off, 1 - toggle on
	static bool bHasConnectionToEHS;

	int lib; //0 - sub-function, 1 - library function, 2 - paste sub-block

	CMainFrame *pFrame;	
	Project* pProject;
	DEP* pDEP;

	TypeConversion converter;
	FunctionBlockSubstitution m_FBSubstitute;

private:
	INXPoint m_cpRButtonDown;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawProgView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDrawProgView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	
public:	
	void init();
	void initUndo();
	void SetToMovingRectangle(INXPOSITION selected);
	void RemoveHighlight();
	void StartLine(INXPOSITION selectedIcon, int PortSelected, int portType);
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
	static UINT checkForEHSConnection( LPVOID ptr );
	static bool getConnectionState();
	bool appUploader_ExportTransferables();
	bool appUploader_TarExportFiles();
//void DebugThread(void *param);

// Generated message map functions
protected:

public:
	//{{AFX_MSG(CDrawProgView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint _point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint _point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint _point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint _point);
	afx_msg void OnDelete();
	afx_msg void OnProperties();
	afx_msg void OnDeleteLine();
	afx_msg void OnDeleteNode();
	afx_msg void OnStraighten();
	afx_msg void OnReRoute();
	afx_msg void OnAddNode();
	afx_msg void OnReRouteAll();
	afx_msg void OnIconShowDesc();
	afx_msg void OnSubset();
	afx_msg void OnTopdown();
//	afx_msg void OnFtpOptions();
//	afx_msg void OnFtpSodl();
	afx_msg void OnPortInitialise();
	afx_msg void OnKey();
	afx_msg void OnCreateInstance();
	afx_msg void OnUpLevel();
	afx_msg void OnDebugStart();
	afx_msg void OnDebugStop();
	afx_msg void OnEditCut();
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	afx_msg void OnDebugPause();
	afx_msg void OnDebugStep();
	afx_msg void OnDebugForce();
	afx_msg void OnDbgHistStart();
	afx_msg void OnDbgHistStep();
	afx_msg void OnDbgHistTime();
	afx_msg void OnDbgHistStop();
	afx_msg void OnUpdateDebugStop(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDebugForce(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDebugPause(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDebugStep(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDbgHistStart(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDbgHistStep(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDbgHistStop(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDbgHistTime(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDebugStart(CCmdUI* pCmdUI);
	afx_msg void OnDestroy();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnDebugRestart();
	afx_msg void OnUpdateDebugRestart(CCmdUI* pCmdUI);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnUpdateUpLevel(CCmdUI* pCmdUI);
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	afx_msg void OnEditRedo();
	afx_msg void OnUpdateEditRedo(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFtpSodl(CCmdUI* pCmdUI);
	afx_msg void OnAddPort();
	afx_msg void OnUpdateAddPort(CCmdUI* pCmdUI);
	afx_msg void OnDeletePort();
	afx_msg void OnTagLine();
	afx_msg void OnShowLine();
	afx_msg void OnDeleteTag();
	afx_msg void OnAddTag();
	afx_msg void OnViewZoom();
	afx_msg void OnWriteSodl();
	afx_msg void OnUpdateWriteSodl(CCmdUI* pCmdUI);
	afx_msg void OnGroupSetup();
	afx_msg void OnAddIconToGroup();
	afx_msg void OnAddPortToGroup();
	afx_msg void OnAddToGroup();
	afx_msg void OnSaveProject();
	afx_msg void OnLibrary();
	afx_msg void OnImportLib();
	afx_msg void OnExportLib();
	afx_msg void OnCloseProject();
	afx_msg void OnUpdateCloseProject(CCmdUI* pCmdUI);
	afx_msg void OnSelectAll();
	afx_msg void OnLButtonDblClk(UINT nFlags, INXPoint _point);
	afx_msg void OnUpdateGroupSetup(CCmdUI* pCmdUI);
//	afx_msg void OnFtpEhs();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnImportDataFile();
	afx_msg void OnSaveProjectAs();
	afx_msg void OnEditProjectDesc();
	afx_msg void OnEditDelete();
	virtual BOOL OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll = TRUE);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, INXPoint pt);
	afx_msg void OnTransferOptions();
	afx_msg void OnZoomIn();
	afx_msg void OnZoomOut();
	afx_msg void OnUpdateZoomIn(CCmdUI *pCmdUI);
	afx_msg void OnUpdateZoomOut(CCmdUI *pCmdUI);
	//afx_msg void OnTransferManager();
	//afx_msg void OnLaunchTransfer();
	afx_msg void OnUpdateImportLib(CCmdUI *pCmdUI);
	afx_msg void OnUpdateExportLib(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTransferManager(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLaunchTransfer(CCmdUI *pCmdUI);
	afx_msg void OnViewRefresh();
	afx_msg void OnUpdateViewRefresh(CCmdUI *pCmdUI);
	void setLftBtnDownState(const int &val);
	virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, INXPoint point);
	virtual BOOL OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, INXPoint point);
	ConData* processComponentDrop(INXPoint point, INXString &csIconType, INXString &csBlock );
	afx_msg void OnRenamePort();
	afx_msg void OnRenameXport();
	afx_msg void OnAddToLibrary();
	afx_msg void OnUpdateAddToGroup(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTransferChanged(CCmdUI *pCmdUI);
	afx_msg void OnLabTransferAll();
	afx_msg void OnLabTransferChanged();
	afx_msg void OnDefineMonitors();
	afx_msg void OnSelectAllMonitors();
	afx_msg void OnClearAllMonitors();
	afx_msg void OnUpdateSelectAllMonitors(CCmdUI *pCmdUI);
	afx_msg void OnUpdateClearAllMonitors(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDefineMonitors(CCmdUI *pCmdUI);
	afx_msg void OnTrace();
	afx_msg void OnUpdateTrace(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTransferAll(CCmdUI *pCmdUI);
	afx_msg void OnNationalLanguageSupport();
	afx_msg void OnEHSStartRestart();
	afx_msg void OnEHSStop();
//	afx_msg void OnEHSUpdate();
	afx_msg void OnEHSTopmost();
	afx_msg void OnEHSBottommost();
	afx_msg void OnEHSNormalZOrder();
	afx_msg void OnEHSInitParams();
	afx_msg void OnEHSManageLocally();
	afx_msg void OnEHSManageRemotely();
	afx_msg void OnSelChangeEHSHostCombo();
	afx_msg void OnUpdateEHSManageLocally(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEHSManageRemotely(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEHSStartRestart(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEHSStop(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEHSInitParams(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLocalHost(CCmdUI *pCmdUI);
public:
	afx_msg void OnImportResourceFile();
public:
	afx_msg void OnDebugStartwithrestart();
public:
	afx_msg void OnUpdateDebugStartwithrestart(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // debug version in DrawProgView.cpp
inline CDrawProgDoc* CDrawProgView::GetDocument()
   { return (CDrawProgDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWPROGVIEW_H__EC34D26E_981B_11D3_A9AD_00001C21326E__INCLUDED_)
