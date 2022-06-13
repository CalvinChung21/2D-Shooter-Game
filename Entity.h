#pragma once
// code reference from https://www.youtube.com/watch?v=8LbVpkEqKuY
#include "entt.hpp"

#include "Scene.h"

class Entity
{
private:
	entt::entity entity_handle = entt::entity(0);
	Scene* scene = NULL;

public:
	Entity();
	Entity(entt::entity s_entity_handle, Scene* s_scene);

	template<typename T, typename... Args>
	T& add_component(Args&&... args)
	{
		return scene->registry.emplace<T>(entity_handle, std::forward<Args>(args)...);
	}

	template<typename T>
	T& get_component()
	{
		return scene->registry.get<T>(entity_handle);
	}

	template<typename T>
	void remove_component()
	{
		return scene->registry.remove<T>(entity_handle);
	}

	template<typename T>
	bool has_component()
	{
		return scene->registry.all_of<T>(entity_handle);
	}
};