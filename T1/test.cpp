#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <vector>
using namespace std;

int main(int argc, char const *argv[]) {
	string joe = "joe";
	string haine = "carol";
	string bacon = "bacon";
	map<string, int> age;
	stringstream ss;
	int i;

	age[joe] = 21;
	age[haine] = 19;

	cout << "comparing" << endl;
	cout << joe.compare(haine) << endl;
	cout << haine.compare(bacon) << endl;
	cout << bacon.compare(haine) << endl;
	cout << joe.compare(joe) << endl;

	if (age.count(joe))
		cout << age[joe] << endl;
	if (age.count(bacon))
		cout << age[bacon] << endl;

	vector<int> num;

	for (i = 0; i < 10; ++i)
		num.push_back(i);

	vector<int>::iterator it;
	cout << "writing stuff" << endl;
	for (it = num.begin(); it != num.end(); ++it)
	{
		cout << "  " <<  *it << endl;
	}

	i = 2;
	cout << joe.at(i--) << endl;

	return 0;
}
