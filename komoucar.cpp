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
	short iks, short ipsilon)
{
	x = iks;
	y = ipsilon;
	img->init(igra, path, x, y, w, h);
}
void komoucar::updateImg(GameManager& igra)
{
	if (igra.trenutniNivo < 5) {
		img->init(igra, "common/img/nasprotnik.png", x, y, w, h);
	}
	else {
		img->init(igra, "common/img/boss.png", x, y, w, h);
	}
}
void komoucar::display(GameManager& igra) {
	img->display(igra.okno.ren);
}
void komoucar::zrcuniRandomDestinacijo() {
	short ax = 0, bx = 1280 - w;
	short ay = 0, by = 720 - h;
	dest_x = rand() % (bx - ax) + ax;
	dest_y = rand() % (by - ay) + ay;
}
bool komoucar::sprehodNaRandomDestinacijo() {
	if (ManhattanDistance(x, y, dest_x, dest_y) < 10) {
		return true;
	}
	else {
		if (x != dest_x)
			(x < dest_x) ? x += hitrost : x -= hitrost;
		if (y != dest_y)
			(y < dest_y) ? y += hitrost : y -= hitrost;
		return false;
	}
}
void komoucar::setDest(short iks, short ipsilon) {
	dest_x = iks;
	dest_y = ipsilon;
}