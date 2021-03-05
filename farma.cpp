#include "igra.h"

void GameManager::farma() {
	printf("sm na farmi\n");
	if (stTjulnFarma > 0) {
		//tuki se bo dogaju farma stuff (main farma loop)

		printf("Hvala, resil si me z farme!!\n");
		--stTjulnFarma;
	}
}