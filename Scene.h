#pragma once
// code reference from https://www.youtube.com/watch?v=8LbVpkEqKuY
#include "entt.hpp"

class Entity;

class Scene
{
private:
	entt::registry registry;

public:
	Entity create_entity(std::string tag);
	Scene() {};
	~Scene() {};
	inline static bool pause = false;
	void update(int screen_width, int screen_height);
	void endGame();
	void move_system(int screen_width, int screen_height);
	friend class Entity;
};