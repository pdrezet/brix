// DrawProgDoc.h : interface of the CDrawProgDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWPROGDOC_H__EC34D26C_981B_11D3_A9AD_00001C21326E__INCLUDED_)
#define AFX_DRAWPROGDOC_H__EC34D26C_981B_11D3_A9AD_00001C21326E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "MainFrm.h"
#include "condat.h"
//#include "ProjectChooser.h"
#include "PathDialog.h"
//#include "Project.h"
#include "DEP.h"

/*

Handles the GUI selection of reading and writing files - The actual objects that are read or written to files
are all contained in the associated CDrawProgView object.

*/
class CDrawProgDoc : public CDocument
{
protected: // create from serialization only
	CDrawProgDoc();
	DECLARE_DYNCREATE(CDrawProgDoc)

// Attributes
public:
	CMainFrame* pFrame;
	bool closing;
	Project* pProject;
	DEP* pDEP;

// Operations
	void SaveUserDefDoc();

public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawProgDoc)
	public:
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	protected:
	virtual BOOL SaveModified();
	//}}AFX_VIRTUAL
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);

// Implementation
public:
	virtual ~CDrawProgDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDrawProgDoc)
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
	afx_msg void OnUpdateFileSaveAs(CCmdUI* pCmdUI);
	afx_msg void OnUpdateNewsubsystem(CCmdUI* pCmdUI);
	afx_msg void OnNewsubsystem();
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSaveProject(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWPROGDOC_H__EC34D26C_981B_11D3_A9AD_00001C21326E__INCLUDED_)
