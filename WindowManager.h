#pragma once
#include <sdl.h>
#include <iostream>
using namespace std;

class WindowManager
{
private:
    short Window_width = 720; //default
    short Window_height = 640; //default
	short scaler = 15; // default je 15 (aka 1.5) za 1920x1080, za manjse zaslone se lahko spremeni na 1 ()
	
public:
	SDL_Renderer* ren;
	SDL_Window* window;
	SDL_Surface* surface;
	SDL_Surface* image;

	WindowManager();
	short returnWindowWidth();
	short returnWindowHeight();
	void toggleScaler();
	short vrniScaler();
	int scaleCal(int stevilo);
	~WindowManager();
};

