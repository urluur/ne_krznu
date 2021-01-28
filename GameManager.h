#pragma once
#include "function_definitions.h"
#include "WindowManager.h"
#include "SoundManager.h"
#include "Igralec.h"
#include <iostream>
#include <string>
#include <SDL_image.h>
using namespace std;
class GameManager{
private:
	//bom pol spremenu na private
	bool konecLevela;
	bool completed;
public:
	WindowManager okno;
	SoundManager sound;
	SDL_Event event;
	Igralec igralec;
	GameManager();
	int init();
	const Uint8* keys = SDL_GetKeyboardState(NULL);
	void level(int &nivo);
	void pripraviPolje();
	void haltEnter(int nivo);
	void updateMap();
	bool isCompleted();
	void setCompleted();
};