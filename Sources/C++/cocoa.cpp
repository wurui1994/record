/*
 * test1.cpp
 * This program shows how to access Cocoa GUI from pure C/C++
 * and build a truly functional GUI application (although very simple).
 * 
 * Compile using:
 *   g++ -framework Cocoa -o test1 test1.cpp
 *
 * that will output 'test1' binary.
 */


#include <CoreFoundation/CoreFoundation.h>
#include <objc/objc.h>
#include <objc/objc-runtime.h>
#include <iostream>

extern "C" int NSRunAlertPanel(CFStringRef strTitle, CFStringRef strMsg,
                               CFStringRef strButton1, CFStringRef strButton2, 
                               CFStringRef strButton3, ...);


int main(int argc, char** argv)
{
    id app = NULL;
    id pool = (id)objc_getClass("NSAutoreleasePool");
    if (!pool)
    {
        std::cerr << "Unable to get NSAutoreleasePool!\nAborting\n";
        return -1;
    }
    pool = objc_msgSend(pool, sel_registerName("alloc"));
    if (!pool)
    {
        std::cerr << "Unable to create NSAutoreleasePool...\nAborting...\n";
        return -1;
    }
    pool = objc_msgSend(pool, sel_registerName("init"));

    app = objc_msgSend((id)objc_getClass("NSApplication"),
                       sel_registerName("sharedApplication"));

    NSRunAlertPanel(CFSTR("Testing"),
                    CFSTR("This is a simple test to display NSAlertPanel."),
                    CFSTR("OK"), NULL, NULL);

    objc_msgSend(pool, sel_registerName("release"));
    return 0;
}