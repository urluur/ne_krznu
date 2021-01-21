#include "WindowManager.h"

WindowManager::WindowManager() {
	window = NULL;
	surface = NULL;
	image = NULL;
	ren = nullptr;

}
WindowManager::~WindowManager() {
	window = NULL;
	surface = NULL;
	image = NULL;
	ren = nullptr;
}
int WindowManager::returnWindowWidth() {
	return Window_width;
}
int WindowManager::returnWindowHeight() {
	return Window_height;
}
void WindowManager::toggleScaler() {
	switch (scaler) {
	case 1:
		scaler = 12;
		break;
	case 12:
		scaler = 15;
		break;
	case 15:
		scaler = 100;
		break;
	case 100:
		scaler = 5;
		break;
	case 5:
		scaler = 1;
		break;
	default:
		std::cout << "Error: toggleScaler" << std::endl;
	}
}
int WindowManager::scaleCal(int stevilo) {
	switch (scaler) {
	case 1:
		return stevilo * 1;
	case 12:
		return stevilo * 1.2;
	case 15:
		return stevilo * 1.5;
	case 5:
		return stevilo * 0.5;
	case 100:
		return stevilo * 1.7;
	default:
		std::cout << "Error: scaleCal" << std::endl;
	}
}
int WindowManager::vrniScaler() {
	return scaler;
}