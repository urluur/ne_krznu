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
	void setName();
	string getName() { return ime; }
	void setName(string);
	void coutName();
	Igralec() { ime = "bumbar"; }
	short getX() { return x; }
	short getY() { return y; }
	// setX in setY nastavita pozicijo igralca na zeljeno mesto, a le ce ta ni izven zaslona
	void setX(short notr) { x = (notr < (1280 - getW()) && notr > 0) ? notr : x; }
	void setY(short notr) { y = (notr < (720 - getH()) && notr > 0) ? notr : y; }
	short getW() { return w; }
	short getH() { return h; }
	void sepremika(bool resnica) { sepremikam = resnica; }
	bool sepremika() { return sepremikam; }
};
