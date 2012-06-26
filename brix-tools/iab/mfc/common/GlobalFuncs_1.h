#pragma once
#include "stdafx.h"

#include "../common/LgbIconDataStrucs.h"

extern bool cleanupGuiLayoutBasics( LgbIconEssentialData_t &rEssDat, CString &csWarnings  );

extern void parseGuiFile(
				const CString &csFileName, 
				std::vector< LgbTextIconEssentialData_t > &textIcons, 
				std::vector< LgbPatchIconEssentialData_t > &patchIcons, 
				std::vector< LgbImageIconEssentialData_t > &imageIcons,
				std::vector< LgbTextStyleEssentialData_t > &vTextStyles);

