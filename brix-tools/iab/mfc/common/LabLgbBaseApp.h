#pragma once
#include "afxwin.h"
#include "LucidEnums.h"
#include "ProjectMetaData.h"
#include "../LucidApplicationBuilder/Project.h"
#include "Log.h"
#include "EHSInitParams.h"
#include "LucidEnums.h"

//class ProjectMetaData;
#include <set>

class CTgtTransProgDlog;
class CTransferErrorDlog;

class CLabLgbBaseApp :  
	public CWinApp
{

private:
	vector<pair<CString, CString> > m_vToolsPairVec;

public:

	CLabLgbBaseApp(void);
	~CLabLgbBaseApp(void);

	void CLabLgbBaseApp::InitialiseWinsock();
	void CLabLgbBaseApp::getEHSParamsFromFile();
	void setProjMetaData( ProjectMetaData *pVal ); 
	void setProject(Project *pProject);

	int getOpenDocCount(void);

	static CTgtTransProgDlog *c_pTgtTransProgressDlog;

	static CTransferErrorDlog *c_pTgtTransErrorDlog;

	void transferToTarget( const bool &updatedOnly );

	static UINT transferToTargetThread( LPVOID ptr ); 

	static UINT showTransferDialogThread( LPVOID ptr );

	void LoadImageInfFromGuiFile( const CString	&layoutName,
										std::set<CString>	&vNames);

	void LoadFontInfFromGuiFile( const CString &layoutName , std::set< CString > &vFontNames);

	void translateGuiFile(			ProjectMetaData *pProjMetaData,
							const	CString &translatableFullPath,
							const	CString &translatedFullPath );


	virtual BOOL GetInstallationBaseDir( CString &baseDir );

	void GetExecutableName(CString & execName);

	BOOL CheckExecutableFolderContextIsOk() ;

	LucidErrEnum openDocInBackground(
					   const LucidManualsEnum manualTypeEnum );

	void addProjectToMRUList(CString csProjectPathName);

	LucidErrEnum getActiveImages( ProjectMetaData *pProjMetaData, std::set< CString > &vImageFiles );

	LucidErrEnum getActiveFonts(ProjectMetaData *pProjMetaData, std::set< CString > &vFontNames );

	bool anyDocsHaveUnsavedChanges(void);

	bool startEHS(bool aboutToSendSODL);
	bool isConnectionToEHS(void);
	void openEHSInitParamsDialog(void);
	int copyTransferrablesToExports(	ProjectMetaData *pProjMetaData, 
												const bool &updatedOnly, const bool &bAppUpload );
	double MyGetFreeDiskSpaceMB(void);


private:

	static LucidErrEnum transferExportsToTarget(	ProjectMetaData *pProjMetaData, 
											//CTgtTransProgDlog *pDlog, 
											const int &nFilesX );

public:
	static bool c_bSendAllToTargetHasOccurred;
	static Log c_Log;

	virtual void writeSodl(void);
	ProjectMetaData *m_pProjMetaData;
	Project *m_pProject; // LAB only
	// ! set to true when 'all' has been sent to target at least once
	void showTransferDialog(const bool & bVisible);
	void LoadToolVec();
	CString GetToolExecPath(const CString csTool);
	EHSInitParams* pEHSInitParams;
	bool isInstalledInWindows;	// flag to distinguish between windows and wine installation
	CString csCurrentTarget;	// holds current target - local, remote or appserver
	bool isEHSLocalInstallPathKnown; // flag to indicate if EHS is installed in a known location
	LtsStatusType ltsStatusType;	// tcpip connection status

private:
	virtual BOOL InitInstance();

};
