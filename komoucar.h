#pragma once
#include "slika.h"
#include "igra.h"
class komoucar {
private:
	short x, y, dest_x = 0, dest_y = 0;
	short hitrost;
	const short w = 29, h = 64;
	class Image* img = nullptr;
public:
	short nosim = -1;
	komoucar();
	~komoucar();
	short getX() { return x; }
	short getY() { return y; }
	void setX(short notr) { x = (notr < (1280 - getW()) && notr > 0) ? notr : x; }
	void setY(short notr) { y = (notr < (720 - getH()) && notr > 0) ? notr : y; }
	void rage() { hitrost = 2; }
	void chill() { hitrost = 1; }
	short getW() { return w; }
	short getH() { return h; }
	void initImg(class GameManager&, const char*, short, short);
	void updateImg(class GameManager&);
	void display(class GameManager&);
	void zrcuniRandomDestinacijo();
	void setDest(short, short);
	bool sprehodNaRandomDestinacijo();
};
