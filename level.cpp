#include "includes.h"
using namespace std;

void GameManager::level(short& nivo) {
    trenutniNivo = nivo + 1;
    igralec.coutName();
    cout << " zacenja " << trenutniNivo << " level" << endl;

    pripraviVse();

    //pripravi odzadje
    Image odzadje;
    string pathFragment = "common/img/odzadje";
    pathFragment += to_string(trenutniNivo);
    pathFragment += ".png";
    char* path = new char[pathFragment.size() + 1];
    std::copy(pathFragment.begin(), pathFragment.end(), path);
    path[pathFragment.size()] = '\0';
    odzadje.ini(*this, path);
    delete[] path;

    cout << "Se " << stTjuln[trenutniNivo - 1] << " tjulnov!" << endl;
    cout << "Se " << stNaspr[trenutniNivo - 1] << " nasprotnikov!" << endl << endl;
    //main game loop
    while (!keys[SDL_SCANCODE_ESCAPE] && !konecLevela && !adios) {
        okno.stejFrame();
        handleEvents();
        
        //realn game objective
        if(semNaIzhodniLokaciji)
            if ((stTjuln[trenutniNivo - 1] == 0 && nivo < 5) || (trenutniNivo == 5 && stNaspr[trenutniNivo - 1] == 0))
                konecLevela = true; //cilj nase igre
        
        SDL_RenderClear(okno.ren);
        odzadje.display(okno.ren);
        jaz.at(0)->init(*this, "common/img/player.png",igralec.getX(), igralec.getY(), igralec.getW(), igralec.getH());

        switch (trenutniNivo) {
        case 1:
            if (isPlayerCollidingAt(1110, 10, 170, 150)) {
                cout << "sm na farmi" << endl;
            }
            if(isPlayerCollidingAt(160, 660, 125, 60))
                semNaIzhodniLokaciji = true;
            else
                semNaIzhodniLokaciji = false;
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        default:
            cerr << "Error: collision check" << trenutniNivo << endl;
        }

        //* za provo dok ni levela tuki
        if (keys[SDL_SCANCODE_SPACE]) {
            if (nivo < 5) {
                if(stTjuln[trenutniNivo - 1] > 0)
                    stTjuln[trenutniNivo - 1]--;
                cout << "Se " << stTjuln[trenutniNivo - 1] << " tjulnov!" << endl;
                cout << "Se " << stNaspr[trenutniNivo - 1] << " nasprotnikov!" << endl << endl;
            }
            else {
                if (stNaspr[trenutniNivo - 1] > 0)
                    stNaspr[trenutniNivo - 1]--;
                cout << "Se " << stTjuln[trenutniNivo - 1] << " tjulnov!" << endl;
                cout << "Se " << stNaspr[trenutniNivo - 1] << " nasprotnikov!" << endl << endl;
            }
            SDL_Delay(100);
        }
        //*/


        updateMap();
    }

    if (konecLevela)
        std::cout << "Koncal si " << ++nivo << " nivo!" << endl;
    else if (adios)
        zasilnoShranjevanje();
}