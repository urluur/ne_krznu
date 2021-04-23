#pragma once
#include <iostream>
#include <string>
using namespace std;

class Igralec {
private:
	string ime;
	short x, y;
	const short w = 29, h = 64;
	bool sepremikam = false;
public:
	friend class GameManager;
	friend class Kepa;
	friend class ponovitev;
	void setName();
	string getName() { return ime; }
	void setName(string);
	void coutName();
	Igralec();
	short getX() { return x; }
	short getY() { return y; }
	// setX in setY nastavita pozicijo igralca na zeljeno mesto, a le ce ta ni izven zaslona
	void setX(short notr) { x = (notr < (1280 - w) && notr > 0) ? notr : x; }
	void setY(short notr) { y = (notr < (720 - h) && notr > 0) ? notr : y; }
	short getW() { return w; }
	short getH() { return h; }
	void sepremika(bool resnica) { sepremikam = resnica; }
	bool sepremika() { return sepremikam; }
};
