// RJMFileFind2.cpp: implementation of the RJMFileFind2 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "bob_photo.h"
#include "RJMFileFind2.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

RJMFileFind2::RJMFileFind2()
{
	m_pFinder = NULL;
}

RJMFileFind2::~RJMFileFind2()
{
	if (m_pFinder) delete m_pFinder;
}

void RJMFileFind2::FindFiles(bool sub, INXString dir, INXString filter, INXObjArray<INXString> *res)
{
	//Searches dir for files and loads into res array
	PhraseFilter(filter);
	res->RemoveAll();

	if (m_pFinder) delete m_pFinder;
	m_pFinder = new CFileFind;
	
	if (!(dir.Right(1) == _T("\\"))) {
		dir = dir + _T("\\");
	};

	BOOL bWorking = m_pFinder->FindFile(dir + _T("*.*"));
	INXString t;
	bool gosub = false;
	while (bWorking) {
		bWorking = m_pFinder->FindNextFile();
		t = m_pFinder->GetFileName();
		if (m_pFinder->IsDirectory()) { 
			gosub = true;
			if (t == _T(".")) gosub = false;
			if (t == _T("..")) gosub = false;
	
			if (sub) if (gosub) {
				SearchSubDir(dir + (INXString)m_pFinder->GetFileName(),res);
			};
		} else {
			if (PassFilter(t)) {
				t = dir + t;
				res->Add(t);
			};
		};
	}

}

bool RJMFileFind2::PassFilter(INXString t)
{
	//checks if t passes the filter

	int c = t.Find(_T("."),0);
	INXString start = t.Left(c);
	INXString end = t.Right(t.GetLength() - (c+1));
	start.MakeUpper();
	end.MakeUpper();
	INXString l;
	INXString r;
	for (c=0;c<Acc_Exts_Left.GetSize();c++) {
		l = Acc_Exts_Left.GetAt(c);
		r = Acc_Exts_Right.GetAt(c);
		if (l == _T("*")) {
			if (r == _T("*")) return true;
			//only right matters
			if (r == end) return true;
		} else {
			//left matters
			if (l == start) {
				if (r == _T("*")) {
					//only left matters
					return true;
				} else {
					//they both matter
					if (r == start) return true;
				};
			};
		};
	};
	return false;
}

void RJMFileFind2::PhraseFilter(INXString filter)
{
	Acc_Exts_Left.RemoveAll();
	Acc_Exts_Right.RemoveAll();
	//Split string on ";"
	INXString t;
	int c = filter.Find(_T(";"),0);
	while (!(c ==-1)) {  //while
		//valid c value	
		t = filter.Left(c);
		filter = filter.Right(filter.GetLength() - (c+1));		
		Acc_Exts_Left.Add(t);
		c = filter.Find(_T(";"),0);	
	};
	Acc_Exts_Left.Add(filter);
	Acc_Exts_Right.SetSize(Acc_Exts_Left.GetSize());
	int d;
	INXString l = _T("");
	INXString r = _T("");
	for (c=0;c<Acc_Exts_Left.GetSize();c++) {
		t = Acc_Exts_Left.GetAt(c);
		d = t.Find(_T("."),0);
		l = t.Left(d);
		r = t.Right(t.GetLength() - (d+1));
		l.MakeUpper();
		r.MakeUpper();
		Acc_Exts_Left.SetAt(c,l);
		Acc_Exts_Right.SetAt(c,r);
	};
}

void RJMFileFind2::SearchSubDir(INXString DIR, INXObjArray<INXString> *res)
{
//	TRACE(_T("SearchSubDir start DIR:"));
//	TRACE(DIR);
//	TRACE(_T(":\n"));

	DIR += _T("\\");
	CFileFind finder;
	BOOL bWorking = finder.FindFile(DIR + _T("*.*"));
	INXString t;
	bool gosub = false;
	while (bWorking) {
		bWorking = finder.FindNextFile();
		t = finder.GetFileName();
		if (finder.IsDirectory()) { 
			gosub = true;
			if (t == _T(".")) gosub = false;
			if (t == _T("..")) gosub = false;

			if (gosub) SearchSubDir(DIR + (INXString)finder.GetFileName(),res);
		} else {
//			TRACE(_T("File Found:"));
//			TRACE(t);
//			TRACE(_T(":\t"));
			if (PassFilter(t)) {
				t = DIR + t;
				res->Add(t);
//				TRACE(_T("PASS"));
			};
//			TRACE(_T("\n"));
		};
	}

//	TRACE(_T("SearchSubDir end\n"));

}
