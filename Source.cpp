#include "includes.h"
#undef main

void nastavitve(GameManager& igra);
void vec(GameManager& igra);
void overworld(GameManager& igra);

int main() {
	GameManager igra;

	bool problemi = igra.init();
	if (problemi) {
		cerr << "Problemi pri inicializaciji!" << endl;
		return EXIT_FAILURE;
	}

	// debug faster
	igra.sound.toggle(); //samo za testing

	igra.branjeShranjenega();
	SDL_Event event;
	SDL_PollEvent(&event);
	short cur_pos = 1;
	bool izhod_switch = false;
	Image main;
	Image cursor;

	//main menu loop
	while (!igra.keys[SDL_SCANCODE_ESCAPE] && event.type != SDL_QUIT) {
		igra.okno.stejFrame();
		SDL_PollEvent(&event);
		SDL_RenderClear(igra.okno.ren);
		if (igra.isCompleted())
			main.ini(igra, "common/img/main_completed.png");
		else
			main.ini(igra, "common/img/main.png");

		main.display(igra.okno.ren);

		if (igra.keys[SDL_SCANCODE_UP]) {
			while (igra.keys[SDL_SCANCODE_UP]) { SDL_PollEvent(&event); }
			igra.sound.cursorMove();
			if (cur_pos == 1)
				cur_pos = 4;
			else
				cur_pos--;
		}
		else if (igra.keys[SDL_SCANCODE_DOWN]) {
			while (igra.keys[SDL_SCANCODE_DOWN]) { SDL_PollEvent(&event); }
			igra.sound.cursorMove();
			if (cur_pos == 4)
				cur_pos = 1;
			else
				cur_pos++;
		}

		switch (cur_pos) {
		case 1:
			cursor.init(igra, "common/img/cursor.png", 20, 120, 98, 49);
			cursor.display(igra.okno.ren);
			if (igra.keys[SDL_SCANCODE_RETURN]) {
				while (igra.keys[SDL_SCANCODE_RETURN]) { SDL_PollEvent(&event); }
				igra.sound.zacni();
				overworld(igra);
			}
			break;
		case 2:
			cursor.init(igra, "common/img/cursor.png", 20, 180, 98, 49);
			cursor.display(igra.okno.ren);
			if (igra.keys[SDL_SCANCODE_RETURN]) {
				while (igra.keys[SDL_SCANCODE_RETURN]) { SDL_PollEvent(&event); }
				igra.sound.vec();
				vec(igra);
			}
			break;
		case 3:
			cursor.init(igra, "common/img/cursor.png", 20, 240, 98, 49);
			cursor.display(igra.okno.ren);
			if (igra.keys[SDL_SCANCODE_RETURN]) {
				while (igra.keys[SDL_SCANCODE_RETURN]) { SDL_PollEvent(&event); }
				igra.sound.nastavitve();
				nastavitve(igra);
				cur_pos = 1;
			}
			break;
		case 4:
			if (igra.keys[SDL_SCANCODE_RETURN]) {
				while (igra.keys[SDL_SCANCODE_RETURN]) { SDL_PollEvent(&event); }
				igra.sound.izhod();
				izhod_switch = true;
			}
			cursor.init(igra, "common/img/cursor.png", 20, 320, 98, 49);
			cursor.display(igra.okno.ren);
			break;
		}
		SDL_RenderPresent(igra.okno.ren);
		if (izhod_switch)
			break;
		igra.okno.omejiFrame();
	}
	//igra.sound.nasvidenje();

	// cleanup
	igra.cleanup();
	return EXIT_SUCCESS;
}