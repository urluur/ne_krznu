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
	friend class GameManager; // to odpravi nepotrebne funkcije getX, getY, a ni se popravljeno v programu
	void setX(short notr) { x = (notr < (1280 - w) && notr > 0) ? notr : x; }
	void setY(short notr) { y = (notr < (720 - h) && notr > 0) ? notr : y; }
	/*
	short getX() { return x; }
	short getY() { return y; }
	short getW() { return w; }
	short getH() { return h; }
	//*/
	// ManhattanDistance vrne razdaljo med dvema koordinatama
	inline short ManhattanDistance(short x1, short y1, short x2, short y2) { return short(abs(x1 - x2) + abs(y1 - y2)); }
};

class komoucar: public ZivoBitje {
private:
	float dest_x = 0, dest_y = 0; // spremen u float za ragemode
	float hitrost; // same here
public:
	short nosim = -1;
	komoucar();
	~komoucar();
	void rage() { hitrost = 1.2; } //1.2 za ragemode
	void chill() { hitrost = 1; }
	void initImg(class GameManager&, const char*, short, short);
	void updateImg(class GameManager&, const char*);
	void display(GameManager&);
	void zrcuniRandomDestinacijo();
	void setDest(short, short);
	bool sprehodNaRandomDestinacijo();
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

class Kepa: public Tjuln {
private:
	short to_go, done;
	GameManager* igra;
	bool ww, a, s, d, ignore_me;
	short hitrost;
public:
	friend class GameManager;
	friend class Igralec;
	Kepa(GameManager &);
	~Kepa();
	void startMoving();
	bool move();
};