clang++ -S -emit-llvm main1.cpp -o - | opt -analyze -dot-callgraph
dot -Tpng -ocallgraph.png callgraph.dot