#include "menu.h"
using namespace std;

void overworld(GameManager& igra) { // klice se iz glavnega menija -> zacni
	SDL_RenderClear(igra.okno.ren); // pocistimo renderer
	bool stay = true;

	//deklariramo slike
	Image img_overworld;
	Image img_player;
	Image img_zastavica_fullscreen;

	// igralec zacne na poziciji ladje
	short x = 300, y = 170;

	// ce v datoteki pise da smo kaksen nivo ze koncali ga nastavimo
	short level_clear = igra.getNivo();

	// izrise odzadje
	img_overworld.ini(igra, "common/img/overworld.png");
	img_overworld.display(igra.okno.ren);

	// ce to ni nova igra, moramo igralca premakniti na nazadnje dokoncan nivo
	if (level_clear != 0) {
		if (igra.getNivo() >= 5) { // ce smo koncali vse nivoje
			printf("Nalagam srecen konec :)\n");
		}
		else {
			printf("Nalagam %d. nivo.\n", igra.getNivo() + 1); // nalozimo na en nivo visje od nazadnje opravljenega
		}
		for (;;) { // igralca pemikamo po svetu dokler ne pridemo do zeljenega nivoja
			premakniNaXY(igra, x, y, 440, 190, img_overworld, img_player, level_clear);
			if (level_clear == 1) break;
			premakniNaXY(igra, x, y, 335, 310, img_overworld, img_player, level_clear);
			premakniNaXY(igra, x, y, 410, 395, img_overworld, img_player, level_clear);
			if (level_clear == 2) break;
			premakniNaXY(igra, x, y, 460, 530, img_overworld, img_player, level_clear);
			premakniNaXY(igra, x, y, 560, 570, img_overworld, img_player, level_clear);
			premakniNaXY(igra, x, y, 620, 520, img_overworld, img_player, level_clear);
			if (level_clear == 3) break;
			premakniNaXY(igra, x, y, 725, 365, img_overworld, img_player, level_clear);
			premakniNaXY(igra, x, y, 750, 280, img_overworld, img_player, level_clear);
			premakniNaXY(igra, x, y, 710, 220, img_overworld, img_player, level_clear);
			if (level_clear == 4) break;
			premakniNaXY(igra, x, y, 705, 125, img_overworld, img_player, level_clear);
			if (level_clear >= 5) break;
			premakniNaXY(igra, x, y, 710, 20, img_overworld, img_player, level_clear);
		}
	}

	// glavna overworld zanka
	while (stay) {
		SDL_PollEvent(&igra.event); // osvezimo stanje pritisnjenih gumbov
		SDL_RenderClear(igra.okno.ren); // ponastavimo renderer

		// narisemo slike
		img_overworld.ini(igra, "common/img/overworld.png");
		img_overworld.display(igra.okno.ren);
		narisiFarmeAliDosezke(igra, level_clear); // narise igluje oz. farme
		SDL_RenderPresent(igra.okno.ren);
		system("cls");
		cout << "### Tjulenlandija ###" << endl;
		for (int i = 0; i <= 5; ++i) {
			if (igra.trenutniNivo == i) {
				cout << "->";
			}
			else
				cout << "  ";
			switch (i) {
			case 0:
				cout << "1. nivo" << endl;
				break;
			case 1:
				cout << "2. nivo" << endl;
				break;
			case 2:
				cout << "3. nivo" << endl;
				break;
			case 3:
				cout << "4. nivo" << endl;
				break;
			case 4:
				cout << "5. nivo" << endl;
				break;
			case 5:
				cout << "Tjulenlandija resena!" << endl;
				break;
			}
		}

		switch (level_clear) { // odvisno od koncanega levela nadaljujemo po svetu
		case 0:
			img_player.init(igra, "common/img/player.png", x, y, igra.igralec.getW(), igra.igralec.getH());
			img_player.display(igra.okno.ren);
			igra.haltEnter(level_clear); // lokacija takoj ko odpremo in je na ladji
			animacija(igra, 1);

			do {
				premakniNaXY(igra, x, y, 440, 190, img_overworld, img_player, level_clear);
				igra.haltEnter(level_clear); // lokacijs prej ko se zacne prvi nivo
				igra.level(level_clear);
			} while (level_clear != 1);
			x = 335;
			y = 310;
			break;
		case 1:
			premakniNaXY(igra, x, y, 335, 310, img_overworld, img_player, level_clear);
			igra.haltEnter(level_clear); // stojimo pred mostom
			animacija(igra, 2);
			do {
				premakniNaXY(igra, x, y, 410, 395, img_overworld, img_player, level_clear);
				igra.haltEnter(level_clear); // stojimo pred 2. nivojem
				igra.level(level_clear);
			} while (level_clear != 2);
			x = 560;
			y = 570;
			break;
		case 2:
			premakniNaXY(igra, x, y, 560, 570, img_overworld, img_player, level_clear);
			igra.haltEnter(level_clear); // stojimo na kotu
			animacija(igra, 3);
			do {
				premakniNaXY(igra, x, y, 620, 520, img_overworld, img_player, level_clear);
				igra.haltEnter(level_clear); // stojimo na 3. levelu
				igra.level(level_clear);
			} while (level_clear != 3);
			x = 725;
			y = 365;
			break;
		case 3:
			premakniNaXY(igra, x, y, 725, 365, img_overworld, img_player, level_clear);
			igra.haltEnter(level_clear); // stojimo na lojtri
			animacija(igra, 4);
			do {
				premakniNaXY(igra, x, y, 750, 280, img_overworld, img_player, level_clear);
				igra.haltEnter(level_clear); // stojimo na 4. nivoju
				igra.level(level_clear);
			} while (level_clear != 4);
			premakniNaXY(igra, x, y, 710, 220, img_overworld, img_player, level_clear);
			igra.haltEnter(level_clear); // smo na vrvi
			break;
		case 4:
			animacija(igra, 5);
			do {
				premakniNaXY(igra, x, y, 705, 125, img_overworld, img_player, level_clear);
				igra.haltEnter(level_clear); // na 5. nivoju
				animacija(igra, 6);
				igra.level(level_clear);
			} while (level_clear != 5);
			break;
		case 5:
			premakniNaXY(igra, x, y, 710, 20, img_overworld, img_player, level_clear);
			igra.haltEnter(level_clear); // smo na vrhu hriba

			printf("Zmaga!\n");
			animacija(igra, 7);

			// inicializacija vseh slik in lestvice najboljsih
			img_overworld.ini(igra, "common/img/overworld.png");
			img_overworld.display(igra.okno.ren);
			img_player.init(igra, "common/img/player.png", x, y, igra.igralec.getW(), igra.igralec.getH());
			img_player.display(igra.okno.ren);
			img_zastavica_fullscreen.ini(igra, "common/img/zastavica_fullscreen.png");
			img_zastavica_fullscreen.display(igra.okno.ren);
			narisiFarmeAliDosezke(igra, level_clear);
			SDL_RenderPresent(igra.okno.ren);

			// naredi: ispisvanje lestvice na zaslon
			igra.shranjevanjeLestvice();
			SDL_Delay(3000);
			stay = false;
			igra.setCompleted(true); // igro smo koncali, to nam spremeni zacetni menu na veselo razlicico
			break;
		default:
			cerr << "Error: level_clear" << endl;
		}
		SDL_RenderPresent(igra.okno.ren);

		// testiram: mislim da to ni nikoli uporabljeno in lahko brisem
		if ((igra.keys[SDL_SCANCODE_ESCAPE] || igra.event.type == SDL_QUIT)) {
			stay = false;
			igra.zasilnoShranjevanje();
		}
	}
	SDL_RenderClear(igra.okno.ren);
	if (igra.isCompleted()) {
		// naredi: prikazovanje lestvice najboljsih
		// naredi: sound effect odvisno od tega kolk si dobr
	}
}

