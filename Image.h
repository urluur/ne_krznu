#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "GameManager.h"

class Image {
public:
	Image();
	Image(SDL_Renderer* ren, const char* filePath, unsigned short x, unsigned short y, unsigned short w, unsigned short h);
	void init(class GameManager& igra, const char* filePath, unsigned short x, unsigned short y, unsigned short w, unsigned short h);
	// unsigned short sliko lahko raztegne celo do resolucije ~64K.. ce bojo meli monitorji vec piksov
	// kot to, pa samo spremeni "unsigned short" na "unsigned int" in smo reseni se za ksno tisocletje
	void ini(class GameManager& igra, const char* filePath) { init(igra, filePath, 0, 0, 720, 640); }
	void display(SDL_Renderer* ren);
	SDL_Surface returnSurface() { return *image_surface; }
	~Image();
private:
	SDL_Surface* image_surface = nullptr;
	SDL_Texture* image_texture = nullptr;
	SDL_Rect rect;
	bool flipped;
};
