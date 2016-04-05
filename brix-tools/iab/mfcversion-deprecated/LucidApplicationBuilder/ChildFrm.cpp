// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "DrawProg.h"

#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	// TODO: add member initialization code here
	
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CMDIChildWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers

int CChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_StatusBar.Create(this);

	// Work out width of text to display
	INXRect textRect, textRect2;
	CClientDC aDC(&m_StatusBar);
	aDC.SelectObject(m_StatusBar.GetFont());
	aDC.DrawText("Zoom: 100% ", -1, textRect, DT_SINGLELINE|DT_CALCRECT);
	aDC.DrawText("    Line Editing ", -1, textRect2, DT_SINGLELINE|DT_CALCRECT);

	// Setup a part big enough to take the text
	int width = textRect.Width();
	m_StatusBar.GetStatusBarCtrl().SetParts(1, &width);
	// Initialize the text for the status bar
	m_StatusBar.GetStatusBarCtrl().SetText("Zoom: 100%", 0, 0);
	int width2 = textRect2.Width();
	m_StatusBar.GetStatusBarCtrl().SetParts(2, &width2);
	m_StatusBar.GetStatusBarCtrl().SetText("Line Editing",1,0);
	
	return 0;
}
