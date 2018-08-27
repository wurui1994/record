# For Windows
src\tools\windows\refresh_binaries.bat
dump_syms file.pdb > file.sym
# or dump_syms file.exe > file.sym
minidump_stackwalk file.dmp . > info.txt 2>&1

# For macOS
# dsymutil file -> file.dSYM
# dump_syms file.dSYM
xcodebuild dump_syms.xcodeproj -project
dump_syms file > file.sym

# MacOS Example
dump_syms SubtitleClient > SubtitleClient.sym
minidump_stackwalk file.dmp . > info.txt 2>&1
# SubtitleClient/C644C83DD49C3403BCDA79C869398B840/SubtitleClient.sym
string=$(grep "SubtitleClient|" info.txt | cut -d '|' -f 2|tr -d '\r')
mkdir -p SubtitleClient/$string
cp SubtitleClient.sym SubtitleClient/$string/ 
minidump_stackwalk file.dmp . > info.txt

# MacOS build dump_syms, ref:
# http://www.cnblogs.com/csuftzzk/p/mac_breakpad_qt_dump_debug.html
# https://groups.google.com/forum/#!topic/google-breakpad-discuss/fierVnIAv1M
git checkout 01431c2f61aa2af1804f1e139da9bc7c4afa9e7b
cd src/tools/mac/dump_syms
xcodebuild -project dump_syms.xcodeproj -configuration Release