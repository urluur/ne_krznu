#pragma once
#include "WindowManager.h"
#include "SoundManager.h"
#include "Igralec.h"
#include <string>
class GameManager{
private:
public:
	WindowManager okno;
	SoundManager zvok;
	Igralec igralec;
	GameManager();

};