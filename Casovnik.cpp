#include "Casovnik.h"

short Casovnik::milisekunde = 0;
short Casovnik::sekunde = 0;
bool Casovnik::paused = false;

Casovnik::Casovnik() {
	sekunde = 0;
	milisekunde = 0;
	p_okno = nullptr;
	paused = false;
}

void Casovnik::setup(WindowManager& notr) {
	p_okno = &notr;
}

bool Casovnik::odstej() {
	while (milisekunde >= 1000) {
		--sekunde;
		milisekunde -= 1000;
		printf("%d\n", sekunde);
	}
	return sekunde < 0;
}

void Casovnik::set(short zelim) {
	sekunde = zelim;
	milisekunde = 0;
}