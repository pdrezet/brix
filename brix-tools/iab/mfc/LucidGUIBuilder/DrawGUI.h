
#pragma once

#include "Resource.h"       // main symbols
#include "../common/ProjectMetaData.h"
#include "../common/LabLgbBaseApp.h"
#include <afxadv.h>

/////////////////////////////////////////////////////////////////////////////
// CDrawGUIApp:
// See DrawGUI.cpp for the implementation of this class
//



class CDrawGUIDoc;
class LgbZOrderDlog;

class CDrawGUIApp : public CLabLgbBaseApp
{
public:

	CDrawGUIApp();

	~CDrawGUIApp();

	CMultiDocTemplate* m_pDocTemplate;

	ProjectMetaData m_ProjectMetaData;

	bool anyDocsHaveUnsavedChanges(void);

	bool processProjectClosure();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawGUIApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDrawGUIApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


//BOOL OnOpenRecentFile(UINT nID);

void OnProjectOpen();

//	CScreenTagDialog *m_pScreenTagDialog;

//	CScreenTagDialog m_ScreenTagDialog;

protected:
	void TransferOpenGuis( const int &nFilesToGo, int &filesGoneSoFar );
	void TransferGuiFile( const CString &fullHostFileName );

public:	


	afx_msg void OnTestTestdialogs();
	afx_msg void OnFileProjManagerOpen();
	afx_msg void OnTransferOptions();

	afx_msg void OnUpdateLaunchTransfer(CCmdUI *pCmdUI);

	virtual CDocument* OpenDocumentFile(LPCTSTR lpszFileName);

	void WriteMruList()
	{
		m_pRecentFileList->WriteList();
	}

	void AddMruString(const CString & str)
	{
		m_pRecentFileList->Add(str);
	}


public:

	void openActiveLayouts();



	//! The z-lean and z-clipping dialog shared between views.
	/*! 
	 The business req is that there is only one dialog for the user to manage, however many views/documents are open.
	 NB.  This member was tried as non-static, the idea being that the
	 z-order dlog for each view was popped-up / down as the view
	 concerned lost / gained focus.  However, which eveent to use to pop up/down the dialog for a given view.
	 'OnActivateFrame' was called too often, and using View::OnKillFocus / OnSetFocus 
	 failed because the view concerned DID lose focus even when you clicked on its zdlog.  Hence the user was
	 put into a circle where clicking the z dlog woul cause the respective z dlogs to be 'popped up' and hence need to be 
	 re focused upon.
	 */
	//static LgbZOrderDlog *c_pLgbZOrderDlog;
	//BOOL GetInstallationBaseDir( CString &baseDir );

	//void TransferToTarget(void);
	afx_msg void OnFileCloseAll();
public:
	afx_msg void OnHelpLgbRefManual();
public:
	afx_msg void OnFileSaveAllGuis();
public:
	afx_msg void OnHelpTutorials();
public:
	virtual void AddToRecentFileList(LPCTSTR lpszPathName);
public:
	CDrawGUIDoc *getActiveDoc(void);
protected:
	bool m_bCurrentlyTransferring;

public:
	afx_msg void OnProjectClose();
	afx_msg void OnFileLayoutmanager();
	afx_msg void OnUpdateFileLayoutManager(CCmdUI *pCmdUI);
	afx_msg void OnUpdateProjectClose(CCmdUI *pCmdUI);

};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.
