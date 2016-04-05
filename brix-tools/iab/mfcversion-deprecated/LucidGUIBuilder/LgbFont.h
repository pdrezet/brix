#pragma once

#include "font.h"

class LgbFont
{
public:
	LgbFont(void);
	LgbFont(CString csFontName, CString csFontFileName, EhsGraphicsFontClass* pFont);

public:
	~LgbFont(void);

private:
	CString m_csFontName;
	CString m_csFontFileName;
	EhsGraphicsFontClass* m_pFont;

public:
	CString GetFontName();
	CString GetFontFileName();
	EhsGraphicsFontClass* GetFontPtr();
};
