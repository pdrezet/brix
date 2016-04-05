// Coninfo.h: interface for the Coninfo class.
//
//////////////////////////////////////////////////////////////////////


#pragma once


#include "../common/bmpfile.h"

class Coninfo : public CObject  
{
public:
	Coninfo(CString _projectDir);
	void init(CString _description,
	CString _tag,
	CString _option,
	CRect	_rectangle,
	CString		_type,
	int _bgRed, int _bgGreen,int _bgBlue,int _fgRed,int _fgGreen,int _fgBlue,int _Bevel,int _foreground,
	int _location,
	bool _exists);
	void Draw(CDC * theDC);

	CString description;
	CString tag;
	CString option;
	CRect	rectangle;
	CString		type;
	int fgRed; int fgGreen;int fgBlue;int bgRed;int bgGreen;int bgBlue;int Bevel;int foreground;
	int location;
	bool exists;
	HTREEITEM treebranch;
	Bitmap bitmap;
	CString projectDir;

	virtual ~Coninfo();

};

