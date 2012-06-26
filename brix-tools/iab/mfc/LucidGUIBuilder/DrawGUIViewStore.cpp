/** @file DrawGUIView.cpp
 * Implementation of CDrawGUIView class.
 * @author: Matthew Rutherford
 * @version: $Revision: 576 $
 * @date: $Date$
 * 
 * Copyright (c) Ncapsa Ltd, 2007. All rights reserved.
 */

#include "stdafx.h"
/*
#include "LgbDrawable.h"

#include "DrawGUIDoc.h"
#include "DrawGUIView.h"
#include "DrawGUI.h"
#include "LgbTextIcon.h"
#include "DrawGUIDoc.h"
#include "../LucidApplicationBuilder/FileOperations.h"
#include "MainFrm.h"
#include "../common/GlobalFuncs_2.h"
#include "..\common\bmpfile.h"
#include "../common\TgtTransProgDlog.h"
#include "config.h"
#include "FTP.h"
#include "../common/LucidConstants.h"
#include "ColourEdit.h"
#include "ColourStatic.h"
#include "properties_textbox.h"
#include "Properties_Image.h"
#include "Properties_Drawable.h"
#include <fstream>
#include <cassert>
#include <math.h>
#include <direct.h>
#include "common.h"
#include "LgbZOrderDlog.h"
#include "../common/LucidTypedefs.h"
#include "LgbImageIcon.h"
#include "LgbColorsDef.h"
#include "../common/GlobalFuncs_1.h"

#include <vector>
*/
#include "DrawGUIView.h"
#include "DrawGUIViewStore.h"

CDrawGUIViewStore::CDrawGUIViewStore()
{}

CDrawGUIViewStore::~CDrawGUIViewStore()
{
	//for(size_t i=0;i<m_vCopiedDrawablePtrs.size();i++)
	//	delete m_vCopiedDrawablePtrs[i];

	m_vCopiedDrawablePtrs.clear();
}


void CDrawGUIViewStore::copyFrom( const CDrawGUIView *pView )
{

	// Get data from view to this.
	pView->copyDrawables( m_vCopiedDrawablePtrs, m_vCopiedSelectionPtrs ); 

	m_iNumberIconsCurrentlySelected = pView->m_iNumberIconsCurrentlySelected;

	m_bShowTags = pView->m_bShowTags;

	m_cZDatMaxMins = pView->m_cZDatMaxMins;

	m_cZDatVals = pView->m_cZDatVals;

	m_bNativeBackgroundColors = pView->m_bNativeBackgroundColors;

	m_bZSliderNeverMoved = pView->m_bZSliderNeverMoved;

}


void CDrawGUIViewStore::copyTo( CDrawGUIView *pView )
{

	// Get main data from this to view
	pView->loadDrawables( m_vCopiedDrawablePtrs, m_vCopiedSelectionPtrs ); 

	pView->m_cDrawableBag.setNeedsUpdate();

	pView->m_iNumberIconsCurrentlySelected= m_iNumberIconsCurrentlySelected;

	pView->m_bShowTags= m_bShowTags;

	pView->m_cZDatMaxMins= m_cZDatMaxMins;

	pView->setZLeanLevel( m_cZDatVals.zLeanVal );

	pView->setUpperZActiveLevel( m_cZDatVals.zClipVal );

	pView->m_bNativeBackgroundColors= m_bNativeBackgroundColors;

	pView->m_bZSliderNeverMoved = m_bZSliderNeverMoved;

}
