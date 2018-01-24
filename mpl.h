#pragma once
#include <array>
#include <bitset>
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

	namespace impl { // Index in template parameter pack
		// Generic Pack Version
		// Thanks to Barry
		// https://stackoverflow.com/a/30736376
		template <class... R>
		struct index_of : std::false_type {};

		template <class T, class... R>
		struct index_of<T, T, R...>
			: std::integral_constant<std::size_t, 0> {};

		template <class T, class F, class... R>
		struct index_of<T, F, R...>
			: std::integral_constant<std::size_t, 1 + index_of<T, R...>::value> {};

		// Generic Aggregate specialization (Holy shit this actually works)
		// Based on tuple solution by Casey
		// https://stackoverflow.com/a/18063608
		template <class T, template <class... Args> class Aggregate, class... R>
		struct index_of<T, Aggregate<R...>> : index_of<T, R...> {};

		template <class... R>
		struct index_of_slice : std::false_type {};

		template <
			template <class... Args> class Aggregate,
			template <class... Args> class Slice,
			class... TypeList, class... ArgTypes>
		struct index_of_slice<Aggregate<TypeList...>, Slice<ArgTypes...>>
			: std::index_sequence<index_of<ArgTypes, TypeList...>::value...> {};

	} // namespace impl

	template <class T, class... R>
	constexpr std::size_t index_of_v = impl::index_of<T, R...>::value;
} // namespace mpl
