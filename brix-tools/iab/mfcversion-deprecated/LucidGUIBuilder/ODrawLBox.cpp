// ODrawLBox.cpp : implementation file
//

#include "stdafx.h"
//#include "Lists.h"
#include "ODrawLBox.h"
#include ".\odrawlbox.h"

// CODrawLBox

IMPLEMENT_DYNAMIC(CODrawLBox, CListBox)
CODrawLBox::CODrawLBox()
{
}

CODrawLBox::~CODrawLBox()
{
}


BEGIN_MESSAGE_MAP(CODrawLBox, CListBox)
END_MESSAGE_MAP()



// CODrawLBox message handlers


void CODrawLBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	m_pDrawC->MeasureItem(lpMeasureItemStruct);
}

void CODrawLBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	ASSERT(lpDrawItemStruct->CtlType == ODT_LISTBOX);
	m_pDrawC->DrawItem(lpDrawItemStruct, (GetFocus()->GetSafeHwnd() == m_hWnd));
}
