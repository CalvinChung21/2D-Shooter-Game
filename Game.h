#pragma once
//include SDL stuff
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <vector>

class GameObject;

class Game {
public:
	static Game* GetInstance() { return (s_Instance == nullptr ? new Game() : s_Instance); };
	void init(const char* title, uint32_t width, uint32_t height, bool fullscreen);
	void update();
	void render();
	void clean();
	bool running() { return isRunning; }
	static void reset();

	inline static int score = 0;
	inline static int getTeammate = false;
	inline static int life = 1;
	inline static bool isStart = false;
	inline static bool resetGame = false;
	inline static int game_mode = 0;

	inline static SDL_Renderer* renderer;
	inline static int SCREEN_WIDTH;
	inline static int SCREEN_HEIGHT;
private:
	Game();
	~Game();
	static Game* s_Instance;
	void handleEvent();

	SDL_Window* window;
	

	bool isRunning;

	bool doneInit = false;


};

