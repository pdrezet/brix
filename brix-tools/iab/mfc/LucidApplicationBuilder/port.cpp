// port.cpp: implementation of the port class.
// Parent is the class ConDat (Icon Data)
// Ports are the positions of Icon ports, each inpout type port can have a line child 
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "DrawProg.h"
#include "port.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// global variable declared in CDrawProgApp
extern char workDir[WORK_DIR_SIZE];

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Port::Port(int _userdefined)
{
	P.x=0;
	P.y=0;
	porttype = -1;
	datatype = -1;
	portNum = -1;
	description = "";
	connected=0;
	location =0;
	lineID = -1;
	funcName = new INXObjArray<INXString>;
	funcArg = new CUIntArray;
	xportConnected = 0;
	xportID = -1;
	initialise = 0;
	atomicFlag = 1;
	mandatoryFlag = 0;
	tag = "";
	groupID = 1;
	bPortVertical = 0;
	line.valueRect = INXRect(P.x-(20*5),P.y,P.x,P.y+2);
	userdefined = _userdefined;
}

/*
 @todo need New Constructor - new spec for cdf means that funcArg is not known at time of port creation
 and is removed from the constructor for this reason

Port::Port(INXPoint _P, UINT _portNum, int _dataType, int _portType, INXString _description, INXObjArray<INXString>* _funcName, CUIntArray* _tempFuncArg, int _atomicFlag, bool bVerticalIn, int _userdefined)
{
	Port(_P, _portNum, _dataType, _portType, _description, _funcName, NULL, _atomicFlag, bVerticalIn, _userdefined);
	tempFuncArg = _tempFuncArg;
}
*/
/*
 Deprecated Constructor - new spec for cdf means that funcArg is not known at time of port creation
 and is removed from the constructor for this reason
*/
Port::Port(INXPoint _P, UINT _portNum, int _dataType, int _portType, INXString _description, INXObjArray<INXString>* _funcName, CUIntArray* _funcArg, int _atomicFlag, bool bVerticalIn, int _userdefined, int _mandatoryFlag)
{
	
	P.x=_P.x;
	P.y=_P.y;
	porttype = _portType;
	datatype = _dataType;
	portNum = _portNum;
	description = _description;
	//funcName = new INXObjArray<INXString>;
	//funcArg = new CUIntArray;
	funcName = _funcName;
	funcArg = _funcArg;
	connected=0;
	location=0;
	lineID = -1;
	line.setPortType(porttype);
	line.dataType = _dataType;
	xportConnected = 0;
	xportID = -1;
	initialise = 0;
	atomicFlag = _atomicFlag;
	mandatoryFlag = _mandatoryFlag;
	tag = "";
	groupID = 1;
	bPortVertical = bVerticalIn;
	line.valueRect = INXRect(P.x-(20*5),P.y,P.x,P.y+2);
	userdefined = _userdefined;
	init();
}



Port::Port(UINT _portNum, int _portType, INXObjArray<INXString>* _funcName, CUIntArray* _funcArg, int _atomicFlag)
{
	P.x=0;
	P.y=0;
	porttype = _portType;
	datatype = -1;
	portNum = _portNum;
	description = "";
	//funcName = new INXObjArray<INXString>;
	funcName = _funcName;
	funcArg = _funcArg;
	connected=0;
	location =0;
	lineID = -1;
	line.setPortType(porttype);
	xportConnected = 0;
	xportID = -1;
	initialise = 0;
	atomicFlag = _atomicFlag;
	tag = "";
	groupID = 1;
	bPortVertical = 0;
	line.valueRect = INXRect(P.x-(20*5),P.y,P.x,P.y+2);
	userdefined = 0;
	mandatoryFlag = false;
}

Port::~Port()
{
	delete funcName;
	delete funcArg;
}



