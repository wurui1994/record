// clang fileSize.m -fobjc-arc

#import <Foundation/Foundation.h>

int main(int argc, const char * argv[])
{
    NSFileManager *fm = [NSFileManager defaultManager];
    NSString *fileName = [[NSString alloc] initWithCString:argv[0] encoding:NSASCIIStringEncoding];
    NSLog(@"%llu", [[fm attributesOfItemAtPath:fileName error:NULL] fileSize]);
    return 0;
}
