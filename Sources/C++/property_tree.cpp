#include <iostream> 
#include <string> 
#include <iterator> 
#include <iomanip>

#include <boost/property_tree/json_parser.hpp>  

using namespace std;
using namespace boost::property_tree;
using namespace boost::property_tree::json_parser;

auto nth_name = [](auto tree, auto index) {auto bounds = tree.equal_range(""); advance(bounds.first, index); return bounds.first->first.data(); };

auto nth_value = [](auto tree, auto index) {auto bounds = tree.equal_range(""); advance(bounds.first, index); return bounds.first->second.data(); };

auto object_to_string = [](auto tree, auto format) {stringstream ss; write_json(ss, tree, format); return ss.str(); };

#if 0
int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		cout << "usage: " << argv[0] << " file.json" << endl;
		return -1;
	}
	//
	ptree tree;
	try {
		read_json(argv[1], tree);
	}
	catch (ptree_error & e) {
		cout << "read error" << endl;
		return -1;
	}

	cout << nth_name(tree, 0) << " " << nth_value(tree, 0) << endl;
	return 0;
}
#else 
//cling -Dmain=property_tree property_tree.cpp  -std=c++14
int main() 
{

	string str_json = "{\"array\":[1,2,3],\"boolean\":true,\"null\":null,\"number\":123,\"object\":{\"a\":\"b\",\"c\":\"d\",\"e\":\"f\"},\"string\":\"Hello World\"}";

	ptree tree;            
	stringstream ss(str_json);
	try {
		read_json(ss, tree);
	}
	catch (ptree_error & e) {
		return 1;
	}

	ptree arraypt = tree.get_child("array");
	for (auto it : arraypt) 
	{
		cout << it.second.data() << " ";
	}
	cout << boolalpha << endl;

	cout << tree.get<bool>("boolean") << endl;
	cout << tree.get<string>("null") << endl;
	cout << tree.get<int>("number") << endl;
	cout << tree.get<string>("string") << endl;
	cout << object_to_string(tree.get_child("object"), true) << endl;

	return 0;
}
#endif	