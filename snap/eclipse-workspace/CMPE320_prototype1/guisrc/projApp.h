#pragma once
#include <wx/wxprec.h>
#include "wx/wx.h"
#include "guiMainScr.h"

class projApp : public wxApp {

private:
	guiMainScr* m_frame1 = nullptr;
public:
	projApp();
	~projApp();

	virtual bool OnInit();
};