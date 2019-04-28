#include "titlebar.h"
#import <Cocoa/Cocoa.h>
//
@interface AppDelegate : NSObject

@property (strong) IBOutlet NSWindow *window;
@property (strong) IBOutlet NSView *titlebar;
@property (strong) IBOutlet NSButton *OpenSideBar;
@property (strong) IBOutlet NSVisualEffectView *visualEffectView;
@property (strong) IBOutlet NSView *content_view;
@property (strong) NSTitlebarAccessoryViewController *dummyTitlebarAccessoryViewController;

@end

@implementation AppDelegate
@synthesize window, titlebar, OpenSideBar, visualEffectView, content_view;

- (void) setView:(NSView*) view_in
{
    content_view = view_in;
}
- (void) setWindow:(NSWindow*) window_in
{
    window = window_in;
#if 0
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(window_resize:)
      name:NSWindowDidResizeNotification object:window];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(enter_fullscreen:)
      name:NSWindowDidEnterFullScreenNotification object:window];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(exit_fullscreen:)
      name:NSWindowDidExitFullScreenNotification object:window];
#endif

    //addTitlebarAccessoryViewController
    NSView *view = [[NSView alloc] initWithFrame:NSMakeRect(0, 0, 0, 16 + 16)];//16
    _dummyTitlebarAccessoryViewController = [NSTitlebarAccessoryViewController new];
    _dummyTitlebarAccessoryViewController.view = view;
    _dummyTitlebarAccessoryViewController.fullScreenMinHeight = 0;
    [window addTitlebarAccessoryViewController:_dummyTitlebarAccessoryViewController];

    NSView * titlebarview = [[window standardWindowButton:NSWindowCloseButton] superview];
    NSButton *sidebar_button = [[NSButton alloc] initWithFrame:NSMakeRect(255, 4 + 16 + 4, 45, 28)];
    [sidebar_button setButtonType:NSMomentaryPushInButton];
    [sidebar_button setBezelStyle:NSTexturedSquareBezelStyle];
    [sidebar_button setBordered:YES];
    [sidebar_button setImage:[NSImage imageNamed:NSImageNameTouchBarSidebarTemplate]];
    [sidebar_button setAction:@selector(sidebar_Clicked)];
    [titlebarview addSubview:sidebar_button];

    NSButton *back_button = [[NSButton alloc] initWithFrame:NSMakeRect(340, 4 + 16 + 4, 45, 28)];
    [back_button setButtonType:NSMomentaryPushInButton];
    [back_button setBezelStyle:NSTexturedSquareBezelStyle];
    [back_button setBordered:YES];
    [back_button setImage:[NSImage imageNamed:NSImageNameGoBackTemplate]];
    [back_button setAction:@selector(back_button_Clicked)];
    [titlebarview addSubview:back_button];

    if (content_view)
    {
        [titlebarview addSubview:content_view];
        [content_view setFrame:CGRectOffset(content_view.frame,230,-4)];
    }

    visualEffectView = (NSVisualEffectView *)[self replaceSubview:[[window standardWindowButton:NSWindowCloseButton] superview] withViewOfClass:[NSVisualEffectView class]];
    [visualEffectView setAutoresizingMask:NSViewWidthSizable | NSViewHeightSizable];

    [self adjust_traffic_light];
}

- (void) replaceSubview: (NSView *) aView withView: (NSView *) newView resizing:(BOOL)flag
{
    if (flag)
    {
        [newView setFrame:aView.frame];
    }

    [newView setAutoresizesSubviews:aView.autoresizesSubviews];
#if 0
    [aView.subviews.copy enumerateObjectsUsingBlock:^(NSView *subview, NSUInteger idx, BOOL *stop)
    {
        NSRect frame = subview.frame;
        if (subview.constraints.count>0)
        {
            // Note: so far, constraint based contentView subviews are not supported yet
            NSLog(@"WARNING: [%@ %@] does not work yet with NSView instances, that use auto-layout.",
                  NSStringFromClass([self class]),
                    NSStringFromSelector(_cmd));
        }
        [subview removeFromSuperview];
        [newView addSubview:subview];
        [subview setFrame:frame];
    }];


    [aView.superview replaceSubview:aView with:newView];
    //   [aView.superview addSubview:newView];
#endif
    [aView.superview addSubview:newView positioned:NSWindowBelow relativeTo:aView];
}

