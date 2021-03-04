#include "Tjuln.h"
Tjuln::Tjuln() {
	short ax = 0, bx = 1280 - w;
	short ay = 0, by = 720 - h;
	x = rand() % (bx - ax) + ax;
	y = rand() % (by - ay) + ay;

	img = new Image;
	jeNaFarmi = false;
}
Tjuln::~Tjuln() {
	if (img != nullptr) {
		delete img;
		img = nullptr;
	}
}
void Tjuln::display(class GameManager& igra) {
	img->display(igra.okno.ren);
}
void Tjuln::initImg(GameManager& igra, const char* path) {
	img->init(igra, path, x, y, w, h);
}