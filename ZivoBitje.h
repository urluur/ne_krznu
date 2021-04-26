#pragma once
#include <iostream>
#include <string>
#include "igra.h"

using namespace std;

class ZivoBitje {
protected:
	short x=0, y=0, w=0, h=0;
	class Image* img = nullptr;
public:
	friend class GameManager;
	void setX(short notr) { x = (notr < (1280 - w) && notr > 0) ? notr : x; }
	void setY(short notr) { y = (notr < (720 - h) && notr > 0) ? notr : y; }
	// ManhattanDistance vrne razdaljo med dvema koordinatama
	inline short ManhattanDistance(short x1, short y1, short x2, short y2) { return short(abs(x1 - x2) + abs(y1 - y2)); }
};

class komoucar: public ZivoBitje {
private:
	short dest_x = 0, dest_y = 0; // spremen u float za ragemode
	short hitrost; // same here
public:
	friend class ponovitev;
	friend class Kepa;
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
};

class Tjuln: public ZivoBitje {
public:
	friend class ponovitev;
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
	friend class ponovitev;
	friend class GameManager;
	friend class Igralec;
	Kepa(GameManager &);
	~Kepa();
	void startMoving();
	Kepa(GameManager&, komoucar*);
	void startMoving(komoucar*);
	bool move();
};