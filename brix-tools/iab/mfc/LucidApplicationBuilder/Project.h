// Project.h: interface for the Project class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECT_H__BAE59696_6D9D_4162_AF44_02C956BA846F__INCLUDED_)
#define AFX_PROJECT_H__BAE59696_6D9D_4162_AF44_02C956BA846F__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DEP.h"
#include "LucidConstants.h"
#include "Group.h"
#include "Debugger.h"
#include "ProjectMetaData.h"


class Project  
{
public:
	Project();
	Project(ProjectMetaData* _pProjMData, int _projectNum);
	virtual ~Project();

	// Attributes
	ProjectMetaData* pProjMData;
	int projectNum;
	int DEPNum;
	DEP* pDEP[MAX_HIER_LEVELS * MAX_BLOCKS];
	INXObjList* flattened;
	Debugger debug;
private:
	bool m_bDefineMonitors;

public:
	// Methods
	void AddBlockPort(ConData* blob, int iDataType, int iPortType, CString portLabel, DEP* pDEP);
	DEP* AddDEP();
	void AddIconToGroup(INXPOSITION selectedIcon, int groupID, DEP* vwDEP);
	ConData* AddXPort(DEP* pParentDEP, CString type, CString portLabel, INXPoint point, DEP* pDEP);
	void AssignHierLineID();
	void PropagateHierLineId(ConData* blob, HTREEITEM hItem, long hierID, int portType, int iPortNum);
	void AssignSubBlockHierLineId(HTREEITEM hItem);
	void DebugStart(int mode);
	void DeleteDEP(DEP* theDEP);
	void DeleteBlockPort(INXPOSITION blockPos, int portNum, int portType, DEP* pDEP);
	void DeleteUnused(DEP* thisDEP);
	void DeleteXPort(DEP* pParentDEP, CString portLabel, CString blockName);
	void EditGroupSetup();
	//DEP* GetDEPPtr(CString depFilename);
	int LoadProg(CString Info);
	CDrawProgView* OpenView(CString depFilename);
	void RenameBlockPort(INXPOSITION blockPos, int iPortNum, int iPortType, DEP* pDEP);
	void RenameXport(INXPOSITION iconPos, DEP* pDEP, CString &csNewPortLabel);
	void ResetDebug();
	void SaveHierName();
	void SaveProg(CString Info);
	void SaveProjectDep();
	void SaveProject();
	INXObjList* WriteSODL(CString sodlfile);

	// Tag Management
	void addGuiWidget(ConData* icon);
	void removeGuiWidget(ConData* icon);
	void addPastedGuiWidgets(HTREEITEM hItem, INXObjList* pasteList);
	void removeWidgetsInUserDefBlock(HTREEITEM hItem);
	void getWidgetGroupNames(HTREEITEM hItem, set<CString> &sWidgetGroupSet); 
	void setWidgetGroupNames(set<CString> sWidgetGroupSet, vector<pair<CString, CString> > &vWidgetGroupPairVec);
	void updateWidgetGroupNames(HTREEITEM hItem, vector<pair<CString, CString> > vWidgetGroupPairVec);
	void updateWidgetGroup(ConData* pBlob, vector<pair<CString, CString> > vWidgetGroupPairVec);
	bool IsPastedGuiWidgetsInProject(INXObjList* pPasteList, HTREEITEM hItem);
	void GetWidget(const ConData* pBlob, GuiWidget &xWidget);

	DEP* depIsLoaded(HTREEITEM hItem);
	void closeUserDefDoc(HTREEITEM hItem);

	// Define Monitors
	bool getDefineMonitors();
	void setDefineMonitors(bool bDefineMonitors);

	// National Language Support
	bool RunNlsExec();
	void OpenNlsFile();
	

public:
	bool m_bTransferAllHasOccurred;

private:
	long m_iHierIdCount;
};

#endif // !defined(AFX_PROJECT_H__BAE59696_6D9D_4162_AF44_02C956BA846F__INCLUDED_)
