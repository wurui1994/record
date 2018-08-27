
#include <tuple>
#include <string>
#include <iostream>

using namespace std;

template<typename Tuple, size_t N>
struct tuple_print
{
	static void print(const Tuple& t, ostream& os)
	{
		tuple_print<Tuple, N - 1>::print(t, os);
		os << ", " << get<N - 1>(t);
	}
};
// 类模板的特化版本
template<typename Tuple>
struct tuple_print<Tuple, 1>
{
	static void print(const Tuple& t, ostream& os)
	{
		os << "(" << get<0>(t);
	}
};

// operator<<
template<typename... Args>
ostream& operator << (ostream& os, const tuple<Args...>& t)
{
	tuple_print<decltype(t), sizeof...(Args)>::print(t, os);
	return os << ")";
}

template<typename... Args1, typename... Args2>
auto operator +(const tuple<Args1...>& T1, const tuple<Args2...>&T2)
{
	return tuple_cat(T1, T2);
}

auto func()
{
	return make_tuple("hello", "world");
}

int main()
{
	auto t1 = func();
	tuple_element<0, decltype(t1)>::type word = get<0>(t1);
	cout << word << endl;
	cout << t1 << endl;

	auto t2 = make_tuple("c", "c++", "python");
	cout << t2 << endl;

	auto t3 = t1 + t2 + t1;

	cout << t3 << endl;
}