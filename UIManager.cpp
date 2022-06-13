#include "UIManager.h"
#include "Game.h"

UIManager* UIManager::s_Instance = nullptr;

UIManager::UIManager()
{
	srcR = { 0, 1200, 1080, 600 };
	LoadText();
	LoadUI();
}

UIManager::~UIManager()
{
	SDL_FreeSurface(textSurface);
	SDL_FreeSurface(scoreSurface);
	SDL_FreeSurface(restartSurface);
	SDL_DestroyTexture(Message);
	SDL_DestroyTexture(scoreMessage);
	SDL_DestroyTexture(restartMessage);
	SDL_DestroyTexture(pauseIcon);
	SDL_DestroyTexture(menu);
	SDL_DestroyTexture(startGame);
	SDL_DestroyTexture(setting);
	SDL_DestroyTexture(quitGame);

	//close the font// 
	TTF_CloseFont(font);
	//quit SDL_ttf//  
	TTF_Quit();
}

void UIManager::LoadText()
{
	if (!loadText) {
		//for font
		if (TTF_Init() == -1) {
			printf("Could not initialize SDL2_ttf, error: %s", TTF_GetError());
		}
		else {
			printf("SDL2_ttf system ready to go");
		}

		font = TTF_OpenFont("font/arial.ttf", 100);
		if (font == nullptr) {
			printf("Could not load font");
			exit(1);
		}
		loadText = true;
	}

	if (font == nullptr) loadText = false;

	if (Game::game_mode == 1) {
		textSurface = TTF_RenderText_Solid(font, "You Win", { 255,255,255 });
	}
	if (Game::game_mode == 2) {
		textSurface = TTF_RenderText_Solid(font, "You Lose", { 255,255,255 });
	}
	// how to render text in SDL2 reference in https://stackoverflow.com/questions/22886500/how-to-render-text-in-sdl2
	Message = SDL_CreateTextureFromSurface(Game::GetInstance()->renderer, textSurface);
	Message_rect = { 300,  Game::SCREEN_HEIGHT / 2 - 50 , 400, 100 };

	if (Game::game_mode == 0) {
		textSurface = TTF_RenderText_Solid(font, "SCORE", { 255,255,255 });
		// how to render text in SDL2 reference in https://stackoverflow.com/questions/22886500/how-to-render-text-in-sdl2
		Message = SDL_CreateTextureFromSurface(Game::GetInstance()->renderer, textSurface);
		Message_rect = { 12, Game::SCREEN_HEIGHT - 75 , 40, 20 };
	}

	//how to add variable to string for TTF_RenderText_Solid reference from https://stackoverflow.com/questions/13096758/how-add-variables-to-string-for-ttf-rendertext-solid
	//how to clear stringstream reference from https://stackoverflow.com/questions/20731/how-do-you-clear-a-stringstream-variable
	s.str(std::string());
	s << Game::score;
	scoreSurface = TTF_RenderText_Solid(font, s.str().c_str(), { 255,255,255 });
	scoreMessage = SDL_CreateTextureFromSurface(Game::GetInstance()->renderer, scoreSurface);
	
	if (Game::score == 0) scoreMessage_rect = { 25, Game::SCREEN_HEIGHT - 55 , 25, 50 };
	else scoreMessage_rect = { 10, Game::SCREEN_HEIGHT - 55 , 60, 50 };
	

	if (Game::game_mode == 1 || Game::game_mode == 2) {
		restartSurface = TTF_RenderText_Solid(font, "Press 'R' to Restart", { 255,255,255 });
		restartMessage = SDL_CreateTextureFromSurface(Game::GetInstance()->renderer, restartSurface);
		restartMessage_rect = { 350, 350, 300, 50 };
	}

}

