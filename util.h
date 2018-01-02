#ifndef __UTIL
#define __UTIL

#include <type_traits>

namespace std
{
	template <class Base, class Derived> 
	constexpr void assert_base() 
	{ 
		static_assert(std::is_base_of<Base, Derived>::value, "Derived does not implement Base");
	}

	template <class Iter, class Predicate, class Func>
	void apply_if(Iter begin, Iter end, Predicate filter, Func f)
	{
		for(Iter pos = begin; pos != end; pos++)
		{
			if(filter(*pos)) f(*pos);
		}
	}
}

#endif /* __UTIL */
