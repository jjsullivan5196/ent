#ifndef __UTIL
#define __UTIL

#include <typeinfo>
#include <typeindex>
#include <vector>

namespace std
{
	template <class T>
	type_index indexof_type(typeid(T));

	template <class... Types> 
	vector<type_index> type_vector({indexof_type<Types>...});
}

#endif /* __UTIL */
