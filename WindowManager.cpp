#include "WindowManager.h"

WindowManager::WindowManager() {
	window = NULL;
	surface = NULL;
	image = NULL;
	renderer = nullptr;

}
WindowManager::~WindowManager() {
	window = NULL;
	surface = NULL;
	image = NULL;
	renderer = nullptr;
}
int WindowManager::returnWindowWidth() {
	return Window_width;
}
int WindowManager::returnWindowHeight() {
	return Window_height;
}