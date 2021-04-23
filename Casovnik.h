#pragma once
#include "okno.h"
#include <vector>

class Casovnik
{
private:
	static short sekunde, milisekunde;
	static bool paused;
public:
	friend class WindowManager;
	friend class GameManager;
	friend class ponovitev;
	Casovnik();
	static bool odstej();
	void set(short);
};
