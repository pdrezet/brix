#pragma once

#include "stdafx.h"
#include <oledb.h>

#define LCCTIMESTAMP_ANCIENTDATE "0000-00-00 00:00:00:000000000"

class LccTimeStamp :

	public DBTIMESTAMP
{
public:
	LccTimeStamp(void);
public:
	~LccTimeStamp(void);

	bool isNewerThan( const DBTIMESTAMP &ts2 );

	LccTimeStamp& operator=(const DBTIMESTAMP &timeStamp);

	CString csPrint( );//const DBTIMESTAMP &ts );

	void setAncient();

	void csParse( CString &cs );

};
