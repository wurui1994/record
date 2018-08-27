# 先决条件: 
1.VS2017 安装C++和C#
2.VSYASM 
	2.1管理员权限运行VSYASM\install_script.bat
	2.2环境变量PATH加入C:\Program Files (x86)\Microsoft Visual Studio\2017\Enterprise\VC
# 3.WinRar
	# WinRarPath C:\Program Files\WinRAR\WinRar.exe

# boost: git submodule update --init --recursive 比较耗时
	
# wget -c http://fribidi.org/download/fribidi-0.19.6.tar.bz2

# git clone https://github.com/Aegisub/assdraw

# wget http://www.antigrain.com/agg-2.5.zip

# fribidi.vcxproj修改:

# <TarballProject
# Url="file:///E:/Workspace/Aegisub/bin/fribidi-0.19.6.tar.bz2"
# Hash="cba8b7423c817e5adf50d28ec9079d14eafcec9127b9e8c8f1960c5ad585e17d"
# Root="$(FribidiSrcDir)"
# />
  
# PortableInstaller.vcxproj修改:
# <Message Importance="High" Text="&quot;$(WinRarPath)&quot; a -sfx -s -m5 -ep1 -r -zportable-comment.txt -iimgside-logo.bmp -iiconicon.ico $(OutputFile) $(FileName)" />

# <Message Importance="High" Text="@(RarContents)" />