#include <QtWidgets>

#include <Cocoa/Cocoa.h>

CGImageRef CGImageRefCopyFromNSImage(NSImage* image)
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
        CGImageSourceRef imageSource =  CGImageSourceCreateWithData((__bridge CFDataRef)(imageData),  NULL);     //need release
        imageRef = CGImageSourceCreateImageAtIndex( imageSource, 0, NULL);   //need release by caller
        
        CFRelease(imageSource);
    }
    
    return imageRef;    
}

QPixmap QPixmapFromCGImageRef(const CGImageRef &image)
{
    if(!image)
        return QPixmap();
        
    const std::size_t width = CGImageGetWidth(image);
    const std::size_t height = CGImageGetHeight(image);
    QImage result(static_cast<int>(width), static_cast<int>(height), QImage::Format_ARGB32_Premultiplied);
    if(result.isNull())
        return QPixmap();

    // result.fill(Qt::transparent);
    result.fill(Qt::gray);

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

QPixmap drawTextOnImage(QString title,QRect rect,float fontSize)
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
    [aString drawInRect:NSMakeRect(0,0,rect.width(),rect.height()*1.2) withAttributes:attribs];
    // NSBitmapImageRep* bitmap = [[NSBitmapImageRep alloc] initWithFocusedViewRect:
    //     NSMakeRect (0.0f, 0.0f, frameSize.width, frameSize.height)];
    [image unlockFocus]; 
    QPixmap pixmap = QPixmapFromCGImageRef(CGImageRefCopyFromNSImage(image));
    [image release];
    [pool release];
    return pixmap;
}

int main(int argc, char **argv)
{
    QApplication app(argc,argv);
    QString title = "Hello World";
    QRect rect = {0,0,100,20};
    float fontSize = 16;
    QPixmap pixmap = drawTextOnImage(title,rect,fontSize);
    pixmap.save("test.png");
    return 0;
}
