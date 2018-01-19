#include <cstdio>
#include <string>
#include <vector>
#include "sys.h"

using namespace std;
using namespace ent;

struct testcomponent
{
	std::string name;
};

int countTicks(const float dt, vector<entity>& ents)
{
	static int count = 0;

	apply_ents<testcomponent>(ents,
	[](entity& e, testcomponent& t) {
		t.name = "Orange";
	});

	count++;
	printf(
		"Tick %d, deltaTime: %f, name: %s\n",
		count, dt, ents[0].get<testcomponent>()->name.c_str()
	);
	return 0;
}

int main()
{
	vector<entity> ents;
	ents.emplace_back();
	entity& ent = ents[0];

	testcomponent& t = *ent.add<testcomponent>();
	t.name = "Apple";

	return runGame({&countTicks}, ents);
}
