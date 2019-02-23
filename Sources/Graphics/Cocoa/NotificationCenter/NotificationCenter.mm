#include "NotificationCenter.h"
#import <Cocoa/Cocoa.h>
//
static void CallBack(CFNotificationCenterRef center, void *observer, CFStringRef name, const void *object, CFDictionaryRef userInfo);
//

NotificationCenter& NotificationCenter::instance()
{
	static NotificationCenter logger;
	return logger;
}

void NotificationCenter::startServer(QString name)
{
    // Registration in receiver process.
    CFNotificationCenterAddObserver(CFNotificationCenterGetDistributedCenter(),NULL,
        CallBack,(CFStringRef)name.toNSString(),
        NULL,CFNotificationSuspensionBehaviorDeliverImmediately);
}

void NotificationCenter::sendMessage(QString name,QString object)
{  
    CFNotificationCenterPostNotification(CFNotificationCenterGetDistributedCenter(),
        (CFStringRef)name.toNSString(), object.toNSString(), nil, true);
}
//
void NotificationCenter::onMessage(QString name,QString object)
{
	qDebug() << name << object;
}

void NotificationCenter::runLoop()
{
	[[NSRunLoop currentRunLoop] runUntilDate:[NSDate dateWithTimeIntervalSinceNow:0.5]];
	//
	// [[NSRunLoop currentRunLoop] run];
}

//
static void CallBack(CFNotificationCenterRef center, void *observer, CFStringRef name, const void *object, CFDictionaryRef userInfo) 
{
	NSString* ns_name = (__bridge NSString *)name;
	NSString* ns_object = (__bridge NSString *)object;
	NotificationCenterInstance.onMessage(QString::fromNSString(ns_name), 
		QString::fromNSString(ns_object));
}
