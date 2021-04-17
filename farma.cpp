#include "igra.h"

// ta funkcija je klicana ko se igralec dotakne farme
void GameManager::farma() {
	sound.predvajaj("common/sounds/krkh.wav");
	if (stTjulnFarma > 0) {
		// tu je prostor za dodatni "bonus nivo" resevanja tjulnov iz farme

		// zaenkrat je samo dotik dovolj da resimo tjulna iz farme
		printf("Hvala, resil si me z farme!!\n");
		--stTjulnFarma;
		trenutne_tocke = trenutne_tocke + trenutniNivo;
	}
}