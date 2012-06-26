#pragma once

#include <vector>
#include <list>
#include "IconSelection.h"
#include "LgbDrawable.h"
#include "LgbImageIcon.h"
#include "LgbTextIcon.h"
#include "LgbPatchIcon.h"

#define ZLEAN_FCTR_X 2 //!< How much to lean icons in X (per unit of z-pos) for 3D view
#define ZLEAN_FCTR_Y 2 //!< How much to lean icons in Y (per unit of z-pos) for 3D view

using namespace std;

class LgbTextIcon;

//! Class to store, interrogate andd manage the set of icons which are currently loaded into LGB
/*! m_lstDrawables is the main store for the (ptrs to) these.
*/
class LgbDrawableBag
{
public:

	LgbDrawableBag(void);   //!< Std Constructor
	~LgbDrawableBag(void);  //!< Std Destructor

	list< LgbDrawable * > m_lstDrawables; //!< Holder for the pointers to drawable icons

	//! enum used as parameter in some methods, to filter what gets 'processed' by the method
	enum SelnFilterEnum {
		k_Any,
		k_SelectedOnly,
		k_UnselectedOnly
	};

	//! Loads selected textIcon pts and selected bitmaps into the respective holders
    /*!
      \param txtIcons Holder for selected text icons.
      \param bmpIcons Holder for selected bitmap icons.
    */
	void getSelections( IconSelection< LgbTextIcon > &txtIcons, 
						IconSelection< LgbPatchIcon > &ptchIcons,
						IconSelection< LgbImageIcon > &bmpIcons );

	//! Sorts list of icons into order of ascending z-pos.
	void sortAscending();

	//! Loads the border-rectangles of selecetd icons into 'rRects'
	/*! NB. 1st empties rRects */
	int  loadSelectedOutlines( vector <LgbRect> &rRects );

	// void setSelnState( const bool &state );

	//! Sets the state of selection of icons in the bag, to the given, according to whether icon has matching type
	/*!
	\param state The value of the state to which to sets icon's 'selected' ness
	\param eIconType The type of icon which is to be matched if  
	*/
	void setCollectiveState(const bool &state, LgbDrawable::MemberTypesEnum eMember, const LgbIconTypeEnum &eIconType);
	//void setSelnState( const bool &state, const LgbIconTypeEnum &eIconType );

	//! Determines whether a point (in pixel coords) is over an icon.
	/*!
	\param point the point to be tested
	\param selected ptr to icon which lies around point (NULL if no icon present at point)
	\return eenum inicating whether point lies on centre, left edge etc of icon, or on no icon
	*/
	LgbRectSelTypeEnum 
		getSelectedIcon(
		const CPoint &point, 
		LgbDrawable *  &selected );


	//! Sets selection state of icons within a rectangular 'marquee'
	/*!
	\param marquee
	\param getPartials If true, get icons at least partially within the the marquee, if false, get those 
	only totally within marquee.
	\param toggle If true, toggle the selection of selected-in-this-action things, rather than setting them to 
	absolute 'seceted' values.
	*/
	bool 
		setSelectedIcons(
		const LgbRect &marquee, 
		const bool &getPartials,
		const bool toggle  );

	//! Determines whether an icon is already in the list of drawables.
	/*!
	\param type The type of widget ( bitmap, text etc)
	\param widgetTag The widget's tag.
	\param it An iterator to the pointer to the icon (= end() id widget not found)
	\return true if widget is in list, false otherwise.
	*/
	bool 
		isAlreadyInList( 
		const CString &type, 
		const CString &widgetTag, 
		LgbDrawableConstIt_t &it ) const;

	//! Determines whether an icon is already in the list of drawables.
	/*!
	\param pDrawable The widget to be found (must point to a valid widget).
	\param it An iterator to the pointer to the icon (= end() id widget not found)
	\return true if widget is in list, false otherwise.
	*/
	bool 
		isAlreadyInList( 
		const LgbDrawable const *pDrawable, 
		LgbDrawableConstIt_t &it ) const;

	//! Determines whether an icon is already in the list of drawables.
	/*!
	\param pDrawable Ptr to the widget to be found (must point to a valid widget).
	\return true if widget is in list, false otherwise.
	*/
	bool isAlreadyInList( const LgbDrawable const *pDrawable ) const;

