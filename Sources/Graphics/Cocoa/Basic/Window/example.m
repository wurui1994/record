#import <Cocoa/Cocoa.h>
// clang -w -fobjc-arc -framework AppKit example.m -o example && ./example
@interface AppDelegate : NSObject <NSApplicationDelegate> {
    NSWindow* window;
}

@property (strong) IBOutlet NSWindow* window;

@end

@implementation AppDelegate

@synthesize window;

- (void)applicationWillFinishLaunching:(NSNotification*)note
{
    self.window = [[NSWindow alloc] initWithContentRect:(NSMakeRect(0, 0, 640, 480)) styleMask:(NSTitledWindowMask)backing:(NSBackingStoreBuffered)defer:(true)];
    //
    window.styleMask |= NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable;
    //
    [self.window center];

    NSView* view = [[NSView alloc] initWithFrame:NSMakeRect(100, 100, 100, 100)];
    [view setWantsLayer:YES];
    view.layer.backgroundColor = [[NSColor yellowColor] CGColor];

    [self.window.contentView addSubview:view];

    NSRect frame = NSMakeRect(10, 40, 90, 40);
    NSButton* pushButton = [[NSButton alloc] initWithFrame:frame];
    pushButton.bezelStyle = NSRoundedBezelStyle;

    [self.window.contentView addSubview:pushButton];

    NSLog(@"subviews are %@", [self.window.contentView subviews]);
    [self.window orderFrontRegardless];
    //    [self.window setTitleVisibility:NSWindowTitleHidden];
    //    [[self.window standardWindowButton:NSWindowCloseButton] setHidden:NO];
    //    [[self.window standardWindowButton:NSWindowMiniaturizeButton] setHidden:NO];
    //    [[self.window standardWindowButton:NSWindowZoomButton] setHidden:NO];
    //    [NSApp activateIgnoringOtherApps:true];
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)app
{
    return YES;
}

@end

int main(int argc, char const* argv[])
{
    [NSApplication sharedApplication];
    AppDelegate* appDelegate = [[AppDelegate alloc] init];
    [NSApp setDelegate:appDelegate];
    [NSApp run];
}
