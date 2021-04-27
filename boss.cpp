#include "igra.h"
#include "menu.h"

void GameManager::boss() {
	// gledamo zadetke vseh kep
	for (unsigned int i = 0; i < kepe.size(); ++i) {
		// preverimo ce smo zadeli nasprotnika s kepo
		if (!enemy.empty()) { // izognemo se izjemi, ce smo premagali nasprotnika
			if (univerzalniTrk(enemy.at(0)->x, enemy.at(0)->y, enemy.at(0)->w, enemy.at(0)->h,
				kepe.at(i)->x, kepe.at(i)->y, kepe.at(i)->w, kepe.at(i)->h)) {
				if (!kepe.at(i)->ignore_me) { // kepa ima upliv le ob prvem dotiku
					kepe.at(i)->ignore_me = true;
					// nocemo, da od blizu zelo hitro mecemo kepe, a vseeno ni pravicno da so na zaslonu veliko casa
					kepe.at(i)->to_go /= 2;
					//nasprotniku odstejemo malce zivljenja
					if (boss_hp > 0) {
						boss_hp -= 3;
						if (rageMode) {
							trenutne_tocke += Casovnik::sekunde * zivljenja * trenutniNivo;
						}
						else {
							trenutne_tocke += (Casovnik::sekunde + zivljenja) / 10;
						}
						boss_red_hp->init(*this, "common/img/red.png", 140, 10, boss_hp * 10, 20);
					}
					predvajiBOOM(); // predvajamo eden od zvokov ob udarcu
					brisiBossa(); // preverimo in izbrisemo nasprotnika ce je treba
				}
			}
		}
	}

	// cez kepe gremo se enkrat v novem loopu zaradi moznega brisanja
	for (unsigned int i = 0; i < kepe.size(); ++i) {
		// premaknemo kepo, ce je sla dovolj dalec jo zbrisemo
		if (!kepe.at(i)->move()) {
			delete kepe.at(i);
			kepe.erase(kepe.begin() + i);
		}
	}

	// gledamo zadetke slabih kep
	for (unsigned int i = 0; i < slabe_kepe.size(); ++i) {
		if (!enemy.empty()) {
			// ali nas je kepa zadela
			if (isPlayerCollidingAt(slabe_kepe.at(i)->x, slabe_kepe.at(i)->y, slabe_kepe.at(i)->w, slabe_kepe.at(i)->h)) {
				if (!slabe_kepe.at(i)->ignore_me) { // kepa ima upliv le ob prvem dotiku
					slabe_kepe.at(i)->ignore_me = true;
					// nocemo, da od blizu zelo hitro mecemo slabe_kepe, a vseeno ni pravicno da so na zaslonu veliko casa
					slabe_kepe.at(i)->to_go /= 2;
					// prever a crknes
					perfect_run = false;
					sound.predvajaj("common/sounds/au.wav");
					--zivljenja;
					updateSrcki();
					if (!zivljenja) {
						deleteOnlySave();
						if (Mix_PlayingMusic()) {
							Mix_PauseMusic();
						}
						animacija(*this, -1);
						cleanup();
						exit(0);
					}
				}
			}
		}
	}

	// cez slabe_kepe gremo se enkrat v novem loopu zaradi moznega brisanja
	for (unsigned int i = 0; i < slabe_kepe.size(); ++i) {
		if (!slabe_kepe.at(i)->move()) {
			delete slabe_kepe.at(i);
			slabe_kepe.erase(slabe_kepe.begin() + i);
		}
	}

	if (rageMode) {
		if (cajt.sekunde % 2 == 0 && slabe_kepe.size() == 0 && enemy.size() > 0) {
			if (enemy.at(0)->nosim == -1) {
				slabe_kepe.push_back(new Kepa(*this, enemy.at(0)));
			}
		}
	}
	else {
		if (cajt.sekunde % 4 == 0 && slabe_kepe.size() == 0 && enemy.size() > 0) {
			if (enemy.at(0)->nosim == -1) {
				slabe_kepe.push_back(new Kepa(*this, enemy.at(0)));
			}
		}
	}
}

void GameManager::kepaOrReflect() {
	// ustvarimo novo kepo
	if (kepe.size() < 3) { // na zaslonu so lahko najvec 3 kepe
		kepe.push_back(new Kepa(*this));
	}
}

void GameManager::vrziTjulna() {
	// na zaslonu je lahko najvec 1 tjulen
	if (stTjuln[trenutniNivo - 1] == 0) {
		tjulni.push_back(new Tjuln);
		tjulni.at(0)->initAt(*this, "common/img/tjuln.png", igralec.x, igralec.y); // tjulna prikazemo pri igralcu
		++stTjuln[trenutniNivo - 1];
	}
}

void GameManager::udari() {
	// udarimo bossa
	if (stNaspr[trenutniNivo - 1] > 0) { // izognemo se izjemi ce ni naprotnika
		// preverimo ce sta igralec in nasprotnik dovolj blizu
		if (isPlayerCollidingAt(enemy.at(0)->x - 50, enemy.at(0)->y - 50, enemy.at(0)->w + 100, enemy.at(0)->h + 100)) {
			// da udarimo potrebujemo celo vzdrzljivost
			if (stamina >= 99) {
				stamina = 0; // vzdrzljivost nam pade na 0, a ni oznacena kot popolnoma prazna
				if (boss_hp > 0) { // nasprotnikovo zivljenje se mocno zmanjsa
					boss_hp -= 10;
					boss_red_hp->init(*this, "common/img/red.png", 140, 10, boss_hp * 10, 20);
					if (rageMode) {
						trenutne_tocke += Casovnik::sekunde * zivljenja * trenutniNivo;
					}
					else {
						trenutne_tocke += (Casovnik::sekunde * zivljenja) / 3;
					}
				}
				predvajiBOOM();
				brisiBossa(); // preverimo ali smo nasprotnika pokoncali
			}
		}
	}
}

// se klice ko udarimo ali zadanjemo basprotnika
void GameManager::predvajiBOOM() {
	static short stevec = 1;
	if (boss_hp <= 0) { // ko ga pokoncamo se predvaja poseben zvok
		sound.predvajaj("common/sounds/5paw_oh.wav");
	}
	else {
		// drugace se zvoki predvajajo po vrsti
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
	if (boss_hp < 1) { // ce nasprotnik nima vec zivljenja ga brisemo
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
		cajt.paused = true;
	}
}