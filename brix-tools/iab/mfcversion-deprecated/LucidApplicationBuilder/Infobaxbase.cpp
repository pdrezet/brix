// Infobaxbase.cpp: implementation of the Infobaxbase class.
//
//////////////////////////////////////////////////////////////////////

/*

  Base class for icons

  */


#include "stdafx.h"
#include "DrawProg.h"
#include "Infobaxbase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////




Infobaxbase::Infobaxbase()
{
deleteme=0;
	momentary=1;
	constant=0;
	negedge=0;
	plusedge=1;
	recorddelim="\\n";
	fielddelim=',';
	option2="";
	option1="";
	description="";
	fixedinfo="";
}

Infobaxbase::~Infobaxbase()
{

}


//sothat it can be overidden