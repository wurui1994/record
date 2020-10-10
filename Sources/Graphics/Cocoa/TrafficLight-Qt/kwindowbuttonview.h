
#import <Cocoa/Cocoa.h>

@interface KWindowButtonView : NSView

@property (nonatomic, strong, readonly) NSButton *closeButton;
@property (nonatomic, strong, readonly) NSButton *miniButton;
@property (nonatomic, strong, readonly) NSButton *maxButton;

- (void)resetButtonPosition;
- (void)updateWindowRadiusButton;
- (void)adjustWindowState;

@end
