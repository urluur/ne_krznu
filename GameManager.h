#pragma once
#include "includes.h"
#include "WindowManager.h"
#include "SoundManager.h"
#include "Igralec.h"
#include "SDL_ttf.h"
#include "Image.h"

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

class GameManager {
public:
	WindowManager okno;
	SoundManager sound;
	SDL_Event event;
	Igralec igralec;
	GameManager();
	int init();
	const Uint8* keys = SDL_GetKeyboardState(NULL);
	void level(short& nivo);
	void pripraviVse();
	void haltEnter(short nivo);
	void updateMap();
	bool isCompleted();
	void setCompleted(bool resnica);
	short getNivo();
	void setNivo(short lvl);
	void preveriEsc(short& nivo);
	void zasilnoShranjevanje();
	void branjeShranjenega();
	void branjeLestvice();
	void shranjevanjeLestvice();
	void deleteSave();
	void cleanup();

private:
	bool konecLevela;
	bool completed; // zato da se spremeni main menu na koncu zgodbe
	short trenutniNivo;
	short int stAktiv[5] = { 4, 3, 2, 1, 0 };
	short int stNaspr[5] = { 3, 5, 7, 10, 1 };
	short int stTjuln[5] = { 5, 10, 15, 20, 0 };
};