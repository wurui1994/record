#include <iostream>
#include <memory> 
#include <string>
#include <iomanip>

int main(void)
{
	//auto s = std::shared_ptr<std::string> (new std::string("world"));
	auto s = std::make_shared<std::string>("hello");
	std::cout << std::boolalpha;
	std::cout << s.unique() << " " << s.use_count() << std::endl;
	auto ss = s;
	std::cout << s.unique() << " " << s.use_count() << std::endl;
	ss.reset();
	std::cout << s.unique() << " " << s.use_count() << std::endl;
	return 0;
}