#pragma once
#include <sdl.h>

class WindowManager
{
private:
    int Window_width = 720;
    int Window_height = 640;
	
public:
	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_Surface* surface;
	SDL_Surface* image;

	WindowManager();
	int returnWindowWidth();
	int returnWindowHeight();
	~WindowManager();
};

