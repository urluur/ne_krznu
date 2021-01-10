#pragma once
#include <SDL.h>
#include <SDL_image.h>

class Image {
public:
	Image();
	Image(SDL_Renderer* ren, const char* filePath, int x, int y, int w, int h);

	void init(SDL_Renderer* ren, const char* filePath, int x, int y, int w, int h);
	void display(SDL_Renderer* ren);

	~Image();
private:
	SDL_Surface* image_surface = nullptr;
	SDL_Texture* image_texture = nullptr;

	SDL_Rect rect;

	bool flipped;
};

