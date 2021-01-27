#include "GameManager.h"
#include "SDL_ttf.h"
GameManager::GameManager() {
	//definiram privzete lastnosti
    konecLevela = false;
}

void GameManager::level(int &nivo) {
    cout << igralec.getName() << " zacenja " << nivo+1 << " level" << endl;
    //nared strukturo z usemi slikami
    pripraviPolje();
    while (!(keys[SDL_SCANCODE_ESCAPE] || event.type == SDL_QUIT) && !konecLevela) {
        //tuki pride pole igra ku igra
        updateMap();
        konecLevela = true;
    }
    if (konecLevela) {
        cout << "Koncal si " << ++nivo << " nivo!" << endl;
    }
    else{
        //zasilno shranjevanje
    }
}

void GameManager::pripraviPolje() {
    //dodaj da pride prek argumenta se struktura
    //postauljanje usega na pravo zacetno mesto
    //nared strukturo z usemi
    //inicializiri use slike u strukturi
}

void GameManager::updateMap() {
    //(slike).display(okno.ren);
    SDL_RenderPresent(okno.ren);
}

//inicializiranje sdl okna
int GameManager::init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        cout << "SDL Init, Error: " << SDL_GetError() << endl;
        return -1;
    }
    okno.window = SDL_CreateWindow("NE krznu -urlu",
                                        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                        okno.scaleCal(okno.returnWindowWidth()), okno.scaleCal(okno.returnWindowHeight()),
                                        SDL_WINDOW_SHOWN);
    if (okno.window == NULL) {
        cout << "SDL Create Window, Error: " << SDL_GetError() << endl;
        return -1;
    }
    okno.ren = SDL_CreateRenderer(okno.window, -1, 0);
    if (okno.ren == nullptr) {
        std::cout << "Could not create ren! SDL error" << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }
    if (TTF_Init()) {
        std::cout << "TTF_Init Error: " << TTF_GetError() << std::endl;
        return EXIT_FAILURE;
    }
    okno.surface = SDL_GetWindowSurface(okno.window);
    if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)))
    {
        printf("IMG_Init Error: %s\n", IMG_GetError());
        return false;
    }
    srand((unsigned int)time(NULL));
    return EXIT_SUCCESS;
}


void GameManager::haltEnter(int nivo) {
    cout << "Waiting for Enter keystroke" << endl;
    Image img_enter(okno.ren, "common/img/pressreturn.png", 0, 0, okno.scaleCal(okno.returnWindowWidth()), okno.scaleCal(okno.returnWindowHeight()));
    SDL_Delay(200);
    SDL_PollEvent(&event);
    SDL_PumpEvents();
    while (!keys[SDL_SCANCODE_RETURN]) {
        SDL_PollEvent(&event);
        SDL_PumpEvents();
        img_enter.display(okno.ren);
        SDL_RenderPresent(okno.ren);
    }
    cout << "\"Enter\" was pressed" << endl;
}