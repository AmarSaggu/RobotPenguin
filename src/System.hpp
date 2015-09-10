#pragma once

#include <list>

template <typename T>
class System {
	std::list<T> components;

public:
	void Update();

	template <typename... Args>
	T *AddComponent(Args &&...args);
};

template <typename T>
void System<T>::Update()
{
	for (T &c : components) {
		c.Update();
	}
}

template <typename T>
template <typename... Args>
T *System<T>::AddComponent(Args &&...args)
{
	components.emplace_back(std::forward<Args>(args)...);
	return &components.back();
}
