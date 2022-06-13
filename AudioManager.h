#pragma once
#include "Game.h"
#include "Scene.h"
#include <SDL_mixer.h>
#include <stdio.h>

enum audioName {
	HEAL,
	PICKUP,
	SHOOT,
	LASER,
	BOMBERSHOOT,
	EXPLOSION
};

class AudioManager {
public:
	static AudioManager* GetInstance() { return (s_Instance == nullptr ? new AudioManager() : s_Instance); }
	void LoadAudioResources();
	void MenuAudio();
	void PlaySound(audioName sound);
	void FreeAudioResources();

private:
	AudioManager() { LoadAudioResources(); }
	~AudioManager() { FreeAudioResources(); }
	static AudioManager* s_Instance;

	//The music that will be played
	Mix_Music* music;

	bool pauseFlag = false;
	bool startFlag = false;
	Mix_Chunk* pauseAudio;
	Mix_Chunk* startAudio;
	// code for the sound here==================
	//The sound effects that will be used
	Mix_Chunk* heal;
	Mix_Chunk* pickUp;
	Mix_Chunk* shoot;
	Mix_Chunk* laser;
	Mix_Chunk* bomberShoot;
	Mix_Chunk* explosion;
};