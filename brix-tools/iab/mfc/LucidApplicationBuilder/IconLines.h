// IconLines.h: interface for the IconLines class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ICONLINES_H__C1041E81_B35E_11D8_A9B0_00055DD37FD7__INCLUDED_)
#define AFX_ICONLINES_H__C1041E81_B35E_11D8_A9B0_00055DD37FD7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#include <iostream>
#include "Porting_Classes/INXObjArray.h"
#include "Porting_Classes/INXPoint.h"
#include "Porting_Classes/INXSize.h"
#include "Porting_Classes/INXRect.h"


using namespace std;

class IconLines : public CObject
{
public:
	void Save(ostream * file) ;
	void Load(istream * file) ; 
	IconLines();
	virtual ~IconLines();
	void SetEndPoints(INXPoint *start, INXPoint *end,long int _othericon,int _portNum, int _portType) ;
	void addNode(INXPoint _node);
	void AddNode(INXPoint cpNodePt, int iNodeNum);
	int AddDogLeg(int x_postion = 50,int ylevel=50); // makes a forward dogleg of the line
	void editNode(INXPoint _node);
	void deleteNode();
	void DeleteNode(int iNodeNum);
	void deleteAllNodes();
	void Draw(CDC* theDC);
	void Delete();
	void Disconnect();
	void setIDNum(long int _idNum);
	void setPortType(int _portType);
	void Move(INXPoint point);
	void MoveOutNode(INXPoint point);
	void deleteNodeMemory();
	void setShow(int _show);
	// Debug monitor
	void setDbgMonitor(bool bDbgMonitorSel);
	void toggleDbgMonitor();
	bool getDbgMonitor();
	void setDefineMonitor(bool bDefineMonitor);
	// RTA Trace
	void setRtaTraceId(UINT iRtaTraceId);
	UINT getRtaTraceId();
	// Selected Line Segments
	void SetSelectedSegment(int iSegmentNum);
	int GetSelectedSegment();
	void MoveSegment(INXPoint point);
	int GetLineSegment(const INXPoint cpPoint);
	bool IsOnSegment(const INXPoint cpPoint, const int iSegmentNum);
	bool IsSegmentsAligned(const int iSegmentNum1, const int iSegmentNum2);
	void DrawNode(CDC* pDC, INXPoint point);

	int exist;
	INXObjArray <CObject *>points;
	long int othericonid;
    int otherportno;
	INXPoint otherportpoint;
	long int idNum;
	int portType; // port type line is connected to
	int dataType;
	int nodeCount;
	CString dbgValue;
	INXRect valueRect;
	int dbgEvent;
	int lineSelected;
	long hierID; // this is to simplify mapping process in debug mode
	int show; //hides lines when moving selection boxes
private:
	bool m_bDbgMonitorSel;
	bool m_bDefineMonitor;
	UINT m_iRtaTraceId;
	int m_iSelSegmentNum;
};

#endif // !defined(AFX_ICONLINES_H__C1041E81_B35E_11D8_A9B0_00055DD37FD7__INCLUDED_)
