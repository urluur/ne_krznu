#pragma once
#include "slika.h"
#include "igra.h"
class komoucar
{
private:
	unsigned short x, y, dest_x = 10, dest_y = 10;
	short hitrost;
	const unsigned short w=29, h=64;
	class Image* img = nullptr;
public:
	komoucar();
	~komoucar();
	unsigned short getX() { return x; }
	unsigned short getY() { return y; }
	void setX(unsigned short notr) { x = (notr < (1280 - getW()) && notr > 0) ? notr : x; }
	void setY(unsigned short notr) { y = (notr < (720 - getH()) && notr > 0) ? notr : y; }
	unsigned short getW() { return w; }
	unsigned short getH() { return h; }
	void initImg(class GameManager&, const char*, unsigned short, unsigned short);
	void updateImg(class GameManager&);
	void display(class GameManager&);
	void zrcuniRandomDestinacijo();
	bool sprehodNaRandomDestinacijo();
};
