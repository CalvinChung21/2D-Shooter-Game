#pragma once
#include "Game.h"
#include <sstream>
#include <SDL_ttf.h>
#include "Scene.h"

class UIManager {
public:
	static UIManager* GetInstance() { return (s_Instance == nullptr ? new UIManager() : s_Instance); }
	void Render(Scene& scene);
	void LoadText();
	bool DetectMouseClickOnPause(int x, int y, bool pause);
	bool DetectMouseClickOnStart(int x, int y);
	bool DetectMouseClickOnQuit(int x, int y);
private:
	UIManager();
	~UIManager();
	
	bool LoadUI();
	void RenderBackground();
	static UIManager* s_Instance;


	bool loadText = false;
	//for displaying text and UI icons
	TTF_Font* font;

	SDL_Surface* textSurface;
	SDL_Texture* Message;
	SDL_Rect Message_rect;

	std::stringstream s;
	SDL_Surface* scoreSurface;
	SDL_Texture* scoreMessage;
	SDL_Rect scoreMessage_rect;

	SDL_Surface* restartSurface;
	SDL_Texture* restartMessage;
	SDL_Rect restartMessage_rect;

	SDL_Texture* pauseIcon;
	SDL_Rect pauseIconRect;
	// Game background
	SDL_Rect srcR;
	SDL_Texture* background;
	// Game Menu
	SDL_Rect menuRect;
	SDL_Texture* menu;
	SDL_Rect startRect;
	SDL_Texture* startGame;
	SDL_Rect setRect;
	SDL_Texture* setting;
	SDL_Rect quitRect;
	SDL_Texture* quitGame;
};