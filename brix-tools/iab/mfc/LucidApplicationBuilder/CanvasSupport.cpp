// kwhite:canvassupport
#include "stdafx.h"
#include "CanvasSupport.h"

/**
* Author			:	K.White
* Date				:	8th March 2007
* Purpose			:	Allow canvas to stretch upwards/leftwards when object near boundary
*
* Applied Method	:	When object near top/left boundary move other objects down/rightwards.
* Version			:	1.0
***/

CanvasSupport::CanvasSupport(void)
{
	//Clearly indicate moving objects is in process, and control boundary movement
	m_bTopLeftBoundaryHit = false;

	//ScrollPosition is altered when hitting boundary or when OnScroll event occurs
	m_ScrollPosition.cx = 0;
	m_ScrollPosition.cy = 0;

	//Allow trace statements to be turned on or off
	m_bDebugTrace = false;
}

CanvasSupport::~CanvasSupport(void)
{
}

// Return true when object near left or top boundary
bool CanvasSupport::NearTopLeftBoundary(INXPoint point)
{
	m_bLeftBoundary = false;	
	m_bTopBoundary = false;

	if (point.x <= 10) 
	{
		m_bLeftBoundary = true;		
	}

	if (point.y <= 10) 
	{
		m_bTopBoundary = true;
	}

	if ((m_bLeftBoundary) || (m_bTopBoundary)) 
	{
		return true;
	}
	
	return false;
}

//This function needs to be set by the View class
//when ever a scroll resize event occurs.  
void CanvasSupport::SetScrollPosition(INXSize topleft)
{
	m_ScrollPosition.cx = topleft.cx;
	m_ScrollPosition.cy = topleft.cy;
}

//This function needs to be set by the View class
//when ever a resize event occurs. Hence it is called by OnSize 
void CanvasSupport::SetMaxBoundary(INXPoint point)
{
	m_Max.x = point.x;
	m_Max.y = point.y;
}

// Return true when object near bottom or left boundary
bool CanvasSupport::NearBottomRightBoundary(INXPoint point)
{
	m_bRightBoundary = false;	
	m_bBottomBoundary = false;

	//What is the max size of the window

	if (point.x >= (m_Max.x - 10)) 
	{
		m_bRightBoundary = true;		
	}

	if (point.y >= (m_Max.y - 10)) 
	{
		m_bBottomBoundary = true;
	}

	if ((m_bRightBoundary) || (m_bBottomBoundary)) 
	{
		return true;
	}
	return false;
}

// Return minor adjustment value for objects to move 
// out of the way.
INXPoint CanvasSupport::AdjustPositionOfObjects(INXPoint point)
{
	if (m_bLeftBoundary) 
	{
		point.x = point.x + 10;
	}

	if (m_bTopBoundary) 
	{
		point.y = point.y + 10;
	}
	
	return point;
}

// Return minor adjustment of scroll position.
INXPoint CanvasSupport::AdjustPositionOfScrollDownwards()
{
	if (m_bBottomBoundary) 
	{
		m_ScrollPosition.cy = m_ScrollPosition.cy + 10;
	}

	if (m_bRightBoundary) 
	{
		m_ScrollPosition.cx = m_ScrollPosition.cx + 10;
	}

	//INXPoint needed for MFC call ScrollToPosition
	INXPoint point;
	point.x = m_ScrollPosition.cx;
	point.y = m_ScrollPosition.cy;
	
	return point;
}

// Return minor adjustment of scroll position.
INXPoint CanvasSupport::AdjustPositionOfScrollUpwards()
{
	if (m_bTopBoundary) 
	{
		if (m_ScrollPosition.cy < 10) {
			m_ScrollPosition.cy = 0;
		}
		else {
			m_ScrollPosition.cy = m_ScrollPosition.cy - 10;
		}
	}

	if (m_bLeftBoundary) 
	{
		if (m_ScrollPosition.cx < 10) {
			m_ScrollPosition.cx = 0;
		}
		else {
			m_ScrollPosition.cx = m_ScrollPosition.cx - 10;
		}
	}

	//INXPoint needed for MFC call ScrollToPosition
	INXPoint point;
	point.x = m_ScrollPosition.cx;
	point.y = m_ScrollPosition.cy;
	
	return point;
}


void CanvasSupport::SetTopLeftBoundaryHit(bool set)
{
	m_bTopLeftBoundaryHit = set;
}

bool CanvasSupport::TopLeftBoundaryHit()
{
	return m_bTopLeftBoundaryHit;
}

// This ensures we are moving objects for a valid event
bool CanvasSupport::ValidLeftButtonEvent(int m_iLftBtnDownState)
{
	// case 1: ?											INVALID
	// case 2: capture selection of function or encap block VALID
	// case 3: capture line selection						INVALID
	// case 4: rubber band for encapsulation block			INVALID
	// case 5: creation of rubber band						INVALID 
	// case 6: Multiple objects selected with rubberband	VALID 

	if ( (m_iLftBtnDownState == 2)  
		|| (m_iLftBtnDownState == 6)  )
	{
		return true;
	}

	return false;
}

// Debug trace commands can be turned off or on when needed by calling SetDebugTrace
void CanvasSupport::SetDebugTrace(bool set)
{
	m_bDebugTrace = set;
}

// Debug trace commands can be turned off or on when needed by calling SetDebugTrace
void CanvasSupport::DebugTrace(const char* pszFormat, ...)
{
	if (m_bDebugTrace)
	{
		INXString szText;
		char buf[1024];

		va_list arglist;
		va_start(arglist, pszFormat);
		vsprintf_s(buf, pszFormat, arglist);
		va_end(arglist);

		//Add time to messages
		CTime tNow;
		INXString szTime;
		tNow = CTime::GetCurrentTime();
		szTime = tNow.Format( "%H:%M:%S " );

		//Add time and our message
		szText = szTime + buf;

		TRACE(szText.GetBuffer(256));
	}
}

//Needed to remember first point before mouse move.
//Used by MouseUp when calling ConData::RenewPosition(..,oldpoint)
void CanvasSupport::SetTempStore(INXPoint store)
{
	m_TempStore = store;
}

//Needed to remember first point before mouse move.
//Used by MouseUp when calling ConData::RenewPosition(..,oldpoint)
INXPoint CanvasSupport::GetTempStore()
{
	return m_TempStore;
}

//Used to test top of icon or selection box rather than mouse cursor
void CanvasSupport::SetPointToTestAgainst(INXPoint point)
{
	m_pPointToCheckAgainst = point;
}

//Used to test top of icon or selection box rather than mouse cursor
INXPoint CanvasSupport::GetPointToTestAgainst()
{
	return m_pPointToCheckAgainst;
}

//Used to test and stretch canvas beyond 2000,2000
bool CanvasSupport::StretchCanvas(INXRect rect, INXSize &csViewSize)
{
	if (rect.bottom > csViewSize.cy-10) 
	{
		csViewSize.cy = csViewSize.cy + 150;
		return true;
	}

	if (rect.right > csViewSize.cx-10) 
	{
		csViewSize.cx = csViewSize.cx + 150;
		return true;
	}

	return false;
}

//Used to stretch canvas beyond 2000,2000 if top/left boundary hit
void CanvasSupport::StretchCanvas(INXPoint point, INXSize &csViewSize)
{
	csViewSize.cy = csViewSize.cy + point.y;		
	csViewSize.cx = csViewSize.cx + point.x;	
}