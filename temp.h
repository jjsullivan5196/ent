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
