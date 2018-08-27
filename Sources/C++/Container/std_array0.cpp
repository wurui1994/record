

#include <iostream>  
#include <array>  

int main(void) 
{

	std::array<int, 5> ia = {  1, 2, 3, 4, 5  };
	for (const auto i : ia)
		std::cout << i << " ";
	std::cout << std::endl;

	std::array<int, 5> ia2; // 空数组  
							//ia2 = {1, 2, 3, 4, 5}; //错误  
	ia2 = ia;
	for (const auto i : ia2)
		std::cout << i << " ";
	std::cout << std::endl;

	return 0;
}