- (void) updateSubview: (NSView *) aView withView: (NSView *) newView
{
    [aView.subviews.copy enumerateObjectsUsingBlock:^(NSView *subview, NSUInteger idx, BOOL *stop)
    {
        NSRect frame = subview.frame;
        if (subview.constraints.count>0) {
            // Note: so far, constraint based contentView subviews are not supported yet
            NSLog(@"WARNING: [%@ %@] does not work yet with NSView instances, that use auto-layout.",
                  NSStringFromClass([self class]),
                    NSStringFromSelector(_cmd));
        }
        [subview removeFromSuperview];
        [newView addSubview:subview];
        [subview setFrame:frame];
    }];
}

- (NSView *) replaceSubview:(NSView *)aView withViewOfClass:(Class)newViewClass {
    NSView *view = [[newViewClass alloc] initWithFrame:aView.frame];
    [self replaceSubview:aView withView:view resizing:NO];
    return view;
}

// change traffic light position
- (void) adjust_traffic_light
{
    [[window standardWindowButton:NSWindowCloseButton] setFrame:NSMakeRect(12, 8 + 12, 14, 16)];
    [[window standardWindowButton:NSWindowMiniaturizeButton] setFrame:NSMakeRect(32, 8 + 12, 14, 16)];
    [[window standardWindowButton:NSWindowZoomButton] setFrame:NSMakeRect(52, 8 + 12, 14, 16)];
    NSLog(@"NSWindowCloseButton=%@",[window standardWindowButton:NSWindowCloseButton].superview);
}


- (void) window_resize:(NSNotification *)notification
{
    [self adjust_traffic_light];
}

- (void) enter_fullscreen:(NSNotification *)notification
{
    [self updateSubview:[[window standardWindowButton:NSWindowCloseButton] superview] withView:visualEffectView];
}

- (void) exit_fullscreen:(NSNotification *)notification
{
    [self updateSubview:[[window standardWindowButton:NSWindowCloseButton] superview] withView:visualEffectView];
}


-(void) sidebar_Clicked
{
    NSLog(@"sidebar_Clicked");
}

-(void) back_button_Clicked
{
    NSLog(@"back_button_Clicked");
}

@end

void customWindowTitleBar(QWidget *w,QWidget *c)
{
    if (!w)
    {
        return;
    }

    NSView *nsview = (NSView *)w->winId();
    NSWindow *nswindow = [nsview window];
    AppDelegate* delegate = [[AppDelegate alloc] init];
    if (c)
    {
        NSView *view = (NSView *)c->winId();
        [delegate setView:view];
    }
    [delegate setWindow:nswindow];
    [delegate autorelease];
}

void setTitlebarBackgrounColor(QWidget *w, QColor color)
{
    if (!w)
    {
        return;
    }

    NSView *nsview = (NSView *)w->winId();
    NSWindow *nswindow = [nsview window];

    NSView* titlebarView = [[nswindow standardWindowButton:NSWindowCloseButton] superview];

    NSColor *nsColor = [NSColor colorWithSRGBRed:
            color.redF() green:color.greenF() blue:color.blueF() alpha:color.alphaF()];
    titlebarView.layer.backgroundColor = [nsColor CGColor];
}

void setWidgetVisualEffect(QWidget *w)
{
    NSView *aView = (NSView *)w->winId();

    NSVisualEffectView *newView = [[NSVisualEffectView alloc] initWithFrame:aView.frame];
    [newView setFrame:aView.frame];
    [newView setAutoresizesSubviews:aView.autoresizesSubviews];
    [newView setAutoresizingMask:NSViewWidthSizable|NSViewHeightSizable];
    [aView.superview addSubview:newView positioned:NSWindowBelow relativeTo:aView];
}
