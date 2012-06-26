// ExtGuiFile.h: interface for the GuiFile class
//
//////////////////////////////////////////////////////////////////////

#pragma once
#include "ExtFile.h"
#include "../common/LucidTypedefs.h"
#include "LucidEnums.h"

class ExtGuiFile: public ExtFile
{

public:
	ExtGuiFile(void);
	ExtGuiFile(const CString &hostFileName);
	ExtGuiFile(const ExtGuiFile &file);
	ExtGuiFile(const GuiFileEssentialData_t &fileData);


public:
	~ExtGuiFile(void);


// Attributes
protected:
	CString m_csScreenTag;


// Methods
public:
	LucidErrEnum getScreenTag(CString &tag) const;
	LucidErrEnum setScreenTag(const CString &tag);


};
