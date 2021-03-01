#pragma once
#include <iostream>
#include <string>
using namespace std;

class Igralec
{
private:
	string ime;
	unsigned short x, y;
	const unsigned short w=29, h=64;
public:
	void setName();
	string getName() { return ime; }
	void setName(string);
	void coutName();
	Igralec() { ime = "bumbar"; }
	unsigned short getX() { return x; }
	unsigned short getY() { return y; }
	void setX(unsigned short notr) { x = (notr < (1280 - getW()) && notr > 0) ? notr:x; }
	void setY(unsigned short notr) { y = (notr < (720 - getH()) && notr > 0) ? notr:y; }
	unsigned short getW() { return w; }
	unsigned short getH() { return h; }
};
