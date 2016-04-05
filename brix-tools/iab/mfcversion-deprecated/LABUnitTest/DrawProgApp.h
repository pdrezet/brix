#pragma once

#include "../LucidApplicationBuilder/resource.h"
#include "../LucidApplicationBuilder/Project.h"
//#include "../LucidApplicationBuilder/TransferAppDialog.h"
#include "../common/TransferToTargetDialog.h"
class CDrawProgApp
{
public:
	CDrawProgApp(void);
public:
	~CDrawProgApp(void);
	
	// dummy methods
	void CloseProject(Project* pProject);
	void CloseUserDefDoc(HTREEITEM hItem);
	bool IsModified(Project* pProject);

	static CTransferToTargetDialog *c_pTransferToTargetDialog;
};
