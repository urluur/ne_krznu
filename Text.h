#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <iostream>

class Text {
public:
    Text(SDL_Renderer* renderer, const std::string& font_path, int font_size, const std::string& message_text, const SDL_Color& colour);
    void display(int x, int y, SDL_Renderer* renderer) const;
    void update(SDL_Renderer* renderer, const std::string& message_text, const SDL_Color& colour);

    ~Text();
private:
    SDL_Surface* text_surface = nullptr;
    SDL_Texture* text_texture = nullptr;
    mutable SDL_Rect text_rect;

    TTF_Font* font = nullptr;
};
