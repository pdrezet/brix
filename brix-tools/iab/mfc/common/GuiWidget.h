// GuiWidget.h: interface for the GuiWidget class
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "stdafx.h"
#include "LucidEnums.h"

class GuiWidget
{
public:
	GuiWidget(void);
	GuiWidget(const CString &widgetTag, const CString &screenTag );
	~GuiWidget(void);


	bool operator==(const GuiWidget &gw) const;


// Attributes
private:
	CString m_csWidgetTag;
	CString m_csScreenTag;

// Methods
public:
	LucidErrEnum getWidgetTag(CString &csWidgetTag) const;
	LucidErrEnum getScreenTag(CString &csScreenTag) const;
	LucidErrEnum setWidgetTag(const CString &csWidgetTag);
	LucidErrEnum setScreenTag(const CString &csScreenTag);


};
