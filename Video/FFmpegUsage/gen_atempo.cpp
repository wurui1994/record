#include <cmath>
#include <iostream>
#include <vector>

std::vector<float> genSeq(float number)
{
	std::vector<float> result;
	float base = std::log2(number);
	float t = std::trunc(base);
	float res = std::pow(2,base - t);
	int n = std::fabs(t);
	//
	float sign = 0;
	if(base > 0.0)
	{
		sign = 1.0;
	}
	else if(base < 0.0)
	{
		sign = -1.0;
	}
	//
	float cell = std::pow(2.0,sign);
	//
	float factor = std::pow(2,res);
	for(int i = 0; i < n; ++i)
	{
		result.push_back(cell);
	}
	result.push_back(res);
	//
	return result;
}

int main()
{
	float s;
	//
	s = 1.0;
	for(auto const& ele:genSeq(100.0))
	{
		s*=ele;
		std::cout << ele << std::endl;
	}
	std::cout << s << std::endl;

	s = 1.0;
	for(auto const& ele:genSeq(0.01))
	{
		s*=ele;
		std::cout << ele << std::endl;
	}
	std::cout << s << std::endl;
}