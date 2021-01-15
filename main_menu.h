#pragma once

#include "function_definitions.h"
void vec(GameManager& igra);
void nastavitve(GameManager& igra);
void overworld(GameManager& igra);

void animacija(GameManager& igra, int stAnim);
void premakniNaXY(GameManager &igra, int &x, int &y, int final_x, int final_y, Image &img_overworld, Image &img_player);
void haltEnter(GameManager& igra, Image& img_press_enter, SDL_Event &ev_overworld);