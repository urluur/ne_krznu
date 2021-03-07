#include "igra.h"

void GameManager::pripraviVse() { // funkcija se klice na zacetku usakega od petih nivojev
	SDL_PollEvent(&event);

	// vse spremenljivke glede nivoja so resetirane
	konecLevela = false; adios = false;
	semNaIzhodniLokaciji = false;
	staminadown = false; fillingStamina = false;
	w = false; a = false; s = false; d = false;
	stTjulnFarma = 0;
	jaz = new Image;
	
	// pozicija na na kateri se igralec pokaze
	const short spawnPos[2][5] = {
	// 1.  2.   3.   4.   5. nivo
	{200, 70,  30, 320, 150},   // x
	{ 20,  5, 530, 650, 600} }; // y

	// igralca postavimo na zacetno mesto 
	igralec.setX(spawnPos[0][trenutniNivo - 1]);
	igralec.setY(spawnPos[1][trenutniNivo - 1]);
	jaz->init(*this, "common/img/player.png", spawnPos[0][trenutniNivo - 1], spawnPos[1][trenutniNivo - 1], igralec.getW(), igralec.getH());

	// stevilo aktivistov, nasprotnikov in tjulnov, ki jih bomo videli v nivoju
	//           1.              2.              3.              4.             5. nivo
	stAktiv[0] = 2; stAktiv[1] = 2; stAktiv[2] = 1; stAktiv[3] = 1; stAktiv[4] = 0;
	stNaspr[0] = 2; stNaspr[1] = 3; stNaspr[2] = 4; stNaspr[3] = 5; stNaspr[4] = 1;
	stTjuln[0] = 4; stTjuln[1] = 6; stTjuln[2] = 8; stTjuln[3] = 6; stTjuln[4] = 0;

	// ustvarimo toliko nasprotnikov, kolikor jih v nivoju potrebujemo
	for (int i = 0; i < stNaspr[trenutniNivo - 1]; ++i) {
		enemy.push_back(new komoucar);
		if (trenutniNivo < 5) { // v vseh nivojih so nasprotniki rumeni, razen v 5. nivoju je rdec (boss.png)
			enemy.at(i)->initImg(*this, "common/img/nasprotnik.png", farmPos[0][trenutniNivo - 1] - i * 10, farmPos[1][trenutniNivo - 1] - i * 10);
		}
		else {
			enemy.at(i)->initImg(*this, "common/img/boss.png", farmPos[0][trenutniNivo - 1] - i * 10, farmPos[1][trenutniNivo - 1] - i * 10);
		}
		enemy.at(i)->zrcuniRandomDestinacijo(); // nasprotnik si izbere nakljucno lokacijo na katero se bo premaknil
	}

	// ustvarimo toliko tjulnov, kolikor jih v nivoju potrebujemo
	for (int i = 0; i < stTjuln[trenutniNivo - 1]; ++i) {
		tjulni.push_back(new Tjuln);
		tjulni.at(i)->initImg(*this, "common/img/tjuln.png");
	}
	
	// naredi: ustvari aktiviste
}

void GameManager::updateMap() { // funkcija se klice na koncu zanke nivoja
	// vse slike se bodo prikazale
	jaz->display(okno.ren);
	for (unsigned int i = 0; i < enemy.size(); ++i) {
		enemy.at(i)->display(*this);
	}
	for (unsigned int i = 0; i < tjulni.size(); ++i) {
		tjulni.at(i)->display(*this);
	}
	SDL_RenderPresent(okno.ren); // na oknu se prikaze spremenjeno stanje
	okno.omejiFrame(); // omejimo hitrost prikaza
}

GameManager::GameManager() { // konstruktor je klican le enkrat, zgolj ko se program zazene
	// inicializiramo vse spremenljivke
	stTjulnFarma = 0;
	//joystick = nullptr; //(testiram)
	jaz = nullptr;
	stamina_wheel = new Image;
	konecLevela = false;
	adios = false;
	completed = false;
	semNaIzhodniLokaciji = false;
	fillingStamina = false;
	staminadown = false;
	stamina = 100;
	hitrost = 2;
	trenutniNivo = 0;
	stAktiv[0] = 2; stAktiv[1] = 2; stAktiv[2] = 1; stAktiv[3] = 1; stAktiv[4] = 0;
	stNaspr[0] = 2; stNaspr[1] = 3; stNaspr[2] = 4; stNaspr[3] = 5; stNaspr[4] = 1;
	stTjuln[0] = 4; stTjuln[1] = 6; stTjuln[2] = 8; stTjuln[3] = 6; stTjuln[4] = 0;
	SDL_PollEvent(&event);
}

