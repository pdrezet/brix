// Coninfo.h: interface for the Coninfo class.
//
//////////////////////////////////////////////////////////////////////


#include <fstream>
#if !defined(AFX_Coninfo_H__DE3A1922_921E_11D3_A9AC_00001C21326E__INCLUDED_)
#define AFX_Coninfo_H__DE3A1922_921E_11D3_A9AC_00001C21326E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#include "../common/bmpfile.h"
#include "Port.h"
#include "Parameter.h"
#include "PROC_FUNCTION.H"
#include "../common/LucidEnums.h"

/*****************************************************************/
// ConData() contains processing icon data including screen geometry, bitmap
// port node locations, geometry of the input ports, port data types.
// It also contains the methods to read/write the data to file, generating SODL,
// adding connections, screen painting, testing for graphical user selections
// and checking use connection validity.
/*****************************************************************/

class ConData : public CObject  
{

public:

	static long int uniqueidgenerator; // one copy for all instances

	ConData();
	void copyDialogData( const ConData &sourceData );
	void init(CString csIconType, CString csBlockName, CPoint point, int _iShow=1);
	void initBmp(CPoint _point);
	void Draw(CDC *);
	void Draw(CDC *, bool _onlyDrawAnim, int _toggleAnim);
	void DrawDescription(CDC* theDC);
	void DrawTitle(CDC* theDC);
	void DrawFixed(CDC* theDC);
	void Save(ostream* file);
	int Load(istream* file);
	int LoadNoBmp(istream* file);
	void RenewPosition(CPoint newpoint, CPoint oldpoint);
	void DeleteLine(int port, int porttype);
	void ReRouteAll();
	int AddLine(int inPortNum, int InPrtType, ConData* othericon,int otherPortNum, int otherPortType);
	void setOutputPortAsConnected(int portNum, int portType);
	void AddNodes(int selectedPort, int selectedPortType, ConData* othericon, int otherPortNum, int otherPortType);
	int  CheckDatatypes(int portIn, int portInType, ConData*iconOut,int portOut,int portOutType);
	int  GetPortDataType(int portNum, int portType);
	CPoint GetPortPoint(int port, int portType);
	CPoint *GetPortPointPtr(int port, int portType);
	int OnPort(CPoint point,int * portType,int *portConnected);
	void ReadIDFFile(CString csType, CPoint point);
	int portType2Int(CString str);
	int dataType2Int(CString str);

	// widget methods
	bool isGuiWidget();
	LucidErrEnum getWidgetTag(CString &csWidgetTag);
	LucidErrEnum getScreenTag(CString &csScreenTag);
	LucidErrEnum setScreenTag(CString csScreenTag);
	
	// FB substitution methods
	int getPortCount(int iPortType, int iDataType);

	int m_iShow, showdescript, selected;
	long int identnum, blockID;

	CString	m_csIconType;
	CString m_csBlockName; // block name for encapsulated blocks. graphic filename is encapsulate
	CString description;
	CString longDesc;
	CString className;
	CString optionstring;
	CSize size;
	int m_iUserDefined;
	int instNum;
	CString hierarchyName;
	bool saveSelectedFlag;
	CRect rectangle; /// body part of icon


private:
	Bitmap bitmap;
	void LoadNewBMP(CString csType);
	bool encapsulated;
	void readFromIDFFile(CString filepath, CPoint point);
	void readFromCDFFile(CString filepath, CPoint point);
	void updateFunctionArg(struct definedFunctions *funcs);
	void growFunctionArray(struct definedFunctions *funcs, const char *funcName, int iPortType, int iFuncArg);

public:
	int CountNonVerticalPorts(int PortType);
	CRect GetBoundingRectangle();
	void MinusYCoords();
	CPoint GetIconBottomRight();
	CPoint GetIconPos();
	CPoint GetIconCentre();
	CString BuildXPortString(int iPortType,int DataType);
	CPoint CalculateXPortPosition(int iPortType);
	void repositionVerticalPorts();
	void ResizeIcon();
	int In(CPoint point);
	void setEncapsulated(bool encaps);
	bool getEncapsulated();
	void hideSelected();
	void showSelected();
	
	//CPoint input[32];
	//CPoint output[32];
	//CPoint trigin[32];
	//CPoint trigout[32];
	UINT inputport_num, outputport_num, startport_num, finishport_num, internalport_num, iParamNum;
	Port* inputport[MAXPORTS];	//port object  
	Port* outputport[MAXPORTS]; //port object  
	Port* startport[MAXPORTS];					
	Port* finishport[MAXPORTS];	
	Port* internalport[MAXPORTS];	
	Parameter* iconParam[MAXPARAMS];
	Proc_function*  function[MAXFUNCS];
	CStringArray* funcName;
	CUIntArray* funcArg;

	
// PUT THIS data buffer stuff as another class
	//long bufferloc;
	//long bufferchan;
	//long inputloc[32];
	//long outputloc;
	//long option;
	//long finish;
	//long trgoutput;//flag for trigged done signal
	//long batch;
	//int location;
	
	virtual ~ConData();
	//char fielddelim;
	//char recorddelim;
	//long bitmapnum;
	//int boxtype;

};

#endif // !defined(AFX_Coninfo_H__DE3A1922_921E_11D3_A9AC_00001C21326E__INCLUDED_)
