#include <iostream>
using namespace std;

class iter
{
private:
    int v;
public:
    iter(int n) {v = n;}
    int operator*() { return v; }
    bool operator!=(iter e) { return v != *e; }
    iter operator++() { v++;return *this;}
};

void print(int x, std::string end = " ")
{
    std::cout << x << end;
}

int main(int argc, char const *argv[])
{
    iter b(3);
    iter e(8);
    for(; b!=e; ++b) print(*b);
    return 0;
}
