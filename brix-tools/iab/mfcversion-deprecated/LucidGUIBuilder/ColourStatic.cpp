// ColourStatic.cpp : implementation file
//

#include "stdafx.h"
//#include "DrawGUI.h"
#include "ColourStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ColourStatic

ColourStatic::ColourStatic()
{
	m_crBkColor = ::GetSysColor(COLOR_3DFACE); // Initializing the Background Color to the system face color.
	m_crTextColor = RGB(0,0,0); // Initializing the text to Black
	m_brBkgnd.CreateSolidBrush(m_crBkColor); // Create the Brush Color for the Background.
}

ColourStatic::~ColourStatic()
{
}


BEGIN_MESSAGE_MAP(ColourStatic, CStatic)
	//{{AFX_MSG_MAP(ColourStatic)
	//kwhite ON_WM_CTLCOLOR()
	ON_WM_CTLCOLOR_REFLECT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ColourStatic message handlers

void ColourStatic::SetBkColor(COLORREF crColor)
{
	m_crBkColor = crColor; // Passing the value passed by the dialog to the member varaible for Backgound Color
	m_brBkgnd.DeleteObject(); // Deleting any Previous Brush Colors if any existed.
	m_brBkgnd.CreateSolidBrush(crColor); // Creating the Brush Color For the Static Text Background
	//RedrawWindow();
}

void ColourStatic::SetTextColor(COLORREF crColor)
{
	m_crTextColor = crColor; // Passing the value passed by the dialog to the member varaible for Text Color
	//RedrawWindow();
}

//kwhite HBRUSH ColourStatic::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
HBRUSH ColourStatic::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	HBRUSH hbr;
	hbr = (HBRUSH)m_brBkgnd; // Passing a Handle to the Brush
	pDC->SetBkColor(m_crBkColor); // Setting the Color of the Text Background to the one passed by the Dialog
	pDC->SetTextColor(m_crTextColor); // Setting the Text Color to the one Passed by the Dialog

	if (nCtlColor)       // To get rid of compiler warning
      nCtlColor += 0;

	return hbr;
}
