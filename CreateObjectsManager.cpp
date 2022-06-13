#include "CreateObjectsManager.h"
#include <iostream>
using namespace std;
CreateObjectsManager* CreateObjectsManager::s_Instance = nullptr;

void CreateObjectsManager::Init(Scene& scene)
{
	create_player(scene, 540, 590, 0.0, 0.0, 50, 50, "player", 1, "images/player/blue_basic_pos1.png", "images/player/blue_basic_pos2.png", "images/player/blue_basic_pos3.png");
	create_bullet(scene, -100, -100, 0.0, 0.0, 5, 20, "player", 1, "images/player/bullet_std_wTrail.png");
}

void CreateObjectsManager::create_player(Scene& scene, double init_pos_x, double init_pos_y, double init_vel_x, double init_vel_y, int width, int height, std::string name, int id, const char* imgIdel, const char* ImgLeft, const char* ImgRight)
{
	SDL_Rect destRect;
	destRect.x = init_pos_x;
	destRect.y = init_pos_y;
	destRect.w = width;
	destRect.h = height;
	SDL_Rect uiRect;
	uiRect.x = init_pos_x;
	uiRect.y = init_pos_y + height;
	uiRect.w = width;
	uiRect.h = 8;

	Entity object_entity = scene.create_entity(name);
	object_entity.add_component<IDComponent>(id);
	object_entity.add_component<UiComponent>
		(IMG_LoadTexture(Game::GetInstance()->renderer, "images/player/outline_standard.png"), destRect);
	object_entity.add_component<ExplodeComponent>
		(0, IMG_LoadTexture(Game::GetInstance()->renderer, "images/player/vfx_explosion_v1.png"),
			IMG_LoadTexture(Game::GetInstance()->renderer, "images/player/vfx_explosion_v2.png"),
			nullptr, destRect);
	object_entity.add_component<PositionComponent>(init_pos_x, init_pos_y);
	object_entity.add_component<VelocityComponent>(init_vel_x, init_vel_y);
	object_entity.add_component<AccelerationComponent>(0.0, 0.0);
	object_entity.add_component<ControlComponent>();
	object_entity.add_component<SpriteComponent>
		(IMG_LoadTexture(Game::GetInstance()->renderer, imgIdel),
			IMG_LoadTexture(Game::GetInstance()->renderer, ImgLeft),
			IMG_LoadTexture(Game::GetInstance()->renderer, ImgRight), destRect);
	object_entity.add_component<HealthComponent>(100,
		IMG_LoadTexture(Game::GetInstance()->renderer, "images/player/ui_hpbar_v3_3-3.png"),
		IMG_LoadTexture(Game::GetInstance()->renderer, "images/player/ui_hpbar_v3_2-3.png"),
		IMG_LoadTexture(Game::GetInstance()->renderer, "images/player/ui_hpbar_v3_1-3.png"), uiRect);
}

void CreateObjectsManager::create_bullet(
	Scene& scene,
	double init_pos_x, double init_pos_y,
	double init_vel_x, double init_vel_y,
	int width, int height, std::string name, int id, const char* imgName
) {
	SDL_Rect destRect;
	destRect.x = init_pos_x;
	destRect.y = init_pos_y;
	destRect.w = width;
	destRect.h = height;
	Entity object_entity = scene.create_entity(name);
	object_entity.add_component<PositionComponent>(init_pos_x, init_pos_y);
	object_entity.add_component<VelocityComponent>(init_vel_x, init_vel_y);
	object_entity.add_component<AccelerationComponent>(0.0, 0.0);
	object_entity.add_component<SpriteComponent>(IMG_LoadTexture(Game::GetInstance()->renderer, imgName), nullptr, nullptr, destRect);
	object_entity.add_component<ExistComponent>(false);
	object_entity.add_component<IDComponent>(id);
}
//enemy
void CreateObjectsManager::create_stdEnemy(Scene& scene,
	double init_pos_x, double init_pos_y,
	double init_vel_x, double init_vel_y,
	int width, int height, std::string name, int id)
{
	SDL_Rect destRect;
	destRect.x = init_pos_x;
	destRect.y = init_pos_y;
	destRect.w = width;
	destRect.h = height;
	Entity object_entity = scene.create_entity(name);
	object_entity.add_component<PositionComponent>(init_pos_x, init_pos_y);
	object_entity.add_component<VelocityComponent>(init_vel_x, init_vel_y);
	object_entity.add_component<AccelerationComponent>(0.0, 0.0);
	object_entity.add_component<SpriteComponent>(IMG_LoadTexture(Game::GetInstance()->renderer, "images/enemy/red_basic_pos1.png"), nullptr, nullptr, destRect);
	object_entity.add_component<HealthComponent>(100);
	object_entity.add_component<IDComponent>(id);
	object_entity.add_component<ExplodeComponent>
		(0, IMG_LoadTexture(Game::GetInstance()->renderer, "images/player/vfx_explosion_v1.png"),
			IMG_LoadTexture(Game::GetInstance()->renderer, "images/player/vfx_explosion_v2.png"),
			IMG_LoadTexture(Game::GetInstance()->renderer, "images/enemy/medkit.png"), destRect);
}

