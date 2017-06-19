#pragma once
#include "LucidString.h"

INXString getLucidRegValue(INXString csSectionPath, INXString csKey, INXString csDefault);
void setLucidRegValue(const INXString csSectionPath, const INXString csKey, INXString csValue);
