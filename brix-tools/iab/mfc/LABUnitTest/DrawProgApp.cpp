#include "StdAfx.h"
#include "DrawProgApp.h"

CTransferToTargetDialog * CDrawProgApp::c_pTransferToTargetDialog;

CDrawProgApp::CDrawProgApp(void)
{
}

CDrawProgApp::~CDrawProgApp(void)
{
}

void CDrawProgApp::CloseProject(Project* pProject)
{
}

void CDrawProgApp::CloseUserDefDoc(HTREEITEM hItem)
{
}

bool CDrawProgApp::IsModified(Project *pProject)
{
	return FALSE;
}