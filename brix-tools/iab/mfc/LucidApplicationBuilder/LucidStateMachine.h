// LucidStateMachine.h: interface for the CLucidStateMachine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LUCIDSTATEMACHINE_H__0F861F1D_E89C_41AC_AFC3_843870FE65F5__INCLUDED_)
#define AFX_LUCIDSTATEMACHINE_H__0F861F1D_E89C_41AC_AFC3_843870FE65F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DrawProgView.h"


class CLucidStateMachine  
{
public:
	static bool placeComponents(CPoint point, DEP* pDEP, Project* pProject);
	static void AddConditionLogicPortsBelow(ConData* pIconData, DEP* pDEP, Project* pProject);
	static void AddActionPortsBelow(ConData* pIconData, DEP* pDEP, Project* pProject);
	CLucidStateMachine();
	virtual ~CLucidStateMachine();

};

#endif // !defined(AFX_LUCIDSTATEMACHINE_H__0F861F1D_E89C_41AC_AFC3_843870FE65F5__INCLUDED_)
