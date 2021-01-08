#pragma once
#include "WindowManager.h"
#include "SoundManager.h"
#include "Igralec.h"
#include <iostream>
#include <string>
using namespace std;
class GameManager{
private:
public:
	WindowManager okno;
	SoundManager sound;
	Igralec igralec;
	GameManager();
	int init(GameManager& igra);

};