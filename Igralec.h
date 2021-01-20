#pragma once
#include <string>
class Igralec
{
private:
	std::string ime = "bumbar";
public:
	void setName();
	void setName(std::string);
	std::string getName();
	Igralec();
	~Igralec();
};
