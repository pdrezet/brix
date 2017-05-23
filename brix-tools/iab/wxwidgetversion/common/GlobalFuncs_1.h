#pragma once

#include "../common/lgbicondatastrucs.h"
#include "Porting_Classes/INXString.h"

bool cleanupGuiLayoutBasics( LgbIconEssentialData_t &rEssDat, INXString &csWarnings  );

void parseGuiFile(
				const INXString &csFileName, 
				std::vector< LgbTextIconEssentialData_t > &textIcons, 
				std::vector< LgbPatchIconEssentialData_t > &patchIcons, 
				std::vector< LgbImageIconEssentialData_t > &imageIcons,
				std::vector< LgbTextStyleEssentialData_t > &vTextStyles);

