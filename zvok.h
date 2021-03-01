#pragma once
//#include <windows.h>
#include <iostream>
//#include <MMSystem.h>
#include <SDL_mixer.h>
using namespace std;

class SoundManager
{
private:
	Mix_Music* bgm = nullptr;
	Mix_Chunk* efekt = nullptr;
	bool mute;
	bool played;
public:
	SoundManager();
	void predvajaj(const char*);
	void toggle();
	void oof();
	void cursorMove();
	void dimenzije();
	void izhod();
	void nastavitve();
	void nasvidenje();
	void nazaj();
	void spremeni_ime();
	void spremeni_zvok();
	void vec();
	void zacni();
	void lestvica();
	void izvorna();
	void izbris();
	void soundAnimacija(int animSt);
	~SoundManager();
};
