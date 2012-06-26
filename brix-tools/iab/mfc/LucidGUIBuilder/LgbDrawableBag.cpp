#pragma once

#include "stdafx.h"
#include "LucidTypedefs.h"
#include "LucidConstants.h"
#include <vector>
#include <cassert>
#include <fstream>
#include <algorithm>
#include "LgbDrawable.h"
#include "LgbTextIcon.h"
#include "LgbPatchIcon.h"
#include "LgbImageIcon.h"
#include "LgbDrawableBag.h"
#include "LgbColorsDef.h"
#include "DrawGUI.h"

LgbDrawableBag::LgbDrawableBag(void)
: m_bNeedsUpdate(true)
, m_iUpperZActiveLevel(1000000)
, m_iZLean(0)
//, m_pLgbMasterIcon(NULL)
{ }

LgbDrawableBag::~LgbDrawableBag(void)
{ 
	/* A bug means that this gets caalled on closing a window, AFTER the reset has been called,
	yet with non-zero contents thaat have bad pointers!  don't know why, but the call to reset
	from CDrawGUIView::postNCDestroy should clean up memory.
	MRutherford 02Nov0seven.

	list< LgbDrawable *>::iterator it = m_lstDrawables.begin();
	while(it!= m_lstDrawables.end() )
	{
		LgbDrawable *pDraw = *it;
		if(*it != NULL){
			delete *it;
			*it = NULL;
		}
		it++;
	}
	m_lstDrawables.clear();
	*/
}


LgbRectSelTypeEnum LgbDrawableBag::getSelectedIcon( 
							const CPoint &point,
							LgbDrawable * &pIcon )
{

	update();

	LgbRectSelTypeEnum selMode;

	// we wish to search from highest z-pos downwards, as the user will expect to have
	// selected what he saw he cclicked on, not something buried under it.
	// Therefore put the highest z-orders 1st lowest last (temporarily).
	m_lstDrawables.reverse();

	LgbDrawableIt_t it = m_lstDrawables.begin();

	while( it != m_lstDrawables.end()){
		pIcon = *it;
		if(pIcon->isActive() ){
			if( (selMode=pIcon->getSelectionMode( point )) != k_LgbDrawableOutside ){
				// put drawables back into asc order
				m_lstDrawables.reverse();
				return selMode;
			}
		}
		it++;
	}

	// We got to the end of the list of icons without finding one 'under the click pt'.

	pIcon = NULL;
	m_lstDrawables.reverse();
	return k_LgbDrawableOutside;

}

LgbDrawableConstIt_t LgbDrawableBag::find( const CString &type, const CString &tag ) const
{
	LgbDrawable tmp;
	tmp.m_csTag = tag;
	tmp.m_csType = type;
	return find(&tmp);
}


LgbDrawableConstIt_t LgbDrawableBag::find( const LgbDrawable const *pDrawable ) const
{
	LgbDrawableConstIt_t it;
	LgbDrawable *pDraw = NULL;
	it = m_lstDrawables.begin();
	while(it!=m_lstDrawables.end()){
		pDraw = ( LgbDrawable *) *it;
		if( (pDraw->m_csTag==pDrawable->m_csTag)  && (pDraw->m_csType==pDrawable->m_csType) ){
			return it;
		}else {
			it++;
		}
	}
	return it;
}


bool LgbDrawableBag::isAlreadyInList( const CString &type, const CString &tag, LgbDrawableConstIt_t &it ) const
{
	LgbDrawable tmp;
	tmp.m_csTag = tag;
	tmp.m_csType = type;

	if( (it = find(&tmp) )== m_lstDrawables.end() ){
		// If we got to the end without finding the icon, the icon can't be present
		return false;
	}else{
		return true;
	}
}

bool LgbDrawableBag::isAlreadyInList( const LgbDrawable const *pDrawable, LgbDrawableConstIt_t &it ) const
{
	if( (it = find(pDrawable)) == m_lstDrawables.end() ){
		return false;
	}else{
		return true;
	}
}

bool LgbDrawableBag::isAlreadyInList( const LgbDrawable const *pDrawable ) const
{
	if( find(pDrawable) == m_lstDrawables.end() ){
		return false;
	}else{
		return true;
	}
}

void LgbDrawableBag::getSelections( IconSelection< LgbTextIcon > &txtIcons, 
									IconSelection< LgbPatchIcon > &ptchIcons,
									IconSelection< LgbImageIcon > &bmpIcons )
{

	update();
	txtIcons.clear();
	bmpIcons.clear();

	LgbDrawableIt_t it = m_lstDrawables.begin();

	while(it!= m_lstDrawables.end()){
		if((*it)->m_bIsSelected && (*it)->isActive() ){
			if( (*it)->getClassId() == k_LgbTextIcon ){
				txtIcons.push_back( (LgbTextIcon *) *it );
			} else if( (*it)->getClassId() == k_LgbPatchIcon ){
				ptchIcons.push_back( (LgbPatchIcon *) *it );
			} else if( (*it)->getClassId() == k_LgbImageIcon ){
				bmpIcons.push_back( (LgbImageIcon *) *it );
			}
		} // if((*it)->m_bIsSelected)
		it++;

	} // while(it!= m_lstDrawables.end())
}


