#pragma once

#include <fstream>
using namespace std;
#include "DEP.h"
#include "LucidConstants.h"
#include "Porting_Classes/INXString.h"
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
	void rtaTraceDefineTask(INXString csTaskName, int iTaskNum);
	void rtaTraceDefineTracepoint(INXString csName, int iIdNum, int iDataType);
	void rtaTraceLogFlush();
	void rtaTraceLogEvent(UINT kind, UINT info, INXString csTime);
	void rtaTraceLogData(UINT iKind, UINT iInfo, INXString csVal, INXString csTime);
	void rtaTraceLogDataFloat(UINT iKind, UINT iInfo, INXString csVal, INXString csTime);
	void rtaTraceLogDataString(UINT iKind, UINT iInfo, INXString csVal, INXString csTime);
	void rtaTraceActivate(UINT id, INXString csTime);
	void rtaTraceStart(UINT id, INXString csTime);
	void rtaTraceEnd(UINT id, INXString csTime);
	void terminateRtaTraceProc();
	bool isRtaTraceRunning();

	// members
private:
	CDrawProgView* m_pView;
	bool m_bRtaTrace;
	int m_iRtaTraceLogIndex;
	ofstream m_RtaFile;
	// It should be possible to have an array of int rather than INXString
	INXString m_csaRtaTraceLog[RTA_TRACE_SIZE];

};
