#pragma once
#include <iostream>
#include <string>
#include "igra.h"

using namespace std;

class ZivoBitje {
protected:
	short x, y, w, h;
	class Image* img = nullptr;
public:
	void setX(short notr) { x = (notr < (1280 - getW()) && notr > 0) ? notr : x; }
	void setY(short notr) { y = (notr < (720 - getH()) && notr > 0) ? notr : y; }
	short getX() { return x; }
	short getY() { return y; }
	short getW() { return w; }
	short getH() { return h; }
};

class komoucar: public ZivoBitje {
private:
	short dest_x = 0, dest_y = 0; // spremen u float za ragemode
	short hitrost; // same here
public:
	short nosim = -1;
	komoucar();
	~komoucar();
	void rage() { hitrost = 2; } //1.2 za ragemode
	void chill() { hitrost = 1; }
	void initImg(class GameManager&, const char*, short, short);
	void updateImg(class GameManager&, const char*);
	void display(GameManager&);
	void zrcuniRandomDestinacijo();
	void setDest(short, short);
	bool sprehodNaRandomDestinacijo();
	// ManhattanDistance vrne razdaljo med dvema koordinatama
	inline short ManhattanDistance(short x1, short y1, short x2, short y2) { return short(abs(x1 - x2) + abs(y1 - y2)); }
};

class Tjuln: public ZivoBitje {
public:
	short nosilec = -1;
	Tjuln();
	~Tjuln();
	void initImg(class GameManager&, const char*);
	void display(class GameManager&);
	void updateImg(GameManager&);
	void initAt(class GameManager&, const char*, short, short);
};

class Kepa : public Tjuln {
public:
	short to_go, done;
	Kepa();
	~Kepa();
};