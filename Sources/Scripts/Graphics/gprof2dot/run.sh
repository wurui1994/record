# clang -pg -g main.c -o main
clang -g main.c -o main
export PATH=$PATH:/Applications/Xcode.app/Contents/Applications/Instruments.app/Contents/MacOS
instruments -t "Time Profiler" ./main
# dtrace -l -n profile-*
# brew install gprof2dot
dtrace -x ustackframes=100 -n 'profile-997 /execname == "test"/ { @[ustack()] = count(); }' -o user_stacks.txt -c './test'
gprof2dot -f dtrace user_stacks.txt | dot -Tpdf -o output.pdf
# brew install flamegraph
stackcollapse.pl user_stacks.txt | flamegraph.pl > pretty-graph.svg
# brew install gperftools
# Ref:https://www.cnblogs.com/yangzhouyyz/p/5433757.html
clang -g main.c -o main `pkg-config --cflags --libs libprofiler`
env CPUPROFILE=./test.prof ./main
pprof ./main test.prof --text
pprof ./main test.prof --pdf > test.pdf
pprof ./main test.prof --svg > test.svg
pprof ./main test.prof --web
# brew install qcachegrind
pprof --callgrind ./main test.prof > test.callgrind
qcachegrind test.callgrind