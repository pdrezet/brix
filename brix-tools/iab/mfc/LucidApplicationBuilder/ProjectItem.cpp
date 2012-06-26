// ProjectItem.cpp: implementation of the ProjectItem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DrawProg.h"
#include "ProjectItem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ProjectItem::ProjectItem()
{
	depFilename = "";
}

ProjectItem::~ProjectItem()
{

}
