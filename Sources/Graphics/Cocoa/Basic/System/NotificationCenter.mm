#import <Cocoa/Cocoa.h>

// Implement a callback function.
static void CallBack(CFNotificationCenterRef center, void *observer, CFStringRef name,
                     const void *object, CFDictionaryRef userInfo) {
  NSLog(@"\nCallback detected: \nname: %@ \nobject: %@ \nuserInfo: %@", name, object, userInfo);
}

void startServer() {
  // Registration in receiver process.
  CFNotificationCenterAddObserver(CFNotificationCenterGetDistributedCenter(), NULL, CallBack,
                                  CFSTR("server"), NULL,
                                  CFNotificationSuspensionBehaviorDeliverImmediately);
}

// Sender
void sendMessage() {
  CFMutableDictionaryRef dictionary = CFDictionaryCreateMutable(
      NULL, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
  CFDictionaryAddValue(dictionary, @"key:hello", @"value:world");
  CFNotificationCenterPostNotification(CFNotificationCenterGetDistributedCenter(), CFSTR("server"),
                                       @"string object", dictionary, true);
  CFRelease(dictionary);
}

int main() {
  startServer();
  sendMessage();
  [[NSRunLoop currentRunLoop] run];
}
