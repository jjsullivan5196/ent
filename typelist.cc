#include "util.h"
#include <cstdio>

using namespace std;

class typeone {};
class typetwo {};

int main()
{
	auto typelist = type_vector<typeone, typetwo>();

	for(auto& typeidx : typelist) 
	{
		printf("%s\n", typeidx.name());
	}
}
