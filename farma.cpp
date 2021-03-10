#include "igra.h"

void GameManager::farma() {
	// ta funkcija je klicana ko se igralec dotakne farme
	printf("sm na farmi\n");
	sound.predvajaj("common/sounds/krkh.wav");
	if (stTjulnFarma > 0) {
		// tu je prostor za dodatni "bonus nivo" resevanja tjulnov iz farme

		// zaenkrat je samo dotik dovolj da resimo tjulna iz farme
		printf("Hvala, resil si me z farme!!\n");
		--stTjulnFarma;
	}
}