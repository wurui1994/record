#include <iostream>
#include <queue>
#include <functional>


using namespace std;

void PriorityQueueExample1()
{
    priority_queue<int,vector<int>,greater<int> > foo1;
    priority_queue<int,vector<int> >foo2;
    int a[]= {1,3,4,2,5,0,6};
    for(int i=0; i<7; i++)
    {
        foo1.push(a[i]);
        foo2.push(a[i]);
    }
    cout<<"foo1:";
    while(!foo1.empty())
    {
        cout<<foo1.top()<<" ";
        foo1.pop();
    }
    cout << endl;
    cout << "foo2:";
    while(!foo2.empty())
    {
        cout<<foo2.top()<<" ";
        foo2.pop();
    }
    cout << endl;
}

int main()
{
    PriorityQueueExample1();
    return 0;
}