void CreateObjectsManager::create_lightEnemy(Scene& scene,
	double init_pos_x, double init_pos_y,
	double init_vel_x, double init_vel_y,
	int width, int height, std::string name, int id)
{
	SDL_Rect destRect;
	destRect.x = init_pos_x;
	destRect.y = init_pos_y;
	destRect.w = width;
	destRect.h = height;
	Entity object_entity = scene.create_entity(name);
	object_entity.add_component<PositionComponent>(init_pos_x, init_pos_y);
	object_entity.add_component<VelocityComponent>(init_vel_x, init_vel_y);
	object_entity.add_component<AccelerationComponent>(0.0, 0.0);
	object_entity.add_component<SpriteComponent>(IMG_LoadTexture(Game::GetInstance()->renderer, "images/enemy/red_light_pos1.png"), nullptr, nullptr, destRect);
	object_entity.add_component<HealthComponent>(100);
	object_entity.add_component<IDComponent>(id);
	object_entity.add_component<ExplodeComponent>
		(0, IMG_LoadTexture(Game::GetInstance()->renderer, "images/player/vfx_explosion_v1.png"),
			IMG_LoadTexture(Game::GetInstance()->renderer, "images/player/vfx_explosion_v2.png"),
			IMG_LoadTexture(Game::GetInstance()->renderer, "images/enemy/medkit.png"), destRect);
}

void CreateObjectsManager::create_laserEnemy(Scene& scene,
	double init_pos_x, double init_pos_y,
	double init_vel_x, double init_vel_y,
	int width, int height, std::string name, int id
) {
	SDL_Rect destRect;
	destRect.x = init_pos_x;
	destRect.y = init_pos_y;
	destRect.w = width;
	destRect.h = height;
	Entity object_entity = scene.create_entity(name);
	object_entity.add_component<PositionComponent>(init_pos_x, init_pos_y);
	object_entity.add_component<VelocityComponent>(init_vel_x, init_vel_y);
	object_entity.add_component<HealthComponent>(100);
	object_entity.add_component<SpriteComponent>(IMG_LoadTexture(Game::GetInstance()->renderer, "images/enemy/red_laser_pos1.png"),
		IMG_LoadTexture(Game::GetInstance()->renderer, "images/enemy/red_laser_pos3.png"),
		IMG_LoadTexture(Game::GetInstance()->renderer, "images/enemy/red_laser_pos2.png"), destRect);
	object_entity.add_component<IDComponent>(id);
	object_entity.add_component<ExplodeComponent>
		(0, IMG_LoadTexture(Game::GetInstance()->renderer, "images/player/vfx_explosion_v1.png"),
			IMG_LoadTexture(Game::GetInstance()->renderer, "images/player/vfx_explosion_v2.png"),
			IMG_LoadTexture(Game::GetInstance()->renderer, "images/enemy/medkit.png"), destRect);
}

void CreateObjectsManager::create_laser(Scene& scene,
	double init_pos_x, double init_pos_y,
	double init_vel_x, double init_vel_y,
	int width, int height, std::string name, int id
)
{
	SDL_Rect destRect;
	destRect.x = init_pos_x;
	destRect.y = init_pos_y;
	destRect.w = width;
	destRect.h = height;
	Entity object_entity = scene.create_entity(name);
	object_entity.add_component<PositionComponent>(init_pos_x, init_pos_y);
	object_entity.add_component<VelocityComponent>(init_vel_x, init_vel_y);
	object_entity.add_component<SpriteComponent>(IMG_LoadTexture(Game::GetInstance()->renderer, "./images/enemy/bullet_laser_v3_longDemo.png"), nullptr, nullptr, destRect);
	object_entity.add_component<CounterComponent>(100);
	object_entity.add_component<ExistComponent>(false);
	object_entity.add_component<IDComponent>(id);
}

