#pragma once
#include "okno.h"

class Casovnik
{
private:
	class WindowManager* p_okno;
	static short sekunde, milisekunde;
	static bool paused;
public:
	friend class WindowManager;
	friend class GameManager;
	Casovnik();
	void setup(WindowManager &);
	static bool odstej();
	void set(short);
};
