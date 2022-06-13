#pragma once
// code reference from https://www.youtube.com/watch?v=8LbVpkEqKuY
#include <string>
#include "Game.h"

struct TagComponent
{
	std::string tag;
};

struct PositionComponent
{
	double x, y;
};

struct VelocityComponent
{
	double x, y;
};

struct AccelerationComponent
{
	double x, y;
};

struct HealthComponent
{
	int health;
	SDL_Texture* three;
	SDL_Texture* two;
	SDL_Texture* one;
	SDL_Rect healthRect;
};

struct SpriteComponent
{
	SDL_Texture* obj_textureIdle;
	SDL_Texture* obj_textureLeft;
	SDL_Texture* obj_textureRight;
	SDL_Rect destRect;
};

struct UiComponent {
	SDL_Texture* obj_textureIdle;
	SDL_Rect destRect;
};

struct ExplodeComponent {
	int duration;
	SDL_Texture* explodeImg1;
	SDL_Texture* explodeImg2;
	SDL_Texture* healPack;
	SDL_Rect destRect;
	bool played = false;
};

struct ExistComponent
{
	bool exist;
};

struct ControlComponent
{
	const Uint8* keys;
};

struct IDComponent
{
	int id;
};

struct CounterComponent
{
	int counter;
};

struct AngleComponet
{
	double ang;
};