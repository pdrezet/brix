// DrawGUIDoc.h : interface of the CDrawGUIDoc class
//
/////////////////////////////////////////////////////////////////////////////


#pragma once

#include "../common/ProjectMetaData.h"

class CDrawGUIDoc : public CDocument
{
protected: // create from serialization only
	CDrawGUIDoc();
	DECLARE_DYNCREATE(CDrawGUIDoc)



// Attributes
public:

	CString m_csHostFileNameStub;
	CString m_csFullHostFileName;
	CString m_csTargetFileName;
	CString m_csScreenTag;

	CString m_csProjectDir;
	int uptodate;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawGUIDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	//	CObArray m_cDrawableLst;
	virtual ~CDrawGUIDoc();
	void Import();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDrawGUIDoc)
	//afx_msg void OnAppExit();
	//afx_msg void OnFileNew();
	//afx_msg void OnFileOpen();
	//afx_msg void OnFileSave();
	//afx_msg void OnFileSaveAs();
	//afx_msg void OnFileClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpenFred();
	afx_msg void OnBnClickedOpenBtn();
	void InitialiseProjectMetas(ProjectMetaData *pPMD ); 
	// true if the gui file's screen tag is the same as another open doc's screen tag
	bool m_bScreenTagClashes;

	//bool m_bIsActive; //!< Indicates that this layout is the 'active' one for its widget-group

protected:
	ProjectMetaData *m_pProjectMetaData;
public:
	void setProjectMetaData(ProjectMetaData * pPMD);
	ProjectMetaData * getProjectMetaData(void);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

