#pragma once
#include "drawc.h"

class CPicDrawC : public CDrawC
{
public: 
	CPicDrawC() : PicSizeX(25), PicSizeY(25) {}
	const int PicSizeX;
	const int PicSizeY;
protected:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpdis, bool bHasFocus);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpmis);
	
	virtual void InitLBox(CListBox* pLBox) {} //no init needed
	virtual void InitCombo(CComboBox* pCombo) {}

	virtual int AddItemLst(CListBox* pLBox, UINT nItem);
	virtual int AddItemLst(CListBox* pLBox);
	virtual int AddItemCmb(CComboBox* pCombo, UINT nItem);
};
