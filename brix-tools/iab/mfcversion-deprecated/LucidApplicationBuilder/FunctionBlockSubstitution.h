#pragma once

#include "condat.h"
#include "DEP.h"
#include "Porting_Classes/INXString.h"

class FunctionBlockSubstitution
{
public:
	FunctionBlockSubstitution(void);
	~FunctionBlockSubstitution(void);

	// methods
	void createInitDraggee(INXString type, INXString block);
	void setDraggee(ConData* draggee);
	void setDroppee(ConData* droppee);
	ConData* getDroppee();
	void setDEP(DEP* _pDEP);

	bool isReplaceable(ConData* droppee);
	void connectDraggee();
	bool isSameParamNames();
	int copyParamValues();
	bool isParamValsModified();
	
protected:
	void reassignOtherPortNo(int iOldPortNum, int iNewPortNum, long iFBID);

private:
	// members
	ConData* pInitDraggee;
	ConData* m_Draggee;
	ConData* m_Droppee;
	DEP* pDEP;
};
