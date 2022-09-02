// swift -framework AppKit miniwindow.swift
import Cocoa

class AppDelegate: NSObject, NSApplicationDelegate {
    func applicationShouldTerminateAfterLastWindowClosed(_ sender: NSApplication) -> Bool
    {
        return true;
    }
}

let delegate = AppDelegate()
NSApplication.shared.delegate = delegate
NSApplication.shared.setActivationPolicy(NSApplication.ActivationPolicy.regular)
var newWindow: NSWindow? = NSWindow(contentRect: NSMakeRect(10, 10, 300, 300), 
 styleMask: [.titled, .resizable, .miniaturizable, .closable, .fullSizeContentView], 
 backing: .buffered, defer: false)
newWindow?.center()
// newWindow!.orderFrontRegardless()
newWindow!.makeKeyAndOrderFront(nil)
// NSApplicationMain(CommandLine.argc, CommandLine.unsafeArgv)
NSApplication.shared.activate(ignoringOtherApps: true)
NSApplication.shared.run()