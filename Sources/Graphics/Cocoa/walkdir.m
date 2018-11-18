#import <Foundation/Foundation.h>
 
int main() 
{
    @autoreleasepool {

    //Non-recursively
    NSString *dir = NSHomeDirectory(); // @"/foo/bar";
    // Pre-OS X 10.5
    // NSArray *contents = [[NSFileManager defaultManager] directoryContentsAtPath:dir];
    // OS X 10.5+
    NSArray *contents = [[NSFileManager defaultManager] contentsOfDirectoryAtPath:dir error:NULL];
    
    for (NSString *file in contents)
    if ([[file pathExtension] isEqualToString:@"mp3"])
        NSLog(@"%@", file);
    }

    //Recursively
    NSString *dir = NSHomeDirectory();
    NSDirectoryEnumerator *de = [[NSFileManager defaultManager] enumeratorAtPath:dir];
    
    for (NSString *file in de)
    if ([[file pathExtension] isEqualToString:@"mp3"])
        NSLog(@"%@", file);
}