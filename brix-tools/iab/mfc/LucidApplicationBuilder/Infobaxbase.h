// Infobaxbase.h: interface for the Infobaxbase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFOBAXBASE_H__94ADA2C3_D500_11D3_A9AD_00001C21326E__INCLUDED_)
#define AFX_INFOBAXBASE_H__94ADA2C3_D500_11D3_A9AD_00001C21326E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#include "Porting_Classes/INXString.h"
/*

Note: DeleteMe I am a copy of IconData

  */
class Infobaxbase //: public CDialog 
{
protected:
	Infobaxbase();
	virtual ~Infobaxbase();
	int deleteme;
	int 	momentary;
	int 	constant;
	int		negedge;
	int		plusedge;
	int wantoption;
	INXString	recorddelim;
	INXString	fielddelim;
	INXString	option2;
	INXString	option1;
	INXString	description;
	INXString	fixedinfo;

//virtual int DoModal();

};


#endif // !defined(AFX_INFOBAXBASE_H__94ADA2C3_D500_11D3_A9AD_00001C21326E__INCLUDED_)
