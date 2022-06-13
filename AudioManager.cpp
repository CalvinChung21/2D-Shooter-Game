#include "AudioManager.h"

AudioManager* AudioManager::s_Instance = nullptr;

void AudioManager::LoadAudioResources()
{
	//Initialize SDL_mixer
	// code for the sound here==================
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	}

	//Load music
	// code for the sound here==================
	music = Mix_LoadMUS("audio\\music.mp3");
	if (music == NULL) {
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
	}

	// code for the sound here==================
	//Load sound effects
	shoot = Mix_LoadWAV("audio\\shoot.wav");
	if (shoot == NULL) {
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}
	explosion = Mix_LoadWAV("audio\\explosion.wav");
	if (explosion == NULL) {
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}
	laser = Mix_LoadWAV("audio\\gun_laser_enemy.wav");
	if (laser == NULL) {
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}
	bomberShoot = Mix_LoadWAV("audio\\gun_bomber_player.wav");
	if (bomberShoot == NULL) {
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}
	pauseAudio = Mix_LoadWAV("audio\\pause.wav");
	if (pauseAudio == NULL) {
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}
	startAudio = Mix_LoadWAV("audio\\button.wav");
	if (startAudio == NULL) {
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}
	heal = Mix_LoadWAV("audio\\heal.mp3");
	if (heal == NULL) {
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}
	pickUp = Mix_LoadWAV("audio\\levelUp.wav");
	if (pickUp == NULL) {
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}

	if (Mix_PlayMusic(music, -1) == -1) {
		printf("Mix_PlayMusic: %s\n", Mix_GetError());
		// well, there's no music, but most games don't break without music...
	}
}

void AudioManager::MenuAudio()
{
	// audio playback for start button
	if (Game::isStart == true && startFlag == false) {
		Mix_PlayChannel(-1, startAudio, 0);
		startFlag = true;
	}
	// audio playback for pause button
	if (Scene::pause && pauseFlag == false) {
		Mix_PlayChannel(-1, pauseAudio, 0);
		pauseFlag = true;
	}
	if (Scene::pause == false && pauseFlag == true) {
		Mix_PlayChannel(-1, pauseAudio, 0);
		pauseFlag = false;
	}
	// audio playback for reset button
	if (Game::resetGame == true) {
		Mix_PlayChannel(-1, startAudio, 0);
		Game::resetGame = false;
	}
}

void AudioManager::PlaySound(audioName sound)
{
	switch (sound) {
	case HEAL:Mix_PlayChannel(-1, heal, 0); break;
	case PICKUP:Mix_PlayChannel(-1, pickUp, 0); break;
	case SHOOT:Mix_PlayChannel(-1, shoot, 0); break;
	case LASER:Mix_PlayChannel(-1, laser, 0); break;
	case BOMBERSHOOT:Mix_PlayChannel(-1, bomberShoot, 0); break;
	case EXPLOSION:Mix_PlayChannel(-1, explosion, 0); break;
	default:break;
	}
}

void AudioManager::FreeAudioResources()
{
	Mix_FreeMusic(music);
	Mix_FreeChunk(shoot);
	Mix_FreeChunk(explosion);
	Mix_FreeChunk(bomberShoot);
	Mix_FreeChunk(laser);
	Mix_FreeChunk(pauseAudio);
	Mix_FreeChunk(startAudio);
	Mix_FreeChunk(heal);
	Mix_FreeChunk(pickUp);
}
