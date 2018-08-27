target("hello")
    set_kind("binary")
    add_files("*.c")
    add_includedirs("E:\\Workspace\\vcpkg\\installed\\x86-windows\\include")
    add_linkdirs("E:\\Workspace\\vcpkg\\installed\\x86-windows\\lib")
    add_ldflags("user32.lib gdi32.lib")

    before_run(function ()
        os.setenv("PATH","E:\\Workspace\\vcpkg\\installed\\x86-windows\\bin")
        print("run")
    end)