void LgbDrawableBag::Draw( CDC *pDC, const CRect &clientRect, const COLORREF backGround )
{

	//----------------------------------------------------------------------------------------
	// Overview:
	// The idea of this implementation is to draw the 3D connecting-lines
	// properly.  If the user switches-on 3D perspective, then lines are drawn
	// from the 'actual position' corners to the '3D position' corners.  These lines
	// are drawn per z-level, so that lower lines get correctly 'obscured' by icons at a higher z.
	//----------------------------------------------------------------------------------------


	// Carry on with this routine even if there are 0 drawables at all,
	// ( or at least 0 active ) drawables.  This is because the OnEraseBackground call does
	// nothing, so as to avoid flickering on resize.  Therefore, this routine must
	// continue on, to finally do the blit so that a view with no widgets at least
	// looks like its been drawn.  NB Otherwise the user will 'see straight through' the app
	// window, and will think that the app has crashed!
	LgbDrawableIt_t it = m_lstDrawables.begin();


// Set up blend function for use later ...
	BLENDFUNCTION bf;
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 255;
	bf.AlphaFormat = AC_SRC_ALPHA; 

	CBrush bgBrush( backGround );
	CBrush blackBrush( RGB(0,0,0) );

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// create memory device context which will be used then cleared, 
	// repeatedly for each z-layer.
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	CDC* pMemDCLayer = new CDC;
	assert( NULL != pMemDCLayer );

	pMemDCLayer->CreateCompatibleDC(pDC);
			
	// create bitmap
	CBitmap* pBmpLayer = new CBitmap;
	assert( NULL != pBmpLayer );

	// initialize
	pBmpLayer->CreateCompatibleBitmap( pDC, clientRect.Width(), clientRect.Height() );

	pMemDCLayer->SelectObject( pBmpLayer );

	pMemDCLayer->SetBkMode( OPAQUE );

	CRgn rgn;
	rgn.CreateRectRgn( clientRect.left, clientRect.top, clientRect.right, clientRect.bottom );
	pMemDCLayer->SelectClipRgn( &rgn, RGN_COPY );


	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// create memory device context for compositing the whole image before
	// it is blitted to the view's DC.
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	CDC* pMemDCCompo = new CDC;
	assert( NULL != pMemDCCompo );

	pMemDCCompo->CreateCompatibleDC(pDC);
	//CRgn rgn;
	//rgn.CreateRectRgn( clientRect.left, clientRect.top, clientRect.right, clientRect.bottom );
	pMemDCCompo->SelectClipRgn( &rgn, RGN_COPY );


	// create bitmap
	CBitmap* pBmpCompo = new CBitmap;
	assert( NULL != pBmpCompo );


	// initialize
	pBmpCompo->CreateCompatibleBitmap( pDC, clientRect.Width(), clientRect.Height() );

	pMemDCCompo->SelectObject(pBmpCompo);

	pMemDCCompo->SelectObject( bgBrush );
	pMemDCCompo->Rectangle( clientRect );

	pMemDCCompo->SetBkMode(TRANSPARENT);

	CRect rect(0, 0, clientRect.Width(), clientRect.Height() );

	// Recalculate actual and 3D rectangles, if necessary
	update();

	// Treat the 1st layer of drawables as special, as these don't 
	// have any pseudo-3D 'lean lines' drawn below them.
	bool b_drawLeanLines = false;

	// Holder for all the drawables at a given z-level.
	vector< LgbDrawable *> sameZVec;

	int i_thisZ = -99;
	int i_lastZ = -99;

	// Initialise.
	it = m_lstDrawables.begin();

	bool keepGoing = (it!= m_lstDrawables.end()) && (*it)->isActive();

	if( keepGoing )
	{
		i_thisZ = (*it)->m_iZPosProcessed;
		i_lastZ = 0;			// The lowest 'processed' level is always 0 (from 'update' !)
		sameZVec.push_back( *it );
		it++;
	}



	LgbDrawableIt_t it2; // iterator for later use.

	// Go through each drawable, loading all the ones at the same z-pos into a temp
	// holding vec.

	while(  keepGoing ){

		if ( (it == m_lstDrawables.end() ) ||  ( (*it)->m_iZPosProcessed != i_thisZ) ){

			// We have passed through a layer of same-z drawables, or have got
			// to the end of the list of drawables altogether, so draw this most recent layer.

			// Paint this layer black
			pMemDCLayer->SelectObject( blackBrush );
			pMemDCLayer->Rectangle( clientRect );

			// Draw ALL the base rectangles, and the relevant section of the 3d lean-lines
			// with a call to the LgbDrawable draw method.

			it2 = m_lstDrawables.begin();
			while(it2 != m_lstDrawables.end() )
			{
				// Don't draw 'lean lines' for a given icon at a higher z than icon itself
				// Don't draw lean lines at all for an icon which is not active
				if( (*it2)->m_iZPosProcessed > i_thisZ  && (*it2)->getState(LgbDrawable::k_Active)  )
					(*it2)->LgbDrawable::Draw3DPerspective( 
							pMemDCCompo, i_lastZ, i_thisZ, m_iZLean * ZLEAN_FCTR_X );
				it2++;
			}
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	Just Below in call to sameZVec[i]->Draw is where 'Out of memory' error occurs
	if any icon lies at negative x or y val.
	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

			// Now draw the icons themselves for this z-level
			for(size_t i=0;i<sameZVec.size();i++)
			{
				// Draw the icon
				sameZVec[i]->Draw( pMemDCLayer, i_lastZ, i_thisZ,  m_iZLean * ZLEAN_FCTR_X );

				// Draw the widget tags
				//if( sameZVec[i]->m_bShowTag)
				//	sameZVec[i]->drawTag( pMemDCLayer );
			}

			// Now draw the frames for the icons at this z-level
			// Draw them on the background so far, as then 
			for(size_t i=0;i<sameZVec.size();i++)
			{
				// Draw the icon
				sameZVec[i]->DrawFrame( pMemDCCompo );
			}

			// Blend this layer onto the overall composite.
			AlphaBlend(
						pMemDCCompo->GetSafeHdc(),
						0,
						0,
						rect.Width(),
						rect.Height(),
						pMemDCLayer->GetSafeHdc(),
						0,
						0,
						rect.Width(),
						rect.Height(),
						bf 
				);

			for(size_t i=0;i<sameZVec.size();i++)
			{
				// Draw the widget tags
				if( sameZVec[i]->m_bShowTag)
					sameZVec[i]->drawTag( pMemDCCompo );
			}

			// empty vec ready for next time
			sameZVec.clear();

			// Push the 'new-z' drawable into temp vec
			if(it != m_lstDrawables.end()){

				sameZVec.push_back( *it);

				// set lower z ready for next time round
				i_lastZ = i_thisZ;

				i_thisZ = (*it)->m_iZPosProcessed;
			}

		} else { //if( ((*it)->m_iZPosProcessed != i_thisZ ) || (it == m_lstDrawables.end() )

			sameZVec.push_back( *it);

		}

		if( it == m_lstDrawables.end() || !(*it)->getState(LgbDrawable::k_Active)  )
			keepGoing = false;
		else
			it++;


	} //  while( keepGoing )


	it = m_lstDrawables.begin();
	keepGoing = (it != m_lstDrawables.end() );

	while( keepGoing )
	{
		if( ( it == m_lstDrawables.end() ) || !((*it)->getState( LgbDrawable::k_Active))  ){
			keepGoing = false;
		}else{
			(*it)->DrawSelectionBlobs( pMemDCCompo );
			it++;
		}
	}


	// We've processed all layers now, so blit the memory dc contents to screen
	pDC->BitBlt
	(
		0, 
		0,
		clientRect.Width(),
		clientRect.Height(),
		pMemDCCompo,			// specifies the source device context
		0,						// specifies the x-coordinate (in logical units) of the upper-left corner of the source rectangle
		0,						// specifies the x-coordinate (in logical units) of the upper-left corner of the source rectangle
		SRCCOPY					// specifies the raster operation to be performed
	);


	pMemDCLayer->DeleteDC();
	delete pMemDCLayer;

	pMemDCCompo->DeleteDC();
	delete pMemDCCompo;

	pBmpLayer->DeleteObject();
	delete pBmpLayer;

	pBmpCompo->DeleteObject();
	delete pBmpCompo;

}

