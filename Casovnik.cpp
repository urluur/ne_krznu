#include "Casovnik.h"

// nastavimo staticne spremenljivke
short Casovnik::milisekunde = 0;
short Casovnik::sekunde = 0;
bool Casovnik::paused = false;

Casovnik::Casovnik() {
	sekunde = 0;
	milisekunde = 0;
	paused = false;
}

bool Casovnik::odstej() {
	while (milisekunde >= 1000) {
		--sekunde;
		milisekunde -= 1000;
	}
	return sekunde < 0;
}

void Casovnik::set(short zelim) {
	sekunde = zelim;
	milisekunde = 0;
}