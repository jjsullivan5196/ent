#pragma once
#include <array>
#include <tuple>
#include <functional>
#include <typeinfo>
#include <cstdio>
#include "mpl.h"

namespace ces
{
	template<std::size_t NEntities, template <class... Components> class >
	struct world
	{
		//Useful declarations
		template<class T>
		constexpr static size_t index_offset = mpl::index_of_v<T, Components...>;
		using store = mpl::component_store<NEntities, Components...>;
		using mask_vec = std::array<uint32_t, NEntities>;

		void run()
		{
			for(std::size_t i = 0; i < NEntities; i++)
			{
				auto& mask = entities[i];
				auto ent = std::tuple(&std::get<index_offset<Components>>(components)[i]...);

				std::printf("%s\n", typeid(std::get<0>(ent)).name());
			}
		}

		private:
		store components;
		mask_vec entities;
	};
}