void Port::init() {
	INXString bitmappath;
	INXString csOrientation = "";

	if(bPortVertical)
	{	csOrientation = "VERT";
	}

	//select the bitmap according to porttype and datatype
	if (porttype == STARTPORT || porttype == FINISHPORT) {
		if (initialise) {
			bitmappath = workDir + BMPDIR + csOrientation +"INITPORT.bmp";
		}
		else {
			bitmappath = workDir + BMPDIR + csOrientation +"EVENTPORT.bmp";
		}
	}
	else if (porttype == INPUTPORT || porttype == OUTPUTPORT) {
		switch(datatype) {
			case 0:
				bitmappath = workDir + BMPDIR + csOrientation + "BOOLPORT.bmp"; break;
			case 1:
				bitmappath = workDir + BMPDIR + csOrientation + "INTPORT.bmp"; break;		
			case 2:
				bitmappath = workDir + BMPDIR + csOrientation + "REALPORT.bmp"; break;
			case 3:
				bitmappath = workDir + BMPDIR + csOrientation + "STRINGPORT.bmp"; break;
			default:
				AfxMessageBox("Unrecognised Port Type");
				return;
		}
	}

	// read in bitmap for port
	bitmapSize=bitmap.Init(bitmappath);

	// read in bitmap for port
	bitmHighSize=bitmHighlight.Init(workDir + BMPDIR + csOrientation +"HIGHLIGHTPORT.bmp");

	// position the bitmap
	rectangle = GetPortBitmapArea();
}

int Port::addLine(INXPoint* point,long int othericon,int otherPortNum, int otherPortType) {
	//PP: Colour in here
	//porttype=porttype|
	line.SetEndPoints(point,&P,othericon,otherPortNum,otherPortType);
	connected=1;
	return 0;

}

int Port::RemoveLine() {
	if (connected) line.Delete();
	connected=0;
return 0;

}

int Port::DisconnectLine() {
	if (connected) line.Disconnect();
	connected=0;
return 0;

}

void Port::Draw(CDC* theDC) {	
	Draw(theDC, false, 0);
}

