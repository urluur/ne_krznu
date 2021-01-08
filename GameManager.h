#pragma once
#include <string>
class GameManager{
private:
	std::string player_name;
public:
	GameManager();
	void setPlayerName(std::string);
	std::string getPlayerName();
};
