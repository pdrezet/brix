/** @file LgbDrawable.h
 * Represents an LGB (rectangular-bordered) icon that knows how to draw itself.
 * @author: Matthew Rutherford
 * @version: $Revision: 577 $
 * @date: $Date$
 * 
 * Copyright (c) Ncapsa Ltd, 2007. All rights reserved.
 */

#pragma once
#include "stdafx.h"
#include "lgbrect.h"
#include "../common/LucidTypedefs.h"
#include <fstream>
#include "afxwin.h"

#define LGBDRAWABLE_DEF_H_EXT 140 //!< 
#define LGBDRAWABLE_DEF_V_EXT 50
#define LGBDRAWABLE_EDGE_BAND_MARGIN 4 //!< The margin by which a pt must be inside an icon to be considered interior rather than edge

//! Represents an LGB (rectangular-bordered) icon that knows how to draw itself.
class LgbDrawable
{

public:

	LgbDrawable();//!< Std Constructor

	//! Constructor
	/*!
	\param rect icon'ss outline border
	\param type ie textbox, bitmap etc
	\param tag id string from LAB
	\param zPos the z-level of the icon
	*/
	LgbDrawable(	const CRect		&rect,
					const CString	&type,
					const CString	&tag,	
					const int		&zPos
				);

	LgbDrawable( const LgbDrawable &icon );

	virtual ~LgbDrawable(void); //!< Std destructor

	//! definition of filetr types for what logical fields to change in some calls to collective state-change
	enum MemberTypesEnum {
		k_Master				= 1,
		k_Selected				= 2,
		k_Active				= 4,
		k_MasterSelectedActive	= 8,
		k_LastClicked			= 16
	};

	//! Set the logical members that match 'eMember' to value 'state'
	void setState( MemberTypesEnum eMember, bool state );

	//! Returnsd the value of logical fields specified by 'eMember'
	bool getState( MemberTypesEnum eMember );


	LgbRect m_cRect;			//!< The 'actual' position of the drawable.

	LgbRect m_cRectShown;		//!< The 3D-leaned position that the drawable will be 'drawn' in.

	CString m_csTag;			//!< The text always shown in middle of icon.

	CString m_csType;			//!< The type of the icon - textbox, bitmap etc

	int m_iZPosUser;			//!< The icon's z-position

	int m_iZPosProcessed;

	bool m_bShowTag;		//!< Whether to show the icon's tag
	bool m_bIsSelected;		//!< Whether the user has currently selected this icon
	bool m_bIsToBeDeleted;	//!< Whether the icon is no longer in sodl, and needs to be deleted

	virtual void DrawSelectionBlobs(
		CDC *pMemDC
		); //!< Message to draw the icon to screen

	virtual void DrawFrame( CDC *pMemDC );

	virtual void Draw( 
		CDC *pMemDC, 
		const int &zLower, 
		const int &zUpper , 
		const int &leanDispPerZLevel
		); //!< Message to draw the icon to screen

	virtual void Draw3DPerspective( 
		CDC *pMemDC, 
		const int &zLower, 
		const int &zUpper , 
		const int &leanDispPerZLevel
		); //!< Message to draw the icon to screen

	//! Determines if the drawable's 3D-leaned border rectangle is around the point
	/*!
	\param point The point to be tested
	\param tol The aamount by which the point must be inside the border to be considered 'interior' not 'edge'
	NB Overridded by sub-classes, as for example a textbox is resizable, so needs to return if the pt
	is left, right, corner etc, whereas a bitmap isn't resizable / doesn't
	*/
	virtual LgbRectSelTypeEnum getSelectionMode( 
		const CPoint &point, 
		const int &tol = LGBDRAWABLE_EDGE_BAND_MARGIN  );


	LgbDrawable & operator=( const LgbDrawable &x );

//	bool operator>( LgbDrawable *drwbl  );

	//bool equals(const LgbDrawable &drawable) const;

