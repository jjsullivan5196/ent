#ifndef __ENT
#define __ENT

#include <vector>
#include <string>
#include <typeinfo>
#include <typeindex>
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
		
		template<class T> T* addComponent();
		template<class T> T* getComponent();
		template<class T> bool removeComponent();

		template<class T> bool checkComponents();
		template<class T, class... Args> bool checkComponents();

		bool Enabled() const;
		bool Enabled(bool toggle);
		std::string Tag() const;
		std::string Tag(std::string t);

		private:
		std::map<std::type_index, Component*> components;
		std::string tag;
		bool enabled;
	};

	template<class T> T* Entity::addComponent()
	{
		std::assert_base<Component, T>();
		const std::type_index key(typeid(T));
		if(!components.count(key))
		{
			T* ncomponent = new T();
			components[key] = (Component*)ncomponent;
			return ncomponent;
		}
		return nullptr;
	}
	
	template<class T> T* Entity::getComponent()
	{
		std::assert_base<Component, T>();
		const std::type_index key(typeid(T));
		auto it = components.find(key);
		if(it != components.end())
		{
			return (T*)it->second;
		}
		return nullptr;
	}

	template<class T> bool Entity::removeComponent()
	{
		std::assert_base<Component, T>();
		const std::type_index key(typeid(T));
		auto it = components.find(key);
		if(it != components.end())
		{
			delete (T*)it->second;
			components.erase(key);
			return true;
		}
		return false;
	}

	template<class T> bool Entity::checkComponents()
	{
		std::assert_base<Component, T>();
		const std::type_index key(typeid(T));
		return (bool)components.count(key);
	}
	template<class T, class... Args> bool Entity::checkComponents()
	{
		return checkComponents<Args...>() && checkComponents<T>();
	}
}

#endif /* __ENT */
