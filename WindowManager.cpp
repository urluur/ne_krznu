#include "WindowManager.h"

WindowManager::WindowManager() {
	window = NULL;
	surface = NULL;
	ren = nullptr;
}
WindowManager::~WindowManager() {
	window = NULL;
	surface = NULL;
	ren = nullptr;
}
short WindowManager::returnWindowWidth() {
	return Window_width;
}
short WindowManager::returnWindowHeight() {
	return Window_height;
}
void WindowManager::toggleScaler() {
	switch (scaler) {
	case 1:
		scaler = 12;
		cout << "1,2";
		break;
	case 12:
		scaler = 15;
		cout << "1,5";
		break;
	case 15:
		scaler = 100;
		cout << "fullscreen";
		break;
	case 100:
		scaler = 5;
		cout << "0,5";
		break;
	case 5:
		scaler = 1;
		cout << "1 (original)";
		break;
	default:
		cerr << "Error: toggleScaler" << endl;
	}
	cout << endl;
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
		cerr << "Error: scaleCal: " << scaler << endl;
	}
}
short WindowManager::vrniScaler() {
	return scaler;
}