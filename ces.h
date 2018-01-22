#pragma once
#include <array>
#include <tuple>
#include <functional>
#include <chrono>
#include "mpl.h"

namespace ces
{
	using hrclock = std::chrono::high_resolution_clock;
	using hrpoint = hrclock::time_point;

	template<std::size_t N, class MaskType = std::size_t>
	struct settings
	{
		using mask_t = MaskType;
		constexpr static size_t NEntities = N;
	};

	template<class Settings, class... Components>
	struct world
	{
		static_assert(sizeof...(Components) > 0, "You need at least one component");
		static_assert(sizeof...(Components) <= sizeof(typename Settings::mask_t), "Too many component types to address");

		//Useful declarations
		using pack_t = std::tuple<Components*...>;
		using store_t = mpl::component_store<Settings::NEntities, Components...>;
		using mask_t = typename Settings::mask_t;
		using mask_vec_t = std::array<mask_t, Settings::NEntities>;

		template<class T>
		constexpr static mask_t index_offset = mpl::index_of_t<T, Components...>;

		template<class... Mask>
		constexpr static mask_t bitmask_f()
		{
			mask_t mask = 0 | 1 << 0;
			((mask |= (1 << (index_offset<Mask> + 1))), ...);
			return mask;
		}

		template<class... Mask>
		constexpr static mask_t create_mask = bitmask_f<Mask...>();

		//Delegate metafunction
		template<class... ComponentMask>
		struct delegate
		{
			using world_type = world<Settings, Components...>;
			constexpr static world_type::mask_t use_mask = world_type::create_mask<ComponentMask...>;
			std::function<bool(float, ComponentMask&...)> func;

			bool run(float& dt, world_type::pack_t& ctuple) 
			{
				return func(dt, *std::get<world_type::index_offset<ComponentMask>>(ctuple)...); 
			}
		};

		template<class Init, class... System>
		void run(Init&& init, System&... sys)
		{
			static_assert(sizeof...(System) > 0, "You need at least one system");
			init(entities, components);

			float deltaTime = 0.0;
			bool result = true;
			std::size_t i;
			pack_t ent;

			while(result)
			{
				for(i = 0; i < Settings::NEntities; i++)
				{
					mask_t& mask = entities[i];	
					if(!(mask & 1 << 0)) continue;

					ent = pack_t(&std::get<index_offset<Components>>(components)[i]...);
					((result &= ((System::use_mask & mask) == System::use_mask ? sys.run(deltaTime, ent) : true)), ...);
				}
			}
		}

		private:
		store_t components;
		mask_vec_t entities;
	};
}
