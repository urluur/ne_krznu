#pragma once
#include "includes.h"

// v main_menu.cpp
void vec(GameManager& igra);
void nastavitve(GameManager& igra);

// v overworld.cpp
void overworld(GameManager& igra);
void animacija(GameManager& igra, int stAnim);
void premakniNaXY(GameManager &igra, short &mov_x, short &mov_y, short to_x, short to_y, Image &img_overworld, Image &img_player, short nivo);
void narisiFarmeAliDosezke(GameManager& igra, short nivo);
