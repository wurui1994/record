#include <iostream>
#include <iterator>
#include <list>

int main()
{
	std::list<int> v{ 3, 1, 4 ,5 ,6 };

	auto it = v.begin();

	auto nx = std::next(it, 2);

	std::cout << *it << ' ' << *nx << '\n';

	*std::next(begin(v), 3) = 120;

	for (auto i = 0; i < v.size(); ++i)
	{
		std::cout << *std::next(begin(v), i) << " ";
	}
	std::cout << std::endl;
}
