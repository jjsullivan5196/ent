#pragma once
#include <array>
#include <tuple>
#include <type_traits>
#include <utility>

namespace mpl {
	namespace impl { // Error classes
		template <class... R>
		struct not_in_pack {
			static_assert(sizeof...(R) > 0, "Type T not in parameter pack");
		};
	} // namespace impl

	namespace impl {
		template <class... R>
		struct is_same_any : std::false_type {};

		template <class T, class... R>
		struct is_same_any<T, T, R...> : std::true_type {};

		template <class T, class F, class... R>
		struct is_same_any<T, F, R...> : is_same_any<T, R...> {};
	} // namespace impl

	template <class T, class... R>
	constexpr bool is_same_any_v = impl::is_same_any<T, R...>::value;

	namespace impl { // Index in template parameter pack
		// Generic Pack Version
		// Thanks to Barry
		// https://stackoverflow.com/a/30736376
		template <class... R>
		struct index_of : not_in_pack<R...> {};

		template <class T, class... R>
		struct index_of<T, T, R...>
			: std::integral_constant<std::size_t, 0> {};

		template <class T, class F, class... R>
		struct index_of<T, F, R...>
			: std::integral_constant<std::size_t, 1 + index_of<T, R...>::value> {};

		// Generic Aggregate specialization (Holy shit this actually works)
		// Based on tuple solution by Casey
		// https://stackoverflow.com/a/18063608
		template <class T, class... R, template <class... Args> class Aggregate>
		struct index_of<T, Aggregate<R...>> : index_of<T, R...> {};
	} // namespace impl

	template <class T, class... R>
	constexpr std::size_t index_of_v = impl::index_of<T, R...>::value;

	template <size_t N, class... Ts>
	using component_store = std::tuple<std::array<Ts, N>...>;
} // namespace mpl
