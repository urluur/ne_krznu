#include "igra.h"

void GameManager::boss() {
	//* testiram.. dokler ni petni nivo dokoncan moramo glavnega nasprotnika ubiti z presledkom
	if (keys[SDL_SCANCODE_SPACE]) {
		if (boss_hp > 0) {
		--boss_hp;
		boss_red_hp->init(*this, "common/img/red.png", 140, 10, boss_hp * 10, 20);
		}
		else {
			if (stNaspr[trenutniNivo - 1] > 0) {
				--stNaspr[trenutniNivo - 1];
			}
			if (!enemy.empty()) {
				for (unsigned int i = 0; i < enemy.size(); ++i) {
					delete enemy.at(i);
				}
				enemy.clear();
			}
			enemy.shrink_to_fit();
		}
	}
	//*/
}