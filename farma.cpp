#include "igra.h"

void GameManager::farma() {
	cout << "sm na farmi\n";
	if (stTjulnFarma > 0) {
		//tuki se bo dogaju farma stuff (main farma loop)

		cout << "Hvala, resil si me z farme!!\n";
		--stTjulnFarma;
	}
}
