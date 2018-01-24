#include "ces.h"
#include <cstdio>

using namespace std;
using namespace ces;

struct comp1 {};
struct comp2 {};
struct comp3 {};

using world_t = world<10, comp1, comp2, comp3>;

bool sysone(float dt, comp1& component) {
	static uint32_t ticks = 0;

	printf("I take a comp1! Ticks: %d\n", ticks);
	ticks++;

	return ticks < 2;
}

bool systwo(float dt, comp1&, comp3& component) {
	printf("I take a comp3 and comp1!\n");
	return true;
}

world_t::system<comp1> sys1{sysone};
world_t::system<comp1, comp3> sys2{systwo};

void make_ents(world_t::mask_vec_t& entities, world_t::store_t& components) {
	printf("Initializing...\n");
	entities.fill(world_t::create_mask<comp1, comp3>(true));
	entities[4].set(1, 3);
	entities[6].set(0);
}

int main() {
	world_t test;
	test.run(make_ents, sys1, sys2);
}
