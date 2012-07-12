#if !defined(AFX_MYTREECTRL_H__D0098A3D_93E6_43DF_B37B_5F4747F95133__INCLUDED_)
#define AFX_MYTREECTRL_H__D0098A3D_93E6_43DF_B37B_5F4747F95133__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyTreeCtrl.h : header file
//
#include "../common/LucidConstants.h"
#include "Condat.h"
#include "Project.h"
#include "DEP.h"


/////////////////////////////////////////////////////////////////////////////
// CMyTreeCtrl window

class CMyTreeCtrl : public CTreeCtrl
{
// Construction
public:
	CMyTreeCtrl();

// Attributes
public:
	// projItem is the head of the project tree
	// hSelItem is the item to be opened and must be set whenever opening a new document/view
	HTREEITEM hSelItem;
	Project *pProject[MAX_PROJECTS];
	bool openProject;
	Project *openProj;
	CImageList imageList;

// Operations
public:
	void Init();
	void UpdateProjectDescrptionOnTree(Project* pProject, DEP* pDEP);
	void PopulateProjectTree(INXObjList* iconList, Project* pProject);
	void PopulateNextLevel(HTREEITEM hItem, CString projectDir);
	void AddItem2ProjectTree(ConData* userDefBlob, Project* pProject, HTREEITEM hItem);
	bool CheckItem(HTREEITEM hItem, Project* activeProject, CString blockName);
	void CloseProject(HTREEITEM hItem, Project* activeProject);
	void DelItemFromProjectTree(ConData* userDefBlob, HTREEITEM hItem);
	Project* AddProject(int projectNum, ProjectMetaData* pProjMData);
	void DeleteProject(int projectNum);
	Project* GetProjectPtr(int projectNum);
	Project* GetProjectPtr(HTREEITEM hItem);
	HTREEITEM GetUserDefChildItem(ConData* userDefBlob, HTREEITEM hItem);
	ConData* AddXPort(CString type, CString portLabel, INXPoint point, Project* pProject, DEP* pDEP);
	void DeleteIcon(INXPOSITION iconPos, Project* pProject, DEP* pDEP, bool bDelOutputs);
	void DeleteBlockPort(INXPOSITION blockPos, int portNum, int portType, Project* pProject, DEP* pDEP);
	void RenameBlockPort(INXPOSITION blockPos, int portNum, int portType, Project* pProject, DEP* pDEP);
	void RenameXport(INXPOSITION iconPos, Project* pProject, DEP* pDEP);
	CString GetDEPPath(HTREEITEM hItem);
	bool NameExist(CString blockName, HTREEITEM hItem);
	HTREEITEM GetProjectItem(HTREEITEM hItem);
	void OpenDebugDEP(CDrawProgView* pView);
	void OpenParent(HTREEITEM hItem, Project* pProject);
	void SaveHierName(HTREEITEM hItem, CString projectDir, Project* pProject);
	void UpdateTree(Project* pProject, DEP* pDEP);
	void AddDataFile(ExtDataFile &dataFile, HTREEITEM hItem);
	void AddResourceFile(ExtResourceFile &xResourceFile, HTREEITEM hItem);
	void addWidgetGroup(CString csWidgetGroupName, HTREEITEM hItem);
	void updateWidgetGroups(HTREEITEM hItem);
	void SaveProjectAs(CString projectName, HTREEITEM hItem);
	bool IsSubsytem(Project* pProject, DEP* pDEP);


	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyTreeCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyTreeCtrl();

	// Generated message map functions
protected:
	DECLARE_DYNCREATE(CMyTreeCtrl)

	//{{AFX_MSG(CMyTreeCtrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint _point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint _point);
	afx_msg void OnResourceDelete();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYTREECTRL_H__D0098A3D_93E6_43DF_B37B_5F4747F95133__INCLUDED_)