void CreateObjectsManager::create_bomber(Scene& scene,
	double init_pos_x, double init_pos_y,
	double init_vel_x, double init_vel_y,
	int width, int height, std::string name, int id
)
{
	SDL_Rect destRect;
	destRect.x = init_pos_x;
	destRect.y = init_pos_y;
	destRect.w = width;
	destRect.h = height;
	Entity object_entity = scene.create_entity(name);
	object_entity.add_component<PositionComponent>(init_pos_x, init_pos_y);
	object_entity.add_component<VelocityComponent>(init_vel_x, init_vel_y);
	object_entity.add_component<SpriteComponent>(IMG_LoadTexture(Game::GetInstance()->renderer, "images/enemy/red_bomber_pos1.png"), nullptr, nullptr, destRect);
	object_entity.add_component<HealthComponent>(100);
	object_entity.add_component<CounterComponent>(100);
	object_entity.add_component<IDComponent>(id);
	object_entity.add_component<ExplodeComponent>
		(0, IMG_LoadTexture(Game::GetInstance()->renderer, "images/player/vfx_explosion_v1.png"),
			IMG_LoadTexture(Game::GetInstance()->renderer, "images/player/vfx_explosion_v2.png"),
			IMG_LoadTexture(Game::GetInstance()->renderer, "images/enemy/medkit.png"), destRect);
}

void CreateObjectsManager::create_AdvEnemy(Scene& scene,
	double init_pos_x, double init_pos_y,
	double init_vel_x, double init_vel_y,
	int width, int height, std::string name, int id
)
{
	SDL_Rect destRect;
	destRect.x = init_pos_x;
	destRect.y = init_pos_y;
	destRect.w = width;
	destRect.h = height;
	Entity object_entity = scene.create_entity(name);
	object_entity.add_component<PositionComponent>(init_pos_x, init_pos_y);
	object_entity.add_component<VelocityComponent>(init_vel_x, init_vel_y);
	object_entity.add_component<SpriteComponent>(IMG_LoadTexture(Game::GetInstance()->renderer, "images/enemy/red_advance_pos1.png"), nullptr, nullptr, destRect);
	object_entity.add_component<HealthComponent>(100);
	object_entity.add_component<AngleComponet>(0.0);
	object_entity.add_component<IDComponent>(id);
	object_entity.add_component<ExplodeComponent>
		(0, IMG_LoadTexture(Game::GetInstance()->renderer, "images/player/vfx_explosion_v1.png"),
			IMG_LoadTexture(Game::GetInstance()->renderer, "images/player/vfx_explosion_v2.png"),
			IMG_LoadTexture(Game::GetInstance()->renderer, "images/enemy/medkit.png"), destRect);
}

void CreateObjectsManager::create_pickUp(Scene& scene,
	double init_pos_x, double init_pos_y,
	double init_vel_x, double init_vel_y,
	int width, int height, std::string name, const char* imgPath
) {
	SDL_Rect destRect;
	destRect.x = init_pos_x;
	destRect.y = init_pos_y;
	destRect.w = width;
	destRect.h = height;
	Entity object_entity = scene.create_entity(name);
	object_entity.add_component<PositionComponent>(init_pos_x, init_pos_y);
	object_entity.add_component<VelocityComponent>(init_vel_x, init_vel_y);
	object_entity.add_component<SpriteComponent>(IMG_LoadTexture(Game::GetInstance()->renderer, imgPath), nullptr, nullptr, destRect);
}

void CreateObjectsManager::create_obstacles(Scene& scene,
	double init_pos_x, double init_pos_y,
	double init_vel_x, double init_vel_y,
	int width, int height, std::string name
) {
	SDL_Rect destRect;
	destRect.x = init_pos_x;
	destRect.y = init_pos_y;
	destRect.w = width;
	destRect.h = height;
	Entity object_entity = scene.create_entity(name);
	object_entity.add_component<PositionComponent>(init_pos_x, init_pos_y);
	object_entity.add_component<VelocityComponent>(init_vel_x, init_vel_y);
	object_entity.add_component<AccelerationComponent>(0.0, 0.0);
	object_entity.add_component<SpriteComponent>(IMG_LoadTexture(Game::GetInstance()->renderer, "images/enemy/vfx_explosion_v1.png"), nullptr, nullptr, destRect);
	object_entity.add_component<HealthComponent>(100);
}