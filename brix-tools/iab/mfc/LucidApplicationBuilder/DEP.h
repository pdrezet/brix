// DEP.h: interface for the DEP class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEP_H__F9664C86_F68B_414F_9898_39AA1958B8EA__INCLUDED_)
#define AFX_DEP_H__F9664C86_F68B_414F_9898_39AA1958B8EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "condat.h"
//#include "mainFrm.h"
#include "FSM.h"
#include "LucidEnums.h"
#include <vector> // stl class
#include "Porting_Classes/INXObjList.h"

class DEP  
{
private:
	CSize m_CanvasSize; //Handle canvas size being stretched beyond 2000,2000

public:
	DEP();
	virtual ~DEP();

	// Attributes
	INXObjList* condata;  // declare a list type to point to ConDat objects
	CString depFilename;
	HTREEITEM hItem;
	CString projectDir;
	int projectNum;
	bool dbgMappedFlag;
		
	CStringArray *intTags, *boolTags, *realTags, *stringTags, *eventTags;

	//CMainFrame *pFrame;	
	FSM depFSM;

	// Methods
	int AddBlockPort(CString type, CString portLabel, CString blockName);
	INXPOSITION AddIcon(CString csIconType, CString csBlockName, CPoint point, int iShow=1); // adds a new icon 
	INXPOSITION AddIconObjectList(ConData* blob) ; //add all blobs using this function
	void AddIconToGroup(INXPOSITION selectedIcon, int groupID);
	int AddLine(INXPOSITION selectedIcon, int selectedPort, int selectedPortType, INXPOSITION selectedIcon2,int selectedPort2, int selectedPortType2) ;
	void AddNodes(INXPOSITION selectedIcon, int selectedPort, int selectedPortType, INXPOSITION selectedIcon2, int selectedPort2, int selectedPortType2);
	int AddPort(ConData* blob, int iDataType, int iPortType, CString portLabel);
	int AddTag(INXPOSITION iconPos, int portNum, int portType);
	void AddTag2List(CString tag, int dataType);
	ConData* AddXPort(CString type, CString portLabel, CPoint point);
	void AssignIconLineEndPoints();
	long CheckNewID(INXObjList* encapsulated, long int id);
	void ConnectEncapsulatedIcon(INXPOSITION encapsulatedPos, CRect selectedRect, INXObjList* oldDEP);
	void CreateInstance(ConData* userDefBlob, int lib);
	void DeleteIcon(INXPOSITION number, bool bDelOutputs); // 
	void DeleteLine(INXPOSITION selectedControl,int PortSelected, int portType);
	CString DeletePort(ConData* blob, int portNum, int portType);
	void DeleteTag(INXPOSITION iconPos, int portNum, int portType);
	void Draw(CDC * pDC);
	void Draw(CDC * pDC, bool _onlyDrawAnim, int _toggleAnim);
	INT_PTR EditControl(INXPOSITION selected); //default is that control is assigned if neq 0
	int GetFinishLineID(INXObjList* flattened, ConData* otherBlockIcon, ConData* flatBlob, int endNum, HTREEITEM hItem);
	ConData* GetIconFromID(long int id);
	int GetInLineID(ConData* blob, ConData* flatBlob, int inNum);
	INXObjList* GetLine(long lineID, int dataType);
	int GetOutLineID(INXObjList* flattened, ConData* otherBlockIcon, ConData* flatBlob, int outNum, HTREEITEM hItem);
	int GetStartLineID(ConData* blob, ConData* flatBlob, int startNum);
	int HighlightSelected(CRect selectRect);
	INXPOSITION Incontrol(CPoint point);
	void setFBHighlight(INXPOSITION fbPos);
	void InitTagLists();
	bool IsUniqueID(long id);
	void LoadProg(CString Info);

