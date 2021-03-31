#import "kwindowbuttonview.h"

@interface KWindowButtonView ()

@property (nonatomic, assign) BOOL mouseInside;
@property (nonatomic, strong, readwrite) NSButton *closeButton;
@property (nonatomic, strong, readwrite) NSButton *miniButton;
@property (nonatomic, strong, readwrite) NSButton *maxButton;

@end

@implementation KWindowButtonView

- (instancetype)initWithFrame:(NSRect)frameRect {
    
    self = [super initWithFrame:frameRect];
    if (self) {
        [self commonInitialize];
    }
    return self;
}

- (instancetype)initWithCoder:(NSCoder *)decoder {
    
    self = [super initWithCoder:decoder];
    if (self) {
        [self commonInitialize];
    }
    return self;
}

- (void)dealloc {
    
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [NSApp removeObserver:self forKeyPath:@"effectiveAppearance"];
    [super dealloc];
}

- (void)updateTrackingAreas {
    
    [super updateTrackingAreas];
    NSTrackingArea *const trackingArea = [[NSTrackingArea alloc] initWithRect:NSZeroRect options:(NSTrackingMouseEnteredAndExited | NSTrackingActiveAlways | NSTrackingInVisibleRect) owner:self userInfo:nil];
    [self addTrackingArea:trackingArea];
}

- (void)mouseEntered:(NSEvent *)event {
    
    [super mouseEntered:event];
    self.mouseInside = YES;
    [self setNeedsDisplayForStandardWindowButtons];
}

- (void)mouseExited:(NSEvent *)event {
    
    [super mouseExited:event];
    self.mouseInside = NO;
    [self setNeedsDisplayForStandardWindowButtons];
}

- (void)mouseDown:(NSEvent *)event {
    
    [self mouseDragged:event];
}

- (void)mouseDragged:(NSEvent *)theEvent {
    NSWindow *window = self.window;
    NSRect whereRect = [window convertRectToScreen:NSMakeRect(theEvent.locationInWindow.x, theEvent.locationInWindow.y, 1, 1)];
    NSPoint where = NSMakePoint(whereRect.origin.x, whereRect.origin.y);
    
    NSPoint origin = window.frame.origin;
    CGFloat deltaX = 0.0;
    CGFloat deltaY = 0.0;
    while ((theEvent = [NSApp nextEventMatchingMask:NSEventMaskLeftMouseDown | NSEventMaskLeftMouseDragged | NSEventMaskLeftMouseUp untilDate:[NSDate distantFuture] inMode:NSEventTrackingRunLoopMode dequeue:YES]) && (theEvent.type != NSEventTypeLeftMouseUp)) {
        @autoreleasepool {
            NSRect nowRect = [window convertRectToScreen:NSMakeRect(theEvent.locationInWindow.x, theEvent.locationInWindow.y, 1, 1)];
            NSPoint now = NSMakePoint(nowRect.origin.x, nowRect.origin.y);
            deltaX += now.x - where.x;
            deltaY += now.y - where.y;
            if (fabs(deltaX) >= 1 || fabs(deltaY) >= 1) {
                origin.x += deltaX;
                origin.y += deltaY;
                window.frameOrigin = origin;
                deltaX = 0.0;
                deltaY = 0.0;
            }
            where = now;
        }
    }
}

- (BOOL)_mouseInGroup:(NSButton *)button {
    
    return self.mouseInside;
}

- (void)updateWindowRadiusButton
{
    NSView*  contentView = self.window.contentView;
	[self.window setOpaque:NO];
    [self.window setBackgroundColor:[NSColor clearColor]];
    contentView.wantsLayer = YES;
    contentView.layer.backgroundColor = [NSColor windowBackgroundColor].CGColor;
    contentView.layer.masksToBounds = YES;
    contentView.layer.cornerRadius = 8;
}

- (void)observeValueForKeyPath:(NSString *)keyPath
                  ofObject:(id)object
                    change:(NSDictionary *)change
                   context:(void *)context
{
    NSLog(@"%@", keyPath);
    [self updateWindowRadiusButton];
}

