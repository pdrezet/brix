// ProjectBar.cpp: implementation of the CProjectBar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DrawProg.h"
#include "ProjectBar.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CProjectBar::CProjectBar()
{

}

CProjectBar::~CProjectBar()
{

}

BEGIN_MESSAGE_MAP(CProjectBar, CSizingControlBarG)
	ON_WM_LBUTTONDBLCLK()
	//ON_NOTIFY_REFLECT (NM_CLICK, OnClickList)
	ON_NOTIFY(NM_CLICK, IDC_LIST, OnClickList)
	//NM_CLICK()
END_MESSAGE_MAP()

void CProjectBar::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
}

void CProjectBar::OnClickList(NMHDR* pNMHDR, LRESULT* pResult)
{
}


int CProjectBar::init(void)
{

	m_cProjTree.Create( 
		WS_VISIBLE | 
		WS_OVERLAPPED | 
		WS_CAPTION |   
		//WS_MAXIMIZE | 
		WS_OVERLAPPED | 
		TVS_HASLINES | 
		TVS_HASBUTTONS | 
		TVS_LINESATROOT,
	CRect(0, 0, 0, 0), this, 100);

	m_cProjTree.SetWindowTextA("Project(s)");
	//m_cFuncBlckTree.init();

//	EnableDocking( CBRS_ALIGN_TOP);
//	EnableDocking( CBRS_ALIGN_RIGHT);
//	EnableDocking( CBRS_ALIGN_LEFT);
//	EnableDocking( CBRS_ALIGN_BOTTOM);

	//DockControlBar( & m_cFuncBlckTree );

	return 0;
}