void Port::Draw(CDC* theDC, bool _onlyDrawAnim, int _toggleAnim) {	
	if (_onlyDrawAnim && ((connected == 1) || !mandatoryFlag)) return;

	int descLen, dbgValLen, tagLen;
	double nStrOffset=0.0;
	COLORREF magenta = RGB(255,0,255);

	COLORREF red = RGB(255,83,83);
	COLORREF green = RGB(0,255,0);
	COLORREF blue = RGB(100,177,255);
	COLORREF yellow = RGB(255,255,0);
	INXString cropDescript;
	CLucidString clsTag, clsCropDescript;

	if (!_onlyDrawAnim) {
		descLen = description.GetLength();
		dbgValLen = line.dbgValue.GetLength();
		// define font for port text
		LOGFONT logFont;
		// pitch size is 7
		if (theDC->IsPrinting()) {
			logFont.lfHeight = -MulDiv(7, theDC->GetDeviceCaps(LOGPIXELSY), 432);
		}
		else {
			logFont.lfHeight = -MulDiv(7, theDC->GetDeviceCaps(LOGPIXELSY), 72);
		}
		logFont.lfWidth = 0;
		logFont.lfEscapement = 0;
		logFont.lfOrientation = 0;
		logFont.lfWeight = FW_NORMAL;
		logFont.lfItalic = 0;
		logFont.lfUnderline = 0;
		logFont.lfStrikeOut = 0;
		logFont.lfCharSet = ANSI_CHARSET;
		logFont.lfOutPrecision = OUT_DEFAULT_PRECIS;
		logFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
		logFont.lfQuality = PROOF_QUALITY;
		logFont.lfPitchAndFamily = VARIABLE_PITCH | FF_ROMAN;
		strcpy_s(logFont.lfFaceName, "Arial");
		CFont font;
		font.CreateFontIndirect(&logFont);
		CFont* oldFont = theDC->SelectObject(&font);	

		// the negate the ycoords of the rectangle for MM_LOENGLISH mapping mode when printing
		if (theDC->IsPrinting()) {
			rectangle = INXRect(rectangle.TopLeft().x, -rectangle.TopLeft().y,
						rectangle.BottomRight().x, -rectangle.BottomRight().y);
		}

		theDC->SetBkMode(TRANSPARENT);
		if(bPortVertical==false)
		{
			// limit port names to 6 charaters for userdefined blocks
			if (userdefined) {
				cropDescript = description.Left(6);
				// Maximum length is 6
				if (descLen > 6) {
					descLen = 6;
				}
			}
			else {
				cropDescript = description.Left(10);
				// Maximum length is 10
				if (descLen > 10) {
					descLen = 10;
				}
			}
			clsCropDescript = cropDescript;
			for (int i=0; i<descLen; i++) {
				nStrOffset = nStrOffset + clsCropDescript.GetWidthAt(i);
			}

			// Add port description to icon
			if (theDC->IsPrinting()) {
				if (porttype == STARTPORT || porttype == INPUTPORT) {
					theDC->TextOut(P.x+8,-P.y+7,(CString &)cropDescript);
				}
				else if (porttype == FINISHPORT || porttype == OUTPUTPORT) {
					theDC->TextOut(P.x-6-((int)nStrOffset), P.y+7, (CString&)cropDescript);
				}
			}
			else {
				if (porttype == STARTPORT || porttype == INPUTPORT) {
					theDC->TextOut(P.x+8,P.y-7,(CString)cropDescript);
				}
				else if (porttype == FINISHPORT || porttype == OUTPUTPORT) {
					theDC->TextOut(P.x-6-((int)nStrOffset), P.y-7, (CString&)cropDescript);
				}
			}
		}
		// write out debug values
		if (porttype == INPUTPORT && line.getDbgMonitor()) {
			theDC->SetBkMode(OPAQUE);
			theDC->SetBkColor(RGB(225,225,0));
			theDC->TextOut(P.x-(dbgValLen*5),P.y+2,(CString&)line.dbgValue);
			theDC->SetBkColor(RGB(255,255,255));
		}
		
		// if the port is tagged then write out tag and don't draw line
		if (tag != "") {
			theDC->SetBkMode(OPAQUE);
			tagLen = tag.GetLength();
			// set background colour according to datatype
			if (porttype == INPUTPORT || porttype == OUTPUTPORT) {
				switch (datatype) {
				case 0 : theDC->SetBkColor(yellow); break;
				case 1 : theDC->SetBkColor(blue); break;
				case 2 : theDC->SetBkColor(green); break;
				case 3 : theDC->SetBkColor(red); break;
				}
			}
			
			// write text /
			clsTag = tag;
			// String offset is 7 for uppercase letters and 5 for lowercase
			nStrOffset = 0;
			for (int i=0; i<tagLen; i++) {
				nStrOffset = nStrOffset + clsTag.GetWidthAt(i);
			}
			if (tagLen < 5) {
				nStrOffset+=2;
			}
			if (theDC->IsPrinting()) {
				if (porttype == STARTPORT || porttype == INPUTPORT) {
					theDC->TextOut(P.x-((int)nStrOffset), -1 * (P.y+5), (CString&)tag);
				}
				else if (porttype == FINISHPORT || porttype == OUTPUTPORT) {
					theDC->TextOut(P.x+3, -1 * (P.y+5), (CString&)tag);
				}
			} else {
				if (porttype == STARTPORT || porttype == INPUTPORT) {
				theDC->TextOut(P.x-((int)nStrOffset), P.y-5, (CString&)tag);
				}
				else if (porttype == FINISHPORT || porttype == OUTPUTPORT) {
					theDC->TextOut(P.x+3, P.y-5, (CString&)tag);
				}
			}			
			theDC->SetBkColor(RGB(255,255,255));
		}
//		else {
//			line.Draw(theDC);
//		}		
	}

	// highlight unconnected, mandatory ports when flagg is set to only draw animations
	// but only on every other trigger of the timer, so it flashes on and off
	if (_onlyDrawAnim && (_toggleAnim == 1)){
		// draw the triangles last to override any messy labelling!
		bitmHighlight.Draw(theDC,(INXPoint)(INXPoint)rectangle.TopLeft()); //@ typecast to INXPoint then INXPoint
	} else {
		// draw the triangles last to override any messy labelling!
		bitmap.Draw(theDC,(INXPoint)rectangle.TopLeft());
	}
	// reset the ycoords of the rectangle
	if (theDC->IsPrinting()) {
		rectangle = INXRect(rectangle.TopLeft().x, -rectangle.TopLeft().y,
					rectangle.BottomRight().x, -rectangle.BottomRight().y);
	}
}

int Port::Move(INXPoint point) {
	P = (wxPoint)P - (wxPoint)point;
	// renew the port position
	if (porttype == STARTPORT || porttype == INPUTPORT) {
//		rectangle=INXRect(P.x-5,P.y,P.x+bitmapSize.cx,P.y+bitmapSize.cy-5);
		if (line.exist) {
			line.Move(point);
		}
	}
//	else if (porttype == FINISHPORT || porttype == OUTPUTPORT) {
//		rectangle=INXRect(P.x-5,P.y-5,P.x+bitmapSize.cx-5,P.y+bitmapSize.cy-5);
//	} 


	
	rectangle = GetPortBitmapArea();
return 0;


}

