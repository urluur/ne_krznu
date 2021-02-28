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

    //main game loop
    while (!keys[SDL_SCANCODE_ESCAPE] && !konecLevela && !adios) {
        okno.stejFrame();
        handleEvents();
        
        SDL_RenderClear(okno.ren);
        odzadje.display(okno.ren);
        jaz.at(0)->init(*this, "common/img/player.png",igralec.getX(), igralec.getY(), 58, 128);

        /* za provo dok ni levela tuki
        if (keys[SDL_SCANCODE_SPACE]) //nivo < 5
            stTjuln[trenutniNivo - 1]--;
        else
            stNaspr[trenutniNivo - 1]--;
        //*/


        updateMap();
        //* realn game objective
        if ((stTjuln[trenutniNivo - 1] == 0 && nivo < 5) || (trenutniNivo == 5 && stNaspr[trenutniNivo - 1] == 0))
            konecLevela = true; //cilj nase igre
        //*/
    }

    if (konecLevela)
        std::cout << "Koncal si " << ++nivo << " nivo!" << endl;
    else if (adios)
        zasilnoShranjevanje();
}