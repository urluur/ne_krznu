#include "includes.h"
using namespace std;

void GameManager::level(short& nivo) {
	trenutniNivo = nivo + 1;
	igralec.coutName();
	cout << " zacenja " << trenutniNivo << " level\n";

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

	cout << "Se " << stTjuln[trenutniNivo - 1] << " tjulnov!\n";
	cout << "Se " << stNaspr[trenutniNivo - 1] << " nasprotnikov!\n\n";
	//main game loop
	while (!keys[SDL_SCANCODE_ESCAPE] && !konecLevela && !adios) {
		okno.stejFrame();
		SDL_RenderClear(okno.ren);
		odzadje.display(okno.ren);
		handleEvents();

		//realn game objective
		if (semNaIzhodniLokaciji)
			if ((stTjuln[nivo] == 0 && stTjulnFarma == 0 && trenutniNivo < 5) || (trenutniNivo == 5 && stNaspr[nivo] == 0))
				konecLevela = true; //cilj nase igre

		jaz->init(*this, "common/img/player.png", igralec.getX(), igralec.getY(), igralec.getW(), igralec.getH());

		for (unsigned int i = 0; i < enemy.size(); ++i) {
			if (enemy.at(i)->sprehodNaRandomDestinacijo()) {
				enemy.at(i)->zrcuniRandomDestinacijo();
				
			}
			else {//ta if spodi se ni popoln
				if (isPlayerCollidingAt(enemy.at(i)->getX() - 100, enemy.at(i)->getY() - 100, enemy.at(i)->getW() + 200, enemy.at(i)->getH() + 200)) {//previr okrog sebe
					enemy.at(i)->setDest(igralec.getX(), igralec.getY());
					enemy.at(i)->nosim = -1;
					//enemy.at(i)->rage();
					if (isPlayerCollidingAt(enemy.at(i)->getX(), enemy.at(i)->getY(), enemy.at(i)->getW(), enemy.at(i)->getH())) {
						cout << "smrt\n\n";
						adios = true;
						//tocke rab resetirat pa to
					}
				}
				else {
					for (unsigned int t = 0; t < tjulni.size(); ++t) {
						if((tjulni.at(t)->nosilec == -1 && enemy.at(i)->nosim == -1) || tjulni.at(t)->nosilec == i) {
							if (univerzalniTrk(enemy.at(i)->getX() - 100, enemy.at(i)->getY() - 100, enemy.at(i)->getW() + 200, enemy.at(i)->getH() + 200,
								tjulni.at(t)->getX(), tjulni.at(t)->getY(), tjulni.at(t)->getW(), tjulni.at(t)->getH()) && enemy.at(i)->nosim == -1)
							{
								enemy.at(i)->setDest(tjulni.at(t)->getX(), tjulni.at(t)->getY());
								if (univerzalniTrk(enemy.at(i)->getX(), enemy.at(i)->getY(), enemy.at(i)->getW(), enemy.at(i)->getH(),
									tjulni.at(t)->getX(), tjulni.at(t)->getY(), tjulni.at(t)->getW(), tjulni.at(t)->getH()) && enemy.at(i)->nosim == -1)
								{
									tjulni.at(t)->setX(enemy.at(i)->getX()+t);
									tjulni.at(t)->setY(enemy.at(i)->getY()+t);
									tjulni.at(t)->nosilec = i;
									tjulni.at(t)->updateImg(*this);
									enemy.at(i)->setDest(0, 0); //spawn farme
									if (univerzalniTrk(0, 0, 10, 10, //same here
										tjulni.at(t)->getX(), tjulni.at(t)->getY(), tjulni.at(t)->getW(), tjulni.at(t)->getH()))
									{
										cout << "Joj ne, na zaprt sem v farmi!!!\n";
										stTjulnFarma += 1;
										//updati neko tabelo (k je se ni) k pove kolk tjulnou je na farmi
										if (!tjulni.empty()) {
											delete tjulni.at(t);
											tjulni.erase(tjulni.begin() + t);
										}
										stTjuln[trenutniNivo - 1]--;
										enemy.at(i)->nosim = -1;
									}
								}
							}
							/*
							else {
								enemy.at(i)->chill();
							}
							//*/
						}
					}
				}
				enemy.at(i)->updateImg(*this);
			}
		}

		//* za provo dok ni levela tuki
		if (keys[SDL_SCANCODE_SPACE]) {
			if (trenutniNivo < 5) {
				if (stTjuln[nivo] > 0)
					stTjuln[nivo]--;
				cout << "Se " << stTjuln[nivo] << " tjulnov!\n";
				cout << "Se " << stNaspr[nivo] << " nasprotnikov!\n\n";
			}
			else {
				if (stNaspr[nivo] > 0)
					stNaspr[nivo]--;
				cout << "Se " << stTjuln[nivo] << " tjulnov!\n";
				cout << "Se " << stNaspr[nivo] << " nasprotnikov!\n\n";
			}
		}
		//*/
		updateMap();
	}

	cleanupVectors();

	if (konecLevela)
		std::cout << "Koncal si " << ++nivo << " nivo!\n";
	else if (adios)
		zasilnoShranjevanje();
}