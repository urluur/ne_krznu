#pragma once
#include "WindowManager.h"
#include "SoundManager.h"
#include "Igralec.h"
#include <iostream>
#include <string>
#include <SDL_image.h>
using namespace std;
class GameManager{
private:
public:
	WindowManager okno;
	SoundManager sound;
	Igralec igralec;
	GameManager();
	int init(GameManager& igra);
	const Uint8* keys = SDL_GetKeyboardState(NULL);
	int level(int nivo);
};