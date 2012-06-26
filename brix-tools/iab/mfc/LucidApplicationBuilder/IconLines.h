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
using namespace std;

class IconLines : public CObject
{
public:
	void Save(ostream * file) ;
	void Load(istream * file) ; 
	IconLines();
	virtual ~IconLines();
	void SetEndPoints(CPoint *start, CPoint *end,long int _othericon,int _portNum, int _portType) ;
	void addNode(CPoint _node);
	void AddNode(CPoint cpNodePt, int iNodeNum);
	int AddDogLeg(int x_postion = 50,int ylevel=50); // makes a forward dogleg of the line
	void editNode(CPoint _node);
	void deleteNode();
	void DeleteNode(int iNodeNum);
	void deleteAllNodes();
	void Draw(CDC* theDC);
	void Delete();
	void Disconnect();
	void setIDNum(long int _idNum);
	void setPortType(int _portType);
	void Move(CPoint point);
	void MoveOutNode(CPoint point);
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
	void MoveSegment(CPoint point);
	int GetLineSegment(const CPoint cpPoint);
	bool IsOnSegment(const CPoint cpPoint, const int iSegmentNum);
	bool IsSegmentsAligned(const int iSegmentNum1, const int iSegmentNum2);
	void DrawNode(CDC* pDC, CPoint point);

	int exist;
	INXObjArray <CObject *>points;
	long int othericonid;
    int otherportno;
	CPoint otherportpoint;
	long int idNum;
	int portType; // port type line is connected to
	int dataType;
	int nodeCount;
	CString dbgValue;
	CRect valueRect;
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
