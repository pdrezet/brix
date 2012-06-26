// LucidTypedefs.h: global typedefs
//
//////////////////////////////////////////////////////////////////////

#pragma once
#include "stdafx.h"
#include <map>
#include <list>
#include "LucidEnums.h"
//#include "../LucidGUIBuilder/LgbColorsDef.h"

class LgbDrawable;

typedef std::map<CString, CString> Map2cs_t;
typedef Map2cs_t::iterator Map2csIt_t;

// There are two main consumers of screenTag data: the screentag dialog, and the project
// file.  
// Project meta data.
// The master source is the project data, which is stored as a map of the (unique)
// screenTag, versus a supporting data structure 'TagProjMetaSupportData_t' which contains
// the tag's description and target file name.
//
// Screen manager data.
// The screen tag manager dlog shows the tag, its description and (maybe) how many gui widgets
// the tag is used on.
// this data is stored as mp of screentag vs ScreenMgrSupportData_t structure, which data struc
// has the tags description and usage count.  Note that this structure must be 'inflated' by looking-up
// & correlating proj data against itself.
//



typedef struct  {
	CPoint	topLeft;
	CString tag;
	CString descr;
} LgbDrawableEssentialData_t;


typedef struct  {
	CString tagDescr;
	CString	useCount;
} ScreenMgrSupportData_t;


typedef struct  {
	CString tag;
	CString tagDescr;	
	enum LucidLGBScreenTagProcessOptions	processOption;
} TagAndDescriptionProcessable_t;

typedef struct  {
	CString tag;
	CString tagDescr;	
} TagAndDescription_t;

typedef struct  {
	CString tagDescr;
	CString tgtFilename;	
	CString activeHostFilename;
} TagProjMetaSupportData_t;


//! The 'essential' data needed to create a GuiFile
typedef struct  {
	CString fileHostNameStub;
	CString fileDescr;
	CString screenTag;
} GuiFileEssentialData_t;


//! The 'essential' data needed to create a non-Gui transferable File
typedef struct  {
	CString fileHostName;
	CString fileDescr;
	CString fileTargetName;
} NonGuiFileEssentialData_t;


//! The full set of data displayable in the project/file manager dialog
typedef struct  {
	CString fileHostNameStub;
	CString fileDescr;
	CString tag;
	CString tagDescr;
} GuiFileMonty_t;

//! Holds the frontmost (highest z) and rearmost z-positions for a set of 1 or more LGB icons
typedef struct  {
	int frontMost;
	int rearMost;
} LgbZBounds_t;

typedef struct  {
	bool same;
	int  iVal;
} LgbBoolIntPair_t;

typedef struct  {
	bool		same;
	CString		csVal;
} LgbCsIntPair_t;


//! min and max values of z-lean for dlog slider scale
typedef struct  {
	int zLeanMin;
	int zLeanMax; 
} LgbZLeanBounds_t;

//! slider values of z-lean and z-clip plane for dlog slider scales
typedef struct  {
	int zLeanVal;
	int zClipVal;
} Lgb_UserZVals_t;


//---------------------------------------------------------------------
// Supplementary Convenience definitions.


// ScreenTag manager dialog - based

typedef std::map<CString, ScreenMgrSupportData_t> ScreenMgrDlogMap_t;
typedef std::pair<CString, ScreenMgrSupportData_t> ScreenMgrDlogMapPair_t;
typedef ScreenMgrDlogMap_t::iterator ScreenMgrDlogMapIt_t;
typedef ScreenMgrDlogMap_t::const_iterator ScreenMgrDlogMapConstIt_t;

// Project metas - based.

typedef std::map<CString, TagProjMetaSupportData_t> ScreenProjMetaMap_t;
typedef std::pair<CString, TagProjMetaSupportData_t> ScreenProjMetaMapPair_t;
typedef ScreenProjMetaMap_t::iterator ScreenProjMetaMapIt_t;
typedef ScreenProjMetaMap_t::const_iterator ScreenProjMetaMapConstIt_t;

typedef LgbDrawable * LgbDrawablePtr;

typedef std::pair<int, CString> IntCStringPair_t;

typedef std::list<LgbDrawablePtr>::iterator LgbDrawableIt_t; //!< convenience iterator for a list of ptrs to drawable
typedef std::list<LgbDrawablePtr>::const_iterator LgbDrawableConstIt_t; //!< convenience iterator for a list of ptrs to drawable