void Port::setLineID(long int _lineID) {
	lineID = _lineID;
}

int Port::OnPort(INXPoint point) {
	int xdist,ydist;
	xdist=labs(point.x-P.x);
	ydist=labs(point.y-P.y);
	if ( xdist < CLOSENESS && ydist < CLOSENESS) {
		return  porttype;   //0 input, 1 output, 2 Trig input, 3 Trig output
	}
	
return -1;
}

void Port::Save(ostream * file) {
	
	*file <<endl<< porttype << "\t"<< datatype << "\t"<< P.x << "\t"<< P.y << "\t" << portNum << "\t" << initialise << "\t" << atomicFlag<< "\t" << "mandatory= " << mandatoryFlag<< "\t"  << bPortVertical << "\t" << groupID << "\n";


	*file << (CString)description << endl;
	*file << (CString)tag << endl;
	for (int i=0; i<funcName->GetSize(); i++) {
		*file << (CString)funcName->GetAt(i) << "\t" << funcArg->GetAt(i) << "\t";
	}
	*file << "EndOfFunc";
	*file << endl;
	line.Save(file);
}

void Port::Load(istream * file) {
	char *cTemp = NULL;
	int len;
	char temp[255];
	char temp2[255];
	int tmpInt;
	int tmpIntVertical =0;
	int i = 0;
	long pos;
	char testString[255];
	char mandatoryString[] = "mandatory=";

   *file >> porttype;
   *file >> datatype; 
   *file >> P.x;
   *file >> P.y;
   *file >> portNum;
   *file >> initialise;
   *file >> atomicFlag;

    // note - added mandatory flag to component spec. This means this flag may not be present when loading older DEPs
	// so if no mandatory flag info (indicated by presence of "mandatory=" string), 
    // reset get pointer to before this read and carry on as if nothing happened
	pos = file->tellg();
    *file >> testString;
    if (strcmp (testString, mandatoryString) == 0) {
		*file >> mandatoryFlag;
    } else {
		mandatoryFlag = 0;
		file->seekg(pos, SEEK_SET);
    }

   *file >> tmpIntVertical;
   *file >> groupID;


   bPortVertical =(tmpIntVertical == 1);

   // cannot use >> operator to retrieve description as it may contain whitespaces
   // Use getline. However need to ignore end of line character
	file->ignore(1,'\n');
	file->getline(temp,254);

	// strip out any text in square brackets - this is a unique identifier that used by ICB but not needed in IAB
	//note - we are cheating, just assuming that square brackets are at end of string and only keeping chars before '['
	cTemp = strstr(temp,"[");
	if (cTemp) {
		len = strlen(cTemp);
		temp[strlen(temp) - len] = '\0';
	}

	description = temp;
	file->getline(temp,254);
	tag = temp; //tag is Cstring so this is OK.
	
	// load function name and argument
	*file >> temp;
	strcpy(temp2,temp);
	while (strcmp(temp,"EndOfFunc")) {
		*file >> tmpInt;
		funcName->SetAtGrow(i, temp);
		funcArg->SetAtGrow(i, tmpInt);
		i++;
		*file >> temp;
	}
	// read in bitmap for port once the port data has been loaded
	if (porttype != INTERNALPORT) {
		init();
	}

	line.Load(file);
	// set datatype in line
	line.dataType = datatype;
}

INXRect Port::GetPortBitmapArea()
{
	INXRect r;

	if( bPortVertical == TRUE )
	{
		if (porttype == STARTPORT || porttype == INPUTPORT) {
			r=INXRect(P.x-5,P.y,P.x+bitmapSize.cx,P.y+bitmapSize.cy);
		}
		else if (porttype == FINISHPORT || porttype == OUTPUTPORT) 	{
			r=INXRect(P.x-5,P.y-5,P.x+bitmapSize.cx,P.y+bitmapSize.cy);
		}	

	}
	else if( bPortVertical == FALSE )
	{
		if (porttype == STARTPORT || porttype == INPUTPORT) {
			r=INXRect(P.x,P.y-5,P.x+bitmapSize.cx,P.y+bitmapSize.cy);
		}
		else if (porttype == FINISHPORT || porttype == OUTPUTPORT) 	{
			r=INXRect(P.x-5,P.y-5,P.x+bitmapSize.cx,P.y+bitmapSize.cy);
		}	
	}

	return r;
}
