#include "RespawnObjectsManager.h"
#include "CreateObjectsManager.h"
#include <iostream>

RespawnObjectsManager* RespawnObjectsManager::s_Instance = nullptr;

RespawnObjectsManager::RespawnObjectsManager()
{
	// for respawning enemies
	timer1 = 0;
	timer2 = 0;
	timer3 = 0;
	pickUpType = 0;
	playerId = 1;
}

void RespawnObjectsManager::Update(Scene& scene)
{
	// spawn enemy when the score is less than 1200 and not pause and the game is started
	if ((Game::score < 1200) && (!Scene::pause) && (Game::isStart)) 
	{
		srand(time(NULL));
		// timer1 will be the fastest one to spawn things like standard enemy, light enemy and obstacles.
		timer1++;
		if (timer1 == 200) {
			switch (rand() % 3)
			{
			case 0:
				CreateObjectsManager::GetInstance()->create_stdEnemy(scene, rand() % 1031, -50, 0.0, 0.0, 50, 50, enemyNameList[0], ++enemyIdCount[0]);
				CreateObjectsManager::GetInstance()->create_bullet(scene, -100, -100, 0.0, 0.0, 5, 10, enemyNameList[0], enemyIdCount[0], "images/enemy/bullet_std_downward.png");
				break;
			case 1:
				CreateObjectsManager::GetInstance()->create_lightEnemy(scene, rand() % 1031, 640, 0.0, 0.0, 50, 50, enemyNameList[1], ++enemyIdCount[1]);
				CreateObjectsManager::GetInstance()->create_bullet(scene, -100, 650, 0.0, 0.0, 5, 10, enemyNameList[1], enemyIdCount[1], "images/enemy/bullet_std.png");
				break;
			case 2:
				CreateObjectsManager::GetInstance()->create_obstacles(scene, rand() % 1031, 0, 0.0, 2.0, 50, 50, "obstacle");
				break;
			default:
				break;
			}
			timer1 = 0;
		}
		// timer2 will be the medium speed to spawn advance enemy, bomber and random pick up for player
		timer2++;
		if (timer2 == 400) {
			switch (rand() % 3) {
			case 0:
				CreateObjectsManager::GetInstance()->create_AdvEnemy(scene, rand() % 1031, rand() % 640, 0, 0.0, 50, 50, enemyNameList[4], ++enemyIdCount[4]);
				CreateObjectsManager::GetInstance()->create_bullet(scene, -100, -100, 0.0, 0.0, 5, 20, enemyNameList[4], enemyIdCount[4], "images/enemy/bullet_missile.png");
				break;
			case 1:
				CreateObjectsManager::GetInstance()->create_bomber(scene, rand() % 1031, 0, 5, 0.0, 75, 50, enemyNameList[3], ++enemyIdCount[3]);
				CreateObjectsManager::GetInstance()->create_bullet(scene, -100, -100, 0.0, 0.0, 10, 20, enemyNameList[3], enemyIdCount[3], "images/enemy/bullet_clutser.png");
				break;
			case 2:
				pickUpType = rand() % 5;
				switch (pickUpType)
				{
				case 0: CreateObjectsManager::GetInstance()->create_pickUp(scene, rand() % 1031, 0, 0.0, 2.0, 50, 50, "basicPlayer", "images/player/blue_basic_pos1.png"); break;
				case 1: CreateObjectsManager::GetInstance()->create_pickUp(scene, rand() % 1031, 0, 0.0, 2.0, 36, 42, "lightPlayer", "images/player/blue_light_pos1.png"); break;
				case 2: CreateObjectsManager::GetInstance()->create_pickUp(scene, rand() % 1031, 0, 0.0, 2.0, 30, 50, "laserPlayer", "images/player/blue_laser_pos1.png"); break;
				case 3: CreateObjectsManager::GetInstance()->create_pickUp(scene, rand() % 1031, 0, 0.0, 2.0, 75, 50, "bomberPlayer", "images/player/blue_bomber_pos1.png"); break;
				case 4: CreateObjectsManager::GetInstance()->create_pickUp(scene, rand() % 1031, 0, 0.0, 2.0, 50, 50, "advancePlayer", "images/player/blue_advance_pos1.png"); break;
				default:
					break;
				}
				break;
			default:
				break;
			}
			timer2 = 0;
		}
		// timer3 will be the slowest one to spawn laser enemy
		timer3++;
		if (timer3 == 600) {
			CreateObjectsManager::GetInstance()->create_laserEnemy(scene, rand() % 1031, 0, 5, 0.0, 30, 50, enemyNameList[2], ++enemyIdCount[2]);
			CreateObjectsManager::GetInstance()->create_laser(scene, 0, 0, 0.0, 0.0, 5, 640, enemyNameList[2], enemyIdCount[2]);
			timer3 = 0;
		}
	}
	else if (Game::score >= 1200) { // when the player reach a score higher than 1200, change game mode to 1
		Game::game_mode = 1;
	}

	// if the player get the teammate
	if (Game::getTeammate) {
		Game::life++;
		playerId++;
		switch (pickUpType) {
		case 0:CreateObjectsManager::GetInstance()->create_player(scene, 540, 590, 0.0, 0.0, 50, 50, "player", playerId, "images/player/blue_basic_pos1.png", "images/player/blue_basic_pos2.png", "images/player/blue_basic_pos3.png");
			CreateObjectsManager::GetInstance()->create_bullet(scene, -100, -100, 0.0, 0.0, 5, 20, "player", playerId, "images/player/bullet_std_wTrail.png"); break;
		case 1:CreateObjectsManager::GetInstance()->create_player(scene, 540, 590, 0.0, 0.0, 50, 50, "player", playerId, "images/player/blue_light_pos1.png", "images/player/blue_light_pos2.png", "images/player/blue_light_pos3.png");
			CreateObjectsManager::GetInstance()->create_bullet(scene, -100, -100, 0.0, 0.0, 5, 20, "player", playerId, "images/player/bullet_std_wTrail.png"); break;
		case 2:CreateObjectsManager::GetInstance()->create_player(scene, 540, 590, 0.0, 0.0, 30, 50, "player", playerId, "images/player/blue_laser_pos1.png", "images/player/blue_laser_pos2.png", "images/player/blue_laser_pos3.png");
			CreateObjectsManager::GetInstance()->create_bullet(scene, -100, -100, 0.0, 0.0, 5, 20, "player", playerId, "images/player/bullet_laset_v3f_longDemo.png"); break;
		case 3:CreateObjectsManager::GetInstance()->create_player(scene, 540, 590, 0.0, 0.0, 75, 50, "player", playerId, "images/player/blue_bomber_pos1.png", "images/player/blue_bomber_pos1.png", "images/player/blue_bomber_pos1.png");
			CreateObjectsManager::GetInstance()->create_bullet(scene, -100, -100, 0.0, 0.0, 10, 20, "player", playerId, "images/player/bullet_clutser.png"); break;
		case 4:CreateObjectsManager::GetInstance()->create_player(scene, 540, 590, 0.0, 0.0, 50, 50, "player", playerId, "images/player/blue_advance_pos1.png", "images/player/blue_advance_pos2.png", "images/player/blue_advance_pos3.png");
			CreateObjectsManager::GetInstance()->create_bullet(scene, -100, -100, 0.0, 0.0, 5, 20, "player", playerId, "images/player/bullet_missile.png"); break;
		default:break;
		}
		Game::getTeammate = false;
	}
}

void RespawnObjectsManager::Reset()
{
	timer1 = 0;
	timer2 = 0;
	timer3 = 0;
	pickUpType = 0;
	playerId = 1;
	enemyIdCount[5] = { 0 };
}
