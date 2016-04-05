// Coninfo.cpp: implementation of the Coninfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DrawGUI.h"
#include "Coninfo.h"
#include "../common/LucidConstants.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// global variable declared in CDrawGUIApp
//extern char workDir[4096];

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Coninfo::Coninfo(CString _projectDir)
{
	projectDir = _projectDir;
}

void Coninfo::init(	CString _description,
					CString _tag,
					CString _option,
					CRect	_rectangle,
					CString		_type,
					int _bgRed,int _bgGreen,int _bgBlue,int _fgRed,int _fgGreen,int _fgBlue,int _Bevel,int _foreground,
					int _location,
					bool _exists)
{
	
	description = _description;
	tag = _tag;
	option = _option;
	rectangle = _rectangle;
	type = _type;
	location = _location;
	exists = _exists;
	fgRed   = _fgRed;
	fgGreen = _fgGreen;
	fgBlue  = _fgBlue;
	bgRed = _bgRed;
	bgGreen = _bgGreen;
	bgBlue = _bgBlue;
	Bevel =  _Bevel;
	foreground= _foreground;

	CSize tempSize;
	if (type == "GUI_Bitmap") {

		if (description == "dummy.bmp") {

			CString installDir;
			CLabLgbBaseApp *pApp = ( (CLabLgbBaseApp *)AfxGetApp());
			pApp->GetInstallationBaseDir( installDir );

			tempSize = bitmap.Init(installDir + BMPDIR + description);

		}	else {

			tempSize = bitmap.Init(projectDir + GUIDIR + description);

		}

		rectangle=CRect(_rectangle.TopLeft().x,_rectangle.TopLeft().y,_rectangle.TopLeft().x+tempSize.cx,_rectangle.TopLeft().y+tempSize.cy);
	}

}

Coninfo::~Coninfo()
{

}

void Coninfo::Draw(CDC * theDC) {
	//CBrush bkBrush;

	//bkBrush.CreateSolidBrush(RGB(0,0,0));
	//theDC->SetBkColor(RGB(0,0,0));
	bitmap.Draw(theDC,rectangle.TopLeft());
}
