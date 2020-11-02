#include <QtWidgets>

#include <Cocoa/Cocoa.h>

#include "window.h"

int main(int argc, char **argv)
{
    [NSApplication sharedApplication];
    NSWindow* window = [[Window alloc] initWithContentRect:(NSMakeRect(0, 0, 640, 480)) styleMask:
      (NSWindowStyleMaskTitled
      | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable
      | NSWindowStyleMaskResizable  ) backing:(NSBackingStoreBuffered)defer:(true)];

    //
    NSView* view = [[NSView alloc] initWithFrame:NSMakeRect(100, 100, 100, 100)];
    [view setWantsLayer:YES];
    view.layer.backgroundColor = [[NSColor yellowColor] CGColor];
    window.titlebarAppearsTransparent = YES;
    window.titleVisibility = NSWindowTitleHidden;
    //

    [window.contentView addSubview:view];

    NSLog(@"%@", window);

    NSRect frame = NSMakeRect(10, 40, 90, 40);
    NSButton* pushButton = [[NSButton alloc] initWithFrame:frame];
    pushButton.bezelStyle = NSBezelStyleRounded;

    [window.contentView addSubview:pushButton];

    [window center];

    [window orderFrontRegardless];
    [NSApp run];
}
