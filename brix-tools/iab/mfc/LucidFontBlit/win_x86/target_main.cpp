// EHS_windows.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

#include "ehs_windows.h"
#include "ehs_main.h"
#include "console_queue.h"
#include "revision.h"
#include "console_server.h"
#include <ctype.h>
#include <atlbase.h>

/* #define SHOW_STATUSBAR */
#define MAX_LOADSTRING 100

/**
 * This specifies the subdirectory of the bin directory where EHS files
 * are to go.
 */
const TCHAR* EhsWorkingDir = _T("ehs_env");
extern "C" void EhsTgtViewport_paint(HWND hWnd, LPPAINTSTRUCT lpPS);
extern "C" HWND EhsTgtMainWindowHandle;
#ifdef SHOW_STATUSBAR
EHS_LOCAL HWND EhsTgtStatusbarHandle;
#endif

extern "C"  void EhsWindowsKbHit(long);


/**
 * Output the current state of EHS to the toolbar
 */
EHS_GLOBAL void EhsTgtStatus_state(const char*);
EHS_GLOBAL ehs_bool EhsTgtMainSetWorkingDirectory(const ehs_char* szChildDir);

/**
 * Output the an error message to the toolbar
 */
EHS_GLOBAL void EhsTgtStatus_error(const char*);

