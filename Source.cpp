#include "includes.h"
#undef main

void nastavitve(GameManager&);
void vec(GameManager&);
void overworld(GameManager&);
void narisi(GameManager&, short&, Image&, Image&);
void nadaljuj(GameManager&, short&, bool&);

int main() {
	GameManager igra;

	bool problemi = igra.init();
	if (problemi) {
		cerr << "Problemi pri inicializaciji!" << endl;
		return EXIT_FAILURE;
	}

	// debug faster
	//igra.sound.toggle(); //samo za testing

	/* to je sam za testiranje levela
	for (short i = 0; i < 5;) {
		igra.level(i);
	}
	//*/

	//* ok tuki je overworld in use to
	igra.branjeShranjenega();
	SDL_PollEvent(&igra.event);
	short cur_pos = 1;
	bool izhod_switch = false;
	Image main;
	Image cursor;
	narisi(igra, cur_pos, cursor, main);

	//main menu loop
	while (!igra.keys[SDL_SCANCODE_ESCAPE] && igra.event.type != SDL_QUIT) {
		igra.okno.stejFrame();
		SDL_PollEvent(&igra.event);

		if (igra.checkUp()) {
			while (igra.checkUp()) { SDL_PollEvent(&igra.event); }
			igra.sound.cursorMove();
			if (cur_pos == 1)
				cur_pos = 4;
			else
				cur_pos--;
			narisi(igra, cur_pos, cursor, main);
		}
		else if (igra.checkDown()) {
			while (igra.checkDown()) { SDL_PollEvent(&igra.event); }
			igra.sound.cursorMove();
			if (cur_pos == 4)
				cur_pos = 1;
			else
				cur_pos++;
			narisi(igra, cur_pos, cursor, main);
		}
		else if (igra.checkEnter()) {
			nadaljuj(igra, cur_pos, izhod_switch);
			narisi(igra, cur_pos, cursor, main);
		}

		if (izhod_switch)
			break;
		igra.okno.omejiFrame();
	}
	//igra.sound.nasvidenje();
	//*/
	
	igra.cleanup();
	return EXIT_SUCCESS;
}

void narisi(GameManager& igra, short& cur_pos, Image& cursor, Image& main) {
	SDL_RenderClear(igra.okno.ren);

	if (igra.isCompleted())
		main.ini(igra, "common/img/main_completed.png");
	else
		main.ini(igra, "common/img/main.png");

	main.display(igra.okno.ren);
	switch (cur_pos) {
	case 1:
		cursor.init(igra, "common/img/cursor.png", 20, 120, 98, 49);
		break;
	case 2:
		cursor.init(igra, "common/img/cursor.png", 20, 180, 98, 49);
		break;
	case 3:
		cursor.init(igra, "common/img/cursor.png", 20, 240, 98, 49);
		break;
	case 4:
		cursor.init(igra, "common/img/cursor.png", 20, 320, 98, 49);
		break;
	}
	cursor.display(igra.okno.ren);
	SDL_RenderPresent(igra.okno.ren);
}

void nadaljuj(GameManager& igra, short& cur_pos, bool& izhod_switch) {
	while (igra.checkEnter()) { SDL_PollEvent(&igra.event); }
	switch (cur_pos) {
	case 1:
		igra.sound.zacni();
		overworld(igra);
		break;
	case 2:
		igra.sound.vec();
		vec(igra);
		break;
	case 3:
		igra.sound.nastavitve();
		nastavitve(igra);
		cur_pos = 1;
		break;
	case 4:
		igra.sound.izhod();
		izhod_switch = true;
		break;
	}
}