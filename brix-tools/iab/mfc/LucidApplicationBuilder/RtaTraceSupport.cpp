#include "stdafx.h"
#include "RtaTraceSupport.h"
#include "GlobalFuncs_2.h"
#include "../common/General_Utilities/GlobalFuncs_3.h"
#include "DrawProgView.h"
#include "FileOperations.h"

// global variable declared in CDrawProgApp
extern char workDir[WORK_DIR_SIZE];

RtaTraceSupport::RtaTraceSupport(void)
{
	m_iRtaTraceLogIndex = 0;
	m_bRtaTrace = FALSE;
	m_pView = NULL;
}

RtaTraceSupport::~RtaTraceSupport(void)
{
}

void RtaTraceSupport::setRtaTrace(bool bRtaTrace)
{
	m_bRtaTrace = bRtaTrace;
}

bool RtaTraceSupport::getRtaTrace()
{
	return m_bRtaTrace;
}

void RtaTraceSupport::setView(CDrawProgView *pView)
{
	m_pView = pView;
}

// Method that creates a config file for RTA-TRACE
int RtaTraceSupport::createRtaConfigFile()
{
	CString csFilePath = workDir + TRACEDIR + TRACE_CONFIG_FILE;
	CString csHeaderFilePath = workDir + TRACEDIR + TRACE_HEADER_FILE;
	CString csTmp;
	CFileOperation fo;

	if (!fo.CheckPath(csHeaderFilePath)) {
		csTmp.Format("File %s does not exist", csHeaderFilePath);
		AfxMessageBox(csTmp);
		return 0;
	}

	ifstream headerFile((CString)workDir + TRACEDIR + TRACE_HEADER_FILE);
		
	m_RtaFile.open(csFilePath);
	if (!m_RtaFile.good()) {
		csTmp.Format("File %s could not be written", csFilePath);
		AfxMessageBox(csTmp);
		return 0;
	}
	
	m_RtaFile << headerFile.rdbuf();	

	headerFile.close();
	rtaTraceDefineAll();
	m_RtaFile.close();

	return 1;
}

// Method that writes out a TASK for each monitored event line and a Tracepoint for each monitored data line
void RtaTraceSupport::rtaTraceDefineAll()
{
	INXPOSITION pos;
	ConData* pBlob;
	int iTaskNum = 1;
	CString csName;

	pos = m_pView->pDEP->condata->GetHeadPosition();
	while (pos) {
		pBlob = (ConData *) (m_pView->pDEP->condata->GetNext(pos));
		if (pBlob->description == "") {
			csName = pBlob->className;
		}
		else {
			csName = pBlob->description;
		}
		for (UINT i=0; i<pBlob->startport_num; i++) {
			if (pBlob->startport[i]->line.getDbgMonitor() && pBlob->startport[i]->line.exist) {
				pBlob->startport[i]->line.setRtaTraceId(iTaskNum);
				rtaTraceDefineTask(csName + "_" + pBlob->startport[i]->description + "_" + intToString(iTaskNum), iTaskNum);
				iTaskNum++;
			}
		}
		for (UINT i=0; i<pBlob->inputport_num; i++) {
			if (pBlob->inputport[i]->line.getDbgMonitor() && pBlob->inputport[i]->line.exist) {
				pBlob->inputport[i]->line.setRtaTraceId(iTaskNum);
				rtaTraceDefineTracepoint(csName + "_" + pBlob->inputport[i]->description + "_" + intToString(iTaskNum), iTaskNum, pBlob->inputport[i]->datatype);
				iTaskNum++;
			}
		}
	}
}

void RtaTraceSupport::rtaTraceDefineTask(CString csTaskName, int iTaskNum)
{
	m_RtaFile << "TASK " << csTaskName << " {\n";
	m_RtaFile << "  vs_ID = \"" << iTaskNum << "\";\n";
	m_RtaFile << "  vs_ACTIVATIONS    = 1;\n";
	m_RtaFile << "  vs_TYPE           = \"BCC1\";\n";
	m_RtaFile << "  vs_SCHEDULE       = \"preemptable\";\n";
	m_RtaFile << "  vs_p_Pri          = \"1\";\n";
	m_RtaFile << "  vs_p_Disp         = \"1\";\n};\n\n";
}

