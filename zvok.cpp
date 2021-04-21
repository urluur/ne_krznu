#include "zvok.h"

SoundManager::SoundManager() { // klicemo ko je ustvarjen objekt igra
	// inicializiramo SDL zvok z dvema kanaloma (sstereo)
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		std::cerr << "Mixer error: " << Mix_GetError() << std::endl;

	// nalozimo glasbo za odzadje
	bgm = Mix_LoadMUS("common/sounds/soundtrack.wav");
	if (!Mix_PlayingMusic())
		Mix_PlayMusic(bgm, -1);
	mute = false;
}

void SoundManager::toggle() { // klicemo, ko zelimo vkolopiti ali izklopiti zvoke
	if (!mute) { // ce je zvok vklopljen se izklopi
		Mix_PauseMusic();
		printf("Glasba se je ustavila ..\n");
	}
	else { // ce je zvok izklopljen se vklopi
		Mix_ResumeMusic();
		printf("Glasba se nadaljuje..\n");
	}
	mute = !mute;
}

void SoundManager::toggle(bool notr) { // klicemo, ko zelimo pod nujno odprt ali zaprt zvok
	mute = notr;
	if (!mute) { // zvok se izklopi
		Mix_PauseMusic();
	}
	else { // zvok se vklopi
		Mix_ResumeMusic();
	}
}

void SoundManager::soundAnimacija(int animSt) {
	// predvaja se zvok zgodbe
	if (!mute) {
		// pot do datoteke je sestavljena iz stevilke animacije
		std::string pathFragment = "common/sounds/animacija";
		pathFragment += std::to_string(animSt);
		pathFragment += ".wav";
		char* path = new char[pathFragment.size() + 1];
		std::copy(pathFragment.begin(), pathFragment.end(), path);
		path[pathFragment.size()] = '\0';
		predvajaj(path); //predvajamo zvok
		delete[] path;
	}
}

void SoundManager::predvajaj(const char* path) { // kicemo ko zelimo predvajati zvocni efekt
	if (!mute) {
		Mix_HaltChannel(-1);
		efekt = Mix_LoadWAV(path);
		Mix_PlayChannel(-1, efekt, 0);
	}
}

// pobrisemo vse potrebno ko se unici objekt "igra"
SoundManager::~SoundManager() {
	Mix_FreeChunk(efekt);
	bgm = nullptr;
	efekt = nullptr;
	Mix_CloseAudio();
	Mix_Quit();
}