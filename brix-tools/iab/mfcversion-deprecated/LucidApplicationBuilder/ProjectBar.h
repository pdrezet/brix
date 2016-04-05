// ProjectBar.h: interface for the CProjectBar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECTBAR_H__B7A4346E_DDEB_46AE_8F06_6F7C5B290B5C__INCLUDED_)
#define AFX_PROJECTBAR_H__B7A4346E_DDEB_46AE_8F06_6F7C5B290B5C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "scbarg.h"
#include "mytreectrl.h"

class CProjectBar : public CSizingControlBarG  
{
public:

	CProjectBar();
	virtual ~CProjectBar();
	int init(void);

	afx_msg void OnLButtonDblClk(UINT nFlags, INXPoint point);
	afx_msg void OnClickList(NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
public:
	CMyTreeCtrl m_cProjTree;
};

#endif // !defined(AFX_PROJECTBAR_H__B7A4346E_DDEB_46AE_8F06_6F7C5B290B5C__INCLUDED_)
