#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

vector<string> split(string const& s, char delim=' ')
{
	vector<string> elems;
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

//Here's another solution. It's compact and reasonably efficient :
std::vector<std::string> split2(const std::string &text, char sep) {
	std::vector<std::string> tokens;
	std::size_t start = 0, end = 0;
	while ((end = text.find(sep, start)) != std::string::npos) {
		tokens.push_back(text.substr(start, end - start));
		start = end + 1;
	}
	tokens.push_back(text.substr(start));
	return tokens;
}

//It can easily be templatised to handle string separators, wide strings, etc.
//
//Note that splitting "" results in a single empty string and splitting "," (ie.sep) results in two empty strings.
//
//It can also be easily expanded to skip empty tokens :
std::vector<std::string> split3(const std::string &text, char sep) {
	std::vector<std::string> tokens;
	std::size_t start = 0, end = 0;
	while ((end = text.find(sep, start)) != std::string::npos) {
		if (end != start) {
			tokens.push_back(text.substr(start, end - start));
		}
		start = end + 1;
	}
	if (end != start) {
		tokens.push_back(text.substr(start));
	}
	return tokens;
}
//If splitting a string at multiple delimiters while skipping empty tokens is desired, this version may be used :
std::vector<std::string> split4(const std::string& text, const std::string& delims)
{
	std::vector<std::string> tokens;
	std::size_t start = text.find_first_not_of(delims), end = 0;

	while ((end = text.find_first_of(delims, start)) != std::string::npos)
	{
		tokens.push_back(text.substr(start, end - start));
		start = text.find_first_not_of(delims, end);
	}
	if (start != std::string::npos)
		tokens.push_back(text.substr(start));

	return tokens;
}
int main() 
{
	string s = "It's a test, \nhow are\t you--I'm fine.";
	for (auto ele : split4(s," \t\n-,"))cout << ele << endl;
}