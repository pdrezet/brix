
#pragma once

//#include "ProjectFileManagerDialog.h"
#include "afxcmn.h"

class ProjectFileManagerDialog;

class LgbListCtrl : public CListCtrl
{

public:
	DECLARE_MESSAGE_MAP()

public:
	LgbListCtrl();
	int m_nCheckedItem;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

	void CheckItem(int nNewCheckedItem);
	afx_msg void OnLvnItemchanged(NMHDR *pNMHDR, LRESULT *pResult);

	void setProjMgrDlog(  ProjectFileManagerDialog *pProjFileMgrDlog );

	void setChecked( const int &rowNum );

private:
	ProjectFileManagerDialog *m_pProjFileMgrDlog;

};

/////////////////////////////////////////////////////////////////////////////
