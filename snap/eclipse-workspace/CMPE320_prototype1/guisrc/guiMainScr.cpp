/*
Initial Contributor : Lawrence McKenny
Team Snap, CISC/CMPE 320

Basic GUI layout/prototype. 
Using wxWidgets.
*/


#include "guiMainScr.h"

wxBEGIN_EVENT_TABLE(guiMainScr, wxFrame)
	EVT_BUTTON(1000, OnButtonClicked)
	EVT_BUTTON(1001, OnButtonClicked)
	EVT_BUTTON(1002, OnButtonClicked)
	EVT_BUTTON(1003, OnButtonClicked)
wxEND_EVENT_TABLE()

guiMainScr::guiMainScr() : wxFrame(nullptr, wxID_ANY, "Gui Prototype", wxPoint(30,30), wxSize(800, 600)) {
	//declare main screen buttons and stuff

	m_toolBar = this->CreateToolBar(wxTB_HORIZONTAL, wxID_ANY);
	m_username = new wxStaticText(this, wxID_ANY, wxString("Username:\nUsername Will Go Here"), wxPoint(10, 10), wxSize(150, 50));
	m_mealPlanner = new wxButton(m_toolBar, 1000, "Meal Planner", wxDefaultPosition, wxSize(100, 24), 0);
	m_myIngredients = new wxButton(m_toolBar, 1001, "Ingredient List", wxDefaultPosition, wxSize(100, 24), 0);
	m_profileSettings = new wxButton(m_toolBar, 1002, "Profile Settings", wxDefaultPosition, wxSize(100, 24), 0);
	m_logOut = new wxButton(m_toolBar, 1003, "Log Out", wxDefaultPosition, wxSize(100, 24), 0);

	//add to toolbar

	m_toolBar->AddControl(m_mealPlanner);
	m_toolBar->AddControl(m_myIngredients);
	m_toolBar->AddControl(m_profileSettings);
	m_toolBar->AddControl(m_logOut);
	m_toolBar->Realize();

}

guiMainScr::~guiMainScr() {


}

void guiMainScr::OnButtonClicked(wxCommandEvent& evt) {
	int happening = evt.GetId();

	switch (happening) {
	case 1000:
		evt.Skip();
	case 1001:
		evt.Skip();
	case 1002:
		evt.Skip();
	case 1003:
		Close();

	}


	evt.Skip();
}