	//! Write data to file
	/*!
	File should already be open: this call should come from LgbDrawablebAG
	*/
	virtual void saveToFile(  std::ofstream &rFile );

	// Updates the project meta data with the bdf files used
	virtual void UpdateProjectMetaData();

	bool testPointIsOnEdge();

	//bool testEquals();

	bool test();

	//! Return an enum identifying a string
	virtual LgbClassIDEnum getClassId();

	// Move thee drawable though x,y vector 'vec'
	virtual void move( const CPoint &vec);

	virtual void offsetRgt(const int &mov ); //!< Move border's right side or not -depending on sub-class
	virtual void offsetLft(const int &mov ); //!< Move border's left side or not -depending on sub-class
	virtual void offsetTop(const int &mov ); //!< Move border's top side or not -depending on sub-class
	virtual void offsetBtm(const int &mov ); //!< Move border's bottom side or not -depending on sub-class

	virtual void offsetTopRgt(const CPoint &mov ); //!< Move border's top-right side or not -depending on sub-class
	virtual void offsetTopLft(const CPoint &mov ); //!< Move border's top-left side or not -depending on sub-class
	virtual void offsetBtmLft(const CPoint &mov ); //!< Move border's bottom-left side or not -depending on sub-class
	virtual void offsetBtmRgt(const CPoint &mov ); //!< Move border's bottom-right side or not -depending on sub-class

protected:

	CPen	m_cPenTagText;  //!< Pen for writing text (tags, etc)
	CPen	m_cPenSelOutline;   //!< Pen drawing selected-icon's border-rect
	CPen	m_cPenUnselOutline;   //!< Pen drawing unselected-icon's border-rect

public:

	//! Inner class used for preparation of field-values in the properties dialog for multiple selections
	/*! A given boolean fields is set to true if all the selections haave the same value for the
	associated field.  If so, this common value can be loaded into the dialog's field.  Otherwise, the
	dialog would be set blank
	*/
	class Scan
	{

	public:


		bool m_bSameLft;	//!< true if all selections have same left border posn
		bool m_bSameRgt;	//!< true if all selections have same right border posn
		bool m_bSameTop;	//!< true if all selections have same top border posn
		bool m_bSameBtm;	//!< true if all selections have same bottom border posn
		bool m_bSameWidth;	//!< true if all selections have same width
		bool m_bSameVrtExtnt; //!< true if all selections have same vert extent

		bool m_bSameZPos; //!< true if all selections have same z-pos

		bool m_bSameTag; //!< true if all selections have same tag 
		bool m_bSameType; //!< true if all selections have same type



		void init();		//!< Initialises fields prior to scan of icons

		bool allScanFieldsFalse();	//!< returns true if all logical fileds are false - no point then in more scanning
	};

	//! The main method that scans the selected icons.
	/*!
	The method is called once for each selected icon, with the Scan being initialised
	before the call to the 1st drawable.  The 'sameness' of the fields iss initially true,
	but tends to get set to false as more icons are scanned for equality.
	\param drbl The current icon being scanned
	\param scanSoFar the scan, as set by all calls to this method so far for previous icons
	*/
	Scan scanFieldEquality( 
		LgbDrawable *drbl, 
		LgbDrawable::Scan &scanSoFar
		);

	//void testEqualityScan();

protected:

	bool m_bIsActive;	//!< If true, indicates the icon is active - ie its z-pos is at least as low as z-clip plane

	bool m_bIsMaster;	//!< If true, this icon is the current master

	bool m_bIsLastClicked;	//!< If true, this icon is the last-clicked icon


public:

	bool operator==( const LgbDrawable &rhs );

	void setActive(const bool & state); //!< Sets the 'active' status to value of 'state'

	bool isActive(void); //!< Returns true if icon is active

	virtual void drawTag(CDC * pDC); //!< Draws the icon's tag

	//virtual void setPerCentOpacity(const int & val);

	//unsigned char  getPerCentOpacity();

	//unsigned char getAlpha();

private:
	//int m_iPerCentOpacity;
private:

	int m_iDrawLayer;
};




