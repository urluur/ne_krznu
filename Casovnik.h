#pragma once
#include "okno.h"

class Casovnik
{
private:
	static short sekunde, milisekunde;
	static bool paused;
public:
	friend class WindowManager;
	friend class GameManager;
	Casovnik();
	static bool odstej();
	void set(short);
};
