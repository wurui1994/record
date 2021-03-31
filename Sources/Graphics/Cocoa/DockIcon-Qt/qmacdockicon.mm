#include "qmacdockicon.h"

#include <QImageWriter>
#include <QMenu>
#include <QBuffer>
#include <QWidget>
#include <QDebug>

#undef slots
#define OBJC_OLD_DISPATCH_PROTOTYPES 1
#include <Cocoa/Cocoa.h>
#include <objc/objc.h>
#include <objc/message.h>

static QMacDockIcon *s_instance = NULL;

bool dockClickHandler(id self,SEL _cmd,...) 
{
    Q_UNUSED(self)
    Q_UNUSED(_cmd)

    qDebug() << __FUNCTION__ << __LINE__;
    
    s_instance->handleDockIconClickEvent();
    
    // Return NO (false) to suppress the default OS X actions
    return false;
}

void dockQuitHandler(id self,SEL _cmd,...) 
{
    Q_UNUSED(self)
    Q_UNUSED(_cmd)
    
    s_instance->handleDockIconQuitEvent();
}

QMacDockIcon::QMacDockIcon() : QObject()
{
    Class cls = objc_getClass("NSApplication");
    id appInst = objc_msgSend((id)cls, sel_registerName("sharedApplication"));
    
    qDebug() << __FUNCTION__ << __LINE__ << appInst;
    if (appInst != NULL) 
    {
        id delegate = objc_msgSend(appInst, sel_registerName("delegate"));
        Class delClass = (Class)objc_msgSend(delegate,  sel_registerName("class"));
        SEL shouldHandle = sel_registerName("applicationDidBecomeActive:");
        if (class_getInstanceMethod(delClass, shouldHandle))
        {
            qDebug() << __FUNCTION__ << __LINE__ << "class_replaceMethod";
            class_replaceMethod(delClass, shouldHandle, (IMP)dockClickHandler, "B@:");
        }
        else
        {
            qDebug() << __FUNCTION__ << __LINE__ << "class_addMethod";
            class_addMethod(delClass, shouldHandle, (IMP)dockClickHandler,"B@:");
        }
    }
    
    if (appInst != NULL) 
    {
        id delegate = objc_msgSend(appInst, sel_registerName("delegate"));
        Class delClass = (Class)objc_msgSend(delegate,  sel_registerName("class"));
		SEL shouldHandle = sel_registerName("applicationWillQuit");
        if (class_getInstanceMethod(delClass, shouldHandle))
            class_replaceMethod(delClass, shouldHandle, (IMP)dockQuitHandler, "B@:");
        else
            class_addMethod(delClass, shouldHandle, (IMP)dockQuitHandler,"B@:");
    }
}

QMacDockIcon::~QMacDockIcon()
{
}

void QMacDockIcon::setIcon(const QIcon &icon)
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    NSImage *image = nil;
    if (icon.isNull())
        image = [[NSImage imageNamed:@"NSApplicationIcon"] retain];
    else 
    {
        // generate NSImage from QIcon and use this as dock icon.
        QSize size = icon.actualSize(QSize(128, 128));
        QPixmap pixmap = icon.pixmap(size);

        // Write image into a R/W buffer from raw pixmap, then save the image.
        QBuffer notificationBuffer;
        if (!pixmap.isNull() && notificationBuffer.open(QIODevice::ReadWrite)) 
        {
            QImageWriter writer(&notificationBuffer, "PNG");
            if (writer.write(pixmap.toImage())) 
            {
                NSData* macImgData = [NSData dataWithBytes:notificationBuffer.buffer().data()
                                             length:notificationBuffer.buffer().size()];
                image =  [[NSImage alloc] initWithData:macImgData];
            }
        }

        if(!image) 
        {
            // if testnet image could not be created, load std. app icon
            image = [[NSImage imageNamed:@"NSApplicationIcon"] retain];
        }
    }

    [NSApp setApplicationIconImage:image];
    [image release];
    [pool release];
}