//void LgbDrawableBag::setCollectiveState( LgbDrawable::MemberTypesEnum eMember, bool state )

void LgbDrawableBag::setCollectiveState(const bool &state, LgbDrawable::MemberTypesEnum eMember, const LgbIconTypeEnum &eIconType)
{
	LgbDrawableIt_t it = m_lstDrawables.begin();

	while(it!= m_lstDrawables.end()){

		if( (eIconType==k_LgbAllIconTypes) ||
			(  (eIconType==k_LgbBitmapOnly) && ( (*it)->getClassId()==k_LgbImageIcon) ) ||
			(  (eIconType==k_LgbTextBoxOnly) && ( (*it)->getClassId()==k_LgbTextIcon) ) ||
			(  (eIconType==k_LgbPatchOnly) && ( (*it)->getClassId()==k_LgbPatchIcon) )
			)
		{
			(*it)->m_bIsSelected = state;
		}
		it++;
	}
}

void LgbDrawableBag::setTagShowState(const bool &state)
{
	LgbDrawableIt_t it = m_lstDrawables.begin();

	while(it!= m_lstDrawables.end()){
		(*it)->m_bShowTag = state;
		it++;
	}
}

int LgbDrawableBag::loadSelectedOutlines( vector <LgbRect> &rRects )
{

	update();
	rRects.clear();

	LgbDrawableIt_t it = m_lstDrawables.begin();

	while(it!= m_lstDrawables.end()){
		if( (*it)->m_bIsSelected && (*it)->isActive() ){
			rRects.push_back( (*it)->m_cRectShown );
		}
		it++;
	}

	return rRects.size();

}

void LgbDrawableBag::resize( const LgbRectSelTypeEnum &selMode, const int &mov )
{

	// The 'integer' move  is appropriate only for moving the top, left, bottom or right edges.
	assert(	(selMode!=k_LgbDrawableLwrLft) && 
			(selMode!=k_LgbDrawableLwrRgt) && 
			(selMode!=k_LgbDrawableTopLft) && 
			(selMode!=k_LgbDrawableTopRgt) );

	update();
	LgbDrawable *pDraw = NULL;
	LgbDrawableIt_t it = m_lstDrawables.begin();

	while(it!= m_lstDrawables.end()){
		pDraw = (*it);
		if( pDraw->m_bIsSelected && pDraw->isActive() ){
			if(selMode==k_LgbDrawableLft) pDraw->offsetLft(mov);
			if(selMode==k_LgbDrawableRgt) pDraw->offsetRgt(mov);
			if(selMode==k_LgbDrawableTop) pDraw->offsetTop(mov);
			if(selMode==k_LgbDrawableBtm) pDraw->offsetBtm(mov);
		}
		it++;
	}
	return;
}

void LgbDrawableBag::resize( const LgbRectSelTypeEnum &selMode, const CPoint &mov )
{
	// The 'integer' move  is appropriate only for moving the top-left, top-right etc corners.
	assert(	(selMode!=k_LgbDrawableTop) && 
			(selMode!=k_LgbDrawableRgt) && 
			(selMode!=k_LgbDrawableBtm) && 
			(selMode!=k_LgbDrawableLft) );

	update();
	LgbDrawable *pDraw = NULL;
	LgbDrawableIt_t it = m_lstDrawables.begin();

	while(it!= m_lstDrawables.end()){
		pDraw = (*it);
		if( pDraw->m_bIsSelected && pDraw->isActive() ){
			if(selMode==k_LgbDrawableLwrLft) pDraw->offsetBtmLft(mov);
			if(selMode==k_LgbDrawableLwrRgt) pDraw->offsetBtmRgt(mov);
			if(selMode==k_LgbDrawableTopLft) pDraw->offsetTopLft(mov);
			if(selMode==k_LgbDrawableTopRgt) pDraw->offsetTopRgt(mov);
		}
		it++;
	}
	return;
}

void LgbDrawableBag::moveIcons( const CPoint &vec)
{

	update();
	LgbDrawable *pDraw = NULL;
	LgbDrawableIt_t it = m_lstDrawables.begin();

	while(it!= m_lstDrawables.end()){
		pDraw = (*it);
		if( pDraw->m_bIsSelected && pDraw->isActive() ){
			pDraw->move( vec );
		}
		it++;
	}

	return;

}

int LgbDrawableBag::getSelectionCount()
{
	int count = 0;
	LgbDrawableIt_t it = m_lstDrawables.begin();
	while(it!= m_lstDrawables.end()){
		if( (*it)->m_bIsSelected && (*it)->isActive() ){
			count++;
		}
		it++;
	}

	return count;

}

void LgbDrawableBag::freeAllMemory()
{

	list< LgbDrawable *>::iterator it = m_lstDrawables.begin();
	while(it!= m_lstDrawables.end() )
	{
		LgbDrawable *pDraw = *it;
		if(*it != NULL){
			delete *it;
			*it = NULL;
		}
		it++;
	}

	m_lstDrawables.clear();
	m_bNeedsUpdate = true;
}

void LgbDrawableBag::reset()
{
	m_lstDrawables.clear();
	m_bNeedsUpdate = true;
}


//LgbDrawableIt_t LgbDrawableBag::insert( LgbDrawableIt_t it, LgbDrawable *addable )
//{
//	return m_lstDrawables.insert( it, addable );
//}

LgbDrawableIt_t LgbDrawableBag::erase ( LgbDrawableIt_t &it )
{
	//LgbDrawable *pDraw = *it;
	LgbDrawableIt_t it2 = static_cast< LgbDrawableIt_t > ( it );
	m_bNeedsUpdate = true;
	return m_lstDrawables.erase( it2 );
}

LgbDrawableIt_t LgbDrawableBag::erase ( LgbDrawable *pIcon )
{
	LgbDrawableIt_t it;
	LgbDrawable *pDraw = NULL;

	it = m_lstDrawables.begin();
	while(it!=m_lstDrawables.end()){
		pDraw = ( LgbDrawable *) *it;
		if( *pDraw == *pIcon){
			m_bNeedsUpdate = true;
			return m_lstDrawables.erase( it );
		}else {
			it++;
		}
	}
	return it;
}

