#include "igra.h"

// klice se vsakic ko hocemo preveriti ali je uporabnik kliknil tipko esc za zasilni izhod
void GameManager::preveriEsc(short& nivo) {
	SDL_PollEvent(&event); // osvezimo stanje pritisnjenih tipk
	if ((keys[SDL_SCANCODE_ESCAPE] || event.type == SDL_QUIT)) {
		while (keys[SDL_SCANCODE_ESCAPE]) { // dokler drzimo tipko ne gre naprej
			SDL_PollEvent(&event);
		}

		//shranimo napredek v datoteke
		setNivo(nivo);
		zasilnoShranjevanje();

		// pocistimo pomnilnik in zaustavimo program
		cleanup();
		exit(0);
	}
}

// funkcije vrnejo stanje tipke (testiram da bi delovalo tudi s igralnim plosckom)
bool GameManager::checkQuit() {
	return (keys[SDL_SCANCODE_ESCAPE] || event.type == SDL_QUIT);
}
bool GameManager::checkEnter() {
	return (keys[SDL_SCANCODE_RETURN]);
}
bool GameManager::checkUp() {
	return (keys[SDL_SCANCODE_UP]);/* || event.jhat.value == 1*/
}
bool GameManager::checkDown() {
	return (keys[SDL_SCANCODE_DOWN]);/* || event.jhat.value == 4*/
}
bool GameManager::checkLeft() {
	return (keys[SDL_SCANCODE_LEFT]);/* || event.jhat.value == 8*/
}
bool GameManager::checkRight() {
	return (keys[SDL_SCANCODE_UP]);/* || event.jhat.value == 2*/
}

void GameManager::handleEvents() { // funkcija je klicana v glavni zanki nivoja
// preverimo pritisnjene tipke, trke z okoljem, obdelamo igralcevo uzdrljivost in premikanje
	while (SDL_PollEvent(&event)) {
		// pogledamo kateri dogodki so se zgodili
		switch (event.type) {
		case SDL_QUIT: // ce je bil pritisnjen krizec
			adios = true;
			break;
		case SDL_KEYDOWN: // ce je bila pritisnjena tipka na tipkovnici
			if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w)
				w = true;
			if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s)
				s = true;
			if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a) {
				a = true;
			}
			if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d) {
				d = true;
			}
			if ((event.key.keysym.sym == SDLK_LSHIFT || event.key.keysym.sym == SDLK_RSHIFT) && (w || a || s || d))
				staminadown = true;
			if (keys[SDL_SCANCODE_PAUSE] || event.key.keysym.sym == SDLK_p)
				pause();
			if (trenutniNivo == 5) {
				if (event.key.keysym.sym == SDLK_q || event.key.keysym.sym == SDLK_COMMA)
					udari();
				if (event.key.keysym.sym == SDLK_e || event.key.keysym.sym == SDLK_PERIOD)
					kepaOrReflect();
				if (event.key.keysym.sym == SDLK_f || event.key.keysym.sym == SDLK_MINUS)
					vrziTjulna();
			}
			//* za testiranje nivojev lahko nivo preskocis s tipko "end"
			if (event.key.keysym.sym == SDLK_END)
				konecLevela = true;
			//*/
			igralec.sepremika(true); // dovoli da se animirajo noge, ko se premikamo
			break;
		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w)
				w = false;
			if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s)
				s = false;
			if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a) {
				a = false;
			}
			if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d) {
				d = false;
			}

			if ((event.key.keysym.sym == SDLK_LSHIFT || event.key.keysym.sym == SDLK_RSHIFT) || !(w || a || s || d))
				staminadown = false;
			break;
		}
	}

	// polni ali prazni uzdrzljivost ter jo narise
	racuniStamino();

	if (!(w || a || s || d)) {
		igralec.sepremika(false); // igralcu se ne premikajo noge, ko se ne premika
	}
	else {
		// premaknemo igralca za "hitrost" pikslov v zeljeno smer
		if (w) {
			igralec.setY(igralec.y - hitrost);
		}
		if (a) {
			igralec.setX(igralec.x - hitrost);
		}
		if (s) {
			igralec.setY(igralec.y + hitrost);
		}
		if (d) {
			igralec.setX(igralec.x + hitrost);
		}
		trkiOkolje(); // preveri trke med igralcem in nepremikajocimi zadevami
	}
}