#pragma mark - Public Methods

- (void)adjustWindowState
{
    // movable and resizable
    NSWindow* window = self.window;
    window.movableByWindowBackground = YES;
    window.styleMask |= NSWindowStyleMaskResizable;
    window.styleMask |= NSWindowStyleMaskMiniaturizable;
}

#pragma mark - Private Methods

- (void)commonInitialize {
    
    self.closeButton = [NSWindow standardWindowButton:NSWindowCloseButton forStyleMask:3];
    self.closeButton.frame = NSMakeRect(0, 0, self.closeButton.bounds.size.width, self.closeButton.bounds.size.height);
    
    self.miniButton = [NSWindow standardWindowButton:NSWindowMiniaturizeButton forStyleMask:3];
    self.miniButton.frame = NSMakeRect(20, 0, self.miniButton.bounds.size.width, self.miniButton.bounds.size.height);
    
    self.maxButton = [NSWindow standardWindowButton:NSWindowZoomButton forStyleMask:3];
    self.maxButton.frame = NSMakeRect(40, 0, self.maxButton.bounds.size.width, self.maxButton.bounds.size.height);
    
    [self addSubview:self.closeButton];
    [self addSubview:self.miniButton];
    [self addSubview:self.maxButton];
    
    [self addNotifications];

//    self.wantsLayer = YES;
//    self.layer.backgroundColor = [NSColor cyanColor].CGColor;
}

- (void)addNotifications {
    
    NSNotificationCenter *defaultCenter = [NSNotificationCenter defaultCenter];
    [defaultCenter addObserver:self selector:@selector(applicationWillBecomeActive:) name:NSApplicationWillBecomeActiveNotification object:NSApp];
    [defaultCenter addObserver:self selector:@selector(applicationDidResignActive:) name:NSApplicationDidResignActiveNotification object:NSApp];
    [defaultCenter addObserver:self selector:@selector(windowActiveChanged:) name:NSWindowDidBecomeMainNotification object:self.window];

    [defaultCenter addObserver:self selector:@selector(windowWillEnterFullScreen:) name:NSWindowWillEnterFullScreenNotification object:self.window];
    [defaultCenter addObserver:self selector:@selector(windowExitEnterFullScreen:) name:NSWindowWillExitFullScreenNotification object:self.window];

    [defaultCenter addObserver:self selector:@selector(windowDidEnterFullScreen:) name:NSWindowDidExitFullScreenNotification object:self.window];

    [NSApp addObserver:self forKeyPath:@"effectiveAppearance" options:NSKeyValueObservingOptionNew context:nil];
}

#pragma mark - Private Methods

- (void)setNeedsDisplayForStandardWindowButtons {
    
    self.closeButton.needsDisplay = YES;
    self.miniButton.needsDisplay = YES;
    self.maxButton.needsDisplay = YES;
}

#pragma mark - Notifications

- (void)applicationWillBecomeActive:(NSNotification *)notification {
    
    self.mouseInside = YES;
    [self setNeedsDisplayForStandardWindowButtons];
    
    self.mouseInside = NO;
    [self setNeedsDisplayForStandardWindowButtons];
}

- (void)applicationDidResignActive:(NSNotification *)notification {
    
    self.mouseInside = NO;
    [self setNeedsDisplayForStandardWindowButtons];
}

- (void)windowActiveChanged:(NSNotification *)notification {
    
    self.mouseInside = NO;
    [self setNeedsDisplayForStandardWindowButtons];
}

- (void)windowWillEnterFullScreen:(NSNotification *)notification {
    [self setHidden:YES];
}

- (void)windowExitEnterFullScreen:(NSNotification *)notification {
    [self setHidden:NO];
    self.mouseInside = NO;
}

- (void)windowDidEnterFullScreen:(NSNotification *)notification {
    // use when without modified qt
    [self adjustWindowState];
}

@end
