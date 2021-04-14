#include "ZivoBitje.h"

Kepa::Kepa(GameManager &pointerNaIgro) {
	x = 0;
	y = 0;
	w = 30;
	h = 30;
	
	to_go = 100;
	done = 0;
	hitrost = 3;
	nosilec = -1;
	igra = &pointerNaIgro;
	ignore_me = false;

	ww = igra->w;
	a = igra->a;
	s = igra->s;
	d = igra->d;
	if (!(ww || a || s || d)) {
		d = true; // s tem dolocimo smer premikanja kepe v desno, ce je igralec ne premika
	}
	startMoving();
}

Kepa::~Kepa() {
	if (img != nullptr) {
		delete img;
		img = nullptr;
	}
	if (igra != nullptr) {
		igra = nullptr;
	}
}

void Kepa::startMoving() {
	x = igra->igralec.x + igra->igralec.w;
	y = igra->igralec.y;
}

bool Kepa::move() {
	if (done <= to_go) {
		if (ww) {
			y -= hitrost;
		}
		if (a) {
			x -= hitrost;
		}
		if (s) {
			y += hitrost;
		}
		if (d) {
			x += hitrost;
		}
		++done;
		img->init(*igra, "common/img/kepa.png", x, y, w, h);
		img->display(igra->okno.ren);
		return true;
	}
	else {
		return false;
	}
}