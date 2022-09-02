// swift -framework SwiftUI swiftui.swift
import SwiftUI

struct ContentView: View {
    @State var message = "Hello, World!"
    @State var isRunning = false
    
    var body: some View {
        VStack {
            Text("SayThis")
                .font(.largeTitle)
                .padding()
            HStack {
                TextField("Message", text: $message)
                    .padding(.leading)
                Button(action: {
                    let executableURL = URL(fileURLWithPath: "/usr/bin/say")
                    self.isRunning = true
                    try! Process.run(executableURL,
                                     arguments: [self.message],
                                     terminationHandler: { _ in self.isRunning = false })
                }) {
                    Text("Say")
                }.disabled(isRunning)
                    .padding(.trailing)
            }
        }.frame(maxWidth: .infinity, maxHeight: .infinity)
    }
}

class SwiftUIAppDelegate: NSObject, NSApplicationDelegate {
    func applicationShouldTerminateAfterLastWindowClosed(_ sender: NSApplication) -> Bool
    {
        return true;
    }
}

@available(OSX 11.0, *)
struct SwiftUIApp: App {
    @NSApplicationDelegateAdaptor(SwiftUIAppDelegate.self) var delegate
    var body: some Scene {
        WindowGroup {
            ContentView()
                .frame(maxWidth: .infinity, maxHeight: .infinity)
        }
    }
}

class AppDelegate: NSObject, NSApplicationDelegate {
    var window: NSWindow!

    func applicationDidFinishLaunching(_ aNotification: Notification) {
        // Create the SwiftUI view that provides the window contents.
        let contentView = ContentView()
            .frame(maxWidth: .infinity, maxHeight: .infinity)

        // Create the window and set the content view.
        window = NSWindow(
            contentRect: NSRect(x: 0, y: 0, width: 480, height: 300),
            styleMask: [.titled, .closable, .miniaturizable, .resizable, .fullSizeContentView],
            backing: .buffered, defer: false)

        window.title = "Window Title"
        window.isReleasedWhenClosed = false
        window.center()
        window.setFrameAutosaveName("Main Window")
        window.contentView = NSHostingView(rootView: contentView)
        window.makeKeyAndOrderFront(nil)
    }

    func applicationShouldTerminateAfterLastWindowClosed(_ sender: NSApplication) -> Bool
    {
        return true;
    }
}

if #available(OSX 11.0, *) {
    NSApplication.shared.setActivationPolicy(.regular)
    NSApp.activate(ignoringOtherApps: true)
    SwiftUIApp.main()
} else {
    NSApplication.shared.setActivationPolicy(.regular)
    let appDelegate = AppDelegate()
    NSApp.delegate = appDelegate
    NSApp.activate(ignoringOtherApps: true)
    NSApp.run()
}