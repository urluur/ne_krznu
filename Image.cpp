#include "Image.h"

Image::Image() {
	rect.x = 0;
	rect.y = 0;
	rect.w = 0;
	rect.h = 0;
	flipped = false;
}

Image::Image(SDL_Renderer* ren, const char* filePath, unsigned short x, unsigned short y, unsigned short w, unsigned short h) {
	if (image_texture != nullptr && image_surface != nullptr) {
		SDL_FreeSurface(image_surface);
		SDL_DestroyTexture(image_texture);
	}

	image_surface = IMG_Load(filePath);

	image_texture = SDL_CreateTextureFromSurface(ren, image_surface);

	flipped = (w <= 0) ? true : false;

	w = (w <= 0) ? w *= -1 : w *= 1;

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
}

void Image::init(GameManager& igra, const char* filePath, unsigned short x, unsigned short y, unsigned short w, unsigned short h) {
	if (image_texture != nullptr && image_surface != nullptr) {
		SDL_FreeSurface(image_surface);
		SDL_DestroyTexture(image_texture);
	}

	image_surface = IMG_Load(filePath);
	image_texture = SDL_CreateTextureFromSurface(igra.okno.ren, image_surface);

	flipped = (w <= 0) ? true : false;
	w = (w <= 0) ? w *= -1 : w *= 1;

	rect.x = igra.okno.scaleCal(x);
	rect.y = igra.okno.scaleCal(y);
	rect.w = igra.okno.scaleCal(w);
	rect.h = igra.okno.scaleCal(h);
}

void Image::display(SDL_Renderer* ren) {
	if (!flipped)
		SDL_RenderCopy(ren, image_texture, NULL, &rect);
	else
		SDL_RenderCopyEx(ren, image_texture, NULL, &rect, 0, NULL, SDL_FLIP_HORIZONTAL);
}

Image::~Image() {
	SDL_FreeSurface(image_surface);
	SDL_DestroyTexture(image_texture);
}