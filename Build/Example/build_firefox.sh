cd mozilla-central

./mach bootstrap

./mach build

First: 64:10.59 LLVM ERROR: out of memory
改用mozbuild的lld-link

./mach run

/d/Software/GitHub/Firefox/mozilla-central