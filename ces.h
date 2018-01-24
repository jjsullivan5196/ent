#pragma once
#include "mpl.h"
#include <array>
#include <chrono>
#include <functional>
#include <tuple>

namespace ces {
	using hrclock = std::chrono::high_resolution_clock;
	using hrpoint = hrclock::time_point;

	template <std::size_t NEntities, class... Components>
	struct world {
		static_assert(sizeof...(Components) > 0, "You need at least one component");

		// Useful declarations
		using pack_t = std::tuple<Components*...>;
		using mask_t = std::bitset<sizeof...(Components) + 1>;
		using store_t = std::tuple<std::array<Components, NEntities>...>;
		using mask_vec_t = std::array<mask_t, NEntities>;

		template <class... Mask>
		static mask_t create_mask(bool alive) {
			mask_t mask(alive ? 1 << 0 : 0);
			((mask.set(mpl::index_of_v<Mask, Components...> + 1)), ...);
			return mask;
		}

		template <class... Mask>
		struct system {
			using world_t = world<NEntities, Components...>;
			std::function<bool(float, Mask&...)> func;
			mask_t use_mask = world_t::create_mask<Mask...>(true);

			bool run(float dt, pack_t components) {
				return func(dt, *std::get<mpl::index_of_v<Mask, Components...>>(components)...);
			}
		};

		template <class Init, class... System>
		void run(Init&& init, System&... sys) {
			static_assert(sizeof...(System) > 0, "You need at least one system");
			init(entities, components);

			float deltaTime = 0.0;
			bool result = true;
			std::size_t i;

			while (result) {
				for (i = 0; i < NEntities; i++) {
					mask_t& mask = entities[i];
					if (!mask[0])
						continue;

					((result &= ((sys.use_mask & mask) == sys.use_mask ? sys.run(deltaTime, pack_t(&std::get<mpl::index_of_v<Components, Components...>>(components)[i]...)) : true)), ...);
				}
			}
		}

	  private:
		store_t components;
		mask_vec_t entities;
	};
}	// namespace ces
