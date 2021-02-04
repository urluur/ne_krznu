#pragma once
#include <SDL.h>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <windows.h>
#include <MMSystem.h>
#include <fstream>
#include <SDL_mixer.h>
#include <string>
#include <cstring>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "SoundManager.h"
#include "GameManager.h"
#include "igralec.h"
#include "Text.h"
#include "Image.h"

void zasilnoShranjevanje(class GameManager& igra);
void branjeShranjenega(class GameManager& igra);
void branjeLestvice(GameManager& igra);
void shranjevanjeLestvice(GameManager& igra);
void deleteSave(GameManager& igra);