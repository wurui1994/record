#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    auto p = minmax(32,25);
    cout << p.first << " " << p.second << endl;
    return 0;
}