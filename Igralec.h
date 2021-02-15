#pragma once
#include <iostream>
#include <string>
using namespace std;

class Igralec
{
private:
	string ime;
public:
	void setName();
	void setName(std::string);
	string getName() { return ime; }
	void coutName();
	Igralec() { ime = "bumbar"; }
};
