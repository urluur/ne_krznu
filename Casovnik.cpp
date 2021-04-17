#include "Casovnik.h"

Casovnik::Casovnik() {
	sekunde = 0;
	milisekunde = 0;
}

void Casovnik::setup(WindowManager& notr) {
	p_okno = &notr;
}

bool Casovnik::odstej() {
	milisekunde += p_okno->frameTime + p_okno->frameDelay;
	if (milisekunde > 1000) {
		--sekunde;
		milisekunde -= 1000;
		cout << sekunde << endl;
	}
	return sekunde < 0;
}

void Casovnik::set(short zelim) {
	sekunde = zelim;
	milisekunde = 0;
}