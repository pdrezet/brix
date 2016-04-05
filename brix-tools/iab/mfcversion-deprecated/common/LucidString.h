#pragma once


// CLucidString

class CLucidString : public CString
{

public:
	CLucidString();
	virtual ~CLucidString();

	double GetWidthAt(int nIndex);
	CLucidString& operator=(LPCTSTR lp);
};


