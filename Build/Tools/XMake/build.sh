# yaourt -S xmake
xmake create -l c -P ./hello --root
xmake run -P hello --root

xmake create -l c++ -P ./cpp --root
xmake run -P ./cpp --root

rm -rf hello cpp