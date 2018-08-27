//g++ wxtest.cpp `wx-config --cppflags --libs`

#ifndef SRC_SIMPLE_H_
#define SRC_SIMPLE_H_

#include <wx/wx.h>

class Simple : public wxFrame
{
public:
	Simple(const wxString& title);
};

#endif /* SRC_SIMPLE_H_ */


#ifndef SRC_MAIN_H_
#define SRC_MAIN_H_

#include <wx/wx.h>

class MyApp : public wxApp
{
public:
	virtual bool OnInit();
};

#endif /* SRC_MAIN_H_ */

//#include "../include/simple.h"

Simple::Simple(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(250, 150))
{
	Centre();
}

//#include "main.h"
//#include "simple.h"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
	Simple *simple = new Simple(wxT("Simple"));
	simple->Show(true);

	return true;
}
