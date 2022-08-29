# clang -pg -g main.c -o main
clang -g main.c -o main
export PATH=$PATH:/Applications/Xcode.app/Contents/Applications/Instruments.app/Contents/MacOS
instruments -t "Time Profiler" ./main
# dtrace -l -n profile-*
# brew install gprof2dot
dtrace -x ustackframes=100 -n 'profile-997 /execname == "test"/ { @[ustack()] = count(); }' -o user_stacks.txt -c './test'
gprof2dot -f dtrace user_stacks.txt | dot -Tpdf -o output.pdf