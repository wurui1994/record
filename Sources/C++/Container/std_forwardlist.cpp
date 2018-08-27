#include <iostream>
#include <forward_list>
#include <numeric>
#include <algorithm>

namespace ClassFoo
{

using namespace std;

void ForwardListExample1()
{
    forward_list<int> foo1;
    forward_list<int>::iterator it;

    //从前面向foo1容器中添加数据
    foo1.push_front (2);
    foo1.push_front (1);
    foo1.push_front (14);
    foo1.push_front (17);

    //按从小到大排序
    foo1.sort();
    cout<<"foo1中的元素"<<endl;
    for (it = foo1.begin(); it != foo1.end(); ++it)
        cout << *it << " ";
    cout << endl;

    //使用STL的accumulate(累加)算法
    int result = accumulate(foo1.begin(), foo1.end(),0);
    cout<<"和为："<<result<<endl;

    //使用STL的max_element算法求foo2中的最大元素并显示
    it=max_element(foo1.begin(),foo1.end());
    cout << "最大元素是: "<< *it <<endl;
}
}

int main()
{
    ClassFoo::ForwardListExample1();
    return 0;
}