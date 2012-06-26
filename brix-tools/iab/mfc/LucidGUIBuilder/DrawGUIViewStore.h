/** @file DrawGUIView.h
 * Represent the MFC 'View' class for editing layouts in LGB.
 * Represents a re-write performed during June- July 2007.
 * Code is clearer, but doesn't properly respect the view/model/controlller paradigm
 * ie there is still too much documen data in the view rather than the document.
 * @author: Matthew Rutherford
 * @version: $Revision: 1480 $
 * @date: $Date$
 * 
 * Copyright (c) Ncapsa Ltd, 2007. All rights reserved.
 */

#pragma once

#include "stdafx.h"
#include "DrawGUIDoc.h"
#include "LgbImageIcon.h"
#include "LgbRect.h"
#include "LgbDrawableBag.h"
#include "LgbDrawable.h"
#include "LgbZOrderDlogBar.h"
#include "LgbColorsDef.h"
#include "../common/LgbIconDataStrucs.h"
//#include "LgbUndoStore.h"
#include <list>

using namespace std;


//! The MFC 'view' class for LGB
class CDrawGUIViewStore
{

public:
	CDrawGUIViewStore();
	virtual ~CDrawGUIViewStore();

// Operations

	void copyFrom( const CDrawGUIView *pView );

	void copyTo( CDrawGUIView *pView );

private:

	std::vector< LgbDrawable *> m_vCopiedDrawablePtrs; 
	std::vector< LgbDrawable *> m_vCopiedSelectionPtrs; 


	short m_iNumberIconsCurrentlySelected;

	bool m_bShowTags;

	LgbZLeanBounds_t m_cZDatMaxMins;

	bool m_bZSliderNeverMoved;

	Lgb_UserZVals_t m_cZDatVals;

	bool m_bNativeBackgroundColors;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

