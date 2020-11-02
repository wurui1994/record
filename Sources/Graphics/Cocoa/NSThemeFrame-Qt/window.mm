#import "window.h"

#import <AppKit/AppKit.h>

@interface NSWindow (PrivateBrowserNativeWidgetAPI)
+ (Class)frameViewClassForStyleMask:(NSUInteger)windowStyle;
- (long long)_resizeDirectionForMouseLocation:(CGPoint)location;
// Available in later point releases of 10.10. On 10.11+, use the public
// -performWindowDragWithEvent: instead.
- (void)beginWindowDragWithEvent:(NSEvent*)event;
@end

@interface NSThemeFrame: NSView
- (CGFloat)_titlebarHeight;
- (float)roundedCornerRadius;
- (void)setStyleMask:(NSUInteger)styleMask;
- (void)cr_mouseDownOnFrameView:(NSEvent*)event;
@end

// ------------------------------------------------------------------------
// this will be our frame view for the window
@interface WindowFrame : NSThemeFrame
@end

// private methods on the frame view
@interface WindowFrame ()
  - (CGFloat)_titlebarHeight;
- (void)setStyleMask:(NSUInteger)styleMask;
@end

@implementation WindowFrame
{
    BOOL _inFullScreen;
}

// NSThemeFrame overrides.

- (CGFloat)_titlebarHeight
{

    //    NSLog(@"%@", [super _closeButtonOrigin]);
    if (!_inFullScreen)
    {
        return 60;
    }
    return [super _titlebarHeight];
}


- (void)setStyleMask:(NSUInteger)styleMask {
    _inFullScreen = (styleMask & NSWindowStyleMaskFullScreen) != 0;
    [super setStyleMask:styleMask];
}

- (BOOL)_shouldCenterTrafficLights {
    return YES;
}

- (void)mouseDown:(NSEvent*)event {
    if (!self.window.isMovable)
        [self cr_mouseDownOnFrameView:event];
    [super mouseDown:event];
}

// If a mouseDown: falls through to the frame view, turn it into a window drag.
- (void)cr_mouseDownOnFrameView:(NSEvent*)event
{
    if ([self.window _resizeDirectionForMouseLocation:event.locationInWindow] !=
            -1)
        return;

    if (@available(macOS 10.11, *)) {
        // According to Google, using performWindowDragWithEvent:
        // does not generate a NSWindowWillMoveNotification. Hence post one.
        [[NSNotificationCenter defaultCenter]
                postNotificationName:NSWindowWillMoveNotification
                                     object:self];
        [self.window performWindowDragWithEvent:event];
    }
    else if ([self.window
             respondsToSelector:@selector(beginWindowDragWithEvent:)])
        [self.window beginWindowDragWithEvent:event];
    else
        NSLog(@"%@", @"Error");
}

- (NSPoint)_closeButtonOrigin
{
    NSPoint origin = [super _closeButtonOrigin];

    if (!_inFullScreen)
    {
        origin = NSMakePoint(origin.x + 5, origin.y);
    }
    else
    {
        origin = NSMakePoint(origin.x - 10, origin.y);
    }

    NSLog(@"%f", origin.x);

    return origin;
}

@end

// ------------------------------------------------------------------------

@implementation Window
{
    BOOL _isWindowMovable;
}

- (id)initWithContentRect:(NSRect)contentRect styleMask:(NSUInteger)aStyle backing:(NSBackingStoreType)bufferingType defer:(BOOL)flag
{
    self = [super initWithContentRect:contentRect styleMask:aStyle backing:bufferingType defer:NO];

    if (!self) return nil;

    // defaults
    _isWindowMovable = YES;

    return self;
}

- (BOOL)_usesCustomDrawing
{
    return NO;
}

- (BOOL)isMovable
{
    return _isWindowMovable;
}

// we want to use our custom frame view class
+ (Class)frameViewClassForStyleMask:(NSUInteger)windowStyle
{
    if ([WindowFrame class])
        return [WindowFrame class];
    return [super frameViewClassForStyleMask:windowStyle];
}

- (NSColor *)backgroundColor
{
    return [super backgroundColor];
}
@end
