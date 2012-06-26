/** @file LgbTextIcon.h
 * Represents an resizable icon with a text label and settable fore- and background cols.
 * @author: Matthew Rutherford
 * @version: $Revision: 577 $
 * @date: $Date$
 * 
 * Copyright (c) Ncapsa Ltd, 2007. All rights reserved.
 */
#pragma once
#include "lgbrect.h"
#include "LgbResizedDrawable.h"
#include "LgbColorsDef.h"
#include <fstream>
#include "../common/LucidTypedefs.h"
#include "InlineText.h"
#include "LgbFont.h"

#define LGBTEXTICON_DEF_H_EXT 220 //!< Default icon width.
#define LGBTEXTICON_DEF_V_EXT 100 //!< Default icon vert extent.

class font;

class LgbTextIcon: public LgbResizedDrawable
{

public:

	LgbTextIcon();
	LgbTextIcon( const LgbTextIcon &icon );

	//! Constructor
	/*!
	\param rect icon's outline border
	\param type ie textbox, bitmap etc
	\param tag id string from LAB
	\param zPos the z-level of the icon
	*/
	LgbTextIcon(	
			const CRect			&rect,
			const CString		&type,	
			const CString		&tag,				
			const int			&zPos
				);

	//! Constructor
	/*!
	\param rect icon's outline border
	\param type ie textbox, bitmap etc
	\param tag id string from LAB
	\param zPos the z-level of the icon
	\param colors structure for fore- & background colors
	*/
	LgbTextIcon(	const CRect			&rect,
					const CString		&type,	
					const CString		&tag,	
					const int			&zPos,
					const LgbColorsDef	&colors
				);

	//! Std destructor
	~LgbTextIcon( void );

	//! Returns the icon's colors
	LgbColorsDef getColors();

	//! Sets the icon's colors
	void setColors( const LgbColorsDef &colors  );

	//! Causes icon to draw itself
	void Draw(CDC *pMemDC, const int &zLower, const int &zUpper, const int &zLeanPerZLevel );

	//! Sets the icon's tag label to be drawn
	void drawTag(CDC * pDC);

	//! Returns icon class-id enum
	LgbClassIDEnum getClassId();

	//! saves contents to file
	/*! usually not aclled directly, but via call from LgbDrawableBag
	which has already opened file, etc
	*/
	void saveToFile( std::ofstream &rFile );

	// updates the project meta data with the bdf font file used by this text icon
	void UpdateProjectMetaData();

	// Change alpha value
	void	changeAlpha( const int &increment );

private:
	int m_iFontSize;
	CString m_csFont;
	int m_iLeftIndent;
	int m_iRightIndent;
	int m_iTopIndent;
	int m_iBottomIndent;
	int m_iLineSpacing;
	int m_iNumberOfLines;

public:
	LgbColorsDef m_cColors;
	const static int LgbTextIcon_FlagText;
	const static int LgbTextIcon_FlagBackground;
	static vector<InlineText> c_vInlineTextVec;
	static bool c_bIsTextStyleSaved;
	static vector<LgbFont> c_vFontVec;

public:
	//! Inner class used for preparation of field-values in the properties dialog for multiple selections
	/*! A given boolean fields is set to true if all the selections haave the same value for the
	associated field.  If so, this common value can be loaded into the dialog's field.  Otherwise, the
	dialog would be set blank
	*/
	class Scan
	{

	public:
		void init();
		bool allScanFieldsFalse();

		LgbDrawable::Scan m_cDrblScan;
		bool m_bSameColors;

		bool m_bSameFgAlpha; //!< true if all selections have same f/g alpha
		bool m_bSameBgAlpha; //!< true if all selections have same b/g alpha

		bool m_bSameFont; //!< true if all selections have same font
		bool m_bSameFontSize; //!< true if all selections have same font size

		bool m_bSameLeftIndent; // true if all selections have same left indent
		bool m_bSameRightIndent; // true if all selections have same right indent
		bool m_bSameTopIndent; // true if all selections have same top indent
		bool m_bSameBottomIndent; // true if all selections have same bottom indent

		bool m_bSameLineSpacing; // true if all selections have same line spacing

		bool m_bSameNumberOfLines;
	};

	//! The main method that scans the selected icons.
	/*!
	The method is called once for each selected icon, with the Scan being initialised
	before the call to the 1st drawable.  The 'sameness' of the fields iss initially true,
	but tends to get set to false as more icons are scanned for equality.
	\param drbl The current icon being scanned
	\param scanSoFar the scan, as set by all calls to this method so far for previous icons
	*/
	Scan scanFieldEquality( LgbTextIcon *pTxtIcon, LgbTextIcon::Scan &scanSoFar );

	void testEqualityScan();

public:
	void setAlpha( unsigned char val, const int & flags );

	CString getFont(void);
	int		getFontSize(void);
	int		getLeftIndent(void);
	int		getRightIndent(void);
	int		getTopIndent(void);
	int		getBottomIndent(void);
	int		getLineSpacing(void);
	int		getNumberOfLines(void);

	void setFont( const CString &font);
	void setFontSize( const int sz);
	void setLeftIndent(const int iLeftIndent);
	void setRightIndent(const int iRightIndent);
	void setTopIndent(const int iTopIndent);
	void setBottomIndent(const int iBottomIndent);
	void setLineSpacing(const int iLineSpacing);

	void LoadFonts();
	EhsGraphicsFontClass* GetFontPtr(CString csFontName);
	CString GetFontFileName(CString csFontName);
};
