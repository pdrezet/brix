#pragma once

#include <fstream>
using namespace std;
#include "DEP.h"
#include "LucidConstants.h"

class CDrawProgView;

class RtaTraceSupport
{
public:
	RtaTraceSupport(void);
public:
	~RtaTraceSupport(void);

	union {
		double dIn;
		char szIn[8];
		struct {
			unsigned long out1;
			unsigned short out2;
			unsigned short out3;
		}out_t;
	}m_Data;

	// methods
	void setView(CDrawProgView* _pView);
	void setRtaTrace(bool bRtaTrace);
	bool getRtaTrace();
	int createRtaConfigFile();
	void rtaTraceDefineAll();
	void rtaTraceDefineTask(CString csTaskName, int iTaskNum);
	void rtaTraceDefineTracepoint(CString csName, int iIdNum, int iDataType);
	void rtaTraceLogFlush();
	void rtaTraceLogEvent(UINT kind, UINT info, CString csTime);
	void rtaTraceLogData(UINT iKind, UINT iInfo, CString csVal, CString csTime);
	void rtaTraceLogDataFloat(UINT iKind, UINT iInfo, CString csVal, CString csTime);
	void rtaTraceLogDataString(UINT iKind, UINT iInfo, CString csVal, CString csTime);
	void rtaTraceActivate(UINT id, CString csTime);
	void rtaTraceStart(UINT id, CString csTime);
	void rtaTraceEnd(UINT id, CString csTime);
	void terminateRtaTraceProc();
	bool isRtaTraceRunning();

	// members
private:
	CDrawProgView* m_pView;
	bool m_bRtaTrace;
	int m_iRtaTraceLogIndex;
	ofstream m_RtaFile;
	// It should be possible to have an array of int rather than CString
	CString m_csaRtaTraceLog[RTA_TRACE_SIZE];

};
