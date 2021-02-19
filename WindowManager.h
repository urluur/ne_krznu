#pragma once
#include <sdl.h>
#include <iostream>
using namespace std;

class WindowManager {
private:
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	Uint32 frameStart;
	int frameTime;

	short Window_width = 720; //default
	short Window_height = 640; //default
	short scaler = 1; // default je 15 (aka 1.5) za 1920x1080, za manjse zaslone se lahko spremeni na 1 ()
public:
	SDL_Renderer* ren;
	SDL_Window* window;
	SDL_Surface* surface;

	WindowManager();
	void stejFrame() { frameStart = SDL_GetTicks(); }
	void omejiFrame();
	short returnWindowWidth() { return Window_width; }
	short returnWindowHeight() { return Window_height; }
	void toggleScaler();
	short vrniScaler() { return scaler; }
	int scaleCal(int stevilo);
	~WindowManager();
};