void LgbDrawableBag::saveToFile( const CString &fileName )
{
	bool bIsTextStyleSaved = false;

	assert(fileName != "");

	if (fileName==""){

		return;

	} else {

		ofstream file(fileName);

		CString versionStr = GUI_FILE_VERSION;
		file<<versionStr;	

		LgbTextIcon::c_bIsTextStyleSaved = false;
		LgbDrawableIt_t it = m_lstDrawables.begin();

		while(it!= m_lstDrawables.end()){
			(*it)->saveToFile( file );
			it++;
		}

		file.close();
	}
}
	

void LgbDrawableBag::setDeletionTags(const bool &state)
{

	LgbDrawableIt_t it = m_lstDrawables.begin();
	while(it!= m_lstDrawables.end()){
		(*it)->m_bIsToBeDeleted = state;
		it++;
	}

	return;
}

size_t LgbDrawableBag::size()
{
	return m_lstDrawables.size();
}

int LgbDrawableBag::doDeletions()
{

	int nDeleted = 0;
	LgbDrawable *pDraw=NULL;
	LgbDrawableIt_t it = m_lstDrawables.begin();

	while(it!= m_lstDrawables.end()){

		pDraw = (*it);

		if( pDraw->m_bIsToBeDeleted ){

			it = erase(it);
			delete pDraw;
			nDeleted++;

		} else {
			// erase returns an iterator that points to the element
			// after the one that was deleted, so increment only if
			// last it wasn't deleted.
			it++;
		}
	}

	m_bNeedsUpdate = true;
	return nDeleted;
}

bool sortAscendingFunc( LgbDrawable *a, LgbDrawable *b)
{
	return b->m_iZPosUser > a->m_iZPosUser ;
}

bool LgbDrawableBag::setSelectedIcons( 
	const LgbRect &marquee, 
	const bool &getPartials,
	const bool toggle
	)
{

	vector< bool > vInitialSelectionState;

	// Store opening set of selections:

	size_t i = 0;
	LgbDrawableIt_t it = m_lstDrawables.begin();

	while(it!= m_lstDrawables.end()){
		vInitialSelectionState.push_back( (*it)->m_bIsSelected );
		i++;
		it++;
	}



	update();

	if(!toggle){
	// If ctrl wasn't down, 1st of all deselect all icons
		setCollectiveState( false, LgbDrawable::k_Selected, k_LgbAllIconTypes );
	}

	LgbDrawable *pDraw = NULL;

	it = m_lstDrawables.begin();

	while(it!= m_lstDrawables.end()){

		pDraw = (*it);

		LgbRectIntsecnEnum intsnType = marquee.getIntersection(pDraw->m_cRect);

		if(getPartials){

			if(	(intsnType == k_LgbCompletelyWithin) ||
				(intsnType == k_LgbPartlyWithin)	 ){
				
				if(toggle){
					pDraw->m_bIsSelected = !pDraw->m_bIsSelected;
				}else{
					pDraw->m_bIsSelected = true;
				}
			}

		} else {

			if(	intsnType == k_LgbCompletelyWithin){
				
				if(toggle){
					pDraw->m_bIsSelected = !pDraw->m_bIsSelected;
				}else{
					pDraw->m_bIsSelected = true;
				}

			}

		} 

		it++;

	} // while(it!= m_lstDrawables.end())

	bool bSelectionsChanged = false;
	i = 0;
	it = m_lstDrawables.begin();

	while(it!= m_lstDrawables.end() && !bSelectionsChanged ){

		if(vInitialSelectionState[i] !=  (*it)->m_bIsSelected)
			bSelectionsChanged = true;

		i++;
		it++;
	}

	m_bNeedsUpdate = bSelectionsChanged;

	return bSelectionsChanged;

}


void LgbDrawableBag::sortAscending()
{
	m_lstDrawables.sort(sortAscendingFunc);
	m_bNeedsUpdate = true;
	//update();
}

LucidErrEnum LgbDrawableBag::push_back( LgbDrawable *addable)
{
	if( isAlreadyInList( addable ) ){

		return kErr_LgbDrawableAlreadyInList;
	}else{

		m_lstDrawables.push_back( addable );
		m_bNeedsUpdate = true;

		return kErr_NoErr;
	}
}

/* Not used any more, as now 'master' icon's edge is used for alignment
LucidErrEnum LgbDrawableBag::getLftmostEdge(int & pos)
{
	bool noneYetSampled=true;
	pos = VERY_LARGE_INT;
	int pos2=0;

	LgbDrawableIt_t it = m_lstDrawables.begin();
	while(it!= m_lstDrawables.end()){
		if( (*it)->m_bIsSelected && (*it)->isActive() ){
			pos2 = (*it)->m_cRect.left;
			if(noneYetSampled){
				pos = pos2;
				noneYetSampled = false;
			}else{
				pos = pos<pos2? pos : pos2;
			}
		}

		it++;
	}

	if(noneYetSampled){
		return kErr_NoneSelected;
	}else{
		return kErr_NoErr;
	}
}
*/

/* Not used any more, as now 'master' icon's edge is used for alignment
LucidErrEnum LgbDrawableBag::getRgtmostEdge(int & pos)
{
	bool noneYetSampled=true;
	pos = VERY_LARGE_INT;
	int pos2=0;

	LgbDrawableIt_t it = m_lstDrawables.begin();
	while(it!= m_lstDrawables.end()){
		if( (*it)->m_bIsSelected && (*it)->isActive() ){
			pos2 = (*it)->m_cRect.right;
			if(noneYetSampled){
				pos = pos2;
				noneYetSampled = false;
			}else{
				pos = pos>pos2? pos : pos2;
			}
		}

		it++;
	}

	if(noneYetSampled){
		return kErr_NoneSelected;
	}else{
		return kErr_NoErr;
	}
}*/

/* Not used any more, as now 'master' icon's edge is used for alignment
LucidErrEnum LgbDrawableBag::getTopmostEdge(int & pos)
{
	bool noneYetSampled=true;
	pos = VERY_LARGE_INT;
	int pos2=0;

	LgbDrawableIt_t it = m_lstDrawables.begin();
	while(it!= m_lstDrawables.end()){
		if( (*it)->m_bIsSelected && (*it)->isActive() ){
			pos2 = (*it)->m_cRect.top;
			if(noneYetSampled){
				pos = pos2;
				noneYetSampled = false;
			}else{
				pos = pos<pos2? pos : pos2;
			}
		}

		it++;
	}

	if(noneYetSampled){
		return kErr_NoneSelected;
	}else{
		return kErr_NoErr;
	}
}*/

