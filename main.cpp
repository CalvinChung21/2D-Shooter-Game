//requires VC++ Directories include to SDL210 include folder and library to SDL lib x86 folder
// 
//requires static linkage to:
// SDL2.lib, SDL2main.lib, SDL2_image.lib, SDL2_mixer.lib, SDL2_ttf.lib
//
//requires dynamic linkage to:
// SDL2.dll, SDL2_image.dll, zlib1.dll, libpng16-16.dll, libmpg123-0.dll
//
//requires using C++ language Standard 20 as it is using the Entt (ecs library)
//

// Most of the codes are referenced from https://www.youtube.com/playlist?list=PLhfAbcv9cehhkG7ZQK0nfIGJC_C-wSLrx

#include "Game.h"
#include "Scene.h"

int main(int argc, char* argv[])
{
	Game* game = Game::GetInstance();
	game->init("2DShooterGame", 1080, 600, false);

	// for controlling FPS
	// reference from http://www.helloresolven.com/portfolio/gifbrewery/tutorials/fps.html
	// Really! 42ms is equivalent to 24fps, while 100ms is equivalent to 10fps. In other words, 
	// if you set the frame delay to 100ms, it will show 10 of your frames every second.
	// For reference, (frames per second) = (1000) / (frame delay).
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	while (game->running()) {
		frameStart = SDL_GetTicks();

		game->update();
		game->render();

		// rendered time for each frame
		frameTime = SDL_GetTicks() - frameStart;
		// if the game can't deliver 60 fps
		// then delay it for some time
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();
	fprintf(stdout, "Terminating program normally.\n");

	return 0;
}