#pragma once
#include "afxcmn.h"
#include "LucidConstants.h"
#include "ProjectMetaData.h"
#include "ComponentMenuItem.h"
#include "Porting_Classes/INXObjArray.h"

/////////////////////////////////////////////////////////////////////////////
// FunctionBlockTree dialog
/*****************************************************************/
// Class FunctionBlockTree handles the Dialog box containing the list of processing objects 
// There are three levels of tree to select in a hierachy - typically: Type, name, datatype
// THIS CLASS SHOULD BE RENAMED TO ObjectSelector
/*****************************************************************/

class FunctionBlockTree :	public CTreeCtrl
{
public:
	FunctionBlockTree(void);
	~FunctionBlockTree(void);

	UINT m_DragDropFormat;
	
	HTREEITEM firstlev[MAX_FIRST_LEV];
	HTREEITEM secondlev[MAX_SECOND_LEV];
	HTREEITEM thirdlev[MAX_THIRD_LEV];
	HTREEITEM forthlev[MAX_THIRD_LEV]; //@todo change this to 4th level.
	
	HTREEITEM handle;

// Implementation
	int m_iL2MenuSize;
	int m_iL3MenuSize;
	int m_iL4MenuSize;
	CStringArray m_csaL2IconName;
	CStringArray m_csaL2MenuName;
	CStringArray m_csaL3IconName;
	CStringArray m_csaL3MenuName;
	CStringArray m_csaL4IconName;
	CStringArray m_csaL4MenuName;


	
	CPoint pos;
	int m_iLev1Ind, m_iLev2Ind, m_iLev3Ind, m_iLev4Ind; //@todo should be an array

// Dialog Data
	//{{AFX_DATA(FunctionBlockTree)
	//enum { IDD = IDD_CHOOSE };
	//CTreeCtrl	m_descript;
	//}}AFX_DATA
protected:
	void readIDF(CString csIDFPath, CString fileType);
	void FunctionBlockTree::readMenuMetaInfo();
	void FunctionBlockTree::readMenuItemsFromCDF(CString *level1, CString *level2, CString *level3, CString *level4, CString csIDFPath);
	void FunctionBlockTree::addBitmapToImageList(int bitmapID);
	void FunctionBlockTree::outputNamePriority(ComponentMenuItem *item);
	void FunctionBlockTree::addMenuItem(CString csIconName, CString csUserdefined, CString csLevel1, CString csLevel2, CString csLevel3, CString csLevel4, CString csStyle1, CString csStyle2, CString csStyle3, CString csStyle4);
	void FunctionBlockTree::addComponentsToTree(int currLevel, ComponentMenuItem *item, CString csLevel1, CString csLevel2, CString csLevel3, CString csLevel4, CString csStyle1, CString csStyle2, CString csStyle3, CString csStyle4);

private:
	bool m_bLftBtnDown;
	//bool leafIsSelected();
	bool m_bDraggingIcon;
	set<CString> m_sL2LibMenuNames;
	CImageList m_imageList; // image list used by the tree
	INXObjArray<CObject *> m_rootMenuList; // list of ComponentMenuItems at root level of the menu tree
	CString m_styleLookup[99];
	int m_maxStyle;
	INXObjArray<CObject *> m_componentList; // list of m_ComponentOnTree_t to be placed on tree

	struct ComponentOnTree_t : public CObject {
		CString iconName;
		CString menuNameL1;
		CString menuNameL2;
		CString menuNameL3;
		CString menuNameL4;
		CString userDefined;
	};

public:
	bool leafIsSelected(); 
	void loadContents(); 
	void ReadFile();
	int GetMItemSize(CString csLevel);
	CString GetIconName(int i, CString csLevel);
	void getL2LibMenuNames(set<CString> &sL2MenuNames); // this reads the first column (level 2) if menu items.
	void init(void);

	// Generated message map functions
	//{{AFX_MSG(FunctionBlockTree)
	//virtual BOOL OnInitDialog();
	//virtual void OnOK();
	//}}AFX_MSG
	//DECLARE_MESSAGE_MAP()
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnTvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnNMSetfocus(NMHDR *pNMHDR, LRESULT *pResult);
	HTREEITEM m_hItemClicked;
	HTREEITEM m_hPrevItemClicked;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.


