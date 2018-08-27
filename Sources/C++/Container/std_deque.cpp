#include <iostream>
#include <deque>
#include <algorithm> // std::sort

namespace ClassFoo
{
void PrintIntDeque(std::deque<int>& deq, char* pre)
{
    std::deque<int>::iterator it;
    std::cout << pre;
    for ( it = deq.begin(); it != deq.end(); it++ )
        std::cout << *it << " ";
    std::cout << std::endl;
}
void DequeExample1()
{
    // 创建一个deque
    std::deque<int> foo;

    // 在 deque 头插入元素
    foo.push_front(6);
    foo.push_front(16);
    foo.push_front(1);
    foo.push_front(23);
    PrintIntDeque(foo,"在开头插入3个元素：");

    // 在 deque 尾插入元素
    foo.push_back(10);
    foo.push_back(30);
    foo.push_back(20);
    PrintIntDeque(foo,"在末尾插入3个元素：");

    // 排序
    std::sort(foo.begin(),foo.end());
    PrintIntDeque(foo,"排序：");

    // 去掉最小值
    foo.pop_front();
    PrintIntDeque(foo,"去掉最小值：");

    // 去掉最大值
    foo.pop_back();
    PrintIntDeque(foo,"去掉最大值：");

    std::random_shuffle(foo.begin(),foo.end());
    PrintIntDeque(foo,"随机打乱：");

    std::cout << "逆序输出：";
    std::deque<int>::reverse_iterator rit;
    for (rit = foo.rbegin(); rit != foo.rend(); rit++ )
        std::cout << *rit << " ";
    std::cout << std::endl;
}
}
int main(void)
{
    ClassFoo::DequeExample1();
    return 0;
}