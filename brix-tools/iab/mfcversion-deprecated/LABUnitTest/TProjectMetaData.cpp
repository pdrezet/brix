#include "StdAfx.h"
#include "TProjectMetaData.h"

TProjectMetaData::TProjectMetaData(void)
{
}

TProjectMetaData::~TProjectMetaData(void)
{
}

void TProjectMetaData::setProjectName(CString csProjName)
{
	ProjectMetaData::setProjectName(csProjName);
}

void TProjectMetaData::setProjectDir(CString csProjDir)
{
	ProjectMetaData::setProjectDir(csProjDir);
}

void TProjectMetaData::createDefaultGroup()
{
	ProjectMetaData::createDefaultGroup();
}

void TProjectMetaData::createFolderStructure()
{
	ProjectMetaData::createFolderStructure();
}

void TProjectMetaData::copyFolderTo(CString csNewProjRootDir, CString csNewProjName)
{
	ProjectMetaData::copyFolderTo(csNewProjRootDir, csNewProjName);
}