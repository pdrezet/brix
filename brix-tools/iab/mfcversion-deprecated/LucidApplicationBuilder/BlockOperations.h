// BlockOperations.h: interface for the BlockOperations class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BLOCKOPERATIONS_H__944A5580_E350_4C4A_9FBE_B36C8E3B70D7__INCLUDED_)
#define AFX_BLOCKOPERATIONS_H__944A5580_E350_4C4A_9FBE_B36C8E3B70D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Porting_Classes/INXString.h"

class BlockOperations  
{
public:
	BlockOperations();
	virtual ~BlockOperations();
	
	// Methods
	void AssignIconLineEndPoints(INXObjList* temp);
	ConData* GetBlockIconFromID(long id, INXObjList* encapsulated);
	INXObjList* LoadBlock(INXString Info);
	INXObjList* BlockOperations::NewBlock(INXString Info);
	int SaveBlock(INXString Info, INXObjList* encapsulated);
	void DeleteBlock(INXObjList* encapsulated);
};

#endif // !defined(AFX_BLOCKOPERATIONS_H__944A5580_E350_4C4A_9FBE_B36C8E3B70D7__INCLUDED_)
