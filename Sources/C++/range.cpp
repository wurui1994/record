#include <iostream>
#include <type_traits>

template <typename T>
class Range
{
public:
    Range(T b, T e, T s) : s(s) 
    {
        size_t x = (e - b) / s;
        if (b + s*x != e)
            ++x;
        m = x;
        v = b;
    }
    Range iter(T n)  {c = n;return*this;}
    Range begin() {return iter(0);}
    Range end() {return iter(m);}
    T operator*() { return v; }
    bool operator!=(Range e) {return c != e.c;}
    void operator++() {c++;v+=s;}
private:
    T s; // step
    T v; // value
    size_t c; // cursor (iter)
    size_t m; // max (iter)
};

auto range(auto end)
{
    return Range{{}, end, 1};
}

#if 0 // old style
#if 0 // std::enable_if_t
auto range(auto begin, auto end) ->
std::enable_if_t<std::is_same_v<char, decltype(begin)>, Range<char>>
{
    return Range<char> {begin, end, 1};
}

auto range(auto begin, auto end) ->
std::enable_if_t<!std::is_same_v<char, decltype(begin)>, Range<decltype(begin + end)>>
{
    return Range<decltype(begin + end)> (begin, end, 1);
}
#else // std::conditional_t
template <typename U, typename V>
using T = std::conditional_t<std::is_same_v<char, U>, 
        Range<char>, Range<decltype(U() + V())>>;
// c++ 11
template <typename B, typename E>
T<B,E> range(B begin, E end)
{
    return T<B,E> (begin, end, 1);
}
#endif
#else
auto range(auto begin, auto end) 
{
    if constexpr (std::is_same_v<char, decltype(begin)>
        && std::is_same_v<char, decltype(end)>)
        return Range<char> {begin, end, 1};
    else
        return Range<decltype(begin + end)> (begin, end, 1);
}
#endif

// plus not for char
// Range<char> range(char begin, char end)
// {
//     return {begin, end, 1};
// }

auto range(auto begin, auto end, auto step)
{
    return Range<decltype(begin + step)>(begin, end, step);
}

using namespace std;

void print(auto x, std::string end = " ")
{
    std::cout << x << end;
}

void println(auto x)
{
    std::cout << x << std::endl;
}

void print_range(std::string s, auto r)
{
    print(s);
    for (auto i: r) print(i);
    println("");
}

void test_range(void)
{
    print_range("range(15):", range(15));
    print_range("range(2, 6):", range(2, 6));
    print_range("range(2, 6, 3):", range(2, 6, 3));
    print_range("range(-2, -6, -3):", range(2, 6, 3));
    print_range("range(10.5, 15.5):", range(10.5, 15.5));
    print_range("range(35, 27, -1):", range(35, 27, -1));
    print_range("range(2, 8, 0.5):", range(2, 8, 0.5));
    print_range("range(8, 7, -0.1):", range(8, 7, -0.1));
    print_range("range('a', 'z'):", range('a', 'z'));
    print_range("range(1, 3.0):", range(1, 3.0));
}

int main(int argc, char **argv)
{
    test_range();
    return 0;
}
