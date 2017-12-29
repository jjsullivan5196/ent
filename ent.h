#ifndef __ENT
#define __ENT

#include <vector>
#include <string>
#include <typeinfo>
#include <typeindex>
#include <utility>
#include <map>

namespace ent
{
	class Component
	{
		public:
		const std::string name;
		virtual ~Component() {}
	}

	class Entity
	{
		public:
		Entity();
		
		template<class T> T* addComponent();
		template<class T> T* getComponent();
		template<class T> bool removeComponent();

		bool Enabled();
		bool Enabled(bool toggle);
		std::string Tag();
		std::string Tag(std::string t);

		private:
		std::map<std::type_index, Component*> components;
		std::string tag;
		bool enabled;
	}

	template<class T> T* Entity::addComponent()
	{
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
		const std::type_index key(typeid(T));
		auto it = components.find(key)
		if(it != components.end())
		{
			return (T*)it->second;
		}
		return nullptr;
	}

	template<class T> bool Entity::removeComponent()
	{
		const std::type_index key(typeid(T));
		auto it = components.find(key)
		if(it != components.end())
		{
			delete (T*)it->second;
			components.erase(key);
			return true;
		}
		return false;
	}

}

#endif /* __ENT */
