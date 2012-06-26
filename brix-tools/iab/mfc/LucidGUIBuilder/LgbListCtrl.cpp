// ListVwEx.cpp : implementation of the CListViewEx class
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"
#include "ProjectFileManagerDialog.h"
#include "LgbListCtrl.h"
#include <cassert>

BEGIN_MESSAGE_MAP(LgbListCtrl, CListCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, &LgbListCtrl::OnLvnItemchanged)
END_MESSAGE_MAP()


LgbListCtrl::LgbListCtrl(): m_nCheckedItem(-1)
, m_pProjFileMgrDlog(NULL)
{
}

void LgbListCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	//Do nothing, otherwise active layout can be unchecked by a double-click
}

void LgbListCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{

	LVHITTESTINFO hitTestInfo;
	hitTestInfo.pt = point;
	hitTestInfo.flags = 0;

	HitTest( &hitTestInfo );
	int i = hitTestInfo.iItem;
	int j = hitTestInfo.iSubItem;

	UINT uFlags = 0;
	int nHitItem = HitTest(point, &uFlags);

	bool onStateIcon, onIcon;

	onStateIcon = uFlags & LVHT_ONITEMSTATEICON;
	onIcon = uFlags & LVHT_ONITEMICON;
	int k = 0;

	// we need additional checking in owner-draw mode
	// because we only get LVHT_ONITEM
	BOOL bHit = FALSE;
	DWORD style = GetStyle();
	bool du = style & LVS_OWNERDRAWFIXED;

	if (uFlags == LVHT_ONITEMSTATEICON )//&& (GetStyle() & LVS_OWNERDRAWFIXED))
	{
		// Set the tickbox, unset all other tickboxes.
		CheckItem(nHitItem);

		CString layoutHostName = GetItemText( i, 1 );

		// Flag this as the 'active' guifile layout.
		CString widgetGroup = m_pProjFileMgrDlog->getCurrentTabLabel();

		LucidErrEnum err = 
			m_pProjFileMgrDlog->m_pProjectMetaData->setActiveLayout( widgetGroup, layoutHostName );

		// The PMD must record permanently which layouts are active.
		err = 
			m_pProjFileMgrDlog->m_pProjectMetaData->writeProjectFile();

		assert( kErr_NoErr == err );
		
	} else {
		CListCtrl::OnLButtonDown(nFlags, point);
		m_pProjFileMgrDlog->processListChange();
	}
}

void LgbListCtrl::OnLvnItemchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	//AfxMessageBox("LgbListCtrl Item Changed");
	*pResult = 0;
}

void LgbListCtrl::CheckItem(int nNewCheckedItem)
{
	if (m_nCheckedItem != nNewCheckedItem){

		if (m_nCheckedItem != -1) {
				SetItemState(m_nCheckedItem,
					INDEXTOSTATEIMAGEMASK(1), LVIS_STATEIMAGEMASK);
		}

		if( nNewCheckedItem != -1 ){
			SetItemState( nNewCheckedItem,
					INDEXTOSTATEIMAGEMASK(2), LVIS_STATEIMAGEMASK);
		}

	} // if (m_nCheckedItem != nNewCheckedItem)

	m_nCheckedItem = nNewCheckedItem;
}

void LgbListCtrl::setProjMgrDlog( ProjectFileManagerDialog *pProjFileMgrDlog )
{ 
	m_pProjFileMgrDlog = pProjFileMgrDlog;
}

void LgbListCtrl::setChecked( const int &rowNum )
{ 
	SetItemState( rowNum,
		INDEXTOSTATEIMAGEMASK(2), LVIS_STATEIMAGEMASK);
}