bool UIManager::LoadUI()
{
	menu = IMG_LoadTexture(Game::GetInstance()->renderer, "images/menu/mainMenu_bg.png");
	menuRect = { 0, 0, 1080, 600 };
	startGame = IMG_LoadTexture(Game::GetInstance()->renderer, "images/menu/but_start.png");
	startRect = { 25, 200, 315, 29 };

	setting = IMG_LoadTexture(Game::GetInstance()->renderer, "images/menu/but_setting.png");
	setRect = { 25, 325, 267, 29 };

	quitGame = IMG_LoadTexture(Game::GetInstance()->renderer, "images/menu/but_exit.png");
	quitRect = { 25, 450, 131, 29 };

	background = IMG_LoadTexture(Game::GetInstance()->renderer, "images/background/sea_swbg_1080x1800_lc_v2.png");
	if (background == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "./images/background/sea_swbg_1080x1800_lc_v2.png", SDL_GetError());
		return false;
	}
	pauseIcon = IMG_LoadTexture(Game::GetInstance()->renderer, "images/menu/icon_pause.png");
	if (pauseIcon == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "./images/menu/icon_pause.png", SDL_GetError());
		return false;
	}
	pauseIconRect = { 980, 15, 75, 75 };

	return true;
}

void UIManager::RenderBackground()
{
	// for the always scrolling background
	if (Scene::pause == false) {
		srcR.y--;
		if (srcR.y == 0) {
			srcR.y = 1200;
		}
	}
	SDL_RenderCopy(Game::GetInstance()->renderer, background, &srcR, NULL);
}

void UIManager::Render(Scene& scene)
{
	SDL_RenderClear(Game::GetInstance()->renderer);
	// render when the game is started and when game mode is 0
	if (Game::GetInstance()->game_mode == 0 && Game::GetInstance()->isStart) {
		RenderBackground();
		scene.update(Game::SCREEN_WIDTH, Game::SCREEN_HEIGHT);

		SDL_RenderCopy(Game::GetInstance()->renderer, scoreMessage, NULL, &scoreMessage_rect);
		SDL_RenderCopy(Game::GetInstance()->renderer, pauseIcon, NULL, &pauseIconRect);
	}
	else if (Game::GetInstance()->game_mode > 0 && Game::GetInstance()->isStart) {
		// render when the play has win
		SDL_RenderCopy(Game::GetInstance()->renderer, background, &srcR, NULL);
		SDL_RenderCopy(Game::GetInstance()->renderer, restartMessage, NULL, &restartMessage_rect);
		scene.endGame();
		Game::reset();
	}
	SDL_RenderCopy(Game::GetInstance()->renderer, Message, NULL, &Message_rect);

	if (!Game::GetInstance()->isStart) {
		// render when the game hasn't started yet
		SDL_RenderCopy(Game::GetInstance()->renderer, menu, NULL, &menuRect);
		SDL_RenderCopy(Game::GetInstance()->renderer, startGame, NULL, &startRect);
		SDL_RenderCopy(Game::GetInstance()->renderer, setting, NULL, &setRect);
		SDL_RenderCopy(Game::GetInstance()->renderer, quitGame, NULL, &quitRect);
	}
	SDL_RenderPresent(Game::GetInstance()->renderer);
}

bool UIManager::DetectMouseClickOnPause(int x, int y, bool pause)
{
	if ((x > pauseIconRect.x && x < pauseIconRect.x + pauseIconRect.w) 
		&& (y > pauseIconRect.y && y < pauseIconRect.y + pauseIconRect.h)) {
		return !pause;
	}
}

bool UIManager::DetectMouseClickOnStart(int x, int y)
{
	if ((x > startRect.x && x < startRect.x + startRect.w) 
		&& (y > startRect.y && y < startRect.y + startRect.h)) {
		return true;
	}
	return false;
}

bool UIManager::DetectMouseClickOnQuit(int x, int y)
{
	if ((x > quitRect.x && x < quitRect.x + quitRect.w) 
		&& (y > quitRect.y && y < quitRect.y + quitRect.h)) {
		fprintf(stdout, "Quit event has occurred!\n");
		return false;
	}
	return true;
}
