#include <iostream>
using namespace std;

string test()
{
	return string("say hi");
}

int main(int argc, char const *argv[]) {
	string line;

	cout << test() << endl;
	getline(cin, line);
	if (line.length() > 0)
		cout << "there is something here" << endl;
	else
		cout << "there is nothing here" << endl;

	return 0;
}
