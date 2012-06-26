// kwhite:canvassupport
#pragma once

/**
* Author			:	K.White
* Date				:	8th March 2007
* Purpose			:	Allow canvas to stretch upwards/leftwards when object near boundary
*
* Applied Method	:	When object near top/left boundary move other objects down/rightwards.
* Version			:	1.0
***/

class CanvasSupport
{
private: 
	CSize m_ScrollPosition;			//Remember position of scroll
	CPoint m_Max;					//Needed for boundary check
	CPoint m_TempStore;				//Needed to remember first point before mouse move.
									//Used by MouseUp when calling ConData::RenewPosition(..,oldpoint)

	CPoint m_pPointToCheckAgainst;	//Used to test top of icon or selection box rather than mouse cursor

	bool m_bTopLeftBoundaryHit;		//Used to indicate a boundary hot has occured for top left of screen

	bool m_bTopBoundary;
	bool m_bLeftBoundary;
	bool m_bBottomBoundary;
	bool m_bRightBoundary;
	bool m_bDebugTrace; 

public:
	CanvasSupport(void);
	~CanvasSupport(void);

	bool NearTopLeftBoundary(CPoint point);
	bool NearBottomRightBoundary(CPoint point);
	
	CPoint AdjustPositionOfObjects(CPoint point);
	CPoint AdjustPositionOfScrollDownwards();
	CPoint AdjustPositionOfScrollUpwards();
	
	void SetMaxBoundary(CPoint point);
	void SetScrollPosition(CSize point);
	//CSize GetScrollPosition();

	void SetTopLeftBoundaryHit(bool set);
	bool TopLeftBoundaryHit();
	bool ValidLeftButtonEvent(int m_iLftBtnDownState);

	void DebugTrace(const char* pszFormat, ...);
	void SetDebugTrace(bool set);

	void SetTempStore(CPoint);
	CPoint GetTempStore();

	
	void SetPointToTestAgainst(CPoint point);
	CPoint GetPointToTestAgainst();

	bool StretchCanvas(CRect rect, CSize &csViewSize);
	void StretchCanvas(CPoint point, CSize &csViewSize);
};
