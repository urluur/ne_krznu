#include "GameManager.h"
GameManager::GameManager() {
	//definiram privzete lastnosti
}
void GameManager::setPlayerName(std::string s) {
	player_name = s;
}
std::string GameManager::getPlayerName() {
	return player_name;
}