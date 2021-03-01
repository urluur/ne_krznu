#include "igra.h"

void GameManager::pripraviVse() {
	SDL_PollEvent(&event);
	konecLevela = false, adios = false, semNaIzhodniLokaciji = false;
	
	jaz.push_back(new Image);
	jaz.push_back(new Image);

	const short spawnPos[2][5] = {
	{200, 70,  30, 310, 150},  // x
	{ 20,  0, 530, 560, 555}}; // y
	igralec.setX(spawnPos[0][trenutniNivo - 1]);
	igralec.setY(spawnPos[1][trenutniNivo - 1]);
	jaz.at(0)->init(*this, "common/img/player.png", spawnPos[0][trenutniNivo-1], spawnPos[1][trenutniNivo-1], 58, 128);
	jaz.at(1)->init(*this, "common/img/player_noge.png", spawnPos[0][trenutniNivo-1], spawnPos[1][trenutniNivo-1], 58, 128);

	stAktiv[0] = 4; stAktiv[1] = 3; stAktiv[2] = 2; stAktiv[3] = 1; stAktiv[4] = 0;
	stNaspr[0] = 3; stNaspr[1] = 5; stNaspr[2] = 7; stNaspr[3] = 10; stNaspr[4] = 1;
	stTjuln[0] = 5; stTjuln[1] = 10; stTjuln[2] = 15; stTjuln[3] = 10; stTjuln[4] = 0;
	
	//nared vektorje za nasprotnike aktiviste in tjulne
}

void GameManager::updateMap() {
	//(slike).display(okno.ren); //for cez use vectorje ubistvu
	jaz.at(0)->display(okno.ren);
	SDL_RenderPresent(okno.ren);
	okno.omejiFrame();
}

GameManager::GameManager() {
	joystick = nullptr;
	SDL_PollEvent(&event);
	konecLevela = false;
	adios = false;
	completed = false;
	semNaIzhodniLokaciji = false;
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
	for (int i = 0; i < SDL_NumJoysticks(); i++)
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

void GameManager::cleanup() {
	jaz.clear();
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
	return (keys[SDL_SCANCODE_UP] || event.jhat.value == 1);
}
bool GameManager::checkDown() {
	return (keys[SDL_SCANCODE_DOWN] || event.jhat.value == 4);
}
bool GameManager::checkLeft() {
	return (keys[SDL_SCANCODE_LEFT] || event.jhat.value == 8);
}
bool GameManager::checkRight() {
	return (keys[SDL_SCANCODE_UP] || event.jhat.value == 2);
}
void GameManager::handleEvents() {
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			adios = true;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_UP)
				w = true;
			if (event.key.keysym.sym == SDLK_DOWN)
				s = true;
			if (event.key.keysym.sym == SDLK_LEFT)
				a = true;
			if (event.key.keysym.sym == SDLK_RIGHT)
				d = true;
			if (event.key.keysym.sym == SDLK_END)
				konecLevela = true;
			break;
		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_UP)
				w = false;
			if (event.key.keysym.sym == SDLK_DOWN)
				s = false;
			if (event.key.keysym.sym == SDLK_LEFT)
				a = false;
			if (event.key.keysym.sym == SDLK_RIGHT)
				d = false;
			break;
		}
	}
	if (w) igralec.setY(igralec.getY() - hitrost);
	if (a) igralec.setX(igralec.getX() - hitrost);
	if (s) igralec.setY(igralec.getY() + hitrost);
	if (d) igralec.setX(igralec.getX() + hitrost);
}

bool GameManager::isPlayerCollidingAt(const short x, const short y, const short w, const short h) {
	if (igralec.getX() < x + w &&
		igralec.getX() + igralec.getW() > x &&
		igralec.getY() < y + h &&
		igralec.getY() + igralec.getH() > y)
		return true;
	else
		return false;
}