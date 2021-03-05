#include "igra.h"

void GameManager::pripraviVse() {
	SDL_PollEvent(&event);
	konecLevela = false; adios = false;
	semNaIzhodniLokaciji = false;
	staminadown = false; fillingStamina = false;
	w = false; a = false; s = false; d = false;
	stTjulnFarma = 0;

	jaz = new Image;

	const short spawnPos[2][5] = {
	{200, 70,  30, 320, 150},   // x
	{ 20,  5, 530, 650, 600} }; // y
	igralec.setX(spawnPos[0][trenutniNivo - 1]);
	igralec.setY(spawnPos[1][trenutniNivo - 1]);
	jaz->init(*this, "common/img/player.png", spawnPos[0][trenutniNivo - 1], spawnPos[1][trenutniNivo - 1], igralec.getW(), igralec.getH());

	stAktiv[0] = 2; stAktiv[1] = 2; stAktiv[2] = 1; stAktiv[3] = 1; stAktiv[4] = 0;
	stNaspr[0] = 2; stNaspr[1] = 3; stNaspr[2] = 4; stNaspr[3] = 5; stNaspr[4] = 1;
	stTjuln[0] = 4; stTjuln[1] = 6; stTjuln[2] = 8; stTjuln[3] = 6; stTjuln[4] = 0;

	for (int i = 0; i < stNaspr[trenutniNivo - 1]; ++i) {
		enemy.push_back(new komoucar);
		if (trenutniNivo < 5) {
			enemy.at(i)->initImg(*this, "common/img/nasprotnik.png", 500, 500); // te stevile so spawnpoint
		}
		else {
			enemy.at(i)->initImg(*this, "common/img/boss.png", 500, 500); // te stevile so spawnpoint
		}
		enemy.at(i)->zrcuniRandomDestinacijo();
	}

	for (int i = 0; i < stTjuln[trenutniNivo - 1]; ++i) {
		tjulni.push_back(new Tjuln);
		tjulni.at(i)->initImg(*this, "common/img/tjuln.png");
	}
	//nared vektorje za nasprotnike aktiviste in tjulne
}

void GameManager::updateMap() {
	//for cez use vectorje ubistvu
	jaz->display(okno.ren);
	for (int i = 0; i < stNaspr[trenutniNivo - 1]; ++i) { //spremen na douzino vektorja
		enemy.at(i)->display(*this);
	}
	for (int i = 0; i < stTjuln[trenutniNivo - 1]; ++i) { //spremen na douzino vektorja
		tjulni.at(i)->display(*this);
	}
	SDL_RenderPresent(okno.ren);
	okno.omejiFrame();
}

GameManager::GameManager() {
	stTjulnFarma = 0;
	joystick = nullptr;
	jaz = nullptr;
	stamina_wheel = new Image;
	SDL_PollEvent(&event);
	konecLevela = false;
	adios = false;
	completed = false;
	semNaIzhodniLokaciji = false;
	fillingStamina = false;
	staminadown = false;
	stamina = 100;
	hitrost = 2;
	trenutniNivo = 0;
}

int GameManager::init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cerr << "SDL Init, Error: " << SDL_GetError() << endl;
		return EXIT_FAILURE;
	}
	okno.window = SDL_CreateWindow("NE krznu -urlu",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		okno.scaleCal(okno.returnWindowWidth()), okno.scaleCal(okno.returnWindowHeight()),
		SDL_WINDOW_SHOWN);
	if (okno.window == NULL) {
		cerr << "SDL Create Window, Error: " << SDL_GetError() << endl;
		return EXIT_FAILURE;
	}
	okno.ren = SDL_CreateRenderer(okno.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (okno.ren == nullptr) {
		cerr << "Could not create ren! SDL error" << SDL_GetError() << endl;
		return EXIT_FAILURE;
	}
	if (TTF_Init()) {
		cerr << "TTF_Init Error: " << TTF_GetError() << endl;
		return EXIT_FAILURE;
	}
	okno.surface = SDL_GetWindowSurface(okno.window);
	if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))) {
		printf("IMG_Init Error: %s\n", IMG_GetError());
		return EXIT_FAILURE;
	}

	Image ikona(okno.ren, "common/img/ikona.png", 0, 0, 29, 29);
	SDL_Surface icon = ikona.returnSurface();
	SDL_SetWindowIcon(okno.window, &icon);

	int numJoystick = SDL_NumJoysticks();
	printf("%i joysticks were found.\n\n", SDL_NumJoysticks());
	printf("The names of the joysticks are:\n");
	for (int i = 0; i < SDL_NumJoysticks(); ++i)
		std::cout << "	" << SDL_JoystickNameForIndex(i) << std::endl;
	if (numJoystick > 0) {
		SDL_JoystickEventState(SDL_ENABLE);
		joystick = SDL_JoystickOpen(0);
	}

	srand((unsigned int)time(NULL));
	return EXIT_SUCCESS;
}

void GameManager::haltEnter(short nivo) {
	Image img_enter; //(okno.ren, "common/img/pressreturn.png", 0, 0, okno.scaleCal(okno.returnWindowWidth()), okno.scaleCal(okno.returnWindowHeight()));
	img_enter.ini(*this, "common/img/pressreturn.png");
	img_enter.display(okno.ren);
	SDL_RenderPresent(okno.ren);
	SDL_PollEvent(&event);
	while (!keys[SDL_SCANCODE_RETURN]) {
		okno.stejFrame();
		preveriEsc(nivo);
		okno.omejiFrame();
	}
}

void GameManager::setCompleted(bool resnica) {
	completed = resnica;
	setNivo(0);
	ofstream quicksave;
	quicksave.open("quicksave.txt");
	if (quicksave.is_open())
		quicksave << "bumbar\n0\n";
	else {
		cerr << "Error: setting complete" << endl;
		cleanup();
		exit(1);
	}
	quicksave.close();
}

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

void GameManager::cleanupVectors() {
	if (jaz != nullptr) {
		delete jaz;
		jaz = nullptr;
	}
	if (!enemy.empty()) {
		for (unsigned int i = 0; i < enemy.size(); ++i) {
			delete enemy.at(i);
		}
		enemy.clear();
		enemy.shrink_to_fit();
	}
	if (!tjulni.empty()) {
		for (unsigned int i = 0; i < tjulni.size(); ++i) {
			delete tjulni.at(i);
		}
		tjulni.clear();
		tjulni.shrink_to_fit();
	}
}

void GameManager::cleanup() {
	if (stamina_wheel != nullptr) {
		delete stamina_wheel;
		stamina_wheel = nullptr;
	}
	cleanupVectors();
	// zbris vektor od nasprotnika
	jaz = nullptr;
	SDL_DestroyWindow(okno.window);
	if (joystick != nullptr) SDL_JoystickClose(joystick);
	SDL_Quit();
}

bool GameManager::checkQuit() {
	return (keys[SDL_SCANCODE_ESCAPE] || event.type == SDL_QUIT);
}
bool GameManager::checkEnter() {
	return (keys[SDL_SCANCODE_RETURN]);
}
bool GameManager::checkUp() {
	return (keys[SDL_SCANCODE_UP]/* || event.jhat.value == 1*/);
}
bool GameManager::checkDown() {
	return (keys[SDL_SCANCODE_DOWN]/* || event.jhat.value == 4*/);
}
bool GameManager::checkLeft() {
	return (keys[SDL_SCANCODE_LEFT]/* || event.jhat.value == 8*/);
}
bool GameManager::checkRight() {
	return (keys[SDL_SCANCODE_UP]/* || event.jhat.value == 2*/);
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