int GameManager::init() { // funkcija se klice le enkrat, ko se zazene SDL okno
	 // SDL inicializacija
	 if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cerr << "SDL Init, Error: " << SDL_GetError() << endl;
		return EXIT_FAILURE;
	}
	// ustvarimo SDL okno
	okno.window = SDL_CreateWindow("NE krznu -urlu", // naslov okna
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, // pozicija okna
		// velikost okna pomnozena z nasimi zeljenimi dimentijami
		okno.scaleCal(okno.returnWindowWidth()), okno.scaleCal(okno.returnWindowHeight()),
		SDL_WINDOW_SHOWN); // okno je vidno
	if (okno.window == NULL) {
		cerr << "SDL Create Window, Error: " << SDL_GetError() << endl;
		return EXIT_FAILURE;
	}
	// ustvarimo renderer (SDL struktura, ki prikaze piksle v okno na zaslonu)
	// (-1) uporabimo prvi kompatibilni grficni gonilnik, uporabljamo graficno kartico, ce je mogoce
	okno.ren = SDL_CreateRenderer(okno.window, -1, SDL_RENDERER_ACCELERATED);
	if (okno.ren == nullptr) {
		cerr << "Could not create ren! SDL error" << SDL_GetError() << endl;
		return EXIT_FAILURE;
	}
	if (TTF_Init()) { // inicializacija pisav (TrueTypeFont)
		cerr << "TTF_Init Error: " << TTF_GetError() << endl;
		return EXIT_FAILURE;
	}
	okno.surface = SDL_GetWindowSurface(okno.window); // inicializacija za prikazovanje slik
	if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))) {
		printf("IMG_Init Error: %s\n", IMG_GetError());
		return EXIT_FAILURE;
	}

	// nastavimo ikono v opravilni vrstici in oknu
	Image ikona(okno.ren, "common/img/ikona.png", 0, 0, 29, 29);
	SDL_Surface icon = ikona.returnSurface();
	SDL_SetWindowIcon(okno.window, &icon);

	/* lenartov nacin za kontroler (zelo zelo alfa testiram)
	int numJoystick = SDL_NumJoysticks();
	printf("%i joysticks were found.\n\n", SDL_NumJoysticks());
	printf("The names of the joysticks are:\n");
	for (int i = 0; i < SDL_NumJoysticks(); ++i)
		std::cout << "	" << SDL_JoystickNameForIndex(i) << std::endl;
	if (numJoystick > 0) {
		SDL_JoystickEventState(SDL_ENABLE);
		joystick = SDL_JoystickOpen(0);
	}
	*/
	
	srand((unsigned int)time(NULL)); // poskrbi da generiramo nakljucna stevila
	return EXIT_SUCCESS;
}

void GameManager::haltEnter(short nivo) { // se klice, ko cakamo da igralec pritisne tipko enter
	// prikazemo sliko "pritisni enter"
	Image img_enter;
	img_enter.ini(*this, "common/img/pressreturn.png");
	img_enter.display(okno.ren);
	SDL_RenderPresent(okno.ren);

	// dokler igralec ne pritisne na enter, previrjamo ce bo pritisnil na esc za prisilni izhod
	SDL_PollEvent(&event);
	while (!keys[SDL_SCANCODE_RETURN]) {
		okno.stejFrame();
		preveriEsc(nivo);
		okno.omejiFrame(); // omejimo osvezevanje zaslona, da racunalnik ne dela kolikor hitro zmore
	}
}

void GameManager::setCompleted(bool resnica) { // se klice, ko koncamo vseh 5 nivojev
	completed = resnica; // ta spremenljivka bo nastavila drugacen zacetni zaslon (vesel konec)
	setNivo(0);

	// glede na to da smo igro koncali se podatki resetirajo, da ob izhodu drug igralec lahko upise svoje ime
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

void GameManager::cleanupVectors() { // se klice, ko hocemo izbrisati dinamicni pomnilnik (po vsakem nivoju in na koncu igre)
	if (jaz != nullptr) {
		delete jaz; // izbrisemo sliko igralca
		jaz = nullptr;
	}
	if (!enemy.empty()) { // brisemo
		for (unsigned int i = 0; i < enemy.size(); ++i) {
			delete enemy.at(i); // izbrisemo vse nasprotnike
		}
		enemy.clear(); // izbrisemo vse kazalce na izbrisane nasprotnike
		enemy.shrink_to_fit(); // vektorjevo kapaciteto zmanjsamo, ce je mogoce
	}
	if (!tjulni.empty()) {
		for (unsigned int i = 0; i < tjulni.size(); ++i) {
			delete tjulni.at(i); // izbrisemo vse tjulne
		}
		tjulni.clear();  // izbrisemo vse kazalce na izbrisane tjulne
		tjulni.shrink_to_fit(); // vektorjevo kapaciteto zmanjsamo, ce je mogoce
	}
}

void GameManager::cleanup() { // se klice ko zelimo popolnoma zapreti igro
	if (stamina_wheel != nullptr) {
		delete stamina_wheel; // sliko igralcene uzdrzljivosti brisemo le enkrat, saj jo dinamicno dolocimo le enkrat
		stamina_wheel = nullptr;
	}
	cleanupVectors(); // preverimo in izbrisemo dinamicni pomnilnik
	jaz = nullptr;
	SDL_DestroyWindow(okno.window); // zapremo okno
	/* to samo testiram za kontroler
	if (joystick != nullptr) SDL_JoystickClose(joystick);
	*/
	SDL_Quit(); // izhod iz SDL
}