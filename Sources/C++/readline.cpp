#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main()
{
	ifstream ifs("test.txt");
	string temp;
	vector<string> vec;
	int tempr, tempt;
	while (!ifs.eof())
	{
		getline(ifs, temp);
		vec.push_back(temp);
		//cout<<temp<<endl;
	}
	cout << vec.size() << endl;
	for (int i = 0; i < vec.size(); i++)
		cout << vec[i] << i << endl;
	// cin.get();
	return 0;
}