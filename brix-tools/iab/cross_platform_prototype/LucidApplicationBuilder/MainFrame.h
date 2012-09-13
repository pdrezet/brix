/*
 * MainFrame.h
 *
 *  Created on: 5 Sep 2012
 *      Author: kamil
 */

#ifndef MAINFRAME_H_
#define MAINFRAME_H_


#include <wx/mdi.h>
#include <wx/menu.h>
#include <wx/event.h>
#include <wx/toolbar.h>
#include <wx/combobox.h>
#include "ProjectBar.h"

class MainFrame: public wxMDIParentFrame
{
public:
	MainFrame(wxWindow *parent);
public:
	~MainFrame(void);
public:
	CProjectBar m_wndProjectBar;
protected:
	wxMenuBar *m_menu_bar;

protected:
	void InitToolBar(wxToolBar* toolBar);
    void OnQuit(wxCommandEvent& event);
    DECLARE_EVENT_TABLE()
};

#endif /* MAINFRAME_H_ */
