#include "igra.h"

void GameManager::pripraviVse() {
	SDL_PollEvent(&event);
	konecLevela = false;

	stNaspr[0] = 4; stNaspr[1] = 3; stNaspr[2] = 2; stNaspr[3] = 1; stNaspr[4] = 0;
	stAktiv[0] = 3; stAktiv[1] = 5; stAktiv[2] = 7; stAktiv[3] = 10; stAktiv[4] = 1;
	stTjuln[0] = 5; stTjuln[1] = 10; stTjuln[2] = 15; stTjuln[3] = 20; stTjuln[4] = 0;
	
	//nared vektorje za nasprotnike aktiviste in tjulne
}

void GameManager::updateMap() {
	//(slike).display(okno.ren); //for cez use vectorje ubistvu
	SDL_RenderPresent(okno.ren);
	okno.omejiFrame();
}

GameManager::GameManager() {
	joystick = nullptr;
	SDL_PollEvent(&event);
	konecLevela = false;
	completed = false;
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
		preveriEsc(nivo);
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