void animacija(GameManager& igra, int stAnim) { // se klice iz overworld-a, ko zelimo prikazati sliko in zvok iz zgodbe
	SDL_RenderClear(igra.okno.ren); // resetiramo renderer

	// nastavimo odzadje
	Image odzadje;
	string pathFragment = "common/img/animacija";
	pathFragment += to_string(stAnim);
	pathFragment += ".png";
	char* path = new char[pathFragment.size() + 1];
	std::copy(pathFragment.begin(), pathFragment.end(), path);
	path[pathFragment.size()] = '\0';
	odzadje.ini(igra, path);
	delete[] path;
	odzadje.display(igra.okno.ren);
	SDL_RenderPresent(igra.okno.ren);

	// predvajamo zvok iz zgodbe
	igra.sound.soundAnimacija(stAnim);
	SDL_Delay(500);

	// inicializiramo sliko "pritisni enter"
	Image img_enter;
	img_enter.ini(igra, "common/img/pressreturn.png");

	short blink = 0;
	bool halt = true;

	SDL_PollEvent(&igra.event); // osvezimo stanje pritisnjenih tipk
	static bool done;
	done = false;
	while (halt) {
		igra.okno.stejFrame();
		SDL_PollEvent(&igra.event);
		if (blink < 100) { // prikaze napis
			img_enter.display(igra.okno.ren);
		}
		else if (blink < 150) { // ne prikaze napisa
			SDL_RenderClear(igra.okno.ren);
			odzadje.display(igra.okno.ren);
		}
		else {
			blink = 0;
		}
		++blink;
		SDL_RenderPresent(igra.okno.ren);
		if (igra.keys[SDL_SCANCODE_RETURN]) { // ce ko pritisnemo tipko enter caka da jo spustimo
			while (igra.keys[SDL_SCANCODE_RETURN]) {
				SDL_PollEvent(&igra.event);
			}
			halt = false;
		}

		if (!done) {
			system("cls");
			cout << "### Animacija " << stAnim << " ###" << endl;
			switch (stAnim) {
			case -1:
				system("type common\\txt\\animacija-1.txt");
				break;
			case 1:
				system("type common\\txt\\animacija1.txt");
				break;
			case 2:
				system("type common\\txt\\animacija2.txt");
				break;
			case 3:
				system("type common\\txt\\animacija3.txt");
				break;
			case 4:
				system("type common\\txt\\animacija4.txt");
				break;
			case 5:
				system("type common\\txt\\animacija5.txt");
				break;
			case 6:
				system("type common\\txt\\animacija6.txt");
				break;
			case 7:
				system("type common\\txt\\animacija7.txt");
				break;
			}
			done = true;
		}

		igra.okno.omejiFrame();
	}
	Mix_HaltChannel(-1); // ce preskocimo animacijo se bo zvok zgodbe izklopil
}

