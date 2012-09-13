#include "wx/treectrl.h"

class FunctionBlockTree:public wxTreeCtrl{
	enum
    {
        TreeCtrlIcon_File,
        TreeCtrlIcon_FileSelected,
        TreeCtrlIcon_Folder,
        TreeCtrlIcon_FolderSelected,
        TreeCtrlIcon_FolderOpened
    };
public:
	FunctionBlockTree(void);
	FunctionBlockTree(wxWindow *parent, const wxWindowID id,
                       const wxPoint& pos, const wxSize& size,
					   long style);
public:
	~FunctionBlockTree(void);
	

public:
	 void AddTestItemsToTree(size_t numChildren, size_t depth);
	 void CreateImageList(int size = 16);
private:
	 void AddItemsRecursively(const wxTreeItemId& idParent, size_t nChildren,
		 size_t depth, size_t folder);
	 int          m_imageSize;               // current size of images
	 bool         m_reverseSort;             // flag for OnCompareItems
     wxTreeItemId m_lastItem,                // for OnEnsureVisible()
                 m_draggedItem;             // item being dragged r
	 DECLARE_DYNAMIC_CLASS(MyTreeCtrl)
};

class MyTreeItemData : public wxTreeItemData
{
public:
    MyTreeItemData(const wxString& desc) : m_desc(desc) { }
    const wxChar *GetDesc() const { return m_desc.c_str(); }

private:
    wxString m_desc;
};
