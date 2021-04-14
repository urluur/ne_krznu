#include "igra.h"

void GameManager::boss() {
	for (unsigned int i = 0; i < kepe.size(); ++i) {
		// preverimo ce smo zadeli nasprotnika
		if (!enemy.empty()) {
			if (univerzalniTrk(enemy.at(0)->x, enemy.at(0)->y, enemy.at(0)->w, enemy.at(0)->h,
					kepe.at(i)->x, kepe.at(i)->y, kepe.at(i)->w, kepe.at(i)->h)) {
				if (!kepe.at(i)->ignore_me) {
					kepe.at(i)->ignore_me = true;
					// nocemo, da od blizu zelo hitro mecemo kepe, a vseeno ni pravicno da so na zaslonu veliko casa
					kepe.at(i)->to_go /= 2;
					if (boss_hp > 0) {
						boss_hp -= 3;
						boss_red_hp->init(*this, "common/img/red.png", 140, 10, boss_hp * 10, 20);
					}
					predvajiBOOM();
					brisiBossa();
				}
			}
		}
	}
	for (unsigned int i = 0; i < kepe.size(); ++i) {
		// premaknemo kepo, ce je sla dovolj dalec jo zbrisemo
		if (!kepe.at(i)->move()) {
			delete kepe.at(i);
			kepe.erase(kepe.begin()+i);
		}
	}
	
	// naredi: previr skoz use tjulne ce so se premaknli od zacetne pozicije za neki alpa ce se jih dotika nasprotnik
}

void GameManager::kepaOrReflect() {
	if (kepe.size() < 3) {
		kepe.push_back(new Kepa(*this));
	}
}

void GameManager::vrziTjulna() {
	printf("vrzi tjulna");
	if (stTjuln[trenutniNivo - 1] == 0) {
		tjulni.push_back(new Tjuln);
		tjulni.at(0)->initAt(*this, "common/img/tjuln.png", igralec.x, igralec.y);
		++stTjuln[trenutniNivo - 1];
	}
}

void GameManager::udari() {
	// udarimo bossa
	if (stNaspr[trenutniNivo - 1] > 0) {
		if (isPlayerCollidingAt(enemy.at(0)->x - 50, enemy.at(0)->y - 50, enemy.at(0)->w + 100, enemy.at(0)->h + 100)) {
			if (stamina >= 99) {
				stamina = 0;
				if (boss_hp > 0) {
					boss_hp -= 10;
					boss_red_hp->init(*this, "common/img/red.png", 140, 10, boss_hp * 10, 20);
				}
				predvajiBOOM();
				brisiBossa();
			}
		}
	}
}

void GameManager::predvajiBOOM() {
	static short stevec = 1;
	if (boss_hp <= 0) {
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
	if (boss_hp < 1) {
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