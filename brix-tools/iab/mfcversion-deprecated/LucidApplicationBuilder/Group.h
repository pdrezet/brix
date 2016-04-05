// Group.h: interface for the Group class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GROUP_H__6461E10D_51B7_4B97_97D1_9795C205187D__INCLUDED_)
#define AFX_GROUP_H__6461E10D_51B7_4B97_97D1_9795C205187D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Porting_Classes/INXString.h"

class Group  
{
public:
	Group();
	virtual ~Group();
	
	// Attributes
	UINT ID;
	INXString Name;
	UINT Period;
	UINT Alloc;
};

#endif // !defined(AFX_GROUP_H__6461E10D_51B7_4B97_97D1_9795C205187D__INCLUDED_)