QMacDockIcon *QMacDockIcon::instance()
{
    if (!s_instance)
        s_instance = new QMacDockIcon();
    return s_instance;
}

void QMacDockIcon::handleDockIconClickEvent()
{

    emit this->dockIconClicked();
}

void QMacDockIcon::handleDockIconQuitEvent()
{
    emit this->dockIconTryToQuit();
}

void QMacDockIcon::showDockIcon()
{
    [NSApp setActivationPolicy: NSApplicationActivationPolicyRegular];
}

void QMacDockIcon::hideDockIcon()
{
    [NSApp setActivationPolicy: NSApplicationActivationPolicyAccessory];
}

CGImageRef dock_CGImageRefCopyFromNSImage(NSImage* image)
{
	NSSize size = [image size];
	if(size.width == 0 || size.height ==0)
	{
        NSBitmapImageRep * rep = [NSBitmapImageRep imageRepWithData:[image TIFFRepresentation]];
		NSSize imgSize = NSMakeSize([rep pixelsWide],[rep pixelsHigh]);
		[image setSize:imgSize];
	}
    
    NSData * imageData = [image TIFFRepresentation];
    CGImageRef imageRef = nil;
    if(imageData)
    {
        CGImageSourceRef imageSource = 	CGImageSourceCreateWithData((__bridge CFDataRef)(imageData),  NULL);	 //need release
        imageRef = CGImageSourceCreateImageAtIndex( imageSource, 0, NULL);   //need release by caller
		
		CFRelease(imageSource);
    }
	
    return imageRef;	
}

QPixmap dock_QPixmapFromCGImageRef(const CGImageRef &image)
{
    if(!image)
        return QPixmap();
        
    const std::size_t width = CGImageGetWidth(image);
    const std::size_t height = CGImageGetHeight(image);
    QImage result(static_cast<int>(width), static_cast<int>(height), QImage::Format_ARGB32_Premultiplied);
    if(result.isNull())
        return QPixmap();

    result.fill(Qt::transparent);

    CGColorSpace* colorSpace = CGColorSpaceCreateWithName(kCGColorSpaceSRGB);
    if(!colorSpace)
        return QPixmap();

    CGContext* context = CGBitmapContextCreate(static_cast<void*>(result.bits()),
            width, height, 8, width * 4, colorSpace, kCGImageAlphaPremultipliedFirst | kCGBitmapByteOrder32Host);
    if(!context)
        return QPixmap();

    CGRect rect = CGRectMake(0, 0, width, height);
    CGContextDrawImage(context, rect, image);
    return QPixmap::fromImage(result);
}

QPixmap dock_drawTextOnImage(QString title,QRect rect,float fontSize)
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    NSColor *color = [NSColor whiteColor]; 
    NSFont* font = [NSFont fontWithName:@"PingFangSC-Semibold" size:fontSize];
    NSMutableParagraphStyle * paragraphStyle = [[NSMutableParagraphStyle alloc] init];
    paragraphStyle.alignment = NSTextAlignmentCenter;
    paragraphStyle.lineBreakMode = NSLineBreakByTruncatingTail;
    NSMutableDictionary* attribs = [[NSMutableDictionary dictionaryWithCapacity: 3] retain];
    //
    [attribs setObject:font forKey:NSFontAttributeName]; 
    [attribs setObject:color forKey:NSForegroundColorAttributeName];
    [attribs setObject:paragraphStyle forKey:NSParagraphStyleAttributeName];
    
    NSString* aString = title.toNSString();
    NSSize frameSize = NSMakeSize(rect.width(),rect.height()); 
    
    NSImage* image = [[NSImage alloc] initWithSize:frameSize];
    [image lockFocus]; 
    [aString drawInRect:NSMakeRect(0,0,rect.width(),rect.height()*1.1) withAttributes:attribs];
    [image unlockFocus]; 
    QPixmap pixmap = dock_QPixmapFromCGImageRef(dock_CGImageRefCopyFromNSImage(image));
    [image release];
    [pool release];
    return pixmap;
}
