#ifndef _DRAWPROG_H
#define _DRAWPROG_H

#include <wx/app.h>
#include <wx/event.h>
#include <wx/docview.h>
#include "MainFrame.h"
#include "Resource.h"

#include "LucidConstants.h"
#include "ProjectMetaData.h"
#include "MyTreeCtrl.h"
#include "DEP.h"
#include "Project.h"
#include "DrawProgView.h"

class DrawProg: public wxApp
{
public:
	DrawProg(void);
	bool OnInit();
	~DrawProg(void);

	wxDocument* OpenProject(ProjectMetaData* pProjMData);
	wxDocument* OpenDocumentFile(INXString lpszFileName);


	bool SetWorkDirGlobal(wxChar * workDir);
	bool CheckExecutableFolderContextIsOk();
	bool GetInstallationBaseDir(INXString &installationBaseDir);
	void GetExecutableName(INXString & execName);
	void OnSaveProject(wxCommandEvent& event);
	void OnNewProject(wxCommandEvent& event);
	void OnOpenProject(wxCommandEvent& event);

	bool DropFBInCurrentView(INXPoint point,INXString componentType, INXString component); //used by the function block menu

	/* Project management methods */
	void setProjMetaData(ProjectMetaData* projMetadata ); ///\brief sets metadata ....
	void setProject(Project *);							///\brief sets active project (but not metadata) ....
	Project* getCurrentProject();					    ///\brief gets active project pointer or NULL.
	DEP* getCurrentDEP();					    ///\brief gets active project  pointer or NULL.
	DrawProgView* getActiveProgView();
	bool copyTransferrablesToExports(ProjectMetaData* projMetadata, bool a, bool b); ///\brief collects all taregt files into the export directory

	DECLARE_EVENT_TABLE()
public:
	MainFrame* m_frame;

private:

	DEP 	*pDEP; //* This the current DEP - not sure how it is used!
	Project *m_CurrentProject; //this is the current project or NULL;
	DrawProgView * m_ActiveProgView;
	MyTreeCtrl *m_cProjTree;
private:
	void displayView(Project *proj, INXString doc_file);

};


//the following allows us to use wxGetApp();
DECLARE_APP(DrawProg)

#endif



