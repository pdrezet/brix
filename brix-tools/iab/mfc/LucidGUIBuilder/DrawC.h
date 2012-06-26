#pragma once

class CDrawC
{
protected:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpdis, bool bHasFocus) = 0;
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpmis) = 0;

	virtual void InitLBox(CListBox* pLBox) = 0;
	virtual void InitCombo(CComboBox* pCombo) = 0;

	virtual int AddItemLst(CListBox* pLBox, UINT nItem) = 0;
	virtual int AddItemLst(CListBox* pLBox) = 0;
	virtual int AddItemCmb(CComboBox* pCombo, UINT nItem) = 0;

	friend class CODrawCombo;
	friend class CODrawLBox;
};
