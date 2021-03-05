#include "okno.h"

WindowManager::WindowManager() {
	window = NULL;
	surface = NULL;
	ren = nullptr;
	frameStart = 0;
	frameTime = 0;
}

WindowManager::~WindowManager() {
	window = NULL;
	surface = NULL;
	ren = nullptr;
}

void WindowManager::omejiFrame() {
	frameTime = SDL_GetTicks() - frameStart;
	if (frameDelay > frameTime)
		SDL_Delay(frameDelay - frameTime);
}

void WindowManager::toggleScaler() {
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

int WindowManager::scaleCal(int stevilo) {
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
		return int(stevilo * 1.5);
	default:
		cerr << "Error: scaleCal: " << scaler << endl;
		return 0;
	}
}