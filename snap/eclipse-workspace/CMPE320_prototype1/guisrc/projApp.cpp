#include "projApp.h"

wxIMPLEMENT_APP(projApp);

projApp::projApp() {
}
projApp::~projApp() {
}

bool projApp::OnInit() {

	m_frame1 = new guiMainScr();
	m_frame1->Show();
	
	return true;
}