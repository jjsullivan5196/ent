#include "ces.h"
#include "mpl.h"
#include <cstdio>

using namespace std;
using namespace ces;

struct comp1 {};
struct comp2 {};
struct comp3 {};

using world_t = world<10, comp1, comp2, comp3>;

struct sysone : world_t::system<sysone, comp1> {
	void init(world_t::mask_vec_t& ents, world_t::store_t&) override {
		printf("Initializing...\n");
		ents.fill(world_t::create_mask<comp1, comp3>(true));
	}

	bool update(float dt, comp1&) {
		static uint32_t ticks = 0;
		printf("I take a comp1! Ticks: %d\n", ticks);
		ticks++;

		return ticks < 2;
	}
};

struct systwo : world_t::system<systwo, comp1, comp3> {
	bool update(float dt, comp1&, comp3&) {
		printf("I take a comp3 and comp1!\n");
		return true;
	}
};

struct systhree : world_t::system<systhree, comp3> {
	bool update(float dt, comp3&) {
		printf("I take a comp3!\n");
		return true;
	}

	void finalize(world_t::mask_vec_t&, world_t::store_t&) override {
		printf("Exiting...\n");
	}
};

int main() {
	world_t test;
	test.run(sysone(), systwo(), systhree());
}
