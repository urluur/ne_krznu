#include "igra.h"

// ta funkcija je klicana ko se igralec dotakne farme
void GameManager::farma() {
	if (stTjulnFarma > 0) {
		sound.predvajaj("common/sounds/krkh.wav");
		// tu je prostor za dodatni "bonus nivo" resevanja tjulnov iz farme

		// zaenkrat je samo dotik dovolj da resimo tjulna iz farme
		--stTjulnFarma;
		trenutne_tocke = trenutne_tocke + trenutniNivo;
	}
}