INT_PTR CALLBACK hMsgLogDialogHandler(HWND hWndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

/**
 * Set the working directory as  <Lucid Install>/bin/ehs_env
 * 
 * @param szChildDir if set, this is the child directory that we change to. 
 * @return false if unsuccessful
 */
ehs_bool EhsTgtMainSetWorkingDirectory(const ehs_char* szChildDir)
{
	LPTSTR psCmdLine = GetCommandLine();
	TCHAR *psWorkingDir;
	size_t idx;
	ehs_bool bRet = EHS_FALSE;
	ehs_bool bCurDirUsed = EHS_FALSE; /* indicates that the current directory was used and memory was allocated */

	// ignore leading " (if applicable)
	if (psCmdLine[0] == '"')
		psCmdLine++;

	// remove the executable name from the command line, leaving the path
	for (idx = _tcslen(psCmdLine)-1; (idx > 0) && (psCmdLine[idx] != '\\'); idx--)
		;

	if (idx == 0)
	{
		// there is no path, so just get the current working directory
		idx = GetCurrentDirectory(0,NULL);
		psCmdLine = (LPTSTR)malloc(idx*sizeof(TCHAR));
		GetCurrentDirectory(idx,psCmdLine);
		idx = _tcslen(psCmdLine);
		bCurDirUsed = EHS_TRUE;
	}

	psWorkingDir = (TCHAR*)malloc(sizeof(TCHAR)*(idx+3+_tcslen(EhsWorkingDir)+(szChildDir?strlen(szChildDir):0)));
	_tcsncpy(psWorkingDir, psCmdLine, idx);
	psWorkingDir[idx] = 0;
	_tcscat(psWorkingDir,_T("\\"));
	_tcscat(psWorkingDir,EhsWorkingDir);

	if (szChildDir)
	{
		_tcscat(psWorkingDir,_T("\\"));
#ifdef UNICODE

		/* find the end of the string */
		TCHAR *pEnd = psWorkingDir;
		while (*pEnd)
			pEnd++;
		
		mbstowcs(pEnd,szChildDir,strlen(szChildDir));
		pEnd += strlen(szChildDir);
		*pEnd = 0;
#else
		_tcscat(psWorkingDir,szChildDir);
#endif	
	}
#ifdef UNICODE
	if (!_wchdir(psWorkingDir)) bRet = EHS_TRUE;
#else
	if (!_chdir(psWorkingDir)) bRet = EHS_TRUE;
#endif

	if (bCurDirUsed)
	{
		free(psCmdLine);
	}
	free(psWorkingDir);
	return bRet;
}


/**
 * Contains input from the console
 */
EHS_GLOBAL EhsConsoleQueueType EhsTgtConsoleInputQueue;

/**
 * Thread function to start off the main EHS code
 */
DWORD WINAPI EhsThreadFunctionMain(LPVOID lpParam)
{
	EhsMain();

	return 0;
}

/**
 * Thread function to start off TCP/IP handling
 */
DWORD WINAPI EhsTcpIpThread(LPVOID lpParam)
{
	EhsSvcTcp_server();

	return 0;
}

//This code is from Q243953 in case you lose the article and wonder
//where this code came from.
class CLimitSingleInstance
{
protected:
  DWORD  m_dwLastError;
  HANDLE m_hMutex;

public:
  CLimitSingleInstance(TCHAR *strMutexName)
  {
    //Make sure that you use a name that is unique for this application otherwise
    //two apps may think they are the same if they are using same name for
    //3rd parm to CreateMutex
    m_hMutex = CreateMutex(NULL, FALSE, strMutexName); //do early
    m_dwLastError = GetLastError(); //save for use later...
  }
   
  ~CLimitSingleInstance() 
  {
    if (m_hMutex)  //Do not forget to close handles.
    {
       CloseHandle(m_hMutex); //Do as late as possible.
       m_hMutex = NULL; //Good habit to be in.
    }
  }

  BOOL IsAnotherInstanceRunning() 
  {
    return (ERROR_ALREADY_EXISTS == m_dwLastError);
  }
};

CLimitSingleInstance g_SingleInstanceObj(TEXT("Global\\{B5D8361C-D06B-4162-AC33-A75FF8F8B35B}"));

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
DWORD dwError;									// Last error received
HWND hMsgLogDialog = NULL;


// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);


int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	HANDLE hEhsThread; /* Handle for the EHS thread */
	HANDLE hTcpIpThread; /* Handle for the TCP/IP Server thread */
	DWORD dwEhsThreadId; /* Identifier for the EHS thread */
	DWORD dwTcpIpThreadId; /* Identifier for the TCP/IP Server thread */
	MSG msg;
	HACCEL hAccelTable;
	INITCOMMONCONTROLSEX xInitCtrls;

	/* tell everyone that we haven't started yet */
	*EhsTgtInitCompleteRef = EHS_FALSE;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_EHS_WINDOWS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Check that there are no other instances of EHS running on this machine (see artf1120)
    if (g_SingleInstanceObj.IsAnotherInstanceRunning())
       return FALSE; 


	xInitCtrls.dwSize = sizeof(xInitCtrls);
	xInitCtrls.dwICC = ICC_WIN95_CLASSES; /* required for status bar */
	InitCommonControlsEx(&xInitCtrls);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_EHS_WINDOWS));

	EhsTgtMainSetWorkingDirectory(NULL);

	hEhsThread = CreateThread(NULL /* can't inherit handle */,
		0 /* default stack size */,
		EhsThreadFunctionMain /* start routine */,
		NULL /* parameter passed to the thread */,
		0 /* creation flags - start running the thread immediately */,
		&dwEhsThreadId /* identifier for the thread */
		);

	hTcpIpThread = CreateThread(NULL /* can't inherit handle */,
		0 /* default stack size */,
		EhsTcpIpThread /* start routine */,
		NULL /* parameter passed to the thread */,
		0 /* creation flags - start running the thread immediately */,
		&dwTcpIpThreadId /* identifier for the thread */
		);

	static int count = 0;

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!IsDialogMessage(hMsgLogDialog, &msg) ||
			!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}	
		count++;
		count = count;
	}

	count++;
		if (count > 100000) 
		{
			count = 0;
		}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_EHS_WINDOWS));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+2); /* makes a black background, apparently */
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_EHS_WINDOWS);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;
   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
	   dwError = GetLastError();
      return FALSE;
   }

   EhsTgtMainWindowHandle = hWnd;
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	RECT r;
	static int statusParts[] = {300,400,-1};
	TCHAR DlgText[10000];
	static unsigned int width = 0u;

	switch (message)
	{
    case WM_CREATE:
#ifdef SHOW_STATUSBAR
		EhsTgtStatusbarHandle = CreateWindowEx( 
				0L,                              // no extended styles
				STATUSCLASSNAME,                 // status bar
				_T(""),                              // no text 
				WS_CHILD | WS_VISIBLE,  // styles
				-100, -100, 10, 10,              // x, y, cx, cy
				hWnd,                            // parent window
				(HMENU)100,                      // window ID
				hInst,                           // instance
				NULL);							// window data
		SendMessage(EhsTgtStatusbarHandle,SB_SETPARTS, 3, (LPARAM)statusParts);
		EhsConsoleQueue_push(&EhsTgtConsoleInputQueue, (ehs_uint8*)("?S\n"), 3);
#endif
		break;
	case ID_ERRORMESSAGE:
		if (!hMsgLogDialog)
		{
			hMsgLogDialog = CreateDialog(hInst, MAKEINTRESOURCE(IDD_MSGLOG), EhsTgtMainWindowHandle, hMsgLogDialogHandler);
			ShowWindow(hMsgLogDialog,SW_SHOWNORMAL);
		}
		// Code doesn't yet work - something to look at later.
//		/* if we need to make the box wider, */
//		if (width < _tcslen((LPCWSTR)wParam)*400)
//		{
//			width = _tcslen((LPCWSTR)wParam)*400;
//			SendMessage(GetDlgItem(hMsgLogDialog,1001), LB_SETHORIZONTALEXTENT, (WPARAM)width, 0);
//		}
		GetDlgItemText(hMsgLogDialog,1001,DlgText,10000);
		StrCat(DlgText,(LPCWSTR)wParam);
		SetDlgItemText(hMsgLogDialog,1001,DlgText);
		
		InvalidateRect(hWnd,NULL,TRUE);
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_SCREENSIZE_PAL720X576:
			GetWindowRect(hWnd,&r);
			SetWindowPos(hWnd,HWND_TOP,r.left,r.top,720,576,SWP_SHOWWINDOW);
			break;
		case ID_SCREENSIZE_PAL16:
			GetWindowRect(hWnd,&r);
			SetWindowPos(hWnd,HWND_TOP,r.left,r.top,1024,576,SWP_SHOWWINDOW);
			break;
		case ID_SCREENSIZE_NTSC720X486:
			GetWindowRect(hWnd,&r);
			SetWindowPos(hWnd,HWND_TOP,r.left,r.top,720,486,SWP_SHOWWINDOW);
			break;
		case ID_SCREENSIZE_HD720P:
			GetWindowRect(hWnd,&r);
			SetWindowPos(hWnd,HWND_TOP,r.left,r.top,1280,720,SWP_SHOWWINDOW);
			break;
		case ID_SCREENSIZE_HD1080P:
			GetWindowRect(hWnd,&r);
			SetWindowPos(hWnd,HWND_TOP,r.left,r.top,1920,1080,SWP_SHOWWINDOW);
			break;
		case ID_SCREENSIZE_800X600:
			GetWindowRect(hWnd,&r);
			SetWindowPos(hWnd,HWND_TOP,r.left,r.top,800,600,SWP_SHOWWINDOW);
			break;
		case ID_SCREENSIZE_1024X768:
			GetWindowRect(hWnd,&r);
			SetWindowPos(hWnd,HWND_TOP,r.left,r.top,1024,800,SWP_SHOWWINDOW);
			break;
		case ID_COMMANDS_RUN:
			/* Note: contention with EhsTcpipThread is a possible (but remote) source of problems here */
			EhsConsoleQueue_push(&EhsTgtConsoleInputQueue, (ehs_uint8*)"r\n", 2);
			break;
		case ID_COMMANDS_STEP:
			/* Note: contention with EhsTcpipThread is a possible (but remote) source of problems here */
			EhsConsoleQueue_push(&EhsTgtConsoleInputQueue, (ehs_uint8*)"s\n", 2);
			break;
		case ID_COMMANDS_PAUSE:
			/* Note: contention with EhsTcpipThread is a possible (but remote) source of problems here */
			EhsConsoleQueue_push(&EhsTgtConsoleInputQueue, (ehs_uint8*)"p\n", 2);
			break;
		case ID_DEBUG_ON:
			/* Note: contention with EhsTcpipThread is a possible (but remote) source of problems here */
			EhsConsoleQueue_push(&EhsTgtConsoleInputQueue, (ehs_uint8*)"=+\n", 3);
			break;
		case ID_DEBUG_OFF:
			/* Note: contention with EhsTcpipThread is a possible (but remote) source of problems here */
			EhsConsoleQueue_push(&EhsTgtConsoleInputQueue, (ehs_uint8*)"=-\n", 3);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_ERASEBKGND:
		/* Don't do anything with this message - this helps to avoid 
		   flicker (which is caused by frequent erase followed by paint */
		return (LRESULT)1;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EhsTgtViewport_paint(hWnd,&ps);
		EndPaint(hWnd,&ps);

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		EhsWindowsKbHit((ehs_sint32)wParam);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		SetDlgItemText(hDlg,IDC_VERSION_ID,_T(EHS_REVISION_ID));
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void EhsTgtStatus_send(const char*szText, ehs_uint16 nStatusSection)
{
#ifdef UNICODE
#define BUFFSIZE 100
	TCHAR *buff = (TCHAR*)malloc(sizeof(TCHAR)*(strlen(szText)+3));
	mbstowcs(buff,szText,strlen(szText)+1);
#ifdef SHOW_STATUSBAR
	SendMessageA(     // returns LRESULT in lResult
        EhsTgtStatusbarHandle,        // handle to destination control
        SB_SETTEXT,         // message ID
		nStatusSection,
		(LPARAM)buff);
		//(LPARAM)szText);
#endif
	if (nStatusSection == 0)
	{
		StrCat(buff,_T("\r\n"));
		SendMessage(EhsTgtMainWindowHandle, ID_ERRORMESSAGE,(WPARAM)buff,0);
	}
#else
#ifdef SHOW_STATUSBAR

	SendMessage(     // returns LRESULT in lResult
        EhsTgtStatusbarHandle,        // handle to destination control
        SB_SETTEXT,         // message ID
		nStatusSection,
		//(LPARAM)buff);
		(LPARAM)szText);
#endif
	free(buff);
#endif /* UNICODE */
}

/**
 * Output the current state of EHS to the toolbar
 */
void EhsTgtStatus_state(const char*szState)
{
	EhsTgtStatus_send(szState,1);
}

/**
 * Dialog message handler
 */
INT_PTR CALLBACK hMsgLogDialogHandler(HWND hWndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	INT_PTR ret  = FALSE;
	switch(uMsg)
	{
	case WM_INITDIALOG:
		ret = TRUE;
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		case IDCANCEL:
			DestroyWindow(hWndDlg);
			hMsgLogDialog = NULL;
			ret = TRUE;
			break;
		}
	}


	return ret;
}

/**
 * Output the an error message to the toolbar
 */
void EhsTgtStatus_error(const char*szError)
{
	EhsTgtStatus_send(szError,0);
}

