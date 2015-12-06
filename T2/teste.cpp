#include <iostream>
#include <string>
#include "src/toolbox.hpp"
using namespace std;

int main(int argc, char const *argv[]) {
    string joe = "joe";
    string frank = "frank";
    string joe_frank = "joe frank";
    string tio_frank = "tio frank";

    cout << joe_frank.compare(joe) << endl;
    cout << tio_frank.compare(joe) << endl;
    cout << toolbox::match(joe.c_str(), joe_frank.c_str()) << endl;

    return 0;
}
