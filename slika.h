#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "igra.h"

class Image {
public:
	Image();
	Image(SDL_Renderer*, const char*, unsigned short, unsigned short, unsigned short, unsigned short);
	void init(class GameManager&, const char*, unsigned short, unsigned short, unsigned short, unsigned short);
	// unsigned short sliko lahko raztegne celo do resolucije ~64K.. ce bojo meli monitorji vec piksov
	// kot to, pa samo spremeni "unsigned short" na "unsigned int" in smo reseni se za ksno tisocletje
	void ini(class GameManager&, const char*);
	void display(SDL_Renderer*);
	SDL_Surface returnSurface() { return *image_surface; }
	~Image();
private:
	SDL_Surface* image_surface = nullptr;
	SDL_Texture* image_texture = nullptr;
	SDL_Rect rect;
	bool flipped;
};
