#include "igra.h"

// preveri ce se dva kvadrata prekrivata
bool GameManager::univerzalniTrk(short x1, short y1, short w1, short h1, short x2, short y2, short w2, short h2) {
	if (x2 < x1 + w1 && x2 + w2 > x1 && y2 < y1 + h1 && y2 + h2 > y1) {
		return true;
	}
	else {
		return false;
	}
}

// preveri ali se kvadrat prekriva z igralcem
bool GameManager::isPlayerCollidingAt(short x, short y, short w, short h) {
	if (igralec.getX() < x + w && igralec.getX() + igralec.getW() > x && igralec.getY() < y + h && igralec.getY() + igralec.getH() > y) {
		return true;
	}
	else {
		return false;
	}
}

void GameManager::trkiOkolje() { // se klice ko se premikamo
	trkiMiTjulni(); // preverimo ali se igalec dotika tjulnov

	// preverimo se ostale nepremikajoce kvadrate (npr. farme in izhodne lokacije), ki so odvisne od nivvoja
	switch (trenutniNivo) {
	case 1:
		if (isPlayerCollidingAt(1110, 10, 170, 150)) {
			farma();
		}
		if (isPlayerCollidingAt(160, 660, 125, 60))
			semNaIzhodniLokaciji = true;
		else
			semNaIzhodniLokaciji = false;
		break;
	case 2:
		if (isPlayerCollidingAt(0, 460, 130, 120)) {
			farma();
		}
		if (isPlayerCollidingAt(1270, 520, 10, 200))
			semNaIzhodniLokaciji = true;
		else
			semNaIzhodniLokaciji = false;
		break;
	case 3:
		if (isPlayerCollidingAt(90, 350, 130, 120)) {
			farma();
		}
		if (isPlayerCollidingAt(230, 0, 70, 60))
			semNaIzhodniLokaciji = true;
		else
			semNaIzhodniLokaciji = false;
		break;
	case 4:
		if (isPlayerCollidingAt(990, 350, 190, 150)) {
			farma();
		}
		if (isPlayerCollidingAt(1130, 600, 30, 40)) {
			printf("sm na kolomiti\n");
		}
		if (isPlayerCollidingAt(160, 0, 10, 75))
			semNaIzhodniLokaciji = true;
		else
			semNaIzhodniLokaciji = false;
		break;
	case 5:
		if (isPlayerCollidingAt(1030, 60, 190, 120)) {
			farma();
		}
		if (isPlayerCollidingAt(0, 0, 1280, 40))
			semNaIzhodniLokaciji = true;
		else
			semNaIzhodniLokaciji = false;
		break;
	default:
		cerr << "Error: collision check" << trenutniNivo << endl;
	}
}

// preveri ali se igralec dotika tjulnov
void GameManager::trkiMiTjulni() {
	for (unsigned int i = 0; i < tjulni.size(); ++i) {
		if (isPlayerCollidingAt(tjulni.at(i)->getX(), tjulni.at(i)->getY(), tjulni.at(i)->getW(), tjulni.at(i)->getH())) {
			printf("Hvala lepa, resil si me!!!\n");
			for (unsigned int popravi_nasprotnike = 0; popravi_nasprotnike < enemy.size(); ++popravi_nasprotnike) {
				if (enemy.at(popravi_nasprotnike)->nosim > (int)i && enemy.at(popravi_nasprotnike)->nosim != -1) {
					--enemy.at(popravi_nasprotnike)->nosim;
				}
			}
			for (unsigned int popravi_aktiviste = 0; popravi_aktiviste < aktivisti.size(); ++popravi_aktiviste) {
				aktivisti.at(popravi_aktiviste)->nosim = -1;
			}

			delete tjulni.at(i);
			tjulni.erase(tjulni.begin() + i);
			--stTjuln[trenutniNivo - 1];
			break;
		}
	}
}