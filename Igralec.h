#pragma once
#include <iostream>
#include <string>
using namespace std;

class Igralec
{
private:
	string ime = "bumbar";
public:
	void setName();
	void setName(std::string);
	string getName();
	void coutName();
	Igralec();
};
