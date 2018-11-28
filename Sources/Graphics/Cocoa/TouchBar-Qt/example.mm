#include <QtWidgets>
#import <AppKit/AppKit.h>


@interface TouchBarProvider: NSResponder <NSTouchBarDelegate, NSApplicationDelegate, NSWindowDelegate>

@property (strong) NSCustomTouchBarItem *touchBarItem1;
@property (strong) NSCustomTouchBarItem *touchBarItem2;
@property (strong) NSButton *touchBarButton1;
@property (strong) NSButton *touchBarButton2;

@property (strong) NSColorPickerTouchBarItem *colorPickerItem;

@property (strong) NSObject *qtDelegate;

@property  QWidget* qtWidget;

@property (strong) NSCustomTouchBarItem *customViewItem;

- (void) setQtWidget:(QWidget*) widget;

@end

// Create identifiers for two button items.
static NSTouchBarItemIdentifier Button1Identifier = @"1";
static NSTouchBarItemIdentifier ColorPickerItemIdentifier = @"2";
static NSTouchBarItemIdentifier CustomViewIdentifier = @"3";

@implementation TouchBarProvider

-(void) init
{
    [super init];
    self.qtWidget = nullptr;
}

- (void) setQtWidget:(QWidget*)widget
{
//    self.qtWidget = widget;
}

- (NSTouchBar *)makeTouchBar
{
    NSTouchBar *bar = [[NSTouchBar alloc] init];
    bar.delegate = self;

    // Set the default ordering of items.
    bar.defaultItemIdentifiers = @[
            CustomViewIdentifier,
            Button1Identifier,
            ColorPickerItemIdentifier,
            NSTouchBarItemIdentifierOtherItemsProxy
            ];


    return bar;
}

- (NSTouchBarItem *)touchBar:(NSTouchBar *)touchBar makeItemForIdentifier:(NSTouchBarItemIdentifier)identifier
{
    Q_UNUSED(touchBar);

    // Create touch bar items as NSCustomTouchBarItems which can contain any NSView.
    if ([identifier isEqualToString:Button1Identifier]) {
        QString title = "B1";
        self.touchBarItem1 = [[[NSCustomTouchBarItem alloc] initWithIdentifier:identifier] autorelease];
        self.touchBarItem1.view =  [[NSButton buttonWithTitle:title.toNSString()
                target:self
                action:@selector(button1Clicked)] autorelease];
         return self.touchBarItem1;
    }
    else if ([identifier isEqualToString:ColorPickerItemIdentifier])
    {
        // Create a bar item containing a button with the standard color picker icon that invokes the color picker.
        _colorPickerItem = [NSColorPickerTouchBarItem colorPickerWithIdentifier:ColorPickerItemIdentifier];
        self.colorPickerItem.target = self;
        self.colorPickerItem.action = @selector(colorAction:);
        return self.colorPickerItem;
    }
    else if ([identifier isEqualToString:CustomViewIdentifier])
   {
       NSView *customView = nil;

       if(self.qtWidget)
       {
            customView = [NSTextField labelWithString:@"Catalog"];
       }
       else
       {
            customView = [[NSView alloc] initWithFrame:NSMakeRect(10, 10, 10, 10)];
            customView.wantsLayer = YES;
            customView.layer.backgroundColor = [NSColor cyanColor].CGColor;
       }

       _customViewItem = [[NSCustomTouchBarItem alloc] initWithIdentifier:CustomViewIdentifier];
       self.customViewItem.view = customView;
       self.customViewItem.customizationLabel = @"Custom View";

       return self.customViewItem;
   }

   return nil;
}

- (void)installAsDelegateForWindow:(NSWindow *)window
{
    _qtDelegate = window.delegate; // Save current delegate for forwarding
    window.delegate = self;
}

- (void)installAsDelegateForApplication:(NSApplication *)application
{
    _qtDelegate = application.delegate; // Save current delegate for forwarding
    application.delegate = self;
}

- (BOOL)respondsToSelector:(SEL)aSelector
{
    // We want to forward to the qt delegate. Respond to selectors it
    // responds to in addition to selectors this instance resonds to.
    return [_qtDelegate respondsToSelector:aSelector] || [super respondsToSelector:aSelector];
}

- (void)forwardInvocation:(NSInvocation *)anInvocation
{
    // Forward to the existing delegate. This function is only called for selectors
    // this instance does not responds to, which means that the qt delegate
    // must respond to it (due to the respondsToSelector implementation above).
    [anInvocation invokeWithTarget:_qtDelegate];
}

- (void)button1Clicked
{
    qDebug() << "button1Clicked";
}

- (void)button2Clicked
{
    qDebug() << "button2Clicked";
}

- (void)colorAction:(id)sender
{
    NSLog(@"Color Chosen = %@\n", ((NSColorPickerTouchBarItem *)sender).color);
}

@end

#include "touchbar_mac.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
#if 1
    {
        // Install TouchBarProvider as application delegate
        TouchBarProvider *touchBarProvider = [[TouchBarProvider alloc] init];
        [touchBarProvider installAsDelegateForApplication:[NSApplication sharedApplication]];
    }
#endif
    //
    QTextEdit textEdit;
    textEdit.show();
#if 1
    {
        // Install TouchBarProvider as window delegate
        NSView *view = reinterpret_cast<NSView *>(textEdit.winId());
        TouchBarProvider *touchBarProvider = [[TouchBarProvider alloc] init];
        [touchBarProvider installAsDelegateForWindow:view.window];
    }
#endif

    return app.exec();
}
