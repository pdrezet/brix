#include "stdafx.h"

#include "LgbColorsDef.h"

LgbColorsDef::LgbColorsDef(void):	
					m_iFgAlpha( 255 ),
					m_iFgRed  ( 255   ),
					m_iFgGreen  ( 255   ),
					m_iFgBlue  ( 255   ),

					m_iBgAlpha  ( 255   ),
					m_iBgRed  (  100  ),
					m_iBgGreen  (  100  ),
					m_iBgBlue  (  100  ) 
{
}

LgbColorsDef::LgbColorsDef(	
					unsigned char fgAlpha,
					unsigned char fgRed,
					unsigned char fgGreen,
					unsigned char fgBlue,

					unsigned char bgAlpha,
					unsigned char bgRed,
					unsigned char bgGreen,
					unsigned char bgBlue 

				):	m_iFgAlpha( fgAlpha ),
					m_iFgRed  ( fgRed   ),
					m_iFgGreen  ( fgGreen ),
					m_iFgBlue  ( fgBlue   ),

					m_iBgAlpha  ( bgAlpha   ),
					m_iBgRed  (  bgRed  ),
					m_iBgGreen  (  bgGreen  ),
					m_iBgBlue  (  bgBlue  )
{
}


LgbColorsDef::~LgbColorsDef(void)
{
}

void LgbColorsDef::init(void)
{
}
