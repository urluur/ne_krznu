#pragma once
#include <sdl.h>

class WindowManager
{
private:
    int Window_width = 720; //default
    int Window_height = 640; //default
	
public:
	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_Surface* surface;
	SDL_Surface* image;

	WindowManager();
	int returnWindowWidth();
	int returnWindowHeight();
	void nastaviWindowWidth(int novHeight);
	void nastaviWindowHeight(int novWidth);
	~WindowManager();
};

