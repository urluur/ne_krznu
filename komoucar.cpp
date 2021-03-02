#include "komoucar.h"
komoucar::komoucar() {
	img = new Image;
	x = 0;
	y = 0;
}
komoucar::~komoucar() {
	if (img != nullptr) {
		delete img;
		img = nullptr;
	}
}
void komoucar::initImg(GameManager& igra, const char* path,
	unsigned short x, unsigned short y, unsigned short w, unsigned short h)
{
	img->init(igra, path, x, y, w, h);
}
void komoucar::display(GameManager& igra) {
	img->display(igra.okno.ren);
}