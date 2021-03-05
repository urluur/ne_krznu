#include "zvok.h"

SoundManager::SoundManager() {
	played = false;
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		std::cerr << "Mixer error: " << Mix_GetError() << std::endl;
	bgm = Mix_LoadMUS("common/sounds/soundtrack.wav");
	if (!Mix_PlayingMusic())
		Mix_PlayMusic(bgm, -1);
	mute = false;
}

void SoundManager::toggle() {
	if (!mute) {
		Mix_PauseMusic();
		printf("Glasba se je ustavila ..\n");
	}
	else {
		Mix_ResumeMusic();
		printf("Glasba se nadaljuje..\n");
	}
	mute = !mute;
}
void SoundManager::soundAnimacija(int animSt) {
	if (!mute) {
		std::string pathFragment = "common/sounds/animacija";
		pathFragment += std::to_string(animSt);
		pathFragment += ".wav";
		char* path = new char[pathFragment.size() + 1];
		std::copy(pathFragment.begin(), pathFragment.end(), path);
		path[pathFragment.size()] = '\0';
		predvajaj(path);
		delete[] path;
	}
}

void SoundManager::predvajaj(const char* path) {
	if (!mute) {
		Mix_HaltChannel(-1);
		efekt = Mix_LoadWAV(path);
		Mix_PlayChannel(-1, efekt, 0);
	}
}

SoundManager::~SoundManager() {
	Mix_FreeChunk(efekt);
	bgm = nullptr;
	efekt = nullptr;
	Mix_CloseAudio();
	Mix_Quit();
}