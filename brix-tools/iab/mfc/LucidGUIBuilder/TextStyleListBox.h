#pragma once

#include "afxwin.h"
#include "InlineText.h"

class TextStyleListBox :
	public CListBox
{
public:
	TextStyleListBox(void);
public:
	~TextStyleListBox(void);

private:
	vector<InlineText> m_vTextStylesVec;

protected:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	CString GetFont(CString csStyle);
	void GetColors(CString csStyle, LgbColorsDef &cColors);

public:
	void SetTextStylesVec(vector<InlineText> vTextStylesVec);
};
