#pragma once
#include "slika.h"
#include "igra.h"
class Tjuln {
private:
	short x = 0, y = 0;
	const short w = 63, h = 42; // odvisno od slike
	class Image* img = nullptr;
	bool jeNaFarmi;
public:
	Tjuln();
	~Tjuln();
	short getX() { return x; }
	short getY() { return y; }
	short getW() { return w; }
	short getH() { return h; }
	void setX(short notr) { x = notr; }
	void setY(short notr) { y = notr; }
	void initImg(class GameManager&, const char*);
	void display(class GameManager&);
};
