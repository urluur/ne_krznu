#pragma once
#include <iostream>
#include <SDL_mixer.h>
#include <string>

class SoundManager {
private:
	Mix_Music* bgm = nullptr;
	Mix_Chunk* efekt = nullptr;
	bool mute;
public:
	SoundManager();
	void predvajaj(const char*);
	void toggle();
	void toggle(bool);
	void soundAnimacija(int);
	bool vrniMute() { return mute; }
	void setMus(const char*);
	~SoundManager();
};
