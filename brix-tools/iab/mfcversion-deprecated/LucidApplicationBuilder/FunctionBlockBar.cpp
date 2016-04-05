#include "stdafx.h"
#include "FunctionBlockBar.h"
#include "FunctionBlockTree.h"

FunctionBlockBar::FunctionBlockBar(void)
{
}

FunctionBlockBar::~FunctionBlockBar(void)
{
}
/* @todo MIGRATION_ISSUE unused in the program and causing unusual error 
*/
BEGIN_MESSAGE_MAP(FunctionBlockBar, CSizingControlBarG)	
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MBUTTONDOWN()
END_MESSAGE_MAP() 

void FunctionBlockBar::OnMButtonDown(UINT nFlags, CPoint _point)
{

	//AfxMessageBox("LBD");
	/*@todo MIGRATIONISSUE */
	CSizingControlBarG::OnMButtonDown(nFlags, _point); 
}

void FunctionBlockBar::OnLButtonDown(UINT nFlags, CPoint _point)
{
	//AfxMessageBox("LBD");
	CSizingControlBarG::OnRButtonDown(nFlags, _point);
}

void FunctionBlockBar::OnRButtonDown(UINT nFlags, CPoint _point)
{
	//AfxMessageBox("RBD");
	/*@todo MIGRATIONISSUE */ CSizingControlBarG::OnRButtonDown(nFlags, _point); 
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
	CRect(0, 0, 0, 0), this, 100); /* @todo MIGRATION_ISSUE*/

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