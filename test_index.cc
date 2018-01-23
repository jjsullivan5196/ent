#include "mpl.h"
#include <iostream>
#include <tuple>

using namespace std;
using namespace mpl;

using pack = tuple<int, bool, float, double, char>;

template <class T>
constexpr std::size_t pack_index = index_of_t<T, pack>;

int main() {
	cout << pack_index<int> << ' ' << pack_index<float> << ' '
		 << pack_index<bool> << endl;
}
