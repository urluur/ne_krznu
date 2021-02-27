#pragma once
#include <iostream>
#include <string>
using namespace std;

class Igralec
{
private:
	string ime;
	unsigned short x, y;
public:
	void setName();
	string getName() { return ime; }
	void setName(string);
	void coutName();
	Igralec() { ime = "bumbar"; }
	unsigned short getX() { return x; }
	unsigned short getY() { return y; }
	void setX(unsigned short notr) { x = (notr < 1222 && notr > 0) ? notr:x; }
	void setY(unsigned short notr) { y = (notr < 592 && notr > 0) ? notr:y; }
};
