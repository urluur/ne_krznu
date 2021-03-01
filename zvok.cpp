#include "zvok.h"

SoundManager::SoundManager() {
	played = false;
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		cout << "Mixer error: " << Mix_GetError() << endl;
	bgm = Mix_LoadMUS("common/sounds/soundtrack.wav");
	if (!Mix_PlayingMusic())
		Mix_PlayMusic(bgm, -1);
	mute = 0;
}

void SoundManager::toggle() {
	if (mute == 0) {
		mute = 1;
		Mix_PauseMusic();
		cout << "Glasba se je ustavila .." << endl;
	}
	else {
		mute = 0;
		Mix_ResumeMusic();
		cout << "Glasba se nadaljuje.." << endl;
	}
}
void SoundManager::cursorMove() {
	predvajaj("common/sounds/cur_mov.wav");
}
void SoundManager::oof() {
	predvajaj("common/sounds/oof.wav");
}
void SoundManager::dimenzije() {
	predvajaj("common/sounds/dimenzije.wav");
}
void SoundManager::izhod() {
	predvajaj("common/sounds/izhod.wav");
}
void SoundManager::nastavitve() {
	predvajaj("common/sounds/nastavitve.wav");
}
void SoundManager::nasvidenje() {
	predvajaj("common/sounds/nasvidenje.wav");
}
void SoundManager::nazaj() {
	predvajaj("common/sounds/nazaj.wav");
}
void SoundManager::spremeni_ime() {
	predvajaj("common/sounds/spremeni_ime.wav");
}
void SoundManager::spremeni_zvok() {
	predvajaj("common/sounds/spremeni_zvok.wav");
}
void SoundManager::vec() {
	predvajaj("common/sounds/vec.wav");
}
void SoundManager::zacni() {
	predvajaj("common/sounds/zacni.wav");
}
void SoundManager::lestvica() {
	predvajaj("common/sounds/lestvica.wav");
}
void SoundManager::izvorna() {
	predvajaj("common/sounds/izvorna.wav");
}
void SoundManager::izbris() {
	predvajaj("common/sounds/izbris.wav");
}
void SoundManager::soundAnimacija(int animSt) {
	if (mute == 0)
		switch (animSt) {
		case 1:
			predvajaj("common/sounds/animacija1.wav");
			break;
		case 2:
			predvajaj("common/sounds/animacija2.wav");
			break;
		case 3:
			predvajaj("common/sounds/animacija3.wav");
			break;
		case 4:
			predvajaj("common/sounds/animacija4.wav");
			break;
		case 5:
			predvajaj("common/sounds/animacija5.wav");
			break;
		case 6:
			predvajaj("common/sounds/animacija6.wav");
			break;
		case 7:
			predvajaj("common/sounds/animacija7.wav");
			break;
		default:
			cerr << "Error: sound animSt" << endl;
		}
}

void SoundManager::predvajaj(const char* path) {
	if (mute == 0) {
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