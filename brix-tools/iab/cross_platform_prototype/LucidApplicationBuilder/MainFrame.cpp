/*
 * MainFrame.cpp
 *
 *  Created on: 5 Sep 2012
 *      Author: kamil
 */

#include "MainFrame.h"
#include "DrawProg.h"
#include <wx/icon.h>
#include <wx/bitmap.h>
#include <wx/imaglist.h>
#include "Resource.h"


#define NUMBER_OF_TOOLS 26 // number of tools in the toolbar

BEGIN_EVENT_TABLE(MainFrame, wxMDIParentFrame)
    EVT_MENU(wxID_EXIT, MainFrame::OnQuit)
END_EVENT_TABLE()

MainFrame::MainFrame(wxWindow *parent):
wxMDIParentFrame(parent, wxID_ANY, wxT("INX"), wxPoint(100,100), wxSize(1000,550),
		 wxDEFAULT_FRAME_STYLE | wxHSCROLL | wxVSCROLL)
{
	// create an inx icon for the main frame
#if __WXMSW__
		wxIcon inxIcon(wxT("./res/DrawProg.ico"),wxBITMAP_TYPE_ICO ,-1,-1);
#else
	wxIcon inxIcon(wxT("/home/kamil/workspace/iAB_Project/res/DrawProgIcon.xpm"), wxBITMAP_TYPE_XPM);
#endif
	SetIcon(inxIcon);
	//create a menu bar
	m_menu_bar = new wxMenuBar;

	wxMenu *file_menu = new wxMenu;
    file_menu->Append(INX_NEW_PROJECT, _T("&New window\tCtrl-N"), _T("Create a new child window"));
    file_menu->Append(wxID_EXIT, _T("&Exit\tAlt-X"), _T("Quit the program"));

    wxMenu *help_menu = new wxMenu;
    help_menu->Append(wxID_ABOUT, _T("&About\tF1"));

    m_menu_bar->Append(file_menu, _T("&File"));
    m_menu_bar->Append(help_menu, _T("&Help"));
	SetMenuBar(m_menu_bar);
	// create a toolbar
	CreateToolBar(wxNO_BORDER | wxTB_FLAT | wxTB_HORIZONTAL);

	InitToolBar(GetToolBar());
}

MainFrame::~MainFrame(void)
{
}

void MainFrame::InitToolBar(wxToolBar* toolBar){

	toolBar->SetBackgroundColour(wxColour(218, 218, 218));

	int toolButtonHeight = 24;
	int toolButtonWidth = 24;
	// get the toolbar image sheet
#if __WXMSW__
	wxBitmap tbImageSheet("./res/Toolbar_24bit.bmp", wxBITMAP_TYPE_BMP);
#else
	wxBitmap tbImageSheet(wxT("/home/kamil/workspace/iAB_Project/res/Toolbar_24bit.bmp"), wxBITMAP_TYPE_BMP);
#endif
	wxImageList *tbImageList = new wxImageList(toolButtonWidth, toolButtonHeight, true, NUMBER_OF_TOOLS);
	//add specific bitmap to the image list
	for (int i = 0; i < NUMBER_OF_TOOLS; i++){
		tbImageList->Add(tbImageSheet.GetSubBitmap(wxRect(wxPoint(i*toolButtonWidth,0),
			wxSize(toolButtonWidth,toolButtonHeight))), wxNullBitmap);
	}
	//add tools and images to the toolbar
	/*** @todo still requires to set up the toolbars ****/

	toolBar->AddTool(INX_NEW_PROJECT, _T("New Project"),tbImageList->GetBitmap(0), _T("New Project"));
	toolBar->AddTool(INX_OPEN_PROJECT, _T("Open Project"),tbImageList->GetBitmap(1), _T("Open Project"));
	toolBar->AddTool(INX_SAVE_PROJECT, _T("Save Project"),tbImageList->GetBitmap(2), _T("Save Project"));
	toolBar->AddSeparator();
	toolBar->AddSeparator();
	wxComboBox *m_combo_box =  new wxComboBox(toolBar, -1, wxEmptyString, wxDefaultPosition, wxSize(100,-1) );
	m_combo_box->Append(_T("This"));
	m_combo_box->Append(_T("is a"));
	m_combo_box->Append(_T("combobox"));
	m_combo_box->Append(_T("in a"));
	m_combo_box->Append(_T("toolbar"));
	toolBar->AddControl(m_combo_box);
	toolBar->Realize();
}

void MainFrame::OnQuit(wxCommandEvent& event){
	 Close();
}
