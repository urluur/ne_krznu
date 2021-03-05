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

	const short Window_width = 1280, Window_height = 720;
	short scaler = 12; // default je 1, fulscreen je 100
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
	int scaleCal(int);
	~WindowManager();
};
