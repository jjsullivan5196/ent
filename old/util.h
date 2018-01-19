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

	template <class Type, class Iter, class Predicate>
	struct filter_iterator final
	{
		filter_iterator(const Iter& begin, const Iter& end, const Predicate& filter) 
			: pos(begin), end(end), filter(filter) {}

		bool operator!=(const Iter& other) const { return pos != other; }
		Type operator*() const { return *pos; }

		const filter_iterator<Type, Iter, Predicate>& operator++()
		{
			
		}
		private:
		Iter pos;
		Iter end;
		Predicate filter;
	}
}

#endif /* __UTIL */
