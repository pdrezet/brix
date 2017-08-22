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

#include "Porting_Classes/INXSize.h"
#include "Porting_Classes/INXString.h"
#include "Porting_Classes/INXRect.h"

class CanvasSupport
{
private: 
	INXPoint m_ScrollPosition;			//Remember position of scroll
	INXPoint m_Max;					//Needed for boundary check
	INXPoint m_TempStore;				//Needed to remember first point before mouse move.
									//Used by MouseUp when calling ConData::RenewPosition(..,oldpoint)

	INXPoint m_pPointToCheckAgainst;	//Used to test top of icon or selection box rather than mouse cursor

	bool m_bTopLeftBoundaryHit;		//Used to indicate a boundary hot has occured for top left of screen

	bool m_bTopBoundary;
	bool m_bLeftBoundary;
	bool m_bBottomBoundary;
	bool m_bRightBoundary;
	bool m_bDebugTrace; 

public:
	CanvasSupport(void);
	~CanvasSupport(void);

	bool NearTopLeftBoundary(INXPoint point);
	bool NearBottomRightBoundary(INXPoint point);
	
	INXPoint AdjustPositionOfObjects(INXPoint point);
	INXPoint AdjustPositionOfScrollDownwards();
	INXPoint AdjustPositionOfScrollUpwards();
	
	void SetMaxBoundary(INXPoint point);
	void SetScrollPosition(INXPoint point);
	void SetHScrollPosition(int shift);
	void SetVScrollPosition(int shift);
	INXPoint GetScrollPosition();
	int GetHScrollPosition();
	int GetVScrollPosition();

	void SetTopLeftBoundaryHit(bool set);
	bool TopLeftBoundaryHit();
	bool ValidLeftButtonEvent(int m_iLftBtnDownState);

	void DebugTrace(const char* pszFormat, ...);
	void SetDebugTrace(bool set);

	void SetTempStore(INXPoint);
	INXPoint GetTempStore();

	
	void SetPointToTestAgainst(INXPoint point);
	INXPoint GetPointToTestAgainst();

	bool StretchCanvas(INXRect rect, INXSize &csViewSize);
	void StretchCanvas(INXPoint point, INXSize &csViewSize);
};
