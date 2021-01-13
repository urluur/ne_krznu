#pragma once
#include <sdl.h>
#include <iostream>

class WindowManager
{
private:
    int Window_width = 720; //default
    int Window_height = 640; //default
	int scaler = 15;
	
public:
	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_Surface* surface;
	SDL_Surface* image;

	WindowManager();
	int returnWindowWidth();
	int returnWindowHeight();
	void toggleScaler();
	int scalerCalculator(int stevilo);
	int vrniScaler();
	~WindowManager();
};

