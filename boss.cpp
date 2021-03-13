#include "igra.h"

void GameManager::boss() {
	/* testiram.. dokler ni petni nivo dokoncan moramo glavnega nasprotnika ubiti z presledkom
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


void GameManager::kepaOrReflect() {
	printf("kepa or reflect");
}

void GameManager::vrziTjulna() {
	printf("vrzi tjulna");
}

void GameManager::udari() {
	// udarimo bossa
	if (stNaspr[trenutniNivo - 1] > 0) {
		if (isPlayerCollidingAt(enemy.at(0)->getX() - 50, enemy.at(0)->getY() - 50, enemy.at(0)->getW() + 100, enemy.at(0)->getH() + 100)) {
			if (stamina >= 99) {
				stamina = 0;
				if (boss_hp > 0) {
					boss_hp-=10;
					boss_red_hp->init(*this, "common/img/red.png", 140, 10, boss_hp * 10, 20);
				}
				printf("BUM!");
				predvajiBOOM();
				brisiBossa();
			}
		}
	}
}

void GameManager::predvajiBOOM() {
	static short stevec = 1;
	if (boss_hp <= 1) {
		sound.predvajaj("common/sounds/5paw_oh.wav");
	}
	else {
		switch (stevec) {
		case 1:
			sound.predvajaj("common/sounds/1boom.wav");
			++stevec;
			break;
		case 2:
			sound.predvajaj("common/sounds/2bem.wav");
			++stevec;
			break;
		case 3:
			sound.predvajaj("common/sounds/3bap.wav");
			++stevec;
			break;
		case 4:
			sound.predvajaj("common/sounds/4badabapbum.wav");
			stevec = 1;
			break;
		}
	}
}

void GameManager::brisiBossa() {
	if (boss_hp <= 1) {
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