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
	snapInterval = 1; // na vsake tri sekunde se bo shranjevalo;
}

void ponovitev::checkSnap() {
	if ((Casovnik::sekunde > lastSnapTime && !Casovnik::paused) || Casovnik::sekunde <= lastSnapTime - snapInterval) {
		lastSnapTime = Casovnik::sekunde;
		snapShot();
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
	printf("*snap*\n");
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
	Image odzadje, nasprotnik, aktivist, tjulen, igralec, puscica, pauzica;
	puscica.init(*igra, "common/img/puscica.png", 20, 20, 50, 50);
	pauzica.init(*igra, "common/img/pauzica.png", 20, 20, 50, 50);
	unsigned int buffer_index = 0;
	bool play = true;
	igra->haltEnter(0);
	short play_speed = 1;
	igra->cajt.set(play_speed);
	vector <crta> crte;
	for (short levl = 1; levl <= 5; ++levl) {

		crte.clear();

		// pripravi odzadje
		string pathFragment = "common/img/odzadje";
		pathFragment += to_string(levl);
		pathFragment += ".png";
		char* path = new char[pathFragment.size() + 1];
		std::copy(pathFragment.begin(), pathFragment.end(), path);
		path[pathFragment.size()] = '\0';
		odzadje.ini(*igra, path);
		delete[] path;
		if (!buffer.empty()) {
			if (buffer_index + 1 >= igra->replay->buffer.size()) {
				break;
			}
			while (buffer.at(buffer_index).nivo <= levl) {
				igra->okno.stejFrame();
				SDL_RenderClear(igra->okno.ren);
				odzadje.display(igra->okno.ren);
			
				for (unsigned int i = 0; i < buffer.at(buffer_index).snap_nasprotniki.size(); ++i) {
					short x = buffer.at(buffer_index).snap_nasprotniki.at(i).x;
					short y = buffer.at(buffer_index).snap_nasprotniki.at(i).y;
					nasprotnik.init(*igra, "common/img/nasprotnik.png", x, y, 29, 64);
					nasprotnik.display(igra->okno.ren);
				}
			
				for (unsigned int i = 0; i < buffer.at(buffer_index).snap_aktivisti.size(); ++i) {
					short x = buffer.at(buffer_index).snap_aktivisti.at(i).x;
					short y = buffer.at(buffer_index).snap_aktivisti.at(i).y;
					aktivist.init(*igra, "common/img/aktivist.png", x, y, 29, 64);
					aktivist.display(igra->okno.ren);
				}

				for (unsigned int i = 0; i < buffer.at(buffer_index).snap_tjulni.size(); ++i) {
					short x = buffer.at(buffer_index).snap_tjulni.at(i).x;
					short y = buffer.at(buffer_index).snap_tjulni.at(i).y;
					tjulen.init(*igra, "common/img/tjuln.png", x, y, 63, 42);
					tjulen.display(igra->okno.ren);
				}

				short x = buffer.at(buffer_index).snap_igralec.x;
				short y = buffer.at(buffer_index).snap_igralec.y;
				
				/*
				if (buffer_index > 0) {
					if (buffer.at(buffer_index - 1).nivo == levl) {
						short xprev = buffer.at(buffer_index - 1).snap_igralec.x;
						short yprev = buffer.at(buffer_index - 1).snap_igralec.y;
						SDL_RenderDrawLine(igra->okno.ren, x, y, xprev, yprev);
					}
				}
				*/

				if (buffer_index > 0) {
					if (buffer.at(buffer_index - 1).nivo == levl) {
						crta temp;
						temp.x = x + (igra->igralec.getW());
						temp.y = y + (igra->igralec.getH() / 2);
						temp.xprev = buffer.at(buffer_index - 1).snap_igralec.x + igra->igralec.getW();
						temp.yprev = buffer.at(buffer_index - 1).snap_igralec.y + igra->igralec.getH() / 2;
						crte.push_back(temp);
					}
				}
				for (unsigned int i = 0; i < crte.size(); ++i) {
					SDL_RenderDrawLine(igra->okno.ren,
						crte.at(i).x, crte.at(i).y,
						crte.at(i).xprev, crte.at(i).yprev
					);
				}
				
				igralec.init(*igra, "common/img/player.png", x, y, 29, 64);
				igralec.display(igra->okno.ren);

				while(SDL_PollEvent(&igra->event)){
					switch (igra->event.type) {
					case SDL_KEYDOWN:
						cout << "neki smo prtisnli" << endl;
						if ((igra->event.key.keysym.sym == SDLK_LEFT || igra->event.key.keysym.sym == SDLK_a) && !play && buffer_index > 0 && igra->replay->buffer.at(buffer_index - 1).nivo == levl) {
							--buffer_index;
						}
						if ((igra->event.key.keysym.sym == SDLK_RIGHT || igra->event.key.keysym.sym == SDLK_d) && !play && buffer_index + 1 < igra->replay->buffer.size()) {
							++buffer_index;
						}
						if (igra->event.key.keysym.sym == SDLK_SPACE) {
							play = !play;
						}
						break;
					}
				}

				if (play) {
					puscica.display(igra->okno.ren);
					if (igra->cajt.odstej()) {
						++buffer_index;
						igra->cajt.set(play_speed);
					}
				}
				else {
					pauzica.display(igra->okno.ren);
				}
				
				SDL_RenderPresent(igra->okno.ren);
				if (buffer_index + 1 == igra->replay->buffer.size()) {
					break;
				}
				igra->okno.omejiFrame();
			}
		}
	}
	igra->haltEnter(0);
	SDL_Delay(100);
	SDL_PollEvent(&igra->event);
}