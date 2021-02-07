#include "function_definitions.h"

void GameManager::level(short& nivo) {
    trenutniNivo = nivo + 1;
    cout << igralec.getName() << " zacenja " << trenutniNivo << " level" << endl;

    //nared strukturo z usemi slikami??

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
    while (!(keys[SDL_SCANCODE_ESCAPE] || event.type == SDL_QUIT) && !konecLevela) {
        SDL_RenderClear(okno.ren);
        odzadje.display(okno.ren);

        // im stuck ne vem kko bi zaceu delat actual game :/ i guess bom najprej naredu use backgrounde



        //* za provo dok ni levela tuki
        if (nivo < 5)
            stTjuln[trenutniNivo - 1]--;
        else
            stNaspr[trenutniNivo - 1]--;
        SDL_Delay(500);
        //*/

        updateMap();
        if ((stTjuln[trenutniNivo - 1] == 0 && nivo < 5) || (trenutniNivo == 5 && stNaspr[trenutniNivo - 1] == 0)) {
            konecLevela = true; //cilj nase igre
        }
        SDL_PollEvent(&event);
    }

    if (konecLevela) {
        cout << "Koncal si " << ++nivo << " nivo!" << endl;
    }
    else {
        zasilnoShranjevanje(*this);
    }
}