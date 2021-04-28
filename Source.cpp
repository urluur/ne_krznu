#include "igra.h"

void nastavitve(GameManager&);
void vec(GameManager&);
void overworld(GameManager&);
void narisi(GameManager&, short&, Image&, Image&);
void nadaljuj(GameManager&, short&, bool&);
bool aliSmoNovIgralec(GameManager&);
bool aliSmoAdmin();

int main(int argv, char** args) {

	if (!aliSmoAdmin()) {
		printf("Zazeni igro kot administrator.\n(Potrebno za shranjevanje podatkov.)");
		bool za_izhod = _getch();
		return EXIT_SUCCESS;
	}

	// ustvarimo objekt igra, vecina potrebnega je ze pripravljenega
	GameManager igra;

	// nastavi se SDL
	bool problemi = igra.init();
	if (problemi) {
		cerr << "Problemi pri inicializaciji!" << endl;
		return EXIT_FAILURE;
	}

	// ce je igralec nov bo vpisal svoje ime
	if (aliSmoNovIgralec(igra)) {
		igra.igralec.setName(igra);
	}

	// shranjeni podatki se prekopirajo v glavne spremenjlivke
	igra.branjeShranjenega();

	SDL_PollEvent(&igra.event); // osvezivo stanje pritinjenih tipk

	// kazalec nastavimo na prvo mesto
	Image cursor;
	short cur_pos = 1;

	// ustvarimo sliko menija in meni narisemo na zaslon
	Image main;
	narisi(igra, cur_pos, cursor, main);

	bool izhod_switch = false;
	//glavna zanka menija
	while (!igra.keys[SDL_SCANCODE_ESCAPE] && igra.event.type != SDL_QUIT) {
		igra.okno.stejFrame(); // oznacimo zacetek zanke, da lahko na koncu zanke omejimo osvezevanje zaslona
		SDL_PollEvent(&igra.event); // osvezivo stanje pritinjenih tipk

		// preverimo ce so bile pritisnjene tipke gor dol start ali enter
		if (igra.checkUp()) {
			while (igra.checkUp()) { // ko tipko pritisnemo caka da jo spustimo
				SDL_PollEvent(&igra.event);
			}
			// predvaja zvok kazalca
			igra.sound.predvajaj("common/sounds/cur_mov.wav");
			// premakne kazalec na zeljeno mesto
			if (cur_pos == 1) {
				cur_pos = 4;
			}
			else {
				--cur_pos;
			}
			narisi(igra, cur_pos, cursor, main);
		}
		else if (igra.checkDown()) {
			while (igra.checkDown()) { // ko tipko pritisnemo caka da jo spustimo
				SDL_PollEvent(&igra.event);
			}
			// predvaja zvok kazalca
			igra.sound.predvajaj("common/sounds/cur_mov.wav");
			// premakne kazalec na zeljeno mesto
			if (cur_pos == 4) {
				cur_pos = 1;
			}
			else {
				++cur_pos;
			}
			narisi(igra, cur_pos, cursor, main);
		}
		else if (igra.checkEnter()) {
			nadaljuj(igra, cur_pos, izhod_switch); // nadaljuje program v drugi funkciji
			narisi(igra, cur_pos, cursor, main);
		}

		if (izhod_switch) {
			break;
		}
		igra.okno.omejiFrame(); // omejimo hitrost prikaza
	}

	// vse se izbrise in zapustimo program
	igra.cleanup();
	return EXIT_SUCCESS;
}

