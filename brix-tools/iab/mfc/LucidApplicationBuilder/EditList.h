// EditList.h: interface for the EditList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EDITLIST_H__63F0F3CE_BD1F_4BE6_A990_B65D2BA6DBF1__INCLUDED_)
#define AFX_EDITLIST_H__63F0F3CE_BD1F_4BE6_A990_B65D2BA6DBF1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "condat.h"
#include "DEP.h"
#include "Project.h"

class EditList  
{
private:
	CPoint pasteOffset;

public:
	EditList();
	virtual ~EditList();

	// Attributes
	INXObjList* copySelList; // contains a list of selected icons to be copied

	// Methods
	void SaveCopy(CString Info);
	INXObjList* LoadPaste(CString Info);
	void BufferSelectedIcons(CRect selectRect, Project* pProject, DEP* pDEP);
	INXObjList* LoadTemp();
	CPoint getPasteOffset();
	void setPasteOffset(CPoint point);
	void incPasteOffset();
	void resetPasteOffset();
};

#endif // !defined(AFX_EDITLIST_H__63F0F3CE_BD1F_4BE6_A990_B65D2BA6DBF1__INCLUDED_)
