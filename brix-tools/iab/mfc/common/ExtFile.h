/** @file ExtFile.h
 * 
 * @author: Matthew Rutherford
 * @version: $Revision: 577 $
 * @date: $Date$
 * 
 * Copyright (c) Ncapsa Ltd, 2007. All rights reserved.
 */

#pragma once

#include "LucidEnums.h"

//! The base class for representing external files in LAB and LGB projects
class ExtFile
{
public:
	ExtFile(void);
	ExtFile(const ExtFile &file);

	~ExtFile(void);

// Attributes

protected:
	CString m_csHostFileName;	//!< The file name on the host (PC)
	CString m_csDescription;	//!< User's description of the file
	CString m_csFilePrefix;		//!< 
	CString m_csFileExtension;

// Methods
public:
	bool operator==(const ExtFile &file) const;
	LucidErrEnum getHostFileName(CString &csFileName) const;
	LucidErrEnum setHostFileName(const CString &csFileName);

	LucidErrEnum getDescription(CString &csDescr) const;
	LucidErrEnum setDescription(const CString &csDescr);

};
