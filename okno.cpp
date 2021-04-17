#include "okno.h"

WindowManager::WindowManager() { // konstruktor inicializira spremenljivke
	window = NULL;
	surface = NULL;
	ren = nullptr;
	frameStart = 0;
	frameTime = 0;
}

WindowManager::~WindowManager() { // klice se ko se unici objekt "igra"
	window = NULL;
	surface = NULL;
	ren = nullptr;
}

void WindowManager::omejiFrame() { // klice se na koncu vsake glavne zanke
	// program zaustavi za toliko casa, da se zanka izvede 60x na sekundo
	frameTime = SDL_GetTicks() - frameStart;
	if (!Casovnik::paused) {
		Casovnik::milisekunde += frameTime;
	}
	if (frameDelay > frameTime) {
		SDL_Delay(frameDelay - frameTime);
		if (!Casovnik::paused) {
			Casovnik::milisekunde += (frameDelay - frameTime);
		}
	}
}

void WindowManager::toggleScaler() { // klice se v nastavitvah, ko spremenimo dimenzije
	// spremeni mnozitelj stvari na zaslonu, da so vse pravilno prikazane
	switch (scaler) {
	case 1:
		scaler = 12;
		printf("1,2");
		break;
	case 12:
		scaler = 15;
		printf("1,5");
		break;
	case 15:
		scaler = 100;
		printf("fullscreen");
		break;
	case 100:
		scaler = 5;
		printf("0,5");
		break;
	case 5:
		scaler = 1;
		printf("1 (original)");
		break;
	default:
		cerr << "Error: toggleScaler" << endl;
	}
	printf("\n");
}

int WindowManager::scaleCal(int stevilo) { // klice se pri postavljanju argumentov v druge funkcije
	// stevilko oz. spremenljivko mnozi z mnoziteljem, da se stvari prikazejo na pravem mestu na zaslonu
	switch (scaler) {
	case 1:
		return int(stevilo * 1);
	case 12:
		return int(stevilo * 1.2);
	case 15:
		return int(stevilo * 1.5);
	case 5:
		return int(stevilo * 0.5);
	case 100:
		return int(stevilo * 1.5); // naredi: support za zaslone ki niso 1080p
	default:
		cerr << "Error: scaleCal: " << scaler << endl;
		return 0;
	}
}