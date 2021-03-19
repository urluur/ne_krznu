#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "igra.h"

class Image {
private:
	SDL_Surface* image_surface = nullptr;
	SDL_Texture* image_texture = nullptr;
	SDL_Rect rect;
	bool flipped;
public:
	Image();
	Image(SDL_Renderer*, const char*, short, short, short, short);
	void init(class GameManager&, const char*, short, short, short, short);
	void ini(class GameManager&, const char*);
	void display(SDL_Renderer*);
	SDL_Surface returnSurface() { return *image_surface; }
	void flip();
	void unFlip();
	~Image();
};
