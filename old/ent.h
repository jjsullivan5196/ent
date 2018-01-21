#ifndef __ENT
#define __ENT

#include <map>
#include <vector>
#include <string>
#include <memory>
#include <typeinfo>
#include <typeindex>
#include <boost/any.hpp>
#include "util.h"

namespace ent
{
	using comp_handle = std::shared_ptr<boost::any>;

	class entity final
	{
		public:
		template<class T> T* add();
		template<class T> T* get();
		template<class T> bool remove();
		template<class... Types> bool check();

		bool enabled() const { return enable; }
		bool enabled(bool toggle) { return enable = toggle; }
		std::string tag() const { return tagname; }
		std::string tag(std::string t) { return tagname = t; }

		private:
		std::map<std::type_index, comp_handle> components;
		std::string tagname = "";
		bool enable = true;
	};

	template<class T> T* entity::add()
	{
		const auto key = std::indexof_type<T>;
		if(!components.count(key))
		{
			auto& comp = components[key];
			comp = comp_handle(new boost::any(T())); 
			return boost::any_cast<T>(comp.get());
		}
		return nullptr;
	}
	
	template<class T> T* entity::get()
	{
		const auto key = std::indexof_type<T>;
		auto it = components.find(key);
		if(it != components.end())
		{
			return boost::any_cast<T>(it->second.get());
		}
		return nullptr;
	}

	template<class T> bool entity::remove()
	{
		const auto key = std::indexof_type<T>;
		auto it = components.find(key);
		if(it != components.end())
		{
			components.erase(key);
			return true;
		}
		return false;
	}

	template<class... Types> bool entity::check()
	{
		for(auto& typeidx : std::type_vector<Types...>)
		{
			if(!components.count(typeidx)) return false;
		}
		return true;
	}

	template<class... Types, class Func> 
	void apply_ents(std::vector<entity>& ents, const Func& f)
	{
		for(entity& e : ents)
		{
			if(e.check<Types...>()) f(e, *e.get<Types>()...);
		}
	}
}

#endif /* __ENT */
