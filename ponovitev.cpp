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
	// uprasamo ce clovek zeli videti replay
	if (!igra->zelisReplay()) {
		return;
	}

	// ce clovek zeli replay
	Image odzadje, nasprotnik, aktivist, tjulen, igralec, puscica, pauzica;
	puscica.init(*igra, "common/img/puscica.png", 20, 20, 50, 50);
	pauzica.init(*igra, "common/img/pauzica.png", 20, 20, 50, 50);
	unsigned int buffer_index = 0;
	bool play = true;
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
				if (buffer_index > 0) {
					if (buffer.at(buffer_index - 1).nivo == levl) {
						crta temp;
						temp.x = x + (igra->igralec.getW() / 2);
						temp.y = y + (igra->igralec.getH());
						temp.xprev = buffer.at(buffer_index - 1).snap_igralec.x + igra->igralec.getW() / 2;
						temp.yprev = buffer.at(buffer_index - 1).snap_igralec.y + igra->igralec.getH();
						crte.push_back(temp);
					}
				}
				int vidnost;
				for (unsigned int i = 0; i < crte.size(); ++i) {
					vidnost = int(255 - (float((float)i / crte.size()) * 255));
					if (vidnost < 0 || vidnost > 255) {
						vidnost = 255;
					}
					SDL_SetRenderDrawColor(igra->okno.ren, vidnost, vidnost, vidnost, SDL_ALPHA_OPAQUE);
					SDL_RenderDrawLine(igra->okno.ren,
						igra->okno.scaleCal(crte.at(i).x), igra->okno.scaleCal(crte.at(i).y),
						igra->okno.scaleCal(crte.at(i).xprev), igra->okno.scaleCal(crte.at(i).yprev)
					);
				}
				
				igralec.init(*igra, "common/img/player.png", x, y, 29, 64);
				igralec.display(igra->okno.ren);

				while(SDL_PollEvent(&igra->event)){
					switch (igra->event.type) {
					case SDL_KEYDOWN:
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

void narisiReplay(GameManager& igra, short& cur_pos, Image& cursor, Image& main) {
	SDL_RenderClear(igra.okno.ren); // resetiramo renderer

	// ce igro zacnes se ti narise zalosten zacetek, ce si igro koncal pa srecen konec
	main.ini(igra, "common/img/replay.png");

	// narisemo kazalec na dolocenih koordinatih na zaslonu, odvisno od pozicije
	main.display(igra.okno.ren);
	switch (cur_pos) {
	case 1:
		cursor.init(igra, "common/img/cursor.png", 520, 240, 98, 49);
		break;
	case 2:
		cursor.init(igra, "common/img/cursor.png", 520, 330, 98, 49);
		break;
	}
	cursor.display(igra.okno.ren); // kazalec se bo pokazal
	SDL_RenderPresent(igra.okno.ren); // na oknu se prikaze spremenjeno stanje

	system("cls");
	printf("### Ogled premikov? ###\n");
	for (int i = 1; i <= 2; ++i) {
		if (cur_pos == i) {
			printf("->");
		}
		else {
			printf("  ");
		}
		switch (i) {
		case 1:
			printf("Da");
			break;
		case 2:
			printf("Ne");
			break;
		}
		printf("\n");
	}
}

bool nadaljujReplay(GameManager& igra, short& cur_pos, bool& izhod_switch) {
	while (igra.checkEnter()) { // dokler drzimo na tipko nas ne pusti naprej
		SDL_PollEvent(&igra.event);
	}
	switch (cur_pos) { // predvajamo zvok in naredimo zeljeno stvar
	case 1:
		return true;
	case 2:
		break;
	}
	return false;
}

bool GameManager::zelisReplay() {
	SDL_PollEvent(&event);

	// kazalec nastavimo na prvo mesto
	Image cursor;
	short cur_pos = 1;

	// ustvarimo sliko menija in meni narisemo na zaslon
	Image main;
	narisiReplay(*this, cur_pos, cursor, main);

	bool izhod_switch = false;

	while (!izhod_switch) {
		okno.stejFrame(); // oznacimo zacetek zanke
		SDL_PollEvent(&event); // osvezivo stanje pritinjenih tipk

		// preverimo ce so bile pritisnjene tipke gor dol start ali enter
		if (checkUp() || checkDown()) {
			while (checkUp() || checkDown()) { // ko tipko pritisnemo caka da jo spustimo
				SDL_PollEvent(&event);
			}
			// predvaja zvok kazalca
			sound.predvajaj("common/sounds/cur_mov.wav");
			// premakne kazalec na zeljeno mesto
			if (cur_pos == 1) {
				++cur_pos;
			}
			else {
				--cur_pos;
			}
			narisiReplay(*this, cur_pos, cursor, main);
		}
		else if (checkEnter()) {
			while (!checkEnter()) {
				okno.stejFrame(); // oznacimo zacetek zanke
				SDL_PollEvent(&event);
				okno.omejiFrame(); // omejimo hitrost prikaza
			}
			return nadaljujReplay(*this, cur_pos, izhod_switch);
		}
		okno.omejiFrame(); // omejimo hitrost prikaza
	}
	return false;
}