#include "menu.h"
using namespace std;

//optimiziri menu.cpp tko ku je Source.cpp !

void nastavitve(GameManager& igra) {
	bool stay = true;
	short cur_pos = 1;
	Image img_nastavitve;
	Image cursor;
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
		}
		else if (igra.keys[SDL_SCANCODE_DOWN])
		{
			while (igra.keys[SDL_SCANCODE_DOWN]) { SDL_PollEvent(&igra.event); }
			igra.sound.predvajaj("common/sounds/cur_mov.wav");
			if (cur_pos == 4)
				cur_pos = 1;
			else
				++cur_pos;
		}
		else if (igra.keys[SDL_SCANCODE_ESCAPE]) {
			while (igra.keys[SDL_SCANCODE_ESCAPE]) { SDL_PollEvent(&igra.event); }
			stay = false;
		}

		switch (cur_pos) {
		case 1:
			cursor.init(igra, "common/img/cursor.png", 20, 210, 98, 49);
			cursor.display(igra.okno.ren);
			if (igra.keys[SDL_SCANCODE_RETURN]) {
				while (igra.keys[SDL_SCANCODE_RETURN]) { SDL_PollEvent(&igra.event); }
				igra.sound.predvajaj("common/sounds/dimenzije.wav");
				cout << "spreminjam velikost okna na ";
				igra.okno.toggleScaler();
				SDL_SetWindowSize(igra.okno.window, igra.okno.scaleCal(igra.okno.returnWindowWidth()), igra.okno.scaleCal(igra.okno.returnWindowHeight()));
				if (igra.okno.vrniScaler() == 100)
					SDL_SetWindowFullscreen(igra.okno.window, SDL_WINDOW_FULLSCREEN_DESKTOP);
				else
					SDL_SetWindowFullscreen(igra.okno.window, 0);
				SDL_SetWindowPosition(igra.okno.window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
			}
			break;
		case 2:
			cursor.init(igra, "common/img/cursor.png", 20, 310, 98, 49);
			cursor.display(igra.okno.ren);
			if (igra.keys[SDL_SCANCODE_RETURN]) {
				while (igra.keys[SDL_SCANCODE_RETURN]) { SDL_PollEvent(&igra.event); }
				igra.sound.predvajaj("common/sounds/spremeni_ime.wav");
				igra.igralec.setName();
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
			}
			break;
		case 4:
			cursor.init(igra, "common/img/cursor.png", 20, 510, 98, 49);
			cursor.display(igra.okno.ren);
			if (igra.keys[SDL_SCANCODE_RETURN]) {
				while (igra.keys[SDL_SCANCODE_RETURN]) { SDL_PollEvent(&igra.event); }
				igra.sound.predvajaj("common/sounds/nazaj.wav");
				stay = false;
			}
			break;
		}

		SDL_RenderPresent(igra.okno.ren);
		SDL_PollEvent(&igra.event);
		igra.okno.omejiFrame();
	}
}
void vec(GameManager& igra) {
	bool stay = true;
	int cur_pos = 1;
	Image img_vec;
	Image cursor;
	Image github(igra.okno.ren, "common/img/github.png", igra.okno.scaleCal(20), igra.okno.scaleCal(20), igra.okno.scaleCal(279), igra.okno.scaleCal(66));
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
		}
		else if (igra.keys[SDL_SCANCODE_DOWN]) {
			while (igra.keys[SDL_SCANCODE_DOWN]) { SDL_PollEvent(&igra.event); }
			igra.sound.predvajaj("common/sounds/cur_mov.wav");
			if (cur_pos == 4)
				cur_pos = 1;
			else
				++cur_pos;
		}
		else if (igra.keys[SDL_SCANCODE_ESCAPE]) {
			stay = false;
			while (igra.keys[SDL_SCANCODE_RETURN]) { SDL_PollEvent(&igra.event); }
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
			}
			break;
		case 3:
			cursor.init(igra, "common/img/cursor.png", 20, 420, 98, 49);
			cursor.display(igra.okno.ren);
			if (igra.keys[SDL_SCANCODE_RETURN]) {
				while (igra.keys[SDL_SCANCODE_RETURN]) { SDL_PollEvent(&igra.event); }
				igra.sound.predvajaj("common/sounds/izbris.wav");
				igra.deleteSave();
			}
			break;
		case 4:
			cursor.init(igra, "common/img/cursor.png", 20, 530, 98, 49);
			cursor.display(igra.okno.ren);
			if (igra.keys[SDL_SCANCODE_RETURN]) {
				while (igra.keys[SDL_SCANCODE_RETURN]) { SDL_PollEvent(&igra.event); }
				igra.sound.predvajaj("common/sounds/nazaj.wav");
				stay = false;
			}
			break;
		}

		SDL_RenderPresent(igra.okno.ren);
		SDL_PollEvent(&igra.event);
		igra.okno.omejiFrame();
	}
}