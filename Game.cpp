#include "Game.h"
#include <iostream>
// Most of the codes are referenced from https://www.youtube.com/playlist?list=PLhfAbcv9cehhkG7ZQK0nfIGJC_C-wSLrx
// code reference from https://www.youtube.com/watch?v=8LbVpkEqKuY
#include "UIManager.h"
#include "CreateObjectsManager.h"
#include "RespawnObjectsManager.h"
#include "Scene.h"

Game* Game::s_Instance = nullptr;
RespawnObjectsManager* respawnObjectsManager;
UIManager* uiManager;
Scene scene;

Game::Game() {};

Game::~Game()
{
	window = nullptr;
	renderer = nullptr;
}

void Game::init(const char* title, uint32_t width, uint32_t height, bool fullscreen)
{
	// get the width and height specified by the programmer
	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;

	// check whether all initialize process is working properly
	isRunning = true;

	// whether the programmer want the game to be in fullscreen mode
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	// initialize SDL subsystem
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		fprintf(stderr, "Could not initialize SDL!\n");
		isRunning = false;
	}
	else
	{
		fprintf(stdout, "SDL initialized properly!\n");
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		if (window) {
			fprintf(stdout, "Window created!\n");
			renderer = SDL_CreateRenderer(window, -1, 0);
			if (renderer) {
				fprintf(stdout, "Renderer created!\n");
				uiManager = UIManager::GetInstance();
				respawnObjectsManager = RespawnObjectsManager::GetInstance();
			}
			else {
				fprintf(stderr, "Could not create renderer!\n");
				isRunning = false;
			}
		}
		else {
			fprintf(stderr, "Could not create window!\n");
			isRunning = false;
		}
	}
	
}

void Game::handleEvent()
{
	if (isStart) {
		// reference to https://wiki.libsdl.org/SDL_GetMouseState  and https://stackoverflow.com/questions/35165716/sdl-mouse-click
		int x, y;
		Uint32 buttons;
		SDL_PumpEvents();  // make sure we have the latest mouse state.

		buttons = SDL_GetMouseState(&x, &y);

		SDL_Event event;
		// handle the window event
		if (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT: isRunning = false; fprintf(stdout, "Quit event has occurred!\n"); break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT) {
					Scene::pause=uiManager->DetectMouseClickOnPause(x, y, Scene::pause);
				}; break;
			default: break;
			}
		}
	}
}

void Game::update() {

	if (!isStart) {
		// reference to https://wiki.libsdl.org/SDL_GetMouseState  and https://stackoverflow.com/questions/35165716/sdl-mouse-click
		int x, y;
		Uint32 buttons;
		SDL_PumpEvents();  // make sure we have the latest mouse state.

		buttons = SDL_GetMouseState(&x, &y);

		SDL_Event event;
		// handle the window event
		if (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT: 
				isRunning = false; 
				fprintf(stdout, "Quit event has occurred!\n"); break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT) {
					isStart = uiManager->DetectMouseClickOnStart(x, y);
					isRunning = uiManager->DetectMouseClickOnQuit(x, y);
				}; 
				break;
			default: break;
			}
		}
	}
	else if (isStart && doneInit == false) {
		CreateObjectsManager::GetInstance()->Init(scene);
		doneInit = true;
	}
	uiManager->LoadText();
	respawnObjectsManager->Update(scene);

	// when life is 0, game over
	if (life == 0) {
		game_mode = 2;
	}

	handleEvent();
}

void Game::reset() {
	// reset the game
	if (game_mode == 1 || game_mode == 2) {
		const Uint8* keys;
		keys = SDL_GetKeyboardState(NULL);
		if (keys[SDL_SCANCODE_R]) {
			resetGame = true;
			game_mode = 0;
			score = 0;
			life = 1;
			getTeammate = false;
			RespawnObjectsManager::GetInstance()->Reset();
			CreateObjectsManager::GetInstance()->Init(scene);
		}
	}
}

void Game::render()
{
	uiManager->Render(scene);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	SDL_Quit();
	fprintf(stdout, "Game Cleaned!\n");
}