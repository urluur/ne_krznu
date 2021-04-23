#include "ponovitev.h"

koordinati::koordinati() {
	x = 0;
	y = 0;
}

zapisek::zapisek() {
	nivo = 0;
	st_tock = 0;
	st_polje = 0;
	st_farma = 0;
}

ponovitev::ponovitev(GameManager &notr) {
	igra = &notr;
	lastSnapTime = 0;
	snapInterval = 3; // na vsake tri sekunde se bo shranjevalo;
}

void ponovitev::checkSnap() {
	if ((Casovnik::sekunde > lastSnapTime && !Casovnik::paused) || Casovnik::sekunde == lastSnapTime - snapInterval) {
		lastSnapTime = Casovnik::sekunde;
		snapShot();
		printf("*snap*\n");
	}
}

void ponovitev::snapShot() {
	class zapisek temp;
	class koordinati temp_koordinati;

	// zapis info
	temp.nivo = igra->trenutniNivo;
	temp.st_tock = igra->trenutne_tocke;
	temp.st_polje = igra->stTjuln[igra->trenutniNivo];
	temp.st_farma = igra->stTjulnFarma;

	// zapis igralca
	temp.snap_igralec.x = igra->igralec.x;
	temp.snap_igralec.y = igra->igralec.y;

	// zapis nasprotnikov
	for (unsigned int i = 0; i < igra->enemy.size(); ++i) {
		temp_koordinati.x = igra->enemy.at(i)->x;
		temp_koordinati.y = igra->enemy.at(i)->y;
		temp.snap_nasprotniki.push_back(temp_koordinati);
	}

	// zapis aktivistov
	for (unsigned int i = 0; i < igra->aktivisti.size(); ++i) {
		temp_koordinati.x = igra->aktivisti.at(i)->x;
		temp_koordinati.y = igra->aktivisti.at(i)->y;
		temp.snap_aktivisti.push_back(temp_koordinati);
	}

	// zapis tjulnov
	for (unsigned int i = 0; i < igra->tjulni.size(); ++i) {
		temp_koordinati.x = igra->tjulni.at(i)->x;
		temp_koordinati.y = igra->tjulni.at(i)->y;
		temp.snap_tjulni.push_back(temp_koordinati);
	}

	buffer.push_back(temp);
}

void ponovitev::cleanup() {
	buffer.clear();
}

void ponovitev::cleanLastLevel() {
	for (unsigned int i = 0; i < buffer.size(); ++i) {
		if (buffer.at(i).nivo == igra->trenutniNivo) {
			buffer.erase(buffer.begin()+i);
			--i;
		}
	}
}

void ponovitev::predvajaj() {
	for (unsigned int i = 0; i < buffer.size(); ++i) {
		// napis izris na zaslon
	}
}