#include "igra.h"

bool GameManager::isPlayerCollidingAt(short x, short y, short w, short h) {
	if (igralec.getX() < x + w &&
		igralec.getX() + igralec.getW() > x &&
		igralec.getY() < y + h &&
		igralec.getY() + igralec.getH() > y)
		return true;
	else
		return false;
}

void GameManager::trkiOkolje() {
    switch (trenutniNivo) {
    case 1:
        if (isPlayerCollidingAt(1110, 10, 170, 150)) {
            cout << "sm na farmi" << endl;
        }
        if (isPlayerCollidingAt(160, 660, 125, 60))
            semNaIzhodniLokaciji = true;
        else
            semNaIzhodniLokaciji = false;
        break;
    case 2:
        if (isPlayerCollidingAt(0, 460, 130, 120)) {
            cout << "sm na farmi" << endl;
        }
        if (isPlayerCollidingAt(1270, 520, 10, 200))
            semNaIzhodniLokaciji = true;
        else
            semNaIzhodniLokaciji = false;
        break;
    case 3:
        if (isPlayerCollidingAt(90, 350, 130, 120)) {
            cout << "sm na farmi" << endl;
        }
        if (isPlayerCollidingAt(230, 0, 70, 60))
            semNaIzhodniLokaciji = true;
        else
            semNaIzhodniLokaciji = false;
        break;
    case 4:
        if (isPlayerCollidingAt(990, 350, 190, 150)) {
            cout << "sm na farmi" << endl;
        }
        if (isPlayerCollidingAt(1130, 600, 30, 40)) {
            cout << "sm na kolomiti" << endl;
        }
        if (isPlayerCollidingAt(160, 0, 10, 75))
            semNaIzhodniLokaciji = true;
        else
            semNaIzhodniLokaciji = false;
        break;
    case 5:
        if (isPlayerCollidingAt(1030, 60, 190, 120)) {
            cout << "sm na farmi" << endl;
        }
        if (isPlayerCollidingAt(0, 0, 1280, 40))
            semNaIzhodniLokaciji = true;
        else
            semNaIzhodniLokaciji = false;
        break;
    default:
        cerr << "Error: collision check" << trenutniNivo << endl;
    }
}