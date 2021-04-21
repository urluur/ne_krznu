#pragma once
#include <SDL.h>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <SDL_mixer.h>
#include <string>
#include <cstring>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <vector>
#include <conio.h>

#include "okno.h"
#include "zvok.h"
#include "SDL_ttf.h"
#include "slika.h"
#include "ZivoBitje.h"
#include "tekst.h"
#include "igralec.h"
#include "Casovnik.h"

class GameManager {
public:
	WindowManager okno;
	SoundManager sound;
	Igralec igralec;
	SDL_Event event;
	Casovnik cajt;
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
	void deleteOnlySave();
	void deleteLeaderboard();
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
	void pause();
	void popravi();
	void updateSrcki();
	void boss();
	void kepaOrReflect();
	void vrziTjulna();
	void udari();
	void predvajiBOOM();
	void brisiBossa();
	void preveriSmrt(short i);
	void cmdLevels();
	void perfectRun(bool notr) { perfect_run = notr; }
	bool perfectRun() { return perfect_run; }
	void rageModeSet(bool notr) { rageMode = notr; }
	bool returnRageMode() { return rageMode; }
	friend class Kepa;
	friend void overworld(GameManager&);
	friend void premakniNaXY(GameManager&, short&, short&, short, short, Image&, Image&, short);
private:
	class Image* jaz, *srcki;
	vector <class komoucar*> enemy, aktivisti;
	vector <class Tjuln*> tjulni;
	vector <class Kepa*> kepe, slabe_kepe;
	class Image* stamina_wheel;
	string najboljsi[5];
	int najbolse[5];
	bool konecLevela, perfect_run, semNaIzhodniLokaciji, staminadown, fillingStamina;
	bool rageMode = false; //rageMode je v alfa testingu (spremeni na true za ZELO tezko igro)
	bool w = false, a = false, s = false, d = false;
	bool completed; // zato da se spremeni main menu na koncu zgodbe
	short stAktiv[5], stNaspr[5], stTjuln[5];
	short hitrost, stamina, stTjulnFarma, zivljenja, skupne_tocke, trenutne_tocke;
	const short farmPos[2][5] = {
		{1150, 60, 140, 1000, 1030},
		{100, 510, 400, 440, 60} };
	const short exitPos[2][5] = {
		{160, 1270, 230, 160, 150},
		{20, 520, 5, 5, 600} };
	short stevecNoge = 0;
	short boss_hp;
	class Image* boss_red_hp;
};