#include "stdafx.h"
#include "InlineText.h"

InlineText::InlineText(void)
{
}

InlineText::InlineText(CString csClass, LgbColorsDef cColors, CString csFont)
{
	m_csClass = csClass;
	m_cColors = cColors;
	m_csFont = csFont;
}

InlineText::~InlineText(void)
{
}

CString InlineText::GetClass()
{
	return m_csClass;
}

CString InlineText::GetFont()
{
	return m_csFont;
}

void InlineText::GetColors(LgbColorsDef &cColors)
{
	cColors = m_cColors;
}

void InlineText::SetClass(CString csClass)
{
	m_csClass = csClass;
}

void InlineText::SetFont(CString csFont)
{
	m_csFont = csFont;
}

void InlineText::SetColors(LgbColorsDef cColors)
{
	m_cColors = cColors;
}

void InlineText::SetBgColor(unsigned char iAlpha, unsigned char iRed, unsigned char iGreen, unsigned char iBlue)
{
	m_cColors.m_iBgAlpha = iAlpha;
	m_cColors.m_iBgRed = iRed;
	m_cColors.m_iBgGreen = iGreen;
	m_cColors.m_iBgBlue = iBlue;
}