/* Not used any more, as now 'master' icon's edge is used for alignment
LucidErrEnum LgbDrawableBag::getBtmmostEdge(int & pos)
{
	bool noneYetSampled=true;
	pos = VERY_LARGE_INT;
	int pos2=0;

	LgbDrawableIt_t it = m_lstDrawables.begin();
	while(it!= m_lstDrawables.end()){
		if( (*it)->m_bIsSelected && (*it)->isActive() ){
			pos2 = (*it)->m_cRect.bottom;
			if(noneYetSampled){
				pos = pos2;
				noneYetSampled = false;
			}else{
				pos = pos>pos2? pos : pos2;
			}
		}

		it++;
	}

	if(noneYetSampled){
		return kErr_NoneSelected;
	}else{
		return kErr_NoErr;
	}
}*/

/* Not used any more, as now 'master' icon's centre is used for alignment
LucidErrEnum LgbDrawableBag::getAverageCentre( CPoint &pos)
{

	pos.SetPoint( VERY_LARGE_INT, VERY_LARGE_INT);
	int totalX=0;
	int totalY=0;
	int count=0;

	LgbDrawableIt_t it = m_lstDrawables.begin();
	while(it!= m_lstDrawables.end()){
		if( (*it)->m_bIsSelected && (*it)->isActive() ){
			totalX += (*it)->m_cRect.CenterPoint().x;
			totalY += (*it)->m_cRect.CenterPoint().y;
			count++;
		}
		it++;
	}

	if(!count){
		return kErr_NoneSelected;
	}else{
		pos.SetPoint( totalX/count, totalY/count);
		return kErr_NoErr;
	}
}*/




bool LgbDrawableBag::test()
{	
	bool failed = false;
/*
	LucidErrEnum err;

	LgbDrawable		*pDraw = new LgbDrawable( CRect(10,10,100,20), "d1", "d2", -1 );

	LgbTextIcon		*pTxtIcon = new LgbTextIcon( CRect(10,10,100,20), "t1", "t2", -1 );

	LgbImageIcon	*pBmpIcon = new LgbImageIcon( CRect(10,10,100,20), "b1", "b2", -1, "proj", "rr"  );

	
	LgbDrawableIt_t it;



	failed = failed || isAlreadyInList( "d1", "d2", it );
	failed = failed || isAlreadyInList( pDraw, it );

	// add and check it IS in there
	push_back(pDraw);
	failed = failed || !isAlreadyInList( "d1", "d2", it );
	failed = failed || !isAlreadyInList( pDraw, it );

	// check this isn't in
	failed = failed || isAlreadyInList( "drawTypeX", "drawTag", it );

	// Check we can't add this again
	err = push_back(pDraw);
	failed = failed || err!=kErr_LgbDrawableAlreadyInList ;

	push_back(pTxtIcon);
	failed = failed || !isAlreadyInList( pTxtIcon, it );

	push_back(pBmpIcon);
	failed = failed || !isAlreadyInList( pBmpIcon, it );

	setSelnState( false, k_LgbAllIconTypes );
	failed = failed || getSelectionCount();

	setDeletionTags(false);
	failed = failed || ( doDeletions()!=0 );


	setDeletionTags(true);
	int sz = m_lstDrawables.size();
	failed = failed || ( doDeletions()!=sz );

	LgbColors_t cols;

	cols.fgRed = 21;
	cols.fgGreen = 22;
	cols.fgBlue = 23;

	cols.bgRed = 51;
	cols.bgGreen = 52;
	cols.bgBlue = 53;

	CRect rect(10,10,30,30);

	pTxtIcon = new LgbTextIcon(rect, "a1", "a2", 2, cols );
	failed = failed || ( pTxtIcon->getColors().bgRed != cols.bgRed );
	push_back( pTxtIcon );

	pTxtIcon = new LgbTextIcon(rect, "b1", "b2", 6, cols );
	failed = failed || ( pTxtIcon->getColors().bgRed != cols.bgRed );
	push_back( pTxtIcon );

	pTxtIcon = new LgbTextIcon(rect, "c1", "c2", 1, cols );
	failed = failed || ( pTxtIcon->getColors().bgRed != cols.bgRed );
	push_back( pTxtIcon );

	pBmpIcon = new LgbImageIcon(rect, "x1", "x2", 5, "pDir" , "rr"  );
	failed = failed || ( pTxtIcon->getColors().bgRed != cols.bgRed );
	push_back( pBmpIcon );

	pBmpIcon = new LgbImageIcon(rect, "y1", "y2", 3, "pDir", "rr"  );
	failed = failed || ( pTxtIcon->getColors().bgRed != cols.bgRed );
	push_back( pBmpIcon );

	pBmpIcon = new LgbImageIcon(rect, "z1", "z2",  4, "pDir", "rr"  );
	failed = failed || ( pTxtIcon->getColors().bgRed != cols.bgRed );
	push_back( pBmpIcon );


	it = find( "y1", "y2" );
	pDraw=(*it);
	failed = failed || pDraw->m_csTag != "y1" || pDraw->m_csType != "y2" ;

	it = erase(it);
	pDraw=(*it);
	failed = failed || pDraw->m_csTag != "z1" || pDraw->m_csType != "z2" ;

	sortAscending();

	saveToFile( "fredMungus.gui" );
*/
	return failed;

}


void LgbDrawableBag::drawGhostDragOutlines(
						const LgbRectSelTypeEnum	&eSelnMode,
						const CPoint				&lastMoveVec,
						const CPoint				&thisMoveVec,
						CClientDC					*dc
						)
{

	IconSelection< LgbImageIcon > imageIcons;
	IconSelection< LgbTextIcon >  textIcons;
	IconSelection< LgbPatchIcon >  ptchIcons;

	vector< LgbDrawable * > vpIcons;
	vector< LgbRect > vMorphedRects;

	int iWidth, iHeight;

	getSelections( textIcons, ptchIcons, imageIcons );

	for(size_t i=0; i<textIcons.size(); i++){
		vpIcons.push_back(textIcons.getItem(i));
	}

	for (size_t i=0; i<ptchIcons.size(); i++) {
		vpIcons.push_back(ptchIcons.getItem(i));
	}

	for(size_t i=0;i<imageIcons.size();i++){
		vpIcons.push_back( imageIcons.getItem(i) );
	}

	CPen pen(PS_SOLID, 2, RGB( 255, 0, 0 ));
	dc->SelectObject( pen );
	dc->SetROP2( R2_XORPEN );

	LgbDrawable *pLastClickedIcon = getLastClickedIcon();

	// getMorphedRectangles uses a divide by the width so can't have zero width.
	if (pLastClickedIcon->m_cRectShown.Width() == 0) {
		iWidth = 1;
	}
	else {
		iWidth = pLastClickedIcon->m_cRectShown.Width();
	}

	// getMorphedRectangles uses a divide by the height so can't have zero height.
	if (pLastClickedIcon->m_cRectShown.Height() == 0) {
		iHeight = 1;
	}
	else {
		iHeight = pLastClickedIcon->m_cRectShown.Height();
	}

	getMorphedRectangles(
		eSelnMode, 
		lastMoveVec, // Redraw the 'old' positions, again in xor mode, so that they disappear.
		iWidth, 
		iHeight, 	
		false,
		vpIcons, 
		vMorphedRects );

	for(size_t i=0;i<vMorphedRects.size();i++){
		vMorphedRects[i].Draw( 0, dc );
	}

	getMorphedRectangles(
		eSelnMode, 
		thisMoveVec, // Draw the 'new' positions, in xor mode.
		iWidth, 
		iHeight, 	
		false,
		vpIcons, 
		vMorphedRects );

	for(size_t i=0;i<vMorphedRects.size();i++){
		vMorphedRects[i].Draw( 0, dc );
	}

}

