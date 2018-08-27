
#include <iostream>
#include <tuple>
#include <string>

using namespace std;

// helper function to print a tuple of any size
template<class Tuple, std::size_t N>
struct TuplePrinter {
    static void print(const Tuple& t) 
    {
        TuplePrinter<Tuple, N-1>::print(t);
        cout << ", " << get<N-1>(t);
    }
};

template<class Tuple>
struct TuplePrinter<Tuple, 1> {
    static void print(const Tuple& t) 
    {
        cout << get<0>(t);
    }
};

template<class... Args>
void print(const std::tuple<Args...>& t) 
{
    cout << "(";
    TuplePrinter<decltype(t), sizeof...(Args)>::print(t);
    cout << ")\n";
}
// end helper function

auto func()
{
    return make_tuple("hello","world");
}

int main()
{
    auto t = func();
    print(t);
}