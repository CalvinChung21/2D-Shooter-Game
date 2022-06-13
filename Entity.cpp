#include "Entity.h"
// code reference from https://www.youtube.com/watch?v=8LbVpkEqKuY
Entity::Entity()
{}

Entity::Entity(entt::entity s_entity_handle, Scene* s_scene)
	: entity_handle(s_entity_handle), scene(s_scene)
{}