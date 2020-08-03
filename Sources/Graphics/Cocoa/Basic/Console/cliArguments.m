#import <Foundation/Foundation.h>

int main()
{
    @autoreleasepool {
        NSLog(@"Hello, World!");
        NSLog(@"%@", [NSDate date]);
        //
        NSArray* args = [[NSProcessInfo processInfo] arguments];
        NSLog(@"This program is named %@.", [args objectAtIndex:0]);
        NSLog(@"There are %u arguments.", [args count] - 1);
        for (int i = 1; i < [args count]; ++i) {
            NSLog(@"the argument #%d is %@", i, [args objectAtIndex:i]);
        }
        //
        NSLog(@"%@", [[NSDate date] descriptionWithCalendarFormat:@"%Y-%m-%d" timeZone:nil locale:nil]);
        NSLog(@"%@", [[NSDate date] descriptionWithCalendarFormat:@"%A, %B %d, %Y" timeZone:nil locale:nil]);
        //
        if ([[NSScanner scannerWithString:@"-123.4e5"] scanFloat:NULL])
            NSLog(@"\"-123.4e5\" is numeric");
        else
            NSLog(@"\"-123.4e5\" is not numeric");
        if ([[NSScanner scannerWithString:@"Not a number"] scanFloat:NULL])
            NSLog(@"\"Not a number\" is numeric");
        else
            NSLog(@"\"Not a number\" is not numeric");
        // prints: "-123.4e5" is numeric
        // prints: "Not a number" is not numeric

        //
        NSLog(@"%09.3f", 7.125);
        NSLog(@"%@", [NSString stringWithFormat:@"%09.3f", 7.125]);
        //
        NSLog(@"%@", [[NSProcessInfo processInfo] hostName]);
    }
}