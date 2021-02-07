#include "GameManager.h"

GameManager::GameManager() {
	//definiram privzete lastnosti
    SDL_PollEvent(&event);
    konecLevela = false;
    completed = false;
    trenutniNivo = -1;
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
    okno.ren = SDL_CreateRenderer(okno.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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

void GameManager::pripraviVse() {
    SDL_PollEvent(&event);
    konecLevela = false;

    stNaspr[0] = 3;
    stNaspr[1] = 5;
    stNaspr[2] = 7;
    stNaspr[3] = 10;
    stNaspr[4] = 1;

    stAktiv[0] = 3;
    stAktiv[1] = 5;
    stAktiv[2] = 7;
    stAktiv[3] = 10;
    stAktiv[4] = 1;

    stTjuln[0] = 3;
    stTjuln[1] = 5;
    stTjuln[2] = 7;
    stTjuln[3] = 10;
    stTjuln[4] = 1;
    //dodaj da pride prek argumenta se struktura
    //postauljanje usega na pravo zacetno mesto
    //nared strukturo z usemi
    //inicializiri use slike u strukturi
}

void GameManager::updateMap() {
    //(slike).display(okno.ren);
    SDL_RenderPresent(okno.ren);
}


void GameManager::haltEnter(short nivo) {
    cout << "Waiting for Enter keystroke" << endl;
    Image img_enter(okno.ren, "common/img/pressreturn.png", 0, 0, okno.scaleCal(okno.returnWindowWidth()), okno.scaleCal(okno.returnWindowHeight()));
    SDL_Delay(200);
    img_enter.display(okno.ren);
    SDL_RenderPresent(okno.ren);
    SDL_PollEvent(&event);
    while (!keys[SDL_SCANCODE_RETURN]) {
        preveriEsc(nivo);
    }
    cout << "\"Enter\" was pressed" << endl;
}

bool GameManager::isCompleted() {
    return completed;
}

void GameManager::setCompleted(bool resnica) {
    completed = resnica;
    ofstream quicksave;
    quicksave.open("quicksave.txt");
    if (quicksave.is_open()) {
        quicksave << "bumbar\n-1\n";
    }
    else {
        cout << "Error: setting complete" << endl;
        cleanup();
        exit(1);
    }
    quicksave.close();
}

short GameManager::getNivo() {
    return trenutniNivo;
}

void GameManager::setNivo(short lvl) {
    trenutniNivo = lvl;
}

void GameManager::preveriEsc(short& nivo) {
    SDL_PollEvent(&event);
    if ((keys[SDL_SCANCODE_ESCAPE] || event.type == SDL_QUIT)) {
        setNivo(nivo);
        zasilnoShranjevanje(*this);
        cleanup();
        exit(1);
    }
}

void GameManager::cleanup() {
    SDL_DestroyWindow(okno.window);
    SDL_FreeSurface(okno.image);
    SDL_Quit();
}
