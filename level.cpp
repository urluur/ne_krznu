#include "includes.h"
using namespace std;

void GameManager::level(short& nivo) {
	trenutniNivo = nivo + 1;
	igralec.coutName();
	cout << " zacenja " << trenutniNivo << " level" << endl;

	pripraviVse();

	//pripravi odzadje
	Image odzadje;
	string pathFragment = "common/img/odzadje";
	pathFragment += to_string(trenutniNivo);
	pathFragment += ".png";
	char* path = new char[pathFragment.size() + 1];
	std::copy(pathFragment.begin(), pathFragment.end(), path);
	path[pathFragment.size()] = '\0';
	odzadje.ini(*this, path);
	odzadje.display(okno.ren);
	delete[] path;

	cout << "Se " << stTjuln[trenutniNivo - 1] << " tjulnov!" << endl;
	cout << "Se " << stNaspr[trenutniNivo - 1] << " nasprotnikov!" << endl << endl;
	//main game loop
	while (!keys[SDL_SCANCODE_ESCAPE] && !konecLevela && !adios) {
		okno.stejFrame();
		SDL_RenderClear(okno.ren);
		odzadje.display(okno.ren);
		handleEvents();

		//realn game objective
		if (semNaIzhodniLokaciji)
			if ((stTjuln[nivo] == 0 && trenutniNivo < 5) || (trenutniNivo == 5 && stNaspr[nivo] == 0))
				konecLevela = true; //cilj nase igre

		jaz->init(*this, "common/img/player.png", igralec.getX(), igralec.getY(), igralec.getW(), igralec.getH());

		for (unsigned int i = 0; i < enemy.size(); ++i) {
			if (enemy.at(i)->sprehodNaRandomDestinacijo()) {
				enemy.at(i)->zrcuniRandomDestinacijo();
			}
			else {//ta if spodi se ni popoln
				if (isPlayerCollidingAt(enemy.at(i)->getX() - 100, enemy.at(i)->getY() - 100, enemy.at(i)->getW() + 200, enemy.at(i)->getH() + 200)) {//previr okrog sebe
					enemy.at(i)->setDest(igralec.getX(), igralec.getY());
					//enemy.at(i)->rage();
					if (isPlayerCollidingAt(enemy.at(i)->getX(), enemy.at(i)->getY(), enemy.at(i)->getW(), enemy.at(i)->getH())) {
						cout << "smrt" << endl;
						//adios = true;
						//tocke rab resetirat pa to
					}
				}
				/*
				else {
					enemy.at(i)->chill();
				}
				//*/
				enemy.at(i)->updateImg(*this);
			}
		}

		//* za provo dok ni levela tuki
		if (keys[SDL_SCANCODE_SPACE]) {
			if (trenutniNivo < 5) {
				if (stTjuln[nivo] > 0)
					stTjuln[nivo]--;
				cout << "Se " << stTjuln[nivo] << " tjulnov!" << endl;
				cout << "Se " << stNaspr[nivo] << " nasprotnikov!" << endl << endl;
			}
			else {
				if (stNaspr[nivo] > 0)
					stNaspr[nivo]--;
				cout << "Se " << stTjuln[nivo] << " tjulnov!" << endl;
				cout << "Se " << stNaspr[nivo] << " nasprotnikov!" << endl << endl;
			}
		}
		//*/
		updateMap();
	}

	cleanupVectors();

	if (konecLevela)
		std::cout << "Koncal si " << ++nivo << " nivo!" << endl;
	else if (adios)
		zasilnoShranjevanje();
}