	//! Determines whether an icon is already in the list of drawables.
	/*!
	\param type The type of widget ( bitmap, text etc)
	\param tag The widget's tag.
	\return An iterator to the pointer to the icon (== end() if widget not found)
	*/
	LgbDrawableConstIt_t find( const CString &type, const CString &tag ) const;

	//! Determines whether an icon is already in the list of drawables.
	/*!
	\param pDrawable Ptr to the widget to be found (must point to a valid widget).
	\return An iterator to the pointer to the icon (= end() id widget not found)
	*/
	LgbDrawableConstIt_t find( const LgbDrawable const *pDrawable ) const;

	//! Counts how many icons are currently selected
	/*!
	\return The number of icons selected.
	*/
	int getSelectionCount();

	//! Sets the 'to be deleted' tag on each icon to 'state'
	void setDeletionTags( const bool &state );

	//! deletes all icons that have 'to be deleted' tag == true
	int doDeletions();

	//! resets contents to null
	void reset();

	//! deletes all contained drawables from the heap
	void freeAllMemory();

	//! Move active, selected icons by 'vec'.
	void moveIcons( const CPoint &vec );

	//! Returns the number of icons currently loaded into bag
	size_t size();

	//! Moves the top, left, right etd edge of all selected icons
	/*!
	\param selMode enum indicating whether to move top, right, left etc of icons
	\param mov How many pixels to move the respective edge by
	*/
	void resize( const LgbRectSelTypeEnum &selMode, const int &mov );


	//! Moves the top-left, top-right etc corner of all selected icons
	/*!
	\param selMode enum indicating whether to move top-right, bottom-left etc of icons.
	\param mov How many pixels (x,y) to move the respective corner by.
	*/
	void resize( const LgbRectSelTypeEnum &selMode, const CPoint &mov );

	//! Saves all icons' details to disk
	/*!
	\param fileName name of disk file to be written
	*/
	void saveToFile(const CString &fileName);

	//! Cause all active icons top be drawn to screen
	void Draw( CDC *dc, const CRect &clientRect, const COLORREF backGround );


	//! Add a ptr to an icon to contents
	LucidErrEnum push_back( LgbDrawable *addable);


	//LgbDrawableIt_t insert( LgbDrawableIt_t it, LgbDrawable *addable );

	//! erases an icon from contents
	/*!
	\param it iterator to the icon pointed -to
	\return an iterator pointing to the item after the one that was erased
	*/
	LgbDrawableIt_t erase (  LgbDrawableIt_t &it );

	//! erases an icon from contents
	/*!
	\param pIcon ptr to icon to be erased
	\return an iterator pointing to the item after the one that was erased
	*/
	LgbDrawableIt_t erase (  LgbDrawable *pIcon );


	//! Processes contents an selections on event of left mouse button being released
	/*!
	\param  moveVec vector from initial click pt to point 
	\param  moveMode Where on an icon the user initially left-clicked (indicating what he wanted to 
		do to the selections.
	*/
//	void processLftBtnUp( 
//		const CPoint & moveVec, 
//		const LgbRectSelTypeEnum moveMode
//		);

	bool test();

public:

//	void processLftBtnUp(
//		const CPoint & moveVec,
//		const LgbRect moveMode );

	//! Draw (with XOR pen) the resized or translated outlines of selected icons 
	// both in this and previous drag posns.
	/*!
	\param lastMoveVec the vector from initial LH click to last drag position
	\param thisMoveVec the vector from initial LH click to present drag position
	*/
	void drawGhostDragOutlines(
		const LgbRectSelTypeEnum & eSelnMode,
		const CPoint & lastMoveVec,
		const CPoint & thisMoveVec,
		CClientDC *dc
		);

	void setMorphedRectangles(
		vector< LgbDrawable *>	vMorphedIcons,
		vector< LgbRect >		vMorphedRects 
					);

	void getMorphedRectangles(
				const LgbRectSelTypeEnum	&eSelnMode,
				const CPoint				&moveVec,
				const int					&masterRectWidth,
				const int					&masterRectVertExtent,
				const bool					&useActualRectPos,
				const vector<LgbDrawable *>	&vOrigDrawables,
					  vector< LgbRect >		&vMorphedRects
				);

public:
	//LucidErrEnum getLftmostEdge(int & pos);
	//LucidErrEnum getRgtmostEdge(int & pos);
	//LucidErrEnum getTopmostEdge(int & pos);
	//LucidErrEnum getBtmmostEdge(int & pos);

