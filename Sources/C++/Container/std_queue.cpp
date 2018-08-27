#include <iostream>
#include <queue>

namespace ClassFoo
{
void QueueExample1()
{
    std::queue<int> foo1;

    std::cout << "foo1.empty()：" << std::boolalpha
              << foo1.empty() << std::endl;

    // 逐个压入元素
    std::cout << "压入四个元素：" << std::endl;
    foo1.push(1);
    std::cout << foo1.back() << " ";
    foo1.push(2);
    std::cout << foo1.back() << " ";
    foo1.push(3);
    std::cout << foo1.back() << " ";
    foo1.push(4);
    std::cout << foo1.back() << " " << std::endl;

    std::cout << "foo1.empty()：" << std::boolalpha
              << foo1.empty() << std::endl;
    std::cout << "foo1.size()："
              << foo1.size() << std::endl;

    // 逐个弹出元素
    std::cout << "弹出四个元素：" << std::endl;
    std::cout << foo1.front() << " ";
    foo1.pop();
    std::cout << foo1.front() << " ";
    foo1.pop();
    std::cout << foo1.front() << " ";
    foo1.pop();
    std::cout << foo1.front() << " " << std::endl;
    foo1.pop();

    std::cout << "foo1.empty()：" << std::boolalpha
              << foo1.empty() << std::endl;
    std::cout << "foo1.size()："
              << foo1.size() << std::endl;
}
}
int main ()
{
    ClassFoo::QueueExample1();
    return 0;
}