#include "stdafx.h"
#include "LgbFont.h"

LgbFont::LgbFont(void)
{
}

LgbFont::LgbFont(CString csFontName, CString csFontFileName, EhsGraphicsFontClass* pFont)
{
	m_csFontName = csFontName;
	m_csFontFileName = csFontFileName;
	m_pFont = pFont;
}

LgbFont::~LgbFont(void)
{
}

CString LgbFont::GetFontName()
{
	return m_csFontName;
}

CString LgbFont::GetFontFileName()
{
	return m_csFontFileName;
}

EhsGraphicsFontClass* LgbFont::GetFontPtr()
{
	return m_pFont;
}