// ColourEdit.cpp : implementation file
//

#include "stdafx.h"
//#include "DrawGUI.h"
#include "ColourEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ColourEdit

ColourEdit::ColourEdit()
{
	//m_crBkColor = ::GetSysColor(COLOR_3DFACE); // Initializing background color to the system face color.
	m_crBkColor = RGB(0,255,0);
	m_crTextColor = RGB(255,255,255); // Initializing text color to black
	m_brBkgnd.CreateSolidBrush(m_crBkColor); // Creating the Brush Color For the Edit Box Background
}

ColourEdit::~ColourEdit()
{
}


BEGIN_MESSAGE_MAP(ColourEdit, CEdit)
	//{{AFX_MSG_MAP(ColourEdit)
	//kwhite added following CtlColor doesnt seem to be called ON_WM_CTLCOLOR()
	ON_WM_CTLCOLOR()
	ON_WM_CTLCOLOR_REFLECT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ColourEdit message handlers
// Create a green brush for the background for the class of controls:
/*CBrush ColourEdit::m_brush(RGB(0,128,0));

BOOL ColourEdit::OnChildNotify(UINT message, WPARAM wParam,
                               LPARAM lParam, LRESULT* pLResult)
{
	// If "message" is not the message you're after, do default processing:

	// For 16-bit applications change WM_CTLCOLOREDIT to WM_CTLCOLOR
    if (message != WM_CTLCOLOR)
    {
	   return CEdit::OnChildNotify(message,wParam,lParam,pLResult);
    }

	// Set the text foreground to red:
    HDC hdcChild = (HDC)wParam;
    //SetTextColor(hdcChild, RGB(0,0,255));

	// Set the text background to green:
    //SetBkColor(hdcChild, RGB(0,128,0));

	// Send what would have been the return value of OnCtlColor() - the
	// brush handle - back in pLResult:
    *pLResult = (LRESULT)(m_brush.GetSafeHandle());

	// Return TRUE to indicate that the message was handled:
    return TRUE;
}
*/
void ColourEdit::SetTextColor(COLORREF crColor)
{
	int m_bgRed = GetRValue(crColor);
	int m_bgGreen = GetGValue(crColor);
	int m_bgBlue = GetBValue(crColor);

	m_crTextColor = crColor; // Passing the value passed by the dialog to the member varaible for Text Color
	//RedrawWindow();
}

void ColourEdit::SetBkColor(COLORREF crColor)
{
	m_crBkColor = crColor; // Passing the value passed by the dialog to the member varaible for Backgound Color
	m_brBkgnd.DeleteObject(); // Deleting any Previous Brush Colors if any existed.
	m_brBkgnd.CreateSolidBrush(crColor); // Creating the Brush Color For the Edit Box Background
	//RedrawWindow();
}

BOOL ColourEdit::SetReadOnly(BOOL flag)
{
   /* kwhite
   if (flag == TRUE)
      SetBkColor(m_crBkColor);
   else
      SetBkColor(RGB(255,255,255));
	*/

   return CEdit::SetReadOnly(flag);
}

//kwhite HBRUSH ColourEdit::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
HBRUSH ColourEdit::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	HBRUSH hbr;
	hbr = (HBRUSH)m_brBkgnd; // Passing a Handle to the Brush
	
	int m_bgRed = GetRValue(m_crBkColor);
	int m_bgGreen = GetGValue(m_crBkColor);
	int m_bgBlue = GetBValue(m_crBkColor);

	pDC->SetBkColor(m_crBkColor); // Setting the Color of the Text Background to the one passed by the Dialog
	pDC->SetTextColor(m_crTextColor); // Setting the Text Color to the one Passed by the Dialog

	if (nCtlColor)       // To get rid of compiler warning
      nCtlColor += 0;

	return hbr;
}
