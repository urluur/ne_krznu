#pragma once
#include "includes.h"

// v main_menu.cpp
void vec(GameManager&);
void nastavitve(GameManager&);

// v overworld.cpp
void overworld(GameManager&);
void animacija(GameManager&, int);
void premakniNaXY(GameManager&, short&, short&, short, short, Image&, Image&, short);
void narisiFarmeAliDosezke(GameManager&, short);