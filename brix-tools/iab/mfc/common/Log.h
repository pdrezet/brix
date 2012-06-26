#pragma once

#include "LucidConstants.h"

#include <fstream>
using namespace std;

class Log
{
public:
	Log(void);
public:
	~Log(void);

// methods
	bool Open(CString csFileName);
	bool Close();
	void WriteLogMsg(const CString csMsg);
	bool IsOpen();

// members
private:
	ofstream c_LogFile;
	bool m_bOpen;
	static FILE* c_pFile;

};
