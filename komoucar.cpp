#include "komoucar.h"
komoucar::komoucar() {
	img = new Image;
	x = 0;
	y = 0;
	hitrost = 1;
	dest_x = 0;
	dest_y = 0;
}
komoucar::~komoucar() {
	if (img != nullptr) {
		delete img;
		img = nullptr;
	}
}
void komoucar::initImg(GameManager& igra, const char* path,
	unsigned short iks, unsigned short ipsilon)
{
	x = iks;
	y = ipsilon;
	img->init(igra, path, x, y, w, h);
}
void komoucar::updateImg(GameManager& igra)
{
	img->init(igra, "common/img/boss.png", x, y, w, h);
}
void komoucar::display(GameManager& igra) {
	img->display(igra.okno.ren);
}
void komoucar::zrcuniRandomDestinacijo() {
	unsigned short ax = 0, bx = 1280-w;
	unsigned short ay = 0, by = 720-h;
	dest_x = rand() % (bx - ax) + ax;
	dest_y = rand() % (by - ay) + ay;
}
bool komoucar::sprehodNaRandomDestinacijo() {
	if (x == dest_x && y == dest_y) {
		return true;
	}
	else {
		if(x != dest_x)
			(x < dest_x) ? x+=hitrost : x-=hitrost;
		if(y != dest_y)
			(y < dest_y) ? y+=hitrost : y-=hitrost;
		return false;
	}
}