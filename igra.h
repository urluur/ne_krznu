#pragma once
#include "includes.h"
#include "okno.h"
#include "zvok.h"
#include "igralec.h"
#include "SDL_ttf.h"
#include "slika.h"

class GameManager {
public:
	WindowManager okno;
	SoundManager sound;
	SDL_Event event;
	Igralec igralec;
	SDL_Joystick* joystick;
	GameManager();
	int init();
	void handleEvents();
	const Uint8* keys = SDL_GetKeyboardState(NULL);
	void level(short&);
	void pripraviVse();
	void haltEnter(short);
	void updateMap();
	bool isCompleted() { return completed; }
	void setCompleted(bool resnica);
	short getNivo() { return trenutniNivo; }
	void setNivo(short lvl) { trenutniNivo = lvl; }
	void preveriEsc(short&);
	void zasilnoShranjevanje();
	void branjeShranjenega();
	void branjeLestvice();
	void shranjevanjeLestvice();
	void deleteSave();
	void cleanup();
	bool checkQuit();
	bool checkEnter();
	bool checkUp();
	bool checkDown();
	bool checkLeft();
	bool checkRight();
private:
	vector <class Image*> jaz;
	bool konecLevela, adios;
	bool w = false, a = false, s = false, d = false;
	bool completed; // zato da se spremeni main menu na koncu zgodbe
	short trenutniNivo;
	short stAktiv[5] = { 4, 3, 2, 1, 0 };
	short stNaspr[5] = { 3, 5, 7, 10, 1 };
	short stTjuln[5] = { 5, 10, 15, 20, 0 };
	short hitrost = 4;
};