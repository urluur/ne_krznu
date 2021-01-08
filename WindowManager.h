#pragma once
#include <sdl.h>
class WindowManager
{
private:
	
public:
	SDL_Window* window;
	SDL_Surface* surface;
	SDL_Surface* image;

	WindowManager();
	~WindowManager();
};

