#import <Foundation/Foundation.h>

void runls()
{
    [[NSTask launchedTaskWithLaunchPath:@"/bin/ls"
        arguments:@[]] waitUntilExit];
}
 
void runSystemCommand(NSString *cmd)
{
    [[NSTask launchedTaskWithLaunchPath:@"/bin/sh"
        arguments:@[@"-c", cmd]]
        waitUntilExit];
}
 
int main(int argc, const char **argv)
{
    @autoreleasepool {
 
      runSystemCommand(@"ls");
    }
    return 0;
}