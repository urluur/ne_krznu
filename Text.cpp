#include "Text.h"

Text::Text(SDL_Renderer* ren, const std::string& font_path, int font_size, const std::string& message_text, const SDL_Color& colour) {
	SDL_QueryTexture(text_texture, NULL, NULL, &text_rect.w, &text_rect.h);
	font = TTF_OpenFont(font_path.c_str(), font_size);

	if (!font)
		std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
	auto text_surface = TTF_RenderText_Solid(font, message_text.c_str(), colour);

	if (!text_surface)
		std::cerr << "Failed to create text surface: " << TTF_GetError() << std::endl;
	text_texture = SDL_CreateTextureFromSurface(ren, text_surface);
	if (!text_texture)
		std::cerr << "Failed to create text texture: " << TTF_GetError() << std::endl;
	int w, h;
	if (TTF_SizeText(font, message_text.c_str(), &w, &h))
		std::cerr << "TTF_SizeText error!" << std::endl;

	text_rect.w = w;
	text_rect.h = h;
}

void Text::display(int x, int y, SDL_Renderer* ren) const {
	text_rect.x = x;
	text_rect.y = y;
	SDL_RenderCopy(ren, text_texture, NULL, &text_rect);
}

void Text::update(SDL_Renderer* ren, const std::string& message_text, const SDL_Color& colour) {
	text_surface = TTF_RenderText_Solid(font, message_text.c_str(), colour);
	if (!text_surface)
		std::cerr << "Failed to create text surface: " << TTF_GetError() << std::endl;
	text_texture = SDL_CreateTextureFromSurface(ren, text_surface);
	if (!text_texture)
		std::cerr << "Failed to create text texture: " << TTF_GetError() << std::endl;
}

Text::~Text() {
	TTF_CloseFont(font);
	SDL_FreeSurface(text_surface);
	SDL_DestroyTexture(text_texture);
}