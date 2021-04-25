#pragma once
#include <sdl.h>
#include <iostream>
#include "Casovnik.h"
using namespace std;

class WindowManager {
private:
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	Uint32 frameStart;
	int frameTime;

	// ne spreminjaj Window_width in Window_height ker dolocata "platno" igre, ne pa velikost okna
	const short Window_width = 1280, Window_height = 720;
	short scaler = 1; // default je 1, fulscreen je 100
public:
	SDL_Renderer* ren;
	SDL_Window* window;
	SDL_Surface* surface;
	friend class Casovnik;

	WindowManager();
	void stejFrame() { frameStart = SDL_GetTicks(); }
	void omejiFrame();
	short returnWindowWidth() { return Window_width; }
	short returnWindowHeight() { return Window_height; }
	void toggleScaler();
	short vrniScaler() { return scaler; }
	int scaleCal(int);
	~WindowManager();
};
