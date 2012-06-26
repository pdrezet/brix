#pragma once

#include "stdafx.h"

class LgbColorsDef
{
public:
	LgbColorsDef(void);

	LgbColorsDef(	unsigned char fgAlpha,
					unsigned char fgRed,
					unsigned char fgGreen,
					unsigned char fgBlue,

					unsigned char bgAlpha,
					unsigned char bgRed,
					unsigned char bgGreen,
					unsigned char bgBlue 
					);
 


public:
	~LgbColorsDef(void);

	//! The fore- and background colours for an LGB textbox icon
	unsigned char m_iFgAlpha;
	unsigned char m_iFgRed;
	unsigned char m_iFgGreen;
	unsigned char m_iFgBlue;

	unsigned char m_iBgAlpha;
	unsigned char m_iBgRed;
	unsigned char m_iBgGreen;
	unsigned char m_iBgBlue;

public:
	void init(void);
};
