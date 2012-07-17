// RJMFileFind2.h: interface for the RJMFileFind2 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RJMFILEFIND2_H__C74CA8E0_41F2_11D7_8C28_00C0F0455C98__INCLUDED_)
#define AFX_RJMFILEFIND2_H__C74CA8E0_41F2_11D7_8C28_00C0F0455C98__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Porting_Classes/INXString.h"
#include "Porting_Classes/INXObjArray.h"
class RJMFileFind2  
{
private:
	void SearchSubDir(INXString DIR,INXObjArray<INXString> *res);
	void PhraseFilter(INXString filter);
	INXObjArray<INXString> Acc_Exts_Left;
	INXObjArray<INXString> Acc_Exts_Right;
	CFileFind* m_pFinder;
	bool PassFilter(INXString t);
public:
	void FindFiles(bool sub, INXString dir, INXString filter, INXObjArray<INXString> *res);
	RJMFileFind2();
	virtual ~RJMFileFind2();

};

#endif // !defined(AFX_RJMFILEFIND2_H__C74CA8E0_41F2_11D7_8C28_00C0F0455C98__INCLUDED_)
