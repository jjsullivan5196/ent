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

namespace ent
{
	using system = std::function<int(const float, std::vector<entity>&)>;

	int do_nothing(const float dt, std::vector<entity>& ents)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		return 0;
	}
	
	using hrclock = std::chrono::high_resolution_clock;
	using hrpoint = hrclock::time_point;
	
	int runGame(std::vector<system> systems = {&do_nothing}, std::vector<entity> entities = {}, const uint ticks = 40)
	{
		hrpoint lasttick = hrclock::now();

		for(uint currentTick = 0; currentTick < ticks; currentTick++)
		{
			//Convert microseconds back to seconds for high resolution because fuck you that's why
			double deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(hrclock::now() - lasttick).count() * std::pow(10.0, -6);
			lasttick = hrclock::now();

			for(system& sys: systems)
			{
				int r = sys(deltaTime, entities);
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
