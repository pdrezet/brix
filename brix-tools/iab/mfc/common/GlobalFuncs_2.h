#pragma once
#include "stdafx.h"
#include <list>
#include <vector>
#include "Porting_Classes/INXRect.h"
#include "Porting_Classes/INXPoint.h"
#include "Porting_Classes/INXString.h"

extern DBTIMESTAMP parseTimeStamp( INXString &cs );
extern INXString csPrintTimeStamp( const DBTIMESTAMP &ts );
extern int FileSize(const INXString &fileName );
extern bool firstStampIsNewer( const DBTIMESTAMP &ts1,  const DBTIMESTAMP &ts2 );
extern INXString intToString(const int val);
extern void parseSodlWidgetData( const INXString &fileLine, INXString &widgetTag, INXString &targetFileName );
extern int parseLines( INXString &csTextBlock, std::list<INXString> &rLines );
extern INXString cloneBackSlashes( const INXString &csText );
extern INXString GetIniValue(INXString csSection, INXString csKey, INXString csIniFileName);
extern void GetIniKeys(INXString csSection, INXString csIniFileName, std::vector<INXString> &vKeysVec);
extern CPoint SnapToGrid(CPoint point);