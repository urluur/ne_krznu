#pragma once
#include <iostream>
#include <SDL_mixer.h>
#include <string>

class SoundManager {
private:
	Mix_Music* bgm = nullptr;
	Mix_Chunk* efekt = nullptr;
	bool mute;
	bool played;
public:
	SoundManager();
	void predvajaj(const char*);
	void toggle();
	void soundAnimacija(int);
	~SoundManager();
};