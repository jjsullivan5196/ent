#include "ces.h"
#include "mpl.h"

using namespace ces;
using namespace mpl;

struct comp1 {};
struct comp2 {};
struct comp3 {};

using test_world = world<10, type_list<comp1, comp2, comp3>>;

int main()
{
	test_world t;
	t.run();
}
