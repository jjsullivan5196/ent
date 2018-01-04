#include <boost/any.hpp>
#include <cstdio>

using namespace std;

struct test {};

int main()
{
	test t;
	boost::any t_any = t;
	return 0;
}
