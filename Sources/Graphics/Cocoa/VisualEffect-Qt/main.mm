#include <QtWidgets>

#include <Cocoa/Cocoa.h>

void setVisualEffect(QWidget* parent)
{
    if (!parent)
    {
        return;
    }
    parent->setAttribute(Qt::WA_NoBackground);
    parent->setAttribute( Qt::WA_TranslucentBackground );
	NSView *nsview = (__bridge NSView *)reinterpret_cast<void *>(parent->winId());
	NSWindow *nswindow = [nsview window];

	nswindow.appearance = [NSAppearance appearanceNamed:NSAppearanceNameVibrantDark];
//	nswindow.titlebarAppearsTransparent = true;

//	nswindow.styleMask |= NSFullSizeContentViewWindowMask |
//						 NSClosableWindowMask |
//						 NSResizableWindowMask;

	nswindow.movableByWindowBackground = true;

	static const NSRect frameRect = {
		{ 0.0, 0.0 } ,
		{ static_cast<CGFloat>(parent->width()), static_cast<CGFloat>(parent->height()) }
	};
	NSVisualEffectView * vibrant  = [[NSVisualEffectView alloc] initWithFrame:frameRect];
	vibrant.material = NSVisualEffectMaterialDark;//Dark,MediumLight,PopOver,UltraDark,AppearanceBased,Titlebar,Menu
	vibrant.blendingMode = NSVisualEffectBlendingModeBehindWindow;//I think if you set this to WithinWindow you get the effect safari has in its TitleBar. It should have an Opaque background behind it or else it will not work well
	vibrant.state = NSVisualEffectStateActive;//FollowsWindowActiveState,Inactive

	NSView* qtView = nswindow.contentView;
	[qtView setAutoresizingMask:NSViewWidthSizable|NSViewHeightSizable];

	nswindow.contentView = vibrant;
	[vibrant addSubview:qtView];
	
	//
	[nswindow setLevel:kCGScreenSaverWindowLevel - 1];
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);    
    QMainWindow window;   
    
    QWidget* widget = new QWidget(&window);      
    QHBoxLayout* layout = new QHBoxLayout;
    QPushButton* button = new QPushButton("hello",widget);
    QPushButton* button2 = new QPushButton("world",widget);
    layout->addWidget(button);
    layout->addWidget(button2);
    widget->setLayout(layout);  
    window.setCentralWidget(widget);
    window.show();
    
    setVisualEffect(widget);
    
    return app.exec();
}
