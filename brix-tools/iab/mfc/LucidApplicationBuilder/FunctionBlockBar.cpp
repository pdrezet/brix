#include "stdafx.h"
#include "FunctionBlockBar.h"
#include "FunctionBlockTree.h"

FunctionBlockBar::FunctionBlockBar(void)
{
}

FunctionBlockBar::~FunctionBlockBar(void)
{
}
BEGIN_MESSAGE_MAP(FunctionBlockBar, CSizingControlBarG)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MBUTTONDOWN()
END_MESSAGE_MAP()

void FunctionBlockBar::OnMButtonDown(UINT nFlags, CPoint point)
{
	//AfxMessageBox("LBD");
	CSizingControlBarG::OnMButtonDown(nFlags, point);
}

void FunctionBlockBar::OnLButtonDown(UINT nFlags, CPoint point)
{
	//AfxMessageBox("LBD");
	//CSizingControlBarG::OnRButtonDown(nFlags, point);
}

void FunctionBlockBar::OnRButtonDown(UINT nFlags, CPoint point)
{
	//AfxMessageBox("RBD");
	CSizingControlBarG::OnRButtonDown(nFlags, point);
}

int FunctionBlockBar::init(void)
{

	m_cFuncBlckTree.Create( 
		WS_VISIBLE | 
		WS_OVERLAPPED | 
		WS_CAPTION |   
		//WS_MAXIMIZE | 
		WS_OVERLAPPED | 
		TVS_HASLINES | 
		TVS_HASBUTTONS | 
		TVS_LINESATROOT,
	CRect(0, 0, 0, 0), this, 100);

	m_cFuncBlckTree.SetWindowTextA("Components");
	m_cFuncBlckTree.init();

//	EnableDocking( CBRS_ALIGN_TOP);
//	EnableDocking( CBRS_ALIGN_RIGHT);
//	EnableDocking( CBRS_ALIGN_LEFT);
//	EnableDocking( CBRS_ALIGN_BOTTOM);

	//DockControlBar( & m_cFuncBlckTree );

	return 0;
}

int FunctionBlockBar::loadContents(void)
{
	m_cFuncBlckTree.loadContents();
	return 0;
}