void LgbDrawableBag::setMorphedRectangles(
	vector< LgbDrawable *>	vMorphableIcons,
	vector< LgbRect >		vMorphedRects )
{
	assert( vMorphableIcons.size() == vMorphedRects.size() );

	for(size_t i=0;i<vMorphableIcons.size();i++)
	{
		vMorphableIcons[i]->m_cRect = vMorphedRects[i];
	}
	m_bNeedsUpdate = true;
}

void LgbDrawableBag::getMorphedRectangles(
						const LgbRectSelTypeEnum	&eSelnMode,
						const CPoint				&moveVec,
						const int					&masterRectWidth,
						const int					&masterRectVertExtent,
						const bool					&useActualRectPos,
						const vector<LgbDrawable *>	&vOrigDrawables,
							  vector<LgbRect>		&vMorphedRects
						)
{
	vMorphedRects.clear();

	float frctnLftEdgeDelta = 0.0;
	float frctnRgtEdgeDelta = 0.0;
	float frctnTopEdgeDelta = 0.0;
	float frctnBtmEdgeDelta = 0.0;

	if( k_LgbDrawableInterior == eSelnMode ) {

		// Translate rather than resize
		LgbRect dumRect;

		for(size_t i=0;i<vOrigDrawables.size();i++){
			dumRect = useActualRectPos ? vOrigDrawables[i]->m_cRect : vOrigDrawables[i]->m_cRectShown;
			dumRect.OffsetRect(moveVec);
			vMorphedRects.push_back( dumRect );
		}

	} else {

		//---------------------------------------------
		// Left Edge fractional move

		if( (eSelnMode==k_LgbDrawableTopLft) ||
			(eSelnMode==k_LgbDrawableLft) ||
			(eSelnMode==k_LgbDrawableLwrLft) )
		{
			frctnLftEdgeDelta = (float) moveVec.x / masterRectWidth;
		}

		//---------------------------------------------
		// Right Edge fractional move

		if( (eSelnMode==k_LgbDrawableTopRgt) ||
			(eSelnMode==k_LgbDrawableRgt) ||
			(eSelnMode==k_LgbDrawableLwrRgt) )
		{
			frctnRgtEdgeDelta = (float) moveVec.x / masterRectWidth;
		}

		//---------------------------------------------
		// Top Edge fractional move

		if( (eSelnMode==k_LgbDrawableTopRgt) ||
			(eSelnMode==k_LgbDrawableTop) ||
			(eSelnMode==k_LgbDrawableTopLft) )
		{
			frctnTopEdgeDelta = (float) moveVec.y / masterRectVertExtent;
		}


		//---------------------------------------------
		// Bottom Edge fractional move

		if( (eSelnMode==k_LgbDrawableLwrRgt) ||
			(eSelnMode==k_LgbDrawableBtm) ||
			(eSelnMode==k_LgbDrawableLwrLft) )
		{
			frctnBtmEdgeDelta = (float) moveVec.y / masterRectVertExtent;
		}

		int iWidth, iHeight;

		for(size_t i=0;i<vOrigDrawables.size();i++){

			iWidth = vOrigDrawables[i]->m_cRect.Width();
			// If the width is 0 the rectangle will never resize, so use '1' instead.
			if (iWidth == 0) {
				iWidth = 1;
			}
			iHeight = vOrigDrawables[i]->m_cRect.Height();
			// If the height is 0 the rectangle will never resize, so use '1' instead.
			if (iHeight == 0) {
				iHeight = 1;
			}

			vMorphedRects.push_back( useActualRectPos ? vOrigDrawables[i]->m_cRect : vOrigDrawables[i]->m_cRectShown );
			vMorphedRects[i].offsetLft( (int) ( frctnLftEdgeDelta * iWidth ) );
			vMorphedRects[i].offsetRgt( (int) ( frctnRgtEdgeDelta * iWidth ) );
			vMorphedRects[i].offsetTop( (int) ( frctnTopEdgeDelta * iHeight ) );
			vMorphedRects[i].offsetBtm( (int) ( frctnBtmEdgeDelta * iHeight ) );
		}

	} // ( k_LgbDrawableInterior != eSelnMode )

}







































void LgbDrawableBag::alignLft(void)
{

	update();
	LgbDrawable *pIcon = getMasterIcon();

	LgbDrawableIt_t it = m_lstDrawables.begin();
	while(it!= m_lstDrawables.end()){
		if( (*it)->m_bIsSelected && (*it)->isActive() ){
			(*it)->move( CPoint(pIcon->m_cRect.left - (*it)->m_cRect.left, 0)    );
		}

		it++;
	}
	m_bNeedsUpdate = true;
}

void LgbDrawableBag::alignRgt(void)
{
	update();
	LgbDrawable *pIcon = getMasterIcon();

	LgbDrawableIt_t it = m_lstDrawables.begin();
	while(it!= m_lstDrawables.end()){
		if( (*it)->m_bIsSelected && (*it)->isActive() ){
			(*it)->move( CPoint(pIcon->m_cRect.right - (*it)->m_cRect.right, 0)  );
		}

		it++;
	}
	m_bNeedsUpdate = true;
}


void LgbDrawableBag::alignTop(void)
{

	update();
	LgbDrawable *pIcon = getMasterIcon();

	LgbDrawableIt_t it = m_lstDrawables.begin();
	while(it!= m_lstDrawables.end()){
		if( (*it)->m_bIsSelected && (*it)->isActive() ){
			(*it)->move( CPoint( 0, pIcon->m_cRect.top - (*it)->m_cRect.top ) );
		}

		it++;
	}
		m_bNeedsUpdate = true;

}
void LgbDrawableBag::alignBtm(void)
{

	update();
	LgbDrawable *pIcon = getMasterIcon();

	LgbDrawableIt_t it = m_lstDrawables.begin();
	while(it!= m_lstDrawables.end()){
		if( (*it)->m_bIsSelected && (*it)->isActive() ){
			(*it)->move( CPoint( 0, pIcon->m_cRect.bottom - (*it)->m_cRect.bottom ));
		}

		it++;
	}
		m_bNeedsUpdate = true;

}

