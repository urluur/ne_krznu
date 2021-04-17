#pragma once
#include "okno.h"

class Casovnik
{
private:
	short sekunde, milisekunde;
	class WindowManager* p_okno;
public:
	Casovnik();
	void setup(WindowManager &);
	bool odstej();
	void set(short);
};
