#include "ZivoBitje.h"

Kepa::Kepa(GameManager &pointerNaIgro) {
	// nastavimo privzete spremenljivke
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

	// smer premikanja igralca je tudi smer premikanja kepe
	ww = igra->w;
	a = igra->a;
	s = igra->s;
	d = igra->d;
	if (!(ww || a || s || d)) {
		d = true; // s tem dolocimo smer premikanja kepe v desno, ce je igralec ne premika
	}
	startMoving();
}

Kepa::Kepa(GameManager& pointerNaIgro, komoucar* pointerNaBossa) {
	// nastavimo privzete spremenljivke
	x = 0;
	y = 0;
	w = 30;
	h = 30;

	to_go = 100;
	done = 0;
	igra = &pointerNaIgro;
	if (!igra->returnRageMode()) {
		hitrost = 3;
	}
	else {
		hitrost = 4;
	}
	nosilec = -1;
	ignore_me = false;

	ww = false;
	a = false;
	s = false;
	d = false;
	if (pointerNaBossa->dest_x < pointerNaBossa->x) {
		a = true;
	}
	else if (!(pointerNaBossa->dest_x == pointerNaBossa->x)) {
		d = true;
	}
	if (pointerNaBossa->dest_y < pointerNaBossa->y) {
		ww = true;
	}
	else if (!(pointerNaBossa->dest_y == pointerNaBossa->y)) {
		s = true;
	}
	startMoving(pointerNaBossa);
}

void Kepa::startMoving(komoucar* pointerNaBossa) {
	x = pointerNaBossa->x;
	y = pointerNaBossa->y;
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
	// kepa se premika dokler ne naredi zeljene razdalje
	if (done <= to_go) {
		if (ww) { // premikanje gor
			y -= hitrost;
		}
		if (a) { // premikanje levo
			x -= hitrost;
		}
		if (s) { // premikanje dol
			y += hitrost;
		}
		if (d) { // premikanje desno
			x += hitrost;
		}
		++done;
		img->init(*igra, "common/img/kepa.png", x, y, w, h);
		img->display(igra->okno.ren);
		return true; // kepa se more premikati se naprej
	}
	else {
		return false; // kepa je na svoji destinaciji
	}
}