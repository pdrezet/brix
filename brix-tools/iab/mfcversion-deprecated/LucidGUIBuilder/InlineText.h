#pragma once
#include "stdafx.h"
#include "LgbColorsDef.h"

class InlineText
{
public:
	InlineText(void);
	InlineText(CString csClass, LgbColorsDef cColors, CString csFont);
	~InlineText(void);

private:
	CString m_csClass;
	LgbColorsDef m_cColors;
	CString m_csFont;

public:
	CString GetClass();
	CString GetFont();
	void GetColors(LgbColorsDef &cColors);
	void SetClass(CString csClass);
	void SetFont(CString csFont);
	void SetColors(LgbColorsDef cColors);
	void SetBgColor(unsigned char iAlpha, unsigned char iRed, unsigned char iGreen, unsigned char iBlue);
};
