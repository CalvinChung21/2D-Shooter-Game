#pragma once
#include "SDL.h"
#include "Scene.h"
#include "Entity.h"
#include "Components.h"

class CreateObjectsManager {
public:
	static CreateObjectsManager* GetInstance() { return (s_Instance == nullptr ? new CreateObjectsManager() : s_Instance); }
	void Init(Scene& scene);
	void create_player(Scene& scene,
		double init_pos_x, double init_pos_y,
		double init_vel_x, double init_vel_y,
		int width, int height, std::string name, int id,
		const char* imgIdel, const char* ImgLeft, const char* ImgRight);
	void create_bullet(Scene& scene,
		double init_pos_x, double init_pos_y,
		double init_vel_x, double init_vel_y,
		int width, int height, std::string name, int id, const char* imgName);
	void create_stdEnemy(Scene& scene,
		double init_pos_x, double init_pos_y,
		double init_vel_x, double init_vel_y,
		int width, int height, std::string name, int id);
	void create_lightEnemy(Scene& scene,
		double init_pos_x, double init_pos_y,
		double init_vel_x, double init_vel_y,
		int width, int height, std::string name, int id);
	void create_laserEnemy(Scene& scene,
		double init_pos_x, double init_pos_y,
		double init_vel_x, double init_vel_y,
		int width, int height, std::string name, int id);
	void create_laser(Scene& scene,
		double init_pos_x, double init_pos_y,
		double init_vel_x, double init_vel_y,
		int width, int height, std::string name, int id);
	void create_bomber(Scene& scene,
		double init_pos_x, double init_pos_y,
		double init_vel_x, double init_vel_y,
		int width, int height, std::string name, int id);
	void create_AdvEnemy(Scene& scene,
		double init_pos_x, double init_pos_y,
		double init_vel_x, double init_vel_y,
		int width, int height, std::string name, int id);
	void create_pickUp(Scene& scene,
		double init_pos_x, double init_pos_y,
		double init_vel_x, double init_vel_y,
		int width, int height, std::string name, const char* imgPath);
	void create_obstacles(Scene& scene,
		double init_pos_x, double init_pos_y,
		double init_vel_x, double init_vel_y,
		int width, int height, std::string name);
private:
	static CreateObjectsManager* s_Instance;
};