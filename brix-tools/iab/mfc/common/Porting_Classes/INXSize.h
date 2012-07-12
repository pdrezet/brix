#ifndef _INXSIZE_H
#define _INXSIZE_H

#pragma once

// #include <wx/gdicmn.h> /* @todo */
#include <atltypes.h>
#include "INXPoint.h"

#define LEGACYINX
class INXSize: public wxSize{

#ifdef LEGACYINX
	POINT _point;
#endif
public:
	//@todo mfc's Size coordinates public variables 
		int cx, cy;
public:
	operator LPPOINT(){
		_point.x = x;
		_point.y = y;
		cx = x;
		cy = y;
		return &_point;
	};
	operator CSize(){
		CSize _csize;
		_csize.cx = x;
		_csize.cy = y;
		cx = x;
		cy = y;
		return _csize;
	};
	operator tagSIZE(){
		tagSIZE _tagSize;
		_tagSize.cx = (long)x;
		_tagSize.cy = (long)y;
		cx = x;
		cy = y;
		return _tagSize;
	};
/*	operator SIZE(){
		_size.cx = (long)cx;
		_size.cy = (long)cy;
		return _size;
	};*/
	// constructors
	INXSize(): wxSize(){
		x = 1;
		y = 1;
		cx = x;
		cy = y;
		#ifdef LEGACYINX
			_point.x = x;
			_point.y = y;
		#endif	
	};
	INXSize(int width, int height):wxSize(width ,height){
		cx = x;
		cy = y;
		#ifdef LEGACYINX
			_point.x = x;
			_point.y = y;
		#endif	
	}	
	INXSize (wxSize &sz){
		x = sz.x;
		y = sz.y;
		cx = x;
		cy = y;
		#ifdef LEGACYINX
			_point.x = x;
			_point.y = y;
		#endif	
	};
	INXSize (wxPoint &pnt){
		x = pnt.x;
		y = pnt.y;	
		cx = x;
		cy = y;
		#ifdef LEGACYINX
			_point.x = x;
			_point.y = y;
		#endif	
	};
	INXSize (CPoint &pnt){
		x = pnt.x;
		y = pnt.y;
		cx = x;
		cy = y;
		#ifdef LEGACYINX
			_point.x = x;
			_point.y = y;
		#endif	
	};
	INXSize (CSize &sz){
		x = sz.cx;
		y = sz.cy;
		cx = x;
		cy = y;
		#ifdef LEGACYINX
			_point.x = x;
			_point.y = y;
		#endif	
	};
	void operator +=(const wxPoint &pnt){
		x += pnt.x;
		y += pnt.y;
		cx = x;
		cy = y;
		#ifdef LEGACYINX
			_point.x = x;
			_point.y = y;
		#endif	
	};
	void operator +=(const wxSize &sz){
		x += sz.x;
		y += sz.y;
		cx = x;
		cy = y;
		#ifdef LEGACYINX
			_point.x = x;
			_point.y = y;
		#endif	
	};
	void operator -=(const wxPoint &pnt){
		x += pnt.x;
		y += pnt.y;
		cx = x;
		cy = y;
		#ifdef LEGACYINX
			_point.x = x;
			_point.y = y;
		#endif	
	};
	void operator -=(const wxSize &sz){
		x += sz.x;
		y += sz.y;
		cx = x;
		cy = y;
		#ifdef LEGACYINX
			_point.x = x;
			_point.y = y;
		#endif	
	};
};
#endif