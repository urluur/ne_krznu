#include "igra.h"

void GameManager::preveriEsc(short& nivo) {
	SDL_PollEvent(&event);
	if ((keys[SDL_SCANCODE_ESCAPE] || event.type == SDL_QUIT)) {
		while (keys[SDL_SCANCODE_ESCAPE]) { SDL_PollEvent(&event); }
		setNivo(nivo);
		zasilnoShranjevanje();
		cleanup();
		exit(0);
	}
}

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
void GameManager::handleEvents() {
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			adios = true;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w)
				w = true;
			if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s)
				s = true;
			if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a)
				a = true;
			if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d)
				d = true;
			if (event.key.keysym.sym == SDLK_END)
				konecLevela = true;
			if ((event.key.keysym.sym == SDLK_LSHIFT || event.key.keysym.sym == SDLK_RSHIFT) && (w || a || s || d))
				staminadown = true;
			trkiOkolje();
			break;
		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w)
				w = false;
			if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s)
				s = false;
			if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a)
				a = false;
			if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d)
				d = false;
			if ((event.key.keysym.sym == SDLK_LSHIFT || event.key.keysym.sym == SDLK_RSHIFT) || !(w || a || s || d))
				staminadown = false;
			break;
		}
	}

	racuniStamino();

	if (w) igralec.setY(igralec.getY() - hitrost);
	if (a) igralec.setX(igralec.getX() - hitrost);
	if (s) igralec.setY(igralec.getY() + hitrost);
	if (d) igralec.setX(igralec.getX() + hitrost);
}