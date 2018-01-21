#pragma once
#include <array>
#include <tuple>
#include <type_traits>

namespace mpl
{
	// Thanks to Barry at stackoverflow
	// https://stackoverflow.com/a/30736376
	template <class... R>
	struct index_of_t
	{
		static_assert(sizeof...(R) > 1, "Type is not in the argument list"); 
	};

	template <class T, class... R>
	struct index_of_t<T, T, R...>
	: std::integral_constant<size_t, 0> {};

	template <class T, class F, class... R>
	struct index_of_t<T, F, R...>
	: std::integral_constant<size_t, 1 + index_of_t<T, R...>::value> {};

	template<class T, class... Ts>
	constexpr size_t index_of_v = index_of_t<T, Ts...>::value;

	template <size_t N, class... Ts>
	using component_store = std::tuple<std::array<Ts, N>...>;
}
