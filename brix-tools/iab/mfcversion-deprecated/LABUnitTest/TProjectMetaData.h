#pragma once
#include "projectmetadata.h"

class TProjectMetaData :
	public ProjectMetaData
{
public:
	TProjectMetaData(void);
	~TProjectMetaData(void);

// Methods
	void setProjectName(CString csProjName);
	void setProjectDir(CString csProjDir);
	void createDefaultGroup();
	void createFolderStructure();
	void copyFolderTo(CString csNewProjRootDir, CString csNewProjName);
	
};