void LgbDrawableBag::alignLftRgtCntrs(void)
{
	update();
	LgbDrawable *pIcon = getMasterIcon();

	int avrgVal = ( pIcon->m_cRect.left + pIcon->m_cRect.right ) /2;

	LgbDrawableIt_t it = m_lstDrawables.begin();
	while(it!= m_lstDrawables.end()){
		if( (*it)->m_bIsSelected&& (*it)->isActive() ){

			(*it)->move( CPoint( avrgVal - (*it)->m_cRect.CenterPoint().x , 0) );
		}
		it++;
	}
		m_bNeedsUpdate = true;
}

void LgbDrawableBag::alignTopBtmCntrs(void)
{
	update();
	LgbDrawable *pIcon = getMasterIcon();
	int avrgVal = ( pIcon->m_cRect.top + pIcon->m_cRect.bottom ) /2;

	LgbDrawableIt_t it = m_lstDrawables.begin();
	while(it!= m_lstDrawables.end()){
		if( (*it)->m_bIsSelected && (*it)->isActive() ){

			(*it)->move(CPoint( 0, avrgVal - (*it)->m_cRect.CenterPoint().y) );
		}
		it++;
	}
		m_bNeedsUpdate = true;
}

LucidErrEnum LgbDrawableBag::getZBounds( LgbZBounds_t &zBounds, const SelnFilterEnum &filter )
{
	update();
	bool frontNotYetSampled	=	true;
	bool rearNotYetSampled	=	true;

	zBounds.frontMost = -VERY_LARGE_INT;
	zBounds.rearMost  =  VERY_LARGE_INT;

	int zPos=0;
	//bool selectedOnly = filter==k_SelectedOnly

	LgbDrawableIt_t it = m_lstDrawables.begin();

	while(it!= m_lstDrawables.end()){

		if((*it)->isActive()){

			if(  
				( (filter==k_SelectedOnly) && (*it)->m_bIsSelected ) ||
				( (filter==k_UnselectedOnly) && !(*it)->m_bIsSelected ) ||	
				( filter==k_Any )
				)
				{

				zPos = (*it)->m_iZPosUser;

				if(frontNotYetSampled){
					zBounds.frontMost = zPos;
					frontNotYetSampled = false;
				}else{
					zBounds.frontMost = zBounds.frontMost>zPos? zBounds.frontMost : zPos;
				}

				if(rearNotYetSampled){
					zBounds.rearMost = zPos;
					rearNotYetSampled = false;
				}else{
					zBounds.rearMost = zBounds.rearMost<zPos? zBounds.rearMost : zPos;
				}

			}

		} // if((*it)->isActive())

		it++;
	}

	if(frontNotYetSampled){
		// None selected!
		return kErr_NoneSelected;
	}else{
		return kErr_NoErr;
	}

}

void LgbDrawableBag::setSelectedToZPos(const int & zPos)
{
	update();
	LgbDrawableIt_t it = m_lstDrawables.begin();
	while(it!= m_lstDrawables.end()){
		if( (*it)->m_bIsSelected  && (*it)->isActive() ){
			(*it)->m_iZPosUser = zPos;
		}
		it++;
	}
	m_bNeedsUpdate = true;
}

void LgbDrawableBag::renumberKeepGaps(void)
{
	update();
	sortAscending();

	LgbDrawable *pIcon = NULL;

	if(size() < 2){

		pIcon = m_lstDrawables.front();
		pIcon->m_iZPosUser = 1;
		return;

	} else {

		int currentRevisedPos = 1;

		LgbDrawableIt_t it = m_lstDrawables.begin();
		pIcon = *it;

		int origPos1 = pIcon->m_iZPosUser;
		int origPos2 = 0;

		pIcon->m_iZPosUser = currentRevisedPos;

		while(it!= m_lstDrawables.end()){

			pIcon = *it;
			origPos2 = pIcon->m_iZPosUser;

			// NB If origPos2 == origPos1 we don't need to increment currentRevisedPos;

			if(origPos2 == origPos1+1){

				// Respect the fact if the originals incremented by one.
				currentRevisedPos +=1;

			} else if(origPos2 > origPos1+1){

				// If the original's gap was more than 2, reduce it to 2.
				currentRevisedPos +=2;

			}

			pIcon->m_iZPosUser = currentRevisedPos;
			origPos1 = origPos2;
			it++;

		}

	}

	m_bNeedsUpdate = true;
}


void LgbDrawableBag::renumberConsec(void)
{
	update();
	sortAscending();

	int count = 1;

	LgbDrawableIt_t it = m_lstDrawables.begin();

	while(it!= m_lstDrawables.end()){
		(*it)->m_iZPosUser = count++;
		it++;
	}
	m_bNeedsUpdate = true;

}

void LgbDrawableBag::incrementSelectedZPos(const int &incr )
{
	//update();
	//renumberZ();

	LgbDrawableIt_t it = m_lstDrawables.begin();
	while(it!= m_lstDrawables.end()){
		if( (*it)->m_bIsSelected ){
			(*it)->m_iZPosUser +=incr;
		}
		it++;
	}
	m_bNeedsUpdate = true;
}
// updates all dependent info, then sets 'needsUpdate'-> false
void LgbDrawableBag::update(void)
{
	// Maybe this will get user-reaction tested with value set to 'true'
	const bool LEAN_BY_ZPOS = false;

	if( m_bNeedsUpdate && size() ){

		sortAscending();

		// Update 'perspective' shift of icons.
		LgbDrawableIt_t it = m_lstDrawables.begin();


		// Initialise zPos to be different from 1st icon's zpos.
		int ANY_OFFSET_WILL_DO = 99;
		int oldUserZPos = (*it)->m_iZPosUser - ANY_OFFSET_WILL_DO; 

		int zCount = 0;
		int zCountSimple = 0;

		while(it!= m_lstDrawables.end()){

			if( (*it)->m_iZPosUser <= m_iUpperZActiveLevel){
				// Is the drawable at or below the 'active' level?

				// flag it as active
				(*it)->setActive(true);

				if(LEAN_BY_ZPOS){

					(*it)->m_iZPosProcessed = ++zCountSimple;

				}else{

					// If the next icon has the same z-value as the previous, lean it the same amount as the last
					if( (*it)->m_iZPosUser  != oldUserZPos ) {

						(*it)->m_iZPosProcessed = ++zCount;
					}else{

						(*it)->m_iZPosProcessed = zCount;
					}

					oldUserZPos = (*it)->m_iZPosUser;
				}


				// initialise shown rect to be at same pos as base rect
				(*it)->m_cRectShown = (*it)->m_cRect;

				(*it)->m_cRectShown.OffsetRect( (*it)->m_iZPosProcessed * m_iZLean * ZLEAN_FCTR_X, 
												(*it)->m_iZPosProcessed * m_iZLean * ZLEAN_FCTR_Y );

			} else {

				(*it)->setActive(false);

			}
			it++;

		}

		m_bNeedsUpdate = false;

	}
}

