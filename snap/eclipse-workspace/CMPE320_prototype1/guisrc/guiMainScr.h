#pragma once
#include "wx/wx.h"

class guiMainScr : public wxFrame {

public:
	guiMainScr();
	~guiMainScr();
	wxMenu* m_menu;
	wxMenuBar* m_menuBar;
	wxStaticText* m_username;
	wxTextCtrl* m_txt;
	wxListBox* m_list; //placeholder for now
	wxButton* m_mealPlanner;
	wxButton* m_myIngredients;
	wxButton* m_profileSettings;
	wxButton* m_logOut;

	void OnButtonClicked(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();

};