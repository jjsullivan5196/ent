#ifndef __UTIL
#define __UTIL

#include <typeinfo>
#include <typeindex>
#include <type_traits>
#include <vector>

namespace std
{
	template <class T>
	constexpr type_index indexof_type(typeid(T));

	template <class... Types> 
	constexpr vector<type_index> type_vector({indexof_type<Types>...});

	template <class Base, class Derived> 
	constexpr void assert_base() 
	{ 
		static_assert(is_base_of<Base, Derived>::value, "Derived does not implement Base");
	}

	template <class Iter, class Predicate, class Func>
	void apply_if(Iter begin, Iter end, Predicate filter, Func f)
	{
		for(Iter pos = begin; pos != end; pos++)
		{
			if(filter(*pos)) f(*pos);
		}
	}
	
	template <class Iterable, class Predicate, class Func>
	void apply_if(Iterable collection, Predicate filter, Func f)
	{
		apply_if(collection.begin(), collection.end(), filter, f);
	}

	struct generic_ptr
	{
		virtual void* get() { return nullptr; }
		virtual ~generic_ptr() {}
		template <class T> generic_ptr(T* ptr);
		template <class T> operator T*() { return (T*)get(); }
	};

	template <class T>
	generic_ptr::generic_ptr(T* ptr)
	{
		struct container : generic_ptr
		{
			T* ptr;
			void* get() override { return (void*)ptr; }
			~container() override { delete ptr; }
		} ptr_container{ptr};

		*this = (generic_ptr*)ptr_container;
	}	
}

#endif /* __UTIL */
