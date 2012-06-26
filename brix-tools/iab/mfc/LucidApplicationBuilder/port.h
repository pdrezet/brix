// port.h: icon port information
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PORT_H__9E27DF60_B038_11D8_A9B0_00055DD37FD7__INCLUDED_)
#define AFX_PORT_H__9E27DF60_B038_11D8_A9B0_00055DD37FD7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "bmpfile.h"
#include "IconLines.h"
#include "LucidConstants.h"
#include "LucidString.h"

class Port  : public CObject
{
public:
	Port(int _userdefined); 
	Port(CPoint _P, UINT _portNum, int _dataType, int _portType, CString _description, CStringArray* _funcName, CUIntArray* _funcArg, int _atomicFlag, bool bVerticalIn, int _userdefined, int _mandatoryFlag);
	Port(UINT _portNum, int _portType, CStringArray* _funcName, CUIntArray* _funcArg, int _atomicFlag);
	virtual ~Port();
	CPoint P;   // position
	int porttype;   //0 input, 1 output, 2 Trig input, 3 Trig output
	bool bPortVertical;
	int datatype;   //0 bool, 1 int, 2 float, 3 string 
	int portNum; // port number
	CString description;
	CStringArray* funcName;
	CUIntArray* funcArg;
	int connected;
	IconLines line; //this is the input line (one only allowed)
	long int location;
	long int lineID; //this is for output ports. needed to write out SODL
	// Indicates if port is connected to a xport. Required for subset encapsulation.
	// Ensures that an output with multiple connections only has one xport.
	// Ensures inputs only have one connection
	int xportConnected;
	// Required for subset encapsulation. When an input is connected to an output that has a fanout 
	// greater than 1 only want to create 1 xport. Therefore, when it is created store its id in the
	// output port it is connected to.
	long xportID;
	int initialise;
	CSize bitmapSize;
	CSize bitmHighSize;
	Bitmap bitmap;
	Bitmap bitmHighlight;
	CRect rectangle;
	int atomicFlag;
	bool mandatoryFlag;
	CString tag;
	UINT groupID;
	int userdefined;
	//nb - DEP::swapPortData() copies all the data from one por to another SO if add more attributes here, be sure to include it in this method - there is a bug raised to improve this architecture

// Methods
	void init();
	int OnPort(CPoint);  //accepts coordinated and returns 0 for not close amd then an int> 0 for closeness
	int addLine(CPoint *point,long int othericon,int otherPortNum, int otherPortType); // adds a line to inputs only otherwise return an error -1
	int RemoveLine();
	int DisconnectLine();
	void Draw(CDC* theDC);
	void Draw(CDC* theDC, bool _onlyDrawAnim, int _toggleAnim);
	int Move(CPoint point);
	void setLineID(long int _lineID);
	void Save(ostream *);
	void Load(istream *);
	//CObject* OtherIconID;

private:
	CRect GetPortBitmapArea();
	
};

#endif // !defined(AFX_PORT_H__9E27DF60_B038_11D8_A9B0_00055DD37FD7__INCLUDED_)
