// Module QtWebEngine
// ref: render_widget_host_view_qt.cpp --> void RenderWidgetHostViewQt::handleKeyEvent(QKeyEvent *ev)

if(ev->modifiers() & Qt::AltModifier)
{
	return;
}
//

if (keyDownTextInsertion) {
	// Blink won't consume the RawKeyDown, but rather the Char event in this case.
	// The RawKeyDown is skipped on the way back (see above).
	// The same os_event will be set on both NativeWebKeyboardEvents.
	webEvent.skip_in_browser = false;
	webEvent.SetType(blink::WebInputEvent::kChar);
	m_host->ForwardKeyboardEvent(webEvent);
}