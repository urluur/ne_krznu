#pragma once
#include <sdl.h>
#include <iostream>

class WindowManager
{
private:
    int Window_width = 720; //default
    int Window_height = 640; //default
	int scaler = 15; // default je 15 (aka 1.5) za 1920x1080, za manjse zaslone se lahko spremeni na 1 ()
	
public:
	SDL_Renderer* ren;
	SDL_Window* window;
	SDL_Surface* surface;
	SDL_Surface* image;

	WindowManager();
	int returnWindowWidth();
	int returnWindowHeight();
	void toggleScaler();
	int scaleCal(int stevilo);
	int vrniScaler();
	~WindowManager();
};

