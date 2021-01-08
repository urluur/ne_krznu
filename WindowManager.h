#pragma once
#include <sdl.h>

class WindowManager
{
private:
    int Window_width = 720;
    int Window_height = 640;
	
public:
	SDL_Renderer* renderer;
	/*
	cheat sheet:
	screen = SDL_GetWindowSurface(window);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	SDL_UpdateWindowSurface(igra.okno.window);
	SDL_BlitSurface(igra.okno.image, NULL, igra.okno.surface, NULL);
	*/
	SDL_Window* window;
	SDL_Surface* surface;
	SDL_Surface* image;

	int returnWindow_width();
	int returnWindow_height();
	WindowManager();
	~WindowManager();
};

