

#include <time.h>   // for nanosleep

void sleep_ms(int milliseconds) // cross-platform sleep function
{

    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
}

// check for switch: / or -
//inline bool isswitch(TCHAR c) { return c==L'/' || c==L'-'; }

#if 0
//////////////////
// Main entry point
//
HWND getTitledApplicationWindow( TCHAR* psAppName, TCHAR* psWindowTitle, HANDLE &hProcess )
{
	
	int count=0;
	BOOL bFirstModule = TRUE;
	CProcessIterator itp;
	for (DWORD pid=itp.First(); pid; pid=itp.Next()) {
		// Note: first module in CProcessModuleIterator is EXE for this process
		//
		TCHAR modname[_MAX_PATH];
		CProcessModuleIterator itm(pid);
		HMODULE hModule = itm.First(); // .EXE
		if (hModule) {
			GetModuleBaseName(itm.GetProcessHandle(),
				hModule, modname, _MAX_PATH);

			// Iterate over all top-level windows in process
			//
			BOOL bFirstWindow = TRUE;
			CMainWindowIterator itw(pid);
			for (HWND hwnd = itw.First(); hwnd; hwnd=itw.Next()) {

				if (bFirstWindow) {

					bFirstWindow = FALSE;
					char classname[256],title[256];
					GetClassName(hwnd,classname,sizeof(classname));
					GetWindowText(hwnd,title,sizeof(title));
					if(strstr( modname, psAppName) == modname) {
						if(strstr( title, psWindowTitle) == title) {
							hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
							return hwnd;
						}
					}
				} 
			}
			bFirstWindow || count++;
		}
	}
	return NULL;
}
#endif