void RtaTraceSupport::rtaTraceDefineTracepoint(CString csName, int iIdNum, int iDataType)
{
	m_RtaFile << "Tracepoint " << csName << " {\n";
	m_RtaFile << "  vs_ID = \"" << iIdNum << "\";\n";
	switch(iDataType) {
		case 0: m_RtaFile << "  vs_p_Fmt = \"%b\";\n"; break;
		case 1: m_RtaFile << "  vs_p_Fmt = \"%d\";\n"; break;		
		case 2:	m_RtaFile << "  vs_p_Fmt = \"%f\";\n"; break;
		case 3:	m_RtaFile << "  vs_p_Fmt = \"%0@%4:1E%1@%4:1E%2@%4:1E%3@%4:1E%4@%4:1E%5@%4:1E%6@%4:1E%7@%4:1E\";\n"; break;
		default: m_RtaFile << "  vs_p_Fmt = \"%d\";\n"; break;	
	}	
	m_RtaFile << "};\n\n";
}

/**
 * Flush the current trace log file to a file on the local system.
 */
void RtaTraceSupport::rtaTraceLogFlush()
{
	static UINT nCount = 0;
	char filename[100];
	UINT i;

	if (m_iRtaTraceLogIndex > 2)
	{
		FILE* pFile;
		sprintf(filename,workDir + TRACEDIR+ "tracebuffer%-d.txt",nCount++);
		pFile = fopen(filename,"w");
		fprintf(pFile,"osTraceBufferDataStart = 0x%x\n",(UINT)&m_csaRtaTraceLog);
		fprintf(pFile,"osTraceBufferWrPtr = 0x%x\n",(UINT)&m_csaRtaTraceLog);
		for (i = 0 ; (i+3) < m_iRtaTraceLogIndex; i+=4)
		{
			//fprintf(pFile,"0x%x = %u %u %u %u\n",(UINT)&m_csaRtaTraceLog, m_csaRtaTraceLog[i], m_csaRtaTraceLog[i+1],m_csaRtaTraceLog[i+2],m_csaRtaTraceLog[i+3]);
			fprintf(pFile,"0x%x = %s %s %s %s\n",(UINT)&m_csaRtaTraceLog, m_csaRtaTraceLog[i], m_csaRtaTraceLog[i+1],m_csaRtaTraceLog[i+2],m_csaRtaTraceLog[i+3]);
		}
		if (i+1 < m_iRtaTraceLogIndex)
		{
			m_csaRtaTraceLog[0] = m_csaRtaTraceLog[i];
			m_csaRtaTraceLog[1] = m_csaRtaTraceLog[i+1];
			m_iRtaTraceLogIndex = 2;
		}
		else
		{
			m_iRtaTraceLogIndex = 0;
		}
		fclose(pFile);
	}
}

/**
 * Add a trace message to the log of events traced so far.
 */
void RtaTraceSupport::rtaTraceLogEvent(UINT kind, UINT info, CString csTime)
{
	if ((m_iRtaTraceLogIndex + 2) >= RTA_TRACE_SIZE)
	{
		rtaTraceLogFlush();
	}
	m_csaRtaTraceLog[m_iRtaTraceLogIndex] = csTime;
	m_csaRtaTraceLog[m_iRtaTraceLogIndex+1] = intToString((kind << 16) | info);
	m_iRtaTraceLogIndex += 2;
}

void RtaTraceSupport::rtaTraceLogData(UINT iKind, UINT iInfo, CString csVal, CString csTime)
{
	if ((m_iRtaTraceLogIndex + 4) >= RTA_TRACE_SIZE)
	{
		rtaTraceLogFlush();
	}
	m_csaRtaTraceLog[m_iRtaTraceLogIndex] = csVal;
	// 0x70 or 112 + size of timestamp i.e. 4 bytes
	m_csaRtaTraceLog[m_iRtaTraceLogIndex+1] = "116";
	m_csaRtaTraceLog[m_iRtaTraceLogIndex+2] = csTime;
	m_csaRtaTraceLog[m_iRtaTraceLogIndex+3] = intToString((iKind << 16) | iInfo);
	m_iRtaTraceLogIndex += 4;
}

void RtaTraceSupport::rtaTraceLogDataFloat(UINT iKind, UINT iInfo, CString csVal, CString csTime)
{
	double f;
	char szTmp[128] = {'\0'};
	UINT iTmp;

	if ((m_iRtaTraceLogIndex + 6) >= RTA_TRACE_SIZE)
	{
		rtaTraceLogFlush();
	}
	f = atof(csVal);
	m_Data.dIn = f;
	sprintf(szTmp, "%u", m_Data.out_t.out1);
	m_csaRtaTraceLog[m_iRtaTraceLogIndex] = szTmp;
	// 0x70 or 112 (data record taken from RTapi.h) +  6 bytes
	iTmp = m_Data.out_t.out2 << 16 | 118;
	sprintf(szTmp, "%u", iTmp);
	m_csaRtaTraceLog[m_iRtaTraceLogIndex+1] = szTmp;
	sprintf(szTmp, "%u", m_Data.out_t.out3);
	m_csaRtaTraceLog[m_iRtaTraceLogIndex+2] = szTmp;
	// 0x70 or 112 (data record taken from RTapi.h) +  2 bytes
	m_csaRtaTraceLog[m_iRtaTraceLogIndex+3] = "114";
	m_csaRtaTraceLog[m_iRtaTraceLogIndex+4] = csTime;
	m_csaRtaTraceLog[m_iRtaTraceLogIndex+5] = intToString((iKind << 16) | iInfo);
	m_iRtaTraceLogIndex += 6;
}

