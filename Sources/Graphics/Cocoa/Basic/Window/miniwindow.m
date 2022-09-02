#import <Cocoa/Cocoa.h>
// clang -w -fobjc-arc -framework AppKit miniwindow.m -o mini && ./mini
@interface AppDelegate : NSObject <NSApplicationDelegate> {
}
@end

@implementation AppDelegate

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)app
{
    return YES;
}

@end

int main(int argc, char const* argv[])
{
    [NSApplication sharedApplication];
    [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];

    NSWindow* window = [[NSWindow alloc] initWithContentRect:(NSMakeRect(0, 0, 640, 480)) styleMask:(NSWindowStyleMaskTitled)backing:(NSBackingStoreBuffered)defer:(true)];
    //
    NSView* view = [[NSView alloc] initWithFrame:NSMakeRect(100, 100, 100, 100)];
    [view setWantsLayer:YES];
    view.layer.backgroundColor = [[NSColor yellowColor] CGColor];

    [window.contentView addSubview:view];

    NSRect frame = NSMakeRect(10, 40, 90, 40);
    NSButton* pushButton = [[NSButton alloc] initWithFrame:frame];
    pushButton.bezelStyle = NSBezelStyleRounded;

    [window.contentView addSubview:pushButton];
    window.styleMask |= NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable;

    //
    // [window setTitlebarAppearsTransparent:YES];
    [window center];
    // [window orderFrontRegardless];
    [window makeKeyAndOrderFront : nil];
    AppDelegate* appDelegate = [[AppDelegate alloc] init];
    [NSApp setDelegate:appDelegate];
    [NSApp activateIgnoringOtherApps:YES];
    [NSApp run];
}
