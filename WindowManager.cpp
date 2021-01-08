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
int WindowManager::returnWindow_width() {
	return Window_width;
}
int WindowManager::returnWindow_height() {
	return Window_height;
}