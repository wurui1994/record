// wget https://github.com/cpp-taskflow/cpp-taskflow/raw/master/taskflow.hpp
// g++ cpp-taskflow.cpp -std=c++1z -O2 -lpthread -o cpp-taskflow && ./cpp-taskflow
// cl /std:c++latest cpp-taskflow.cpp [VS2017 cl /std:c++17 cpp-taskflow.cpp]

// A simple example to capture the following task dependencies.
//
// TaskA---->TaskB---->TaskD
// TaskA---->TaskC---->TaskD

#include "taskflow.hpp"  // the only include you need

int main(){

  tf::Taskflow tf(std::thread::hardware_concurrency());

  auto [A, B, C, D] = tf.silent_emplace(
    [] () { std::cout << "TaskA\n"; },               //  the taskflow graph
    [] () { std::cout << "TaskB\n"; },               // 
    [] () { std::cout << "TaskC\n"; },               //          +---+          
    [] () { std::cout << "TaskD\n"; }                //    +---->| B |-----+   
  );                                                 //    |     +---+     |
                                                     //  +---+           +-v-+ 
  A.precede(B);  // B runs after A                   //  | A |           | D | 
  A.precede(C);  // C runs after A                   //  +---+           +-^-+ 
  B.precede(D);  // D runs after B                   //    |     +---+     |    
  C.precede(D);  // D runs after C                   //    +---->| C |-----+    
                                                     //          +---+          
  tf.wait_for_all();  // block until finished

  return 0;
}