	//int OnLine(CPoint point, POSITION* Icon, bool* nodeSel, int* portType);
	//If interrogateOnly is true, nothing is changed in DEP, ie node count, etc
	int OnLine(CPoint point, INXPOSITION* Icon, bool* nodeSel, int* portType, const bool &interrogateOnly );
	bool OnNode(CPoint point, CPoint node);
	int OnConnect(CPoint point,INXPOSITION* Icon,int * portType, int *portConnected) ;
	LabLineSegmentTypeEnum IsOnLineSegment(CPoint point, CPoint node1, CPoint node2);
	void ReassignIconIDs(INXObjList* encapsulated);
	void RemoveTag(CString tag, int dataType);
	void RenewPosition(INXPOSITION selected, CPoint point, CPoint firstpoint);
	CRect RenewSelectedPos(CPoint newpoint, CPoint firstpoint, CRect selectRect);
	void SnapIconToGrid(INXPOSITION selected);

	void SaveProg(CString Info);
	//void SetCondataLineID(CObList* flattened);
	void ShowLine(INXPOSITION iconPos, int portNum, int portType);
	bool IsOutputPortConnected(ConData* pBlob, int iPortNum);
	bool IsFinishPortConnected(ConData* pBlob, int iPortNum);
	void RemoveConnectedInputTags(ConData* pBlob, int iPortNum);
	void RemoveConnectedStartTags(ConData* pBlob, int iPortNum);
	ConData* SubsetEncapsulate(CRect encapsulate, int lib);
	void TagLine(INXPOSITION iconPos, int portNum, int portType);
	void TagPorts(ConData* encapsulatedIcon, INXObjList* encapsulated);
	void TopdownEncapsulate();
	bool WithinEndpoints(CPoint point, CPoint start, CPoint end);
	//void SetView(CDrawProgView* _pView);

	//kwhite:canvassupport
	void HideSelected(INXPOSITION m_ItemSelected);
	void ShowSelected(INXPOSITION m_ItemSelected);
	void HideSelectedPositions();
	void ShowSelectedPositions();	
	void InvertSelected();
	void MoveObjectsWithinSelectedBox(CPoint newpoint, CPoint firstpoint);
	void MoveExternallyConnectedLines(CPoint newpoint, CPoint firstpoint);

	//Handle canvas size being stretched beyond 2000,2000
	void setCanvasSize(CSize CanvasSize);
	void initCanvasSize();
	CSize getCanvasSize();
	CPoint getInitScrollPos(CRect clientRect);
	
	void deleteConData();
	void setSaveSelectedFlag(bool flag);

	void ResetXportConnected();
	CString GetPortLabel(INXPOSITION blockPos, int iPortNum, int iPortType);
	void SetPortLabel(INXPOSITION blockPos, int iPortNum, int iPortType, CString csPortLabel);
	void SetPortLabel(CString csBlockName, CString csOldPortLabel, CString csNewPortLabel);

	void RenameSubsystem(CString csOldInstName, CString csNewInstName, HTREEITEM hUserdefItem);
	void AddToLibrary(INXPOSITION blockPos, CString csMenuName);
	bool IsRectEmpty(CRect selectRect);
	ConData* getIconAtPoint(CPoint point);

	// FB substitution methods
	INXPOSITION getPosFromIcon(ConData* pIcon);

	// Connections
	void dragConnections(INXPOSITION selectedIcon, int iSelectedPort, int iSelectedPortType, INXPOSITION selectedIcon2,int iSelectedPort2, int iSelectedPortType2);
	void swapPortData(Port* pPort1, Port* pPort2);
	void getConnectedLines(long iID, int iPortNum, int iPortType, vector<IconLines*> &linesVec);
	void rerouteDraggedConnections(long iOldID, long iNewID, long iOldPortNum, long iNewPortNum, int iPortType);

	// Define Monitoring
	void setAllMonitors(bool bSetClear);
	void toggleMonitoredLine(int iPortType, long iOtherIconId, int iOtherPortNo);

	// Debug
	void ResetAllDbgEvents();
	void ResetAllDbgValues();
	void MapLineID(INXObjList* flattened);
	void PropagateDebugDataDown(ConData* pSubsysIcon);
	void PropagateDebugDataUp(HTREEITEM hSubsys);

};

#endif // !defined(AFX_DEP_H__F9664C86_F68B_414F_9898_39AA1958B8EA__INCLUDED_)