void LgbDrawableBag::setUpperZActiveLimit( const int & iZLevel )
{
	m_iUpperZActiveLevel = iZLevel;
	//LgbDrawableIt_t it = m_lstDrawables.begin();
	m_bNeedsUpdate = true;
}

void LgbDrawableBag::setZlean(const int & val)
{
	update();
	m_iZLean = val;
	m_bNeedsUpdate = true;
}

int LgbDrawableBag::loadTicMarks(std::vector<int> &tics)
{

	const int ANY_FIRST_VAL = 0;
	const int ANY_LAST_VAL = 0;

	update();
	tics.clear();

	if(size()==0){

		tics.push_back(  ANY_FIRST_VAL );
		tics.push_back( ANY_LAST_VAL );
		return 2;

	}else if(size()==1){

		tics.push_back(  (m_lstDrawables.front()->m_iZPosUser) -1 );
		tics.push_back(m_lstDrawables.front()->m_iZPosUser );

		return 2;

	}else{

		sortAscending();

		LgbDrawableIt_t it = m_lstDrawables.begin();

		int oldZPos = (*it)->m_iZPosUser;

		tics.push_back( oldZPos -1 );	// Have a tic mark less than min z, so user can make even lowest
										// - z item disappear.

		tics.push_back( oldZPos );

		int newZPos = ANY_FIRST_VAL;

		while(it != m_lstDrawables.end())
		{
			newZPos = (*it)->m_iZPosUser;

			if(newZPos != oldZPos){
				tics.push_back( newZPos );
			}

			oldZPos = newZPos;
			it++;
		}

		return size();
	}
	m_bNeedsUpdate = true;
}

void LgbDrawableBag::setMasterIcon(LgbDrawable * pIcon)
{

	assert( isAlreadyInList( pIcon ) );

	setCollectiveState( LgbDrawable::k_Master, false );

//	LgbDrawableConstIt_t it = find( pIcon );

	pIcon->setState( LgbDrawable::k_Master, true );

	m_bNeedsUpdate = true;
}

void LgbDrawableBag::setLastClickedIcon(LgbDrawable * pIcon)
{
	setCollectiveState( LgbDrawable::k_LastClicked, false );

	assert( isAlreadyInList( pIcon ) );

	LgbDrawableConstIt_t it = find( pIcon );

	pIcon->setState( LgbDrawable::k_LastClicked, true );

	m_bNeedsUpdate = true;
}

void LgbDrawableBag::setCollectiveState( LgbDrawable::MemberTypesEnum eMember, bool state )
{
	LgbDrawableIt_t it = m_lstDrawables.begin();
	while(it!= m_lstDrawables.end()){
		(*it)->setState(eMember, state );
		it++;
	}
}

bool LgbDrawableBag::isAtFront(LgbDrawable * pIcon)
{
	if(size()==0){

		return false;
	}else{

		LgbDrawableConstIt_t it = find( pIcon );

		assert( it != m_lstDrawables.end() );

		if(it==m_lstDrawables.begin() ){

			return true;
		}else{

			return false;
		}
	}
}

LgbDrawable * LgbDrawableBag::front(void)
{
	return m_lstDrawables.front();
}

LgbDrawable * LgbDrawableBag::getMasterIcon(void)
{
	LgbDrawableIt_t it = m_lstDrawables.begin();

	while(it!= m_lstDrawables.end()){

		if( (*it)->getState( LgbDrawable::k_Master )){
			return *it;
		}
		it++;
	}

	// trip if no master found
	assert(1==2);

	return NULL; // gets rid of compiler warning about not returning
}

LgbDrawable * LgbDrawableBag::getLastClickedIcon(void)
{
	LgbDrawableIt_t it = m_lstDrawables.begin();

	while(it!= m_lstDrawables.end()){

		if( (*it)->getState( LgbDrawable::k_LastClicked )){
			return *it;
		}
		it++;
	}

	// trip if no master found
	assert(1==2);

	return NULL; // gets rid of compiler warning about not returning
}

void LgbDrawableBag::equaliseWidths(void)
{

	update();
	//CPoint avCntr;
	LgbDrawable *pIcon = getMasterIcon();

	int masterWidth = ( pIcon->m_cRect.Width() );

	LgbDrawableIt_t it = m_lstDrawables.begin();
	while(it!= m_lstDrawables.end()){
		if( (*it)->m_bIsSelected&& (*it)->isActive() ){
			// adjust right given new width, anchored at top left
			(*it)->offsetRgt( masterWidth - (*it)->m_cRect.Width()  );
		}
		it++;
	}
}

void LgbDrawableBag::equaliseHeights(void)
{

	update();
	CPoint avCntr;
	LgbDrawable *pIcon = getMasterIcon();

	int masterHt = ( pIcon->m_cRect.Height() );

	LgbDrawableIt_t it = m_lstDrawables.begin();
	while(it!= m_lstDrawables.end()){
		if( (*it)->m_bIsSelected&& (*it)->isActive() ){
			// adjust bottom given new height, anchored at top left
			(*it)->offsetBtm( masterHt - (*it)->m_cRect.Height() );
		}
		it++;
	}
}

void LgbDrawableBag::copySelectedDrawables(LgbDrawableBag & dBag)
{
	dBag.reset();
	LgbDrawableIt_t it = m_lstDrawables.begin();
	while(it!= m_lstDrawables.end()){
		if( (*it)->m_bIsSelected  && (*it)->isActive() ){
			dBag.push_back( *it );
		}
		it++;
	}
}

void LgbDrawableBag::setNeedsUpdate(void)
{
	m_bNeedsUpdate = true;
}

void LgbDrawableBag::UpdateProjectMetaData()
{
	LgbDrawableIt_t it = m_lstDrawables.begin();

	while(it!= m_lstDrawables.end()){
		(*it)->UpdateProjectMetaData();
		it++;
	}

}
