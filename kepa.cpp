#include "ZivoBitje.h"

Kepa::Kepa() {
	x = 0; y = 0;
	w = 0; h = 0;
	to_go = -1;
	done = -1;
	nosilec = -1;
}

Kepa::~Kepa() {
	if (img != nullptr) {
		delete img;
		img = nullptr;
	}
}

