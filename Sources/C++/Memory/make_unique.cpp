#include <iostream>
#include <memory> 
#include <string>
#include <iomanip>

int main(void)
{
	//auto s = std::unique_ptr<std::string> (new std::string("world"));
	auto s = std::make_unique<std::string>("hello");
	std::cout << std::boolalpha;
	std::cout << *s << std::endl;
	auto ss = std::move(s); // now ths s pointer to NULL
	std::cout << *ss << std::endl;
	std::cout << (s.get() == nullptr) << std::endl; 
	//std::cout << *s << std::endl; //UB
	return 0;
}