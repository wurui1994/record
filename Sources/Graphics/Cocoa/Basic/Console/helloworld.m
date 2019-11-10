// http://rosettacode.org/wiki/Hello_world/Text#Objective-C

// #import <Foundation/Foundation.h>

// int main() {
//     @autoreleasepool {
//         NSLog(@"Hello, World!");
//         NSLog(@"%@", [NSDate date]);
//     }
// }

// #import <Foundation/Foundation.h>

// int main() {
//     @autoreleasepool {
//         NSString *message = @"Hello, World!\n";
//         printf("%s", message.UTF8String);
//     }
// }

#import <Foundation/Foundation.h>

int main()
{
    @autoreleasepool {
        NSFileHandle* standardOutput = [NSFileHandle fileHandleWithStandardOutput];
        NSString* message = @"Hello, World!\n";
        [standardOutput writeData:[message dataUsingEncoding:NSUTF8StringEncoding]];
    }
}