void premakniNaXY(GameManager& igra, short& mov_x, short& mov_y, short to_x, short to_y, Image& img_overworld, Image& img_player, short nivo) {
	// klice se ko premikamo igralca po overworldu (ne nivoju)
	short i = 0;
	system("cls");
	cout << "### Tjulenlandija ###" << endl;
	for (int i = 0; i <= 5; ++i) {
		if (igra.trenutniNivo == i) {
			cout << "->";
		}
		else
			cout << "  ";
		switch (i) {
		case 0:
			cout << "1. nivo" << endl;
			break;
		case 1:
			cout << "2. nivo" << endl;
			break;
		case 2:
			cout << "3. nivo" << endl;
			break;
		case 3:
			cout << "4. nivo" << endl;
			break;
		case 4:
			cout << "5. nivo" << endl;
			break;
		case 5:
			cout << "Tjulenlandija resena!" << endl;
			break;
		}
	}
	while (true) {
		igra.okno.stejFrame();
		igra.preveriEsc(nivo); // vsakic ko osvezimo sliko preverimo ali je pritisnjen esc, ki shrani igro

		// igralec se premakne proti svojemu cilju
		if (mov_x != to_x) {
			if (mov_x < to_x) {
				++mov_x;
			}
			else {
				--mov_x;
			}
		}
		if (mov_y != to_y) {
			if (mov_y < to_y) {
				++mov_y;
			}
			else {
				--mov_y;
			}
		}
		if (mov_x == to_x && mov_y == to_y) {
			// ko smo na cilju se nam prikaze "!" polek igralca
			SDL_RenderClear(igra.okno.ren);
			img_overworld.display(igra.okno.ren);
			narisiFarmeAliDosezke(igra, nivo);
			img_player.init(igra, "common/img/player_event.png", mov_x, mov_y, igra.igralec.getW(), igra.igralec.getH());
			img_player.display(igra.okno.ren);
			SDL_RenderPresent(igra.okno.ren);
			break;
		}

		SDL_RenderClear(igra.okno.ren);
		img_overworld.display(igra.okno.ren);

		// narise igralca z nogami skupaj oz narazen
		if (i < 10) {
			img_player.init(igra, "common/img/player.png", mov_x, mov_y, igra.igralec.getW(), igra.igralec.getH());
		}
		else if (i > 20) {
			i = 0;
		}
		else {
			img_player.init(igra, "common/img/player_noge.png", mov_x, mov_y, igra.igralec.getW(), igra.igralec.getH());
		}

		// narise vse slike na zaslon
		narisiFarmeAliDosezke(igra, nivo);
		img_player.display(igra.okno.ren);
		SDL_RenderPresent(igra.okno.ren);
		++i; // poveca stevec za spreminjanje zaprtih oz. odprtih nog igralca
		igra.okno.omejiFrame(); // omejimo hitrost prikaza
	}
}

void narisiFarmeAliDosezke(GameManager& igra, short nivo) { // narise farme oz. igluje
	// pozicija      1.   2.   3.   4.   5. nivoja
	short x[5] = { 470, 340, 580, 750, 730 };
	short y[5] = { 180, 490, 480, 240, 125 };

	//inicializacija petih slik
	Image hisa[5];
	for (int i = 0; i < 5; ++i) {
		if (i < nivo) { // iglu za resene nivoje
			hisa[i].init(igra, "common/img/iglu.png", x[i], y[i], 66, 61);
		}
		else { // farma za nedokoncane nivoje
			hisa[i].init(igra, "common/img/farma.png", x[i], y[i], 66, 61);
		}
	}

	// vse slike narisemo na zaslon
	for (int i = 0; i < 5; ++i) {
		hisa[i].display(igra.okno.ren);
	}
}