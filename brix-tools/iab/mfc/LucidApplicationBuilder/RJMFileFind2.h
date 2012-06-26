// RJMFileFind2.h: interface for the RJMFileFind2 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RJMFILEFIND2_H__C74CA8E0_41F2_11D7_8C28_00C0F0455C98__INCLUDED_)
#define AFX_RJMFILEFIND2_H__C74CA8E0_41F2_11D7_8C28_00C0F0455C98__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class RJMFileFind2  
{
private:
	void SearchSubDir(CString DIR,CStringArray *res);
	void PhraseFilter(CString filter);
	CStringArray Acc_Exts_Left;
	CStringArray Acc_Exts_Right;
	CFileFind* m_pFinder;
	bool PassFilter(CString t);
public:
	void FindFiles(bool sub, CString dir, CString filter, CStringArray *res);
	RJMFileFind2();
	virtual ~RJMFileFind2();

};

#endif // !defined(AFX_RJMFILEFIND2_H__C74CA8E0_41F2_11D7_8C28_00C0F0455C98__INCLUDED_)
