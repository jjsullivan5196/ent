#ifndef __ENT
#define __ENT

#include <vector>
#include <string>
#include <typeinfo>
#include <typeindex>
#include <memory>
#include <map>
#include "util.h"

namespace ent
{
	class Component
	{
		public:
		const std::string name;
		virtual ~Component() {}
	};

	class Entity final
	{
		public:
		Entity();
		~Entity();
		
		template<class T> T* addComponent();
		template<class T> T* getComponent();
		template<class T> bool removeComponent();

		template<class... Types> bool checkComponents();

		bool Enabled() const;
		bool Enabled(bool toggle);
		std::string Tag() const;
		std::string Tag(std::string t);

		private:
		std::map<std::type_index, std::shared_ptr<Component>> components;
		std::string tag;
		bool enabled;
	};

	template<class T> T* Entity::addComponent()
	{
		std::assert_base<Component, T>();
		const auto key = std::indexof_type<T>;
		if(!components.count(key))
		{
			T* ncomponent = new T();
			components[key] = std::shared_ptr<Component>((Component*)ncomponent);
			return ncomponent;
		}
		return nullptr;
	}
	
	template<class T> T* Entity::getComponent()
	{
		const auto key = std::indexof_type<T>;
		auto it = components.find(key);
		if(it != components.end())
		{
			return (T*)it->second.get();
		}
		return nullptr;
	}

	template<class T> bool Entity::removeComponent()
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

	template<class... Types> bool Entity::checkComponents()
	{
		for(auto& typeidx : std::type_vector<Types...>)
		{
			if(!components.count(typeidx)) return false;
		}
		return true;
	}
}

#endif /* __ENT */
