for /r %f in (*.cc) do @cl %f /I. /DWRAPPING_CEF_SHARED /MD /c /w /EHsc
link *.obj Release\libcef.lib /DLL /OUT:libcef_wrapper.dll /MAP:libcef_wrapper.map