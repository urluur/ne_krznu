#pragma once
#include "function_definitions.h"
#include "WindowManager.h"
#include "SoundManager.h"
#include "Igralec.h"
#include <iostream>
#include <string>
#include <SDL_image.h>
#include "SDL_ttf.h"
using namespace std;

struct koordinati {
	unsigned short x, y;
	unsigned short spawn_x, spawn_y;
};
struct tjulen {
	koordinati kje;
};
struct aktivist {
	koordinati kje;
};
struct nasprotnik {
	koordinati kje;
};

class GameManager{
public:
	WindowManager okno;
	SoundManager sound;
	SDL_Event event;
	Igralec igralec;
	GameManager();
	int init();
	const Uint8* keys = SDL_GetKeyboardState(NULL);
	void level(short& nivo, GameManager& igra);
	void pripraviVse();
	void pripraviOdzadje(GameManager& igra);
	void haltEnter(short nivo, GameManager& igra);
	void updateMap();
	bool isCompleted();
	void setCompleted(bool resnica);
	short getNivo();
	void setNivo(short lvl);
	void preveriEsc(short& nivo);
	void cleanup();
private:
	//bom pol spremenu na private
	bool konecLevela;
	bool completed; // zato da se spremeni main menu na koncu zgodbe
	short trenutniNivo;
};
