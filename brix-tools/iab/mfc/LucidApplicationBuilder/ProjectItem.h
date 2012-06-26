// ProjectItem.h: interface for the ProjectItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECTITEM_H__38AB705F_84E7_4216_855D_DE3ADB9935B5__INCLUDED_)
#define AFX_PROJECTITEM_H__38AB705F_84E7_4216_855D_DE3ADB9935B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ProjectItem  
{
public:
	ProjectItem();
	virtual ~ProjectItem();

	// Attributes
	CString depFilename;

};

#endif // !defined(AFX_PROJECTITEM_H__38AB705F_84E7_4216_855D_DE3ADB9935B5__INCLUDED_)
