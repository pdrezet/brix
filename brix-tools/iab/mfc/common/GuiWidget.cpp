#include "stdafx.h"
#include "GuiWidget.h"

GuiWidget::GuiWidget(void)
{
}

GuiWidget::GuiWidget(const CString &widgetTag, const CString &screenTag ):
m_csScreenTag(screenTag), m_csWidgetTag(widgetTag)
{
}

GuiWidget::~GuiWidget(void)
{
}

LucidErrEnum GuiWidget::getWidgetTag(CString &csWidgetTag) const
{
	csWidgetTag = m_csWidgetTag;
	return kErr_NoErr;
}

LucidErrEnum GuiWidget::getScreenTag(CString &csScreenTag) const
{
	csScreenTag = m_csScreenTag;
	return kErr_NoErr;
}

LucidErrEnum GuiWidget::setWidgetTag(const CString &csWidgetTag)
{
	m_csWidgetTag = csWidgetTag;
	return kErr_NoErr;
}

LucidErrEnum GuiWidget::setScreenTag(const CString &csScreenTag)
{
	m_csScreenTag = csScreenTag;
	return kErr_NoErr;
}

bool GuiWidget::operator==(const GuiWidget &gw) const
{
	CString csWidgetTag, csScreenTag;

	bool b1 = (m_csWidgetTag==gw.m_csWidgetTag);
	bool b2 = (m_csScreenTag==gw.m_csScreenTag);

	return b1&&b2;
}