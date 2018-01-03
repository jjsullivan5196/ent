#ifndef __SYS
#define __SYS

#include <vector>
#include <functional>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <thread>
#include "ent.h"
#include "util.h"

namespace ent
{
	typedef std::function<int(const float, std::vector<Entity>&)> System;

	int do_nothing(const float dt, std::vector<Entity>& ents)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		return 0;
	}
	
	using hrclock = std::chrono::high_resolution_clock;
	using hrpoint = hrclock::time_point;
	
	int runGame(std::vector<System> Systems = {&do_nothing}, std::vector<Entity> Entities = {}, const uint ticks = 40)
	{
		hrpoint lasttick = hrclock::now();

		for(uint currentTick = 0; currentTick < ticks; currentTick++)
		{
			//Convert microseconds back to seconds for high resolution because fuck you that's why
			double deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(hrclock::now() - lasttick).count() * std::pow(10.0, -6);
			lasttick = hrclock::now();

			for(System& sys: Systems)
			{
				int r = sys(deltaTime, Entities);
				if(r == -1)
				{
					std::printf("Exiting...\n");
					std::exit(0);
				}
			}
		}

		return 0;
	}
}

#endif /* __SYS */
