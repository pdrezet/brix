#pragma once
#include "stdafx.h"
#include <list>
#include <vector>

extern DBTIMESTAMP parseTimeStamp( CString &cs );
extern CString csPrintTimeStamp( const DBTIMESTAMP &ts );
extern int FileSize(const CString &fileName );
extern bool firstStampIsNewer( const DBTIMESTAMP &ts1,  const DBTIMESTAMP &ts2 );
extern CString intToString(const int val);
extern void parseSodlWidgetData( const CString &fileLine, CString &widgetTag, CString &targetFileName );
extern int parseLines( CString &csTextBlock, std::list<CString> &rLines );
extern CString cloneBackSlashes( const CString &csText );
extern CString GetIniValue(CString csSection, CString csKey, CString csIniFileName);
extern void GetIniKeys(CString csSection, CString csIniFileName, std::vector<CString> &vKeysVec);
extern CPoint SnapToGrid(CPoint point);