	//LucidErrEnum getAverageCentre(CPoint &centrePnt );

	void alignLft(void);//!< Moves selected icons other than master to have left-edges aligned with master

	void alignRgt(void);//!< Moves selected icons other than master to have right-edges aligned with master

	void alignTop(void);//!< Moves selected icons other than master to have top-edges aligned with master

	void alignBtm(void);//!< Moves selected icons other than master to have bottom-edges aligned with master

	void alignLftRgtCntrs(void);//!< Moves selected icons other than master to have cntrs aligned left-right with master

	void alignTopBtmCntrs(void);//!< Moves selected icons other than master to have cntrs aligned up-down with master

	//! Finds the min and max z-pos's of icons, fitering by selection state.
	/*! 
	\param zBounds The max and min z-pos's 
	\param filter flag to indicate whether to filter in either selected or unselected icons' zpos's
	*/
	LucidErrEnum getZBounds(
		LgbZBounds_t &zBounds, 
		const SelnFilterEnum &filter );

	//! Set zpos of all selected icons to 'zPos'
	void setSelectedToZPos(const int & zPos);

	//! Renumber all icons zpos' consecutively from 1, maintaining order
	void renumberConsec(void);

	//! compress gaps in z-numbering that are more than 2 to be equal to 2
	/*! Eg 1,2,3, 5,5, 11,11,11, 18, 101, 102,102,102 -> 1,2,3, 5,5, 7,7,7, 9, 11, 12,12,12 */
	void renumberKeepGaps(void);

	//! Increment zpos's of by 'incr'
	void incrementSelectedZPos(const int &incr );

	//! For all icons, set the flag controlling whether to show icons' tag to value of 'state'
	void setTagShowState(const bool &state);

protected:
	//! If true, indicates that 'update' should be called before redrawin icons
	bool m_bNeedsUpdate;

	//! z-pos above which icons won't be displayed
	int m_iUpperZActiveLevel;

	//! updates the 3d-leaned icon-outline, and the 'active' status, then sets 'needsUpdate'-> false
	/*! Updates are possibly needed according changes in z-pos of icons or of z-clip level. */
	void update(void);

public:
	//! Set the upper 'z' pos clip level, above which icons won't be shown
	void setUpperZActiveLimit(const int & iZLevel);

	//! Set the amount of pseudo 3D lean to display on icons
	void setZlean(const int & iZLeanLevel);

	//! Load into 'tics' the z-pos's at which icons exist
	int loadTicMarks(std::vector<int> &tics);

	//! Sets the master icon
	void setMasterIcon(LgbDrawable * masterIcon);

	//! Sets the last icon clicked
	void setLastClickedIcon(LgbDrawable * pIcon);

	//! sets various boolean flags for all icons to given value
	/*!
	\param eMember flag indicating which combination of fields should be set
	\param state the value to which to set the state
	*/
	void setCollectiveState( LgbDrawable::MemberTypesEnum eMember, bool state );

	//! Returns true if icon pointed-to by pIcon is at the front of the list of icons.
	/*! Main use is for telling if the icon is the master, ie if it at the front of the
	m_cSelections list
	*/
	bool isAtFront(LgbDrawable * pIcon);

	//! Returns ptr to the icon at the front of the list 
	LgbDrawable * front(void);

	//! Returns ptr to the master icon
	LgbDrawable * getMasterIcon(void);

	//! Returns ptr to the last-clicked icon
	LgbDrawable * getLastClickedIcon(void);

	//! equalise widths of seleected icons to that of the master
	void equaliseWidths(void);

	//! equalise vertical extents of seleected icons to that of the master
	void equaliseHeights(void);

	//! Copy selected icon ptrs into dBag.
	/*! Used to get the set of ptrs into m_cSelections when 
	a group-selection command (such as select all) is issued. */
	void copySelectedDrawables(LgbDrawableBag & dBag);

	// Updates project meta data in particular the BDF files
	void UpdateProjectMetaData();

protected:

	//! Controls 'z-lean' pseudo-perspective view
	int m_iZLean;

public:
	void setNeedsUpdate(void);
};
