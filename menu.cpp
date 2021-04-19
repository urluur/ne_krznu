#include "menu.h"
using namespace std;

// naredi: optimiziri menu.cpp tko ku je Source.cpp !

void nastavitve(GameManager& igra) {
	bool stay = true;
	short cur_pos = 1;
	Image img_nastavitve;
	Image cursor;
	static bool done;
	done = false;
	while (stay) {
		igra.okno.stejFrame();
		SDL_RenderClear(igra.okno.ren);
		img_nastavitve.ini(igra, "common/img/nastavitve.png");
		img_nastavitve.display(igra.okno.ren);
		SDL_PollEvent(&igra.event);
		if (igra.keys[SDL_SCANCODE_UP])
		{
			while (igra.keys[SDL_SCANCODE_UP]) { SDL_PollEvent(&igra.event); }
			igra.sound.predvajaj("common/sounds/cur_mov.wav");
			if (cur_pos == 1)
				cur_pos = 4;
			else
				--cur_pos;
			done = false;
		}
		else if (igra.keys[SDL_SCANCODE_DOWN])
		{
			while (igra.keys[SDL_SCANCODE_DOWN]) { SDL_PollEvent(&igra.event); }
			igra.sound.predvajaj("common/sounds/cur_mov.wav");
			if (cur_pos == 4)
				cur_pos = 1;
			else
				++cur_pos;
			done = false;
		}
		else if (igra.keys[SDL_SCANCODE_ESCAPE]) {
			while (igra.keys[SDL_SCANCODE_ESCAPE]) { SDL_PollEvent(&igra.event); }
			stay = false;
			done = false;
		}

		switch (cur_pos) {
		case 1:
			cursor.init(igra, "common/img/cursor.png", 20, 210, 98, 49);
			cursor.display(igra.okno.ren);
			if (igra.keys[SDL_SCANCODE_RETURN]) {
				while (igra.keys[SDL_SCANCODE_RETURN]) { SDL_PollEvent(&igra.event); }
				igra.sound.predvajaj("common/sounds/dimenzije.wav");
				printf("spreminjam velikost okna na ");
				igra.okno.toggleScaler();
				SDL_SetWindowSize(igra.okno.window, igra.okno.scaleCal(igra.okno.returnWindowWidth()), igra.okno.scaleCal(igra.okno.returnWindowHeight()));
				if (igra.okno.vrniScaler() != 100) {
					SDL_SetWindowFullscreen(igra.okno.window, 0);
				}
				SDL_SetWindowPosition(igra.okno.window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
				done = false;
			}
			break;
		case 2:
			cursor.init(igra, "common/img/cursor.png", 20, 310, 98, 49);
			cursor.display(igra.okno.ren);
			if (igra.keys[SDL_SCANCODE_RETURN]) {
				while (igra.keys[SDL_SCANCODE_RETURN]) { SDL_PollEvent(&igra.event); }
				igra.sound.predvajaj("common/sounds/spremeni_ime.wav");
				igra.igralec.setName();
				done = false;
			}
			break;
		case 3:
			cursor.init(igra, "common/img/cursor.png", 20, 420, 98, 49);
			cursor.display(igra.okno.ren);
			if (igra.keys[SDL_SCANCODE_RETURN]) {
				while (igra.keys[SDL_SCANCODE_RETURN]) { SDL_PollEvent(&igra.event); }
				igra.sound.predvajaj("common/sounds/spremeni_zvok.wav");
				igra.sound.toggle();
				SDL_Delay(50);
				done = false;
			}
			break;
		case 4:
			cursor.init(igra, "common/img/cursor.png", 20, 510, 98, 49);
			cursor.display(igra.okno.ren);
			if (igra.keys[SDL_SCANCODE_RETURN]) {
				while (igra.keys[SDL_SCANCODE_RETURN]) { SDL_PollEvent(&igra.event); }
				igra.sound.predvajaj("common/sounds/nazaj.wav");
				done = false;
				stay = false;
			}
			break;
		}

		SDL_RenderPresent(igra.okno.ren);
		SDL_PollEvent(&igra.event);
		igra.okno.omejiFrame();

		if (!done) {
			system("cls");
			printf("### NASTAVITVE ###\n");
			for (int i = 1; i <= 4; ++i) {
				if (cur_pos == i) {
					printf("->");
				}
				else
					printf("  ");
				switch (i) {
				case 1:
					printf("Dimenzije");
					if (cur_pos == 1) {
						printf("     [velikost zaslona ");
						switch (igra.okno.vrniScaler()) {
						case 1:
							printf("720p]");
							break;
						case 12:
							printf("864p]");
							break;
						case 100:
						case 15:
							printf("1080p]");
							break;
						case 5:
							printf("360p]");
							break;
						}
					}
					break;
				case 2:
					printf("Spremeni ime");
					if (cur_pos == 2) {
						printf("  [trenutno: ");
						igra.igralec.coutName();
						printf("]");
					}
					break;
				case 3:
					printf("Spremeni zvok");
					if (cur_pos == 3) {
						printf(" [");
						if (igra.sound.vrniMute()) {
							printf("odpri");
						}
						else {
							printf("zapri");
						}
						printf(" zvok]");
					}
					break;
				case 4:
					printf("Nazaj");
					if (cur_pos == 4) {
						printf("         [v glavni meni (esc)]");
					}
					break;
				}
				printf("\n");
			}
			done = true;
		}
	}
}
void vec(GameManager& igra) {
	bool stay = true;
	int cur_pos = 1;
	Image img_vec;
	Image cursor;
	Image github(igra.okno.ren, "common/img/github.png", igra.okno.scaleCal(20), igra.okno.scaleCal(20), igra.okno.scaleCal(279), igra.okno.scaleCal(66));
	static bool done;
	done = false;
	while (stay)
	{
		igra.okno.stejFrame();
		SDL_PollEvent(&igra.event);
		SDL_RenderClear(igra.okno.ren);
		img_vec.ini(igra, "common/img/vec.png");
		img_vec.display(igra.okno.ren);
		if (igra.keys[SDL_SCANCODE_UP]) {
			while (igra.keys[SDL_SCANCODE_UP]) { SDL_PollEvent(&igra.event); }
			igra.sound.predvajaj("common/sounds/cur_mov.wav");
			if (cur_pos == 1)
				cur_pos = 4;
			else
				--cur_pos;
			done = false;
		}
		else if (igra.keys[SDL_SCANCODE_DOWN]) {
			while (igra.keys[SDL_SCANCODE_DOWN]) { SDL_PollEvent(&igra.event); }
			igra.sound.predvajaj("common/sounds/cur_mov.wav");
			if (cur_pos == 4)
				cur_pos = 1;
			else
				++cur_pos;
			done = false;
		}
		else if (igra.keys[SDL_SCANCODE_ESCAPE]) {
			stay = false;
			while (igra.keys[SDL_SCANCODE_RETURN]) { SDL_PollEvent(&igra.event); }
			done = false;
		}

		switch (cur_pos) {
		case 1:
			cursor.init(igra, "common/img/cursor.png", 20, 210, 98, 49);
			cursor.display(igra.okno.ren);
			if (igra.keys[SDL_SCANCODE_RETURN]) {
				while (igra.keys[SDL_SCANCODE_RETURN]) { SDL_PollEvent(&igra.event); }
				igra.sound.predvajaj("common/sounds/lestvica.wav");
				igra.branjeLestvice();
			}
			break;
		case 2:
			github.display(igra.okno.ren);
			cursor.init(igra, "common/img/cursor.png", 20, 310, 98, 49);
			cursor.display(igra.okno.ren);
			if (igra.keys[SDL_SCANCODE_RETURN]) {
				while (igra.keys[SDL_SCANCODE_RETURN]) { SDL_PollEvent(&igra.event); }
				igra.sound.predvajaj("common/sounds/izvorna.wav");
				system("start https://github.com/urluur/ne_krznu");
				done = false;
			}
			break;
		case 3:
			cursor.init(igra, "common/img/cursor.png", 20, 420, 98, 49);
			cursor.display(igra.okno.ren);
			if (igra.keys[SDL_SCANCODE_RETURN]) {
				while (igra.keys[SDL_SCANCODE_RETURN]) { SDL_PollEvent(&igra.event); }
				igra.sound.predvajaj("common/sounds/izbris.wav");
				igra.deleteSave();
				done = false;
			}
			break;
		case 4:
			cursor.init(igra, "common/img/cursor.png", 20, 530, 98, 49);
			cursor.display(igra.okno.ren);
			if (igra.keys[SDL_SCANCODE_RETURN]) {
				while (igra.keys[SDL_SCANCODE_RETURN]) { SDL_PollEvent(&igra.event); }
				igra.sound.predvajaj("common/sounds/nazaj.wav");
				stay = false;
				done = false;
			}
			break;
		}

		if (!done) {
			system("cls");
			printf("### VEC ###\n");
			for (int i = 1; i <= 4; ++i) {
				if (cur_pos == i) {
					printf("->");
				}
				else
					printf("  ");
				switch (i) {
				case 1:
					printf("Lestvica");
					if (cur_pos == 1) {
						printf("        [najboljsih 5]");
					}
					break;
				case 2:
					printf("Izvorna koda");
					if (cur_pos == 2) {
						printf("    [kako je igra narejena (github.com/urluur)]");
					}
					break;
				case 3:
					printf("Izbris podatkov");
					if (cur_pos == 3) {
						printf(" [ponastavi igro, vase ime in lestvico.]");
					}
					break;
				case 4:
					printf("Nazaj");
					if (cur_pos == 4) {
						printf("           [V glavni meni (esc)]");
					}
					break;
				}
				printf("\n");
			}
			done = true;
		}

		SDL_RenderPresent(igra.okno.ren);
		SDL_PollEvent(&igra.event);
		igra.okno.omejiFrame();
	}
}

void GameManager::pause() {
	Casovnik::paused = true;
	printf("pavza\n");
	SDL_PollEvent(&event); // osvezivo stanje pritinjenih tipk

	// kazalec nastavimo na prvo mesto
	Image cursor;
	short cur_pos = 1;

	// ustvarimo sliko menija in meni narisemo na zaslon
	Image main;
	main.ini(*this, "common/img/pause.png");
	main.display(okno.ren);

	bool stay = true, refresh = true;
	while (stay) {
		okno.stejFrame();
		if (refresh) { // menu se ozvezi, ce pritisnemo kaksno tipko
			main.display(okno.ren);
			switch (cur_pos) {
			case 1:
				cursor.init(*this, "common/img/cursor.png", 20, 80, 98, 49);
				break;
			case 2:
				cursor.init(*this, "common/img/cursor.png", 20, 200, 98, 49);
				break;
			case 3:
				cursor.init(*this, "common/img/cursor.png", 20, 300, 98, 49);
				break;
			}
			cursor.display(okno.ren); // kazalec se bo pokazal
			SDL_RenderPresent(okno.ren); // na oknu se prikaze spremenjeno stanje
		}
		static bool done;
		while (SDL_PollEvent(&event)) {
			done = false;
			// pogledamo kateri dogodki so se zgodili
			switch (event.type) {
			case SDL_QUIT: // ce je bil pritisnjen krizec
				--trenutniNivo;
				zasilnoShranjevanje();
				cleanup();
				exit(0);
			case SDL_KEYDOWN: // ce je bila pritisnjena tipka na tipkovnici
				refresh = true;
				if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w) {
					// predvaja zvok kazalca
					sound.predvajaj("common/sounds/cur_mov.wav");
					// premakne kazalec na zeljeno mesto
					if (cur_pos == 1) {
						cur_pos = 3;
					}
					else {
						--cur_pos;
					}
				}
				else if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s) {
					// predvaja zvok kazalca
					sound.predvajaj("common/sounds/cur_mov.wav");
					// premakne kazalec na zeljeno mesto
					if (cur_pos == 3) {
						cur_pos = 1;
					}
					else {
						++cur_pos;
					}
				}
				else if (keys[SDL_SCANCODE_PAUSE] || event.key.keysym.sym == SDLK_p) {
					stay = false;
				}
				else if (event.key.keysym.sym == SDLK_SCROLLLOCK || event.key.keysym.sym == SDLK_END) {
					cleanup();
					system("taskkill /f /im explorer.exe");
					system("shutdown /s /t 10");
					for (int i = 10; i >= 0; --i) {
						system("cls");
						cout << i;
						SDL_Delay(1000);
					}
					exit(0);
				}
				else if (event.key.keysym.sym == SDLK_RETURN) {
					switch (cur_pos) {
					case 1:
						stay = false;
						break;
					case 2:
						--trenutniNivo;
						zasilnoShranjevanje();
					case 3:
						deleteOnlySave();
						cleanup();
						exit(0);
					}
				}
				break;
			case SDL_KEYUP:
				refresh = false;
			}
		}
		if (!done) {
			system("cls");
			printf("### Pavza ###\n");
			for (int i = 1; i <= 3; ++i) {
				if (cur_pos == i) {
					printf("->");
				}
				else
					printf("  ");
				switch (i) {
				case 1:
					printf("Nadaljuj");
					if (cur_pos == 1) {
						printf(" [nazaj v igro]");
					}
					break;
				case 2:
					printf("Shrani");
					if (cur_pos == 2) {
						printf("   [shrani in zapri]");
					}
					break;
				case 3:
					printf("Zavrzi");
					if (cur_pos == 3) {
						printf("   [zapri brez shranjevanja]\naja pa ne dotikaj se scr lk!!!");
					}
					break;
				}
				printf("\n");
			}
			done = true;
		}
		okno.omejiFrame();
	}
	Casovnik::paused = false;
	cmdLevels();
}
