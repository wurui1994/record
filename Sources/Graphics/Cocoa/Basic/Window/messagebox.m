// To show a modal alert (Mac):
// clang -fobjc-arc messagebox.m -framework AppKit
#import <AppKit/AppKit.h>
int main()
{
    NSAlert *alert = [[NSAlert alloc] init];
    [alert setMessageText:@"Goodbye, World!"];
    [alert runModal];
}


// To show a modal alert (iOS):

// UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Goodbye, World!" message:nil delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
// [alert show];