#include "menu.h"
using namespace std;

void overworld(GameManager& igra) {
	SDL_RenderClear(igra.okno.ren);
	bool stay = true;
	Image img_overworld;
	Image img_player;
	Image img_zastavica_fullscreen;

	short x = 90, y = 160; //pozicija na ladji

	short level_clear = igra.getNivo();

	img_overworld.ini(igra, "common/img/overworld.png");
	img_overworld.display(igra.okno.ren);

	if (level_clear != 0) {
		cout << "Nalagam " << igra.getNivo() + 1 << ". nivo." << endl;
		for (;;) { // skip travel
			premakniNaXY(igra, x, y, 180, 160, img_overworld, img_player, level_clear);
			if (level_clear == 1) break;
			premakniNaXY(igra, x, y, 90, 250, img_overworld, img_player, level_clear);
			premakniNaXY(igra, x, y, 165, 350, img_overworld, img_player, level_clear);
			if (level_clear == 2) break;
			premakniNaXY(igra, x, y, 200, 450, img_overworld, img_player, level_clear);
			premakniNaXY(igra, x, y, 275, 500, img_overworld, img_player, level_clear);
			premakniNaXY(igra, x, y, 325, 500, img_overworld, img_player, level_clear);
			premakniNaXY(igra, x, y, 350, 450, img_overworld, img_player, level_clear);
			if (level_clear == 3) break;
			premakniNaXY(igra, x, y, 445, 320, img_overworld, img_player, level_clear);
			premakniNaXY(igra, x, y, 460, 240, img_overworld, img_player, level_clear);
			premakniNaXY(igra, x, y, 420, 150, img_overworld, img_player, level_clear);
			if (level_clear == 4) break;
			premakniNaXY(igra, x, y, 420, 100, img_overworld, img_player, level_clear);
			if (level_clear == 5) break;
			premakniNaXY(igra, x, y, 425, 30, img_overworld, img_player, level_clear);
		}
	}

	while (stay) {
		SDL_PollEvent(&igra.event);
		SDL_RenderClear(igra.okno.ren);
		img_overworld.ini(igra, "common/img/overworld.png");
		img_overworld.display(igra.okno.ren);
		narisiFarmeAliDosezke(igra, level_clear);
		SDL_RenderPresent(igra.okno.ren);
		igra.okno.omejiFrame();
		switch (level_clear) {
		case 0:
			img_player.init(igra, "common/img/player.png", 55, 160, 29, 64);
			img_player.display(igra.okno.ren);
			igra.haltEnter(level_clear); // takoj ko odpremo in je na ladji
			animacija(igra, 1);

			premakniNaXY(igra, x, y, 180, 160, img_overworld, img_player, level_clear);
			igra.haltEnter(level_clear); // prej ko se zacne prvi level in smo zravn hiske
			igra.level(level_clear);
			break;
		case 1:
			premakniNaXY(igra, x, y, 90, 250, img_overworld, img_player, level_clear);
			igra.haltEnter(level_clear); // stojimo pred mostom
			animacija(igra, 2);
			premakniNaXY(igra, x, y, 165, 350, img_overworld, img_player, level_clear);
			igra.haltEnter(level_clear); // stojimo pred 2. levelom

			igra.level(level_clear);
			break;
		case 2:
			premakniNaXY(igra, x, y, 200, 450, img_overworld, img_player, level_clear);
			premakniNaXY(igra, x, y, 275, 500, img_overworld, img_player, level_clear);
			premakniNaXY(igra, x, y, 325, 500, img_overworld, img_player, level_clear);
			igra.haltEnter(level_clear); //stojimo na kotu
			animacija(igra, 3);
			premakniNaXY(igra, x, y, 350, 450, img_overworld, img_player, level_clear);
			igra.haltEnter(level_clear); //stojimo na 3. levelu

			igra.level(level_clear);
			break;
		case 3:
			premakniNaXY(igra, x, y, 445, 320, img_overworld, img_player, level_clear);
			igra.haltEnter(level_clear); // stojimo na lojtri
			animacija(igra, 4);
			premakniNaXY(igra, x, y, 460, 240, img_overworld, img_player, level_clear);
			igra.haltEnter(level_clear); //stojimo na 4. levelu
			igra.level(level_clear);
			premakniNaXY(igra, x, y, 420, 150, img_overworld, img_player, level_clear); //testing d se pokaze
			igra.haltEnter(level_clear);
			break;
		case 4:
			animacija(igra, 5);
			premakniNaXY(igra, x, y, 420, 100, img_overworld, img_player, level_clear);
			igra.haltEnter(level_clear);
			animacija(igra, 6);
			igra.level(level_clear);
			break;
		case 5:
			premakniNaXY(igra, x, y, 425, 30, img_overworld, img_player, level_clear);
			igra.haltEnter(level_clear);

			cout << "Zmaga!" << endl;
			animacija(igra, 7);
			img_overworld.ini(igra, "common/img/overworld.png");
			img_overworld.display(igra.okno.ren);
			img_player.init(igra, "common/img/player.png", x, y, 29, 64);
			img_player.display(igra.okno.ren);
			img_zastavica_fullscreen.ini(igra, "common/img/zastavica_fullscreen.png");
			img_zastavica_fullscreen.display(igra.okno.ren);
			narisiFarmeAliDosezke(igra, level_clear);
			SDL_RenderPresent(igra.okno.ren);

			//shranjevanje rekordov
			SDL_Delay(3000);
			stay = false;
			igra.setCompleted(true);
			break;
		default:
			cerr << "Error: level_clear" << endl;
		}
		SDL_RenderPresent(igra.okno.ren);

		if ((igra.keys[SDL_SCANCODE_ESCAPE] || igra.event.type == SDL_QUIT)) {
			stay = false;
			igra.zasilnoShranjevanje();
		} //to rab bit klicano v haltenter in premakninaxy, also nared cist posebno funkcijo
		//za previrjanje esc in sdlquit
	}
	SDL_RenderClear(igra.okno.ren);
	//prikazovanje recordov
}

