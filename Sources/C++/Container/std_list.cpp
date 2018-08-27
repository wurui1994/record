#include <iostream>
#include <list>
#include <numeric>
#include <algorithm>

namespace ClassFoo
{

using namespace std;

//创建一个list容器的实例LISTINT
typedef list<int> LISTINT;

//创建一个list容器的实例LISTCHAR
typedef list<int> LISTCHAR;

void ListExample1()
{
    //--------------------------
    //用list容器处理整型数据
    //--------------------------
    //用LISTINT创建一个名为foo1的list对象
    LISTINT foo1;
    //声明i为迭代器
    LISTINT::iterator i;

    //从前面向foo1容器中添加数据
    foo1.push_front (2);
    foo1.push_front (1);

    //从后面向foo1容器中添加数据
    foo1.push_back (3);
    foo1.push_back (4);

    //从前向后显示foo1中的数据
    cout<<"foo1.begin()--- foo1.end():"<<endl;
    for (i = foo1.begin(); i != foo1.end(); ++i)
        cout << *i << " ";
    cout << endl;

    //从后向后显示foo1中的数据
    LISTINT::reverse_iterator ir;
    cout<<"foo1.rbegin()---foo1.rend():"<<endl;
    for (ir =foo1.rbegin(); ir!=foo1.rend(); ir++)
    {
        cout << *ir << " ";
    }
    cout << endl;

    //使用STL的accumulate(累加)算法
    int result = accumulate(foo1.begin(), foo1.end(),0);
    cout<<"Sum="<<result<<endl;
    cout<<"------------------"<<endl;

    //--------------------------
    //用list容器处理字符型数据
    //--------------------------

    //用LISTCHAR创建一个名为foo1的list对象
    LISTCHAR foo2;
    //声明i为迭代器
    LISTCHAR::iterator j;

    //从前面向foo2容器中添加数据
    foo2.push_front ('A');
    foo2.push_front ('B');

    //从后面向foo2容器中添加数据
    foo2.push_back ('x');
    foo2.push_back ('y');

    //从前向后显示foo2中的数据
    cout<<"foo2.begin()---foo2.end():"<<endl;
    for (j = foo2.begin(); j != foo2.end(); ++j)
        cout << char(*j) << " ";
    cout << endl;

    //使用STL的max_element算法求foo2中的最大元素并显示
    j=max_element(foo2.begin(),foo2.end());
    cout << "The maximum element in foo2 is: "<<char(*j)<<endl;
}
}

int main()
{
    ClassFoo::ListExample1();
    return 0;
}