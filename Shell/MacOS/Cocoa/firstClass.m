#import <Foundation/Foundation.h>

@interface C:NSObject
- (void)M;
@end

@implementation C

- (void)M {
    NSLog(@"Hello, World! \n");
}

@end

int main() {
    /* my first program in Objective-C */
    C *c = [[C alloc]init];
    [c M];
    return 0;
}