void animacija(GameManager& igra, int stAnim) {
	SDL_RenderClear(igra.okno.ren);
	Image odzadje;

	string pathFragment = "common/img/animacija"; // zacetek
	pathFragment += to_string(stAnim);
	pathFragment += ".png";
	char* path = new char[pathFragment.size() + 1];
	std::copy(pathFragment.begin(), pathFragment.end(), path);
	path[pathFragment.size()] = '\0';
	odzadje.ini(igra, path);
	delete[] path;

	odzadje.display(igra.okno.ren);
	SDL_RenderPresent(igra.okno.ren);

	igra.sound.soundAnimacija(stAnim);
	SDL_Delay(500);

	SDL_PollEvent(&igra.event);
	Image img_enter;
	short blink = 0;
	img_enter.ini(igra, "common/img/pressreturn.png");
	bool halt = true;
	while (halt) {
		igra.okno.stejFrame();
		SDL_PollEvent(&igra.event);
		if (blink < 100)
			img_enter.display(igra.okno.ren);
		else if (blink < 150) {
			SDL_RenderClear(igra.okno.ren);
			odzadje.display(igra.okno.ren);
		}
		else
			blink = 0;
		blink++;
		SDL_RenderPresent(igra.okno.ren);
		igra.okno.omejiFrame();
		if (igra.keys[SDL_SCANCODE_RETURN]) {
			while (igra.keys[SDL_SCANCODE_RETURN])
				SDL_PollEvent(&igra.event);
			halt = false;
		}
	}
}

void premakniNaXY(GameManager& igra, short& mov_x, short& mov_y, short to_x, short to_y, Image& img_overworld, Image& img_player, short nivo) {
	short i = 0;
	while (true) {
		igra.okno.stejFrame();
		igra.preveriEsc(nivo);
		if (mov_x != to_x) {
			if (mov_x < to_x) mov_x++;
			else mov_x--;
		}
		if (mov_y != to_y) {
			if (mov_y < to_y) mov_y++;
			else mov_y--;
		}
		if (mov_x == to_x && mov_y == to_y) {
			SDL_RenderClear(igra.okno.ren);
			img_overworld.display(igra.okno.ren);
			narisiFarmeAliDosezke(igra, nivo);
			img_player.init(igra, "common/img/player_event.png", mov_x, mov_y, 29, 64);
			img_player.display(igra.okno.ren);
			SDL_RenderPresent(igra.okno.ren);
			break;
		}

		SDL_RenderClear(igra.okno.ren);
		img_overworld.display(igra.okno.ren);

		if (i < 10)
			img_player.init(igra, "common/img/player.png", mov_x, mov_y, 29, 64);
		else if (i > 20)
			i = 0;
		else
			img_player.init(igra, "common/img/player_noge.png", mov_x, mov_y, 29, 64);
		narisiFarmeAliDosezke(igra, nivo);
		img_player.display(igra.okno.ren);
		SDL_RenderPresent(igra.okno.ren);
		i += 1;
		igra.okno.omejiFrame();
	}
}

void narisiFarmeAliDosezke(GameManager& igra, short nivo) {
	Image hisa[5];
	unsigned short x[5] = { 210, 100, 320, 460, 450 };
	unsigned short y[5] = { 160, 425, 420, 215, 100 };
	for (int i = 0; i < 5; i++)
		if (i < nivo)
			hisa[i].init(igra, "common/img/iglu.png", x[i], y[i], 66, 61);
		else
			hisa[i].init(igra, "common/img/farma.png", x[i], y[i], 66, 61);
	for (int i = 0; i < 5; i++)
		hisa[i].display(igra.okno.ren);
}