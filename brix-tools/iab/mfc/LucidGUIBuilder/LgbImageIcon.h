/** @file LgbImageIcon.h
 * Extends LgbDrawable to represent an icon that is drawn with a bitmap.
 * @author: Matthew Rutherford
 * @version: $Revision: 577 $
 * @date: $Date$
 * 
 * Copyright (c) Ncapsa Ltd, 2007. All rights reserved.
 */


#pragma once

#include <fstream>

#include "LgbResizedDrawable.h"
#include "../../environment/PngImage/PngImage.h"
#include "../common/bmpfile.h"
#include "../common/LgbIconDataStrucs.h"

class Bitmap;
class PngImage;

//! Stores / represents metadata about, and draws a (png) image as shown in LGB.
class LgbImageIcon : public LgbResizedDrawable  
{

public:

	//! Constructor

	LgbImageIcon( const LgbImageIcon &icon );


	/*!
	\param rect icon'ss outline border
	\param type ie textbox, bitmap etc
	\param tag id string from LAB
	\param zPos the z-level of the icon
	\param projDir current project folder
	\param name of file for bitmap (excluding path)
	*/
	LgbImageIcon(	const CRect		&rect = CRect(),
					const CString	&type = "",	
					const CString	&tag = "",
					const int		&zPos = 0,
					const int		&alpha = 0,
					const CString	&projDir = "",
					const CString	&fileName = "",
					const int		&lockApect = 0
				);

	virtual		~LgbImageIcon();


	//! Type of image file for this instance
	enum ImageTypeEnum {
		k_Bitmap,
		k_Png,
		k_Gif,
		k_NULL
	};

	CString m_csProjectDir; //!< Path of present project folder



	ImageTypeEnum getImageType() const;//!< Returns type of image file for this icon

	void Draw(CDC *pMemDC, const int &zLower, const int &zUpper, const int &zLeanPerZLevel );

	//! Sets value of project folder to 'projDir'
	void setProjectDir( const CString &projDir );

	CBitmap * getBitmapFromPng( PngImage &png, CDC* pDC );

	LgbClassIDEnum getClassId();

	//! Returns bitmap file
	CString getFileName() const;

	// Sets name of bitmap file
	void	changeImageFile(const CString &fileName );

	// Sets name of bitmap file
	void	setImageFile(const CString &fileName, const ImageTypeEnum &fileType, bool bChangedImage );

	// Change alpha value
	void	changeAlpha( const int &increment );

	// Change alpha value
	void setAlpha( const int &val );

	// Change alpha value
	int	getAlpha() const;

	// Change lock aspect value
	void setLockAspect( const int &val );

	// Change lock aspect value
	int	getLockAspect() const;

	// Get image height
	long LgbImageIcon::getImageHeight() const;

	// Get image width
	long LgbImageIcon::getImageWidth() const;

	// Get image aspect ratio
	float LgbImageIcon::getImageHtoW() const;

protected:

	ImageTypeEnum getFileNameType( const CString &fileName ) const;//!< returns type of file supporting the icon

	ImageTypeEnum m_eImageType;//!< type of file supporting the icon

	CString		m_csFileName; //!< The name of the bitmap file

	int		m_iLockApect; //!< Lock aspect ratio to image ratio flag



	Bitmap m_cBitmap; //!< Represents a bitmap itself

	PngImage *m_pPngImage; //!< Represents a png image itself

	Bitmap *m_pDrawnThing; //!< Represents a bitmap itself

	void saveToFile( std::ofstream &rFile ); //!< Causes icon to write its details to file

public:
	//! Inner class used for preparation of field-values in the properties dialog for multiple selections
	/*! A given boolean fields is set to true if all the selections haave the same value for the
	associated field.  If so, this common value can be loaded into the dialog's field.  Otherwise, the
	dialog would be set blank
	*/
	class Scan
	{

	public:
		void init();//!< Sets all fields to true for  initialisation

		bool allScanFieldsFalse();//!< Determines if all 'sameness' booleans are false - at this point, cease checking

		LgbDrawable::Scan m_cDrblScan; //!< represent scan of fields common to parent class

		bool m_bSameFileName; //!< true if all selections have same file name

		bool m_bSameLockAspect; //!< true if all selections have same lock aspect ratio

		bool m_bSameAlpha; //!< true if all selections have same alpha

	};

	//! The main method that scans the selected icons.
	/*!
	The method is called once for each selected icon, with the Scan being initialised
	before the call to the 1st drawable.  The 'sameness' of the fields is initially true,
	but tends to get set to false as more icons are scanned for equality.
	\param pBmpIcon The current icon being scanned
	\param scanSoFar the scan, as set by all calls to this method so far for previous icons
	*/
	Scan scanFieldEquality( 
		LgbImageIcon *pBmpIcon, 
		LgbImageIcon::Scan &scanSoFar
		);


public:

	unsigned char *m_pPreMultBGRA;//!< Pre-multiplied image data for use in 'alphablend'

private:
	unsigned char m_iAlpha;//!< Overll alpha-value for this icon.
	long iImageHeight;
	long iImageWidth;
	float dImageHtoW;
};

