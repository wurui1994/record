// Name:        minimal.cpp
// Purpose:     Minimal wxWidgets sample
// Author:      Julian Smart

#include "wx/wx.h"

// Declare the application class
//定义应用程序类
class MyApp : public wxApp
{
public:
    // Called on application startup
    //这个函数将会在程序启动的时候被调用
    virtual bool OnInit();
};

// Declare our main frame class
//定义主窗口类
class MyFrame : public wxFrame
{
public:
    // Constructor
    //主窗口类的构造函数
    MyFrame(const wxString& title);

    // Event handlers
    //事件处理函数
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

private:
    // This class handles events
    //声明事件表
    DECLARE_EVENT_TABLE()
};

// Implements MyApp& GetApp()
//有了这一行就可以使用MyApp & wxGetApp()了
DECLARE_APP(MyApp)

// Give wxWidgets the means to create a MyApp object
//告诉主应用程序是哪个类的wxWidgets
IMPLEMENT_APP(MyApp)

// Initialize the application
//初始化程序
bool MyApp::OnInit()
{
    // Create the main application window
    //创建主窗口
    MyFrame *frame = new MyFrame(wxT("Minimal wxWidgets App"));

    // Show it
    // 显示主窗口
    frame->Show(true);

    // Start the event loop
    //开始事件处理循环
    return true;
}

// Event table for MyFrame
//类的事件表MyFrame
BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
    EVT_MENU(wxID_EXIT,  MyFrame::OnQuit)
END_EVENT_TABLE()

void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg;
    msg.Printf(wxT("Hello and welcome to %s"), wxVERSION_STRING);

    wxMessageBox(msg, wxT("About Minimal"), wxOK | wxICON_INFORMATION, this);
}

void MyFrame::OnQuit(wxCommandEvent& event)
{
    // Destroy the frame
    //释放主窗口
    Close();
}

// #include "mondrian.xpm"

MyFrame::MyFrame(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title)
{
    // Set the frame icon
    //设置窗口图标
    // SetIcon(wxIcon(mondrian_xpm));

    // Create a menu bar
    //创建菜单条
    wxMenu *fileMenu = new wxMenu;
    wxMenu *helpMenu = new wxMenu;

    // The "About" item should be in the help menu
    //添加“关于菜单项”
    helpMenu->Append(wxID_ABOUT, wxT("&About...\tF1"), wxT("Show about dialog"));

    fileMenu->Append(wxID_EXIT, wxT("E&xit\tAlt-X"), wxT("Quit this program"));

    // Now append the freshly created menu to the menu bar...
    //将菜单项添加到菜单条中
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, wxT("&File"));
    menuBar->Append(helpMenu, wxT("&Help"));

    // ... and attach this menu bar to the frame
    //然后将菜单条放置在主窗口上
    SetMenuBar(menuBar);

    // Create a status bar just for fun
    //创建一个状态条让一切更有趣些
    CreateStatusBar(2);
    SetStatusText(wxT("Welcome to wxWidgets!"));
}