//klicemo ko zelimo menu narisati na zaslon
void narisi(GameManager& igra, short& cur_pos, Image& cursor, Image& main) {
	SDL_RenderClear(igra.okno.ren); // resetiramo renderer

	// ce igro zacnes se ti narise zalosten zacetek, ce si igro koncal pa srecen konec
	if (igra.isCompleted()) {
		if (igra.perfectRun()) {
			main.ini(igra, "common/img/main_perfect.png");
			if (!igra.returnRageMode()) {
				igra.sound.setMus("common/sounds/soundtrack_doom.mp3");
				igra.rageModeSet(true);
			}
		}
		else {
			main.ini(igra, "common/img/main_completed.png");
			if (igra.returnRageMode()) {
				igra.sound.setMus("common/sounds/soundtrack.wav");
				igra.rageModeSet(false);
			}
		}
	}
	else {
		main.ini(igra, "common/img/main.png");
		if (igra.returnRageMode()) {
			igra.sound.setMus("common/sounds/soundtrack.wav");
			igra.rageModeSet(false);
		}
	}

	// narisemo kazalec na dolocenih koordinatih na zaslonu, odvisno od pozicije
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
	cursor.display(igra.okno.ren); // kazalec se bo pokazal
	SDL_RenderPresent(igra.okno.ren); // na oknu se prikaze spremenjeno stanje

	system("cls");
	printf("### NE KRZNU -urlu ###\n");
	for (int i = 1; i <= 4; ++i) {
		if (cur_pos == i) {
			printf("->");
		}
		else {
			printf("  ");
		}
		switch (i) {
		case 1:
			printf("Zacni");
			break;
		case 2:
			printf("Vec");
			break;
		case 3:
			printf("Nastavitve");
			break;
		case 4:
			printf("Izhod");
			break;
		}
		if (cur_pos == i) {
			switch (cur_pos) {
			case 1:
				printf("      [Nova igra/nadaljuj]");
				break;
			case 2:
				printf("        [lestvica, koda, reset]");
				break;
			case 3:
				printf(" [slika, zvok, ime]");
				break;
			case 4:
				printf("      [zapri program (esc)]");
				break;
			}
		}
		
		printf("\n");
	}
}

// klicemo ko zelimo potrditi izbrano z kazalcem in nadaljevati v funkcijo oz. izhod
void nadaljuj(GameManager& igra, short& cur_pos, bool& izhod_switch) {
	while (igra.checkEnter()) { // dokler drzimo na tipko nas ne pusti naprej
		SDL_PollEvent(&igra.event);
	}
	switch (cur_pos) { // predvajamo zvok in naredimo zeljeno stvar
	case 1:
		igra.sound.predvajaj("common/sounds/zacni.wav");
		igra.replay->cleanup();
		overworld(igra); // zacnemo igro
		break;
	case 2:
		igra.sound.predvajaj("common/sounds/vec.wav");
		vec(igra); // gremo v meni "vec"
		cur_pos = 1;
		break;
	case 3:
		igra.sound.predvajaj("common/sounds/nastavitve.wav");
		nastavitve(igra); // gremo v nastavitve
		cur_pos = 1;
		break;
	case 4:
		igra.sound.predvajaj("common/sounds/izhod.wav");
		izhod_switch = true; // gremo iz glavne zanke menija
		break;
	}
}

bool aliSmoNovIgralec(GameManager& igra) { // klice se na zacetku, da odlocimo ali je igralec nov
	string tempName;
	short tempLvl;
	// beremo v dve zacasni spremenljivki
	igra.branjeShranjenega(tempName, tempLvl);

	// ce je prebrano enako privzetemu, domnevamo, da je igralec nov
	if ((tempName == "bumbar" && tempLvl == 0)) {
		igra.perfectRun(true);
		return true;
	}
	else {
		igra.perfectRun(false);
		return false;
	}
}

bool aliSmoAdmin() {
	ofstream preveri;
	ifstream preveri_branje;
	preveri.open("testiram.txt");
	if (preveri.is_open()) {
		preveri.close();
		remove("testiram.txt");

		// preverimo tudi ostale datoteke
		preveri_branje.open("quicksave.txt");
		if (preveri_branje.fail()) {
			preveri.open("quicksave.txt");
			preveri << "bumbar\n0\n3\n0\n";
			preveri.close();
		}
		else {
			preveri_branje.close();
		}

		preveri_branje.open("lestvica.txt");
		if (preveri_branje.fail()) {
			preveri.open("lestvica.txt");
			preveri << "[prosto] 0\n[prosto] 0\n[prosto] 0\n[prosto] 0\n[prosto] 0\n";
			preveri.close();
		}
		else {
			preveri_branje.close();
		}

		return true;
	}
	else {
		return false;
	}
}