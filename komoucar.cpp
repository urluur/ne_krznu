#include "komoucar.h"
komoucar::komoucar() { // konstruktor se klice za vsakega ustvarjenega nasprotnika
	img = new Image;
	x = 0;
	y = 0;
	hitrost = 1;
	dest_x = 0;
	dest_y = 0;
}
komoucar::~komoucar() { // destruktor se klice na koncu vsakega nivoja
	if (img != nullptr) {
		delete img;
		img = nullptr;
	}
}
void komoucar::initImg(GameManager& igra, const char* path,
	short iks, short ipsilon) // se klice da nastavimo sliko in zaceno pozicijo naprotnika
{
	x = iks;
	y = ipsilon;
	img->init(igra, path, x, y, w, h);
}
void komoucar::updateImg(GameManager& igra) { // se klice ob posodobitvi nasprotnikove slike
	if (igra.trenutniNivo < 5) {
		img->init(igra, "common/img/nasprotnik.png", x, y, w, h); // rumen nasprotnik
	}
	else {
		img->init(igra, "common/img/boss.png", x, y, w, h); // rdec nasprotnik
	}
}
void komoucar::display(GameManager& igra) { // prikaze nasprotnika
	img->display(igra.okno.ren);
}
void komoucar::zrcuniRandomDestinacijo() { // nasprotniku nastavi naklucno koordinato v zaslonu kot cilj
	short ax = 0, bx = 1280 - w;
	short ay = 0, by = 720 - h;
	dest_x = rand() % (bx - ax) + ax;
	dest_y = rand() % (by - ay) + ay;
}
bool komoucar::sprehodNaRandomDestinacijo() { // premakne nasprotika za stevilo "hitrost" pikslov proti svojemu cilju
	if (ManhattanDistance(x, y, dest_x, dest_y) < 10) { // racuna razdalno med nasprotnikom in ciljem
		return true; // ce je razdalja dovolj majhna se steje, kot da je ze na cilju (to popravi napako, ce je hitrost drugacna od 1)
	}
	else { // premakne se proti svojemu cilju
		if (x != dest_x)
			(x < dest_x) ? x += hitrost : x -= hitrost;
		if (y != dest_y)
			(y < dest_y) ? y += hitrost : y -= hitrost;
		return false; // pove da se ne nahaja na cilju
	}
}
void komoucar::setDest(short iks, short ipsilon) { // nastavi zeljeno koordinato kot cilj
	dest_x = iks;
	dest_y = ipsilon;
}