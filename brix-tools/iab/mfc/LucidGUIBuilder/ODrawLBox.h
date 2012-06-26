#pragma once

#include "drawc.h"

class CODrawLBox : public CListBox
{
	DECLARE_DYNAMIC(CODrawLBox)

public:
	CODrawLBox();
	virtual ~CODrawLBox();
	void SetDrawC(CDrawC* pDrwC) {
        m_pDrawC = pDrwC;
	}

	void Init() {
		m_pDrawC->InitLBox(this);
	}

	
	int AddItem(UINT nItem) {
        return m_pDrawC->AddItemLst(this, nItem);
	}

	int AddItem() {
		return m_pDrawC->AddItemLst(this);
	}

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void MeasureItem(LPMEASUREITEMSTRUCT /*lpMeasureItemStruct*/);
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
protected:
	CDrawC* m_pDrawC;
};


