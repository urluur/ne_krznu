#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <iostream>

class Text {
public:
	Text(SDL_Renderer*, const std::string&, int, const std::string&, const SDL_Color&);
	void display(int, int, SDL_Renderer*) const;
	void update(SDL_Renderer*, const std::string&, const SDL_Color&);
	~Text();
private:
	SDL_Surface* text_surface = nullptr;
	SDL_Texture* text_texture = nullptr;
	mutable SDL_Rect text_rect;
	TTF_Font* font = nullptr;
};
