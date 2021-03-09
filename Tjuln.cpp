#include "ZivoBitje.h"
Tjuln::Tjuln() { // konstruktor klican veckrat na zacetku usakega nivoja
	x = 0, y = 0;
	w = 63, h = 42;
	// nastavi nakljucno lokacijo, kjer se bo tjulen prikaze
	short ax = 0, bx = 1280 - w;
	short ay = 0, by = 720 - h;
	x = rand() % (bx - ax) + ax;
	y = rand() % (by - ay) + ay;
	img = new Image;
}
Tjuln::~Tjuln() {
	if (img != nullptr) {
		delete img;
		img = nullptr;
	}
}
void Tjuln::display(class GameManager& igra) { // tjulen se narise na zaslon
	img->display(igra.okno.ren);
}
void Tjuln::initImg(GameManager& igra, const char* path) { // inicializiramo sliko tjulna
	img->init(igra, path, x, y, w, h);
}
void Tjuln::updateImg(GameManager& igra) { // sliko posodobimo in narisemo na novih koordinatih
	img->init(igra, "common/img/tjuln.png", x, y, w, h);
}