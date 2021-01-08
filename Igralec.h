#pragma once
#include <string>
class Igralec
{
private:
	std::string ime;
public:
	void setName();
	void setName(std::string);
	std::string getName();
	Igralec();
	~Igralec();
};