void RtaTraceSupport::rtaTraceLogDataString(UINT iKind, UINT iInfo, CString csVal, CString csTime)
{
	char szStr[9] = {'\0'};
	char szTmp[128] = {'\0'};
	UINT iTmp;

	if ((m_iRtaTraceLogIndex + 6) >= RTA_TRACE_SIZE)
	{
		rtaTraceLogFlush();
	}

	// Initialise szStr to spaces
	memset(szStr, ' ', sizeof(szStr));
	int len = sprintf(szStr, "%s", csVal.Left(sizeof(szStr)));
	// Replace null character with space
	if (len < sizeof(szStr)) {
		szStr[len] = ' ';
	}
	memcpy(m_Data.szIn, szStr, 8);
	sprintf(szTmp, "%u", m_Data.out_t.out1);
	m_csaRtaTraceLog[m_iRtaTraceLogIndex] = szTmp;
	// 0x70 or 112 (data record taken from RTapi.h) +  6 bytes
	iTmp = m_Data.out_t.out2 << 16 | 118;
	sprintf(szTmp, "%u", iTmp);
	m_csaRtaTraceLog[m_iRtaTraceLogIndex+1] = szTmp;
	sprintf(szTmp, "%u", m_Data.out_t.out3);
	m_csaRtaTraceLog[m_iRtaTraceLogIndex+2] = szTmp;
	// 0x70 or 112 (data record taken from RTapi.h) +  8 bytes
	m_csaRtaTraceLog[m_iRtaTraceLogIndex+3] = "120";
	m_csaRtaTraceLog[m_iRtaTraceLogIndex+4] = csTime;
	m_csaRtaTraceLog[m_iRtaTraceLogIndex+5] = intToString((iKind << 16) | iInfo);
	m_iRtaTraceLogIndex += 6;
}

/**
 * Represents an event being fired. Equivalent to task activation in RTA-TRACE.
 */
void RtaTraceSupport::rtaTraceActivate(UINT id, CString csTime)
{
	rtaTraceLogEvent(id, 257, csTime);
}

/**
 * Represents a function starting execution. Equivalent to task activation in RTA-TRACE
 */
void RtaTraceSupport::rtaTraceStart(UINT id, CString csTime)
{
	rtaTraceLogEvent(id, 259, csTime);
}

/**
 * End of a function. Equivalent to task termination in RTA-TRACE
 */
void RtaTraceSupport::rtaTraceEnd(UINT id, CString csTime)
{
	rtaTraceLogEvent(id, 260, csTime);
}

// Method that terminates the RTA-Trace process
void RtaTraceSupport::terminateRtaTraceProc()
{
	CString csRtaFilePath = (CString)"localhost.Generic-Debugger:" + workDir + TRACEDIR + TRACE_CONFIG_FILE + " - RTA-TRACE";

	TCHAR psAppName[300];
	_tcscpy_s( psAppName, 300, _T("RTA-TRACE.exe") );	

	TCHAR psWindowTitle[300];
	_tcscpy_s( psWindowTitle, 300, _T(csRtaFilePath) );

	HANDLE hProcess;
	HWND hWnd = getTitledApplicationWindow( psAppName, psWindowTitle, hProcess);
	DWORD dwExitCode;
	::GetExitCodeProcess(hProcess, &dwExitCode);
	::TerminateProcess(hProcess, dwExitCode);
}

// Method that returns TRUE if RTA-TRACE is running, otherwise FALSE
bool RtaTraceSupport::isRtaTraceRunning()
{
	HWND hWnd = NULL;
	bool bRet;
	CString csRtaFilePath = (CString)"localhost.Generic-Debugger:" + workDir + TRACEDIR + TRACE_CONFIG_FILE + " - RTA-TRACE";

	TCHAR psAppName[300];
	_tcscpy_s( psAppName, 300, _T("RTA-TRACE.exe") );	

	TCHAR psWindowTitle[300];
	_tcscpy_s( psWindowTitle, 300, _T(csRtaFilePath) );

	HANDLE hProcess;
	if (getTitledApplicationWindow( psAppName, psWindowTitle, hProcess)) {
		bRet = TRUE;
	}
	else {
		bRet = FALSE;
	}

	return bRet;
}