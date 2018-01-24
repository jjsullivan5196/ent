#include "mpl.h"
#include <bitset>
#include <iostream>

using namespace std;

int main() {
	cout << bitset<64>(mpl::bitmask_v<4, 20, 3, 7>) << endl;
}
