#pragma once
#include "includes.h"
#include "okno.h"
#include "zvok.h"
#include "SDL_ttf.h"
#include "slika.h"
#include "ZivoBitje.h"
#include "igralec.h"
#include "tekst.h"

class GameManager {
public:
	WindowManager okno;
	SoundManager sound;
	SDL_Event event;
	Igralec igralec;
	//SDL_Joystick* joystick;//(testiram)
	bool adios = false;
	short trenutniNivo;
	bool getAdios() { return adios; }
	GameManager();
	int init();
	void handleEvents();
	const Uint8* keys = SDL_GetKeyboardState(NULL);
	void level(short&);
	void obnasanjeNaPolju();
	void farma();
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
	void branjeShranjenega(string&, short&);
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
	bool isPlayerCollidingAt(short, short, short, short);
	bool univerzalniTrk(short, short, short, short, short, short, short, short);
	void initNavadnaStamina();
	void initRisingStamina();
	void trkiOkolje();
	void trkiMiTjulni();
	void racuniStamino();
	void cleanupVectors();
private:
	class Image* jaz;
	vector <class komoucar*> enemy;
	vector <class Tjuln*> tjulni;
	class Image* stamina_wheel;
	bool konecLevela, semNaIzhodniLokaciji, staminadown, fillingStamina;
	bool rageMode = false; //rageMode je v alfa testingu (spremeni na true za ZELO tezko igro)
	bool w = false, a = false, s = false, d = false;
	bool completed; // zato da se spremeni main menu na koncu zgodbe
	short stAktiv[5], stNaspr[5], stTjuln[5];
	short hitrost, stamina, stTjulnFarma;
	const short farmPos[2][5] = {
		{1150, 60, 140, 1000, 1030},
		{100, 510, 400, 440, 60} };
	const short exitPos[2][5] = {
		{160, 1270, 230, 160, 150},
		{20, 520, 5, 5, 600} };
	short stevecNoge = 0;
};