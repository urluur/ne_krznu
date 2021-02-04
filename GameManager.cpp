#include "GameManager.h"

GameManager::GameManager() {
	//definiram privzete lastnosti
    SDL_PollEvent(&event);
    konecLevela = false;
    completed = false;
    trenutniNivo = -1;
}

void GameManager::level(short &nivo, GameManager& igra) {
    trenutniNivo = nivo + 1;
    cout << igralec.getName() << " zacenja " << trenutniNivo << " level" << endl;

    //nared strukturo z usemi slikami

    pripraviVse();
    while (!(keys[SDL_SCANCODE_ESCAPE] || event.type == SDL_QUIT) && !konecLevela) {
        //tuki pride pole igra ku igra


        //za testing
        SDL_RenderClear(okno.ren);
        SDL_RenderPresent(okno.ren);
        SDL_Delay(5000);


        updateMap();
        konecLevela = true; //to bo v enem if-u
        SDL_PollEvent(&event);
    }
    if (konecLevela) {
        cout << "Koncal si " << ++nivo << " nivo!" << endl;
    }
    else{
        //zasilnoShranjevanje(igra);
    }
}

void GameManager::pripraviVse() {
    SDL_PollEvent(&event);
    //dodaj da pride prek argumenta se struktura
    //postauljanje usega na pravo zacetno mesto
    //nared strukturo z usemi
    //inicializiri use slike u strukturi
}

void GameManager::pripraviOdzadje(GameManager& igra) {
    string pathFragment = "common/img/odzadje";
    pathFragment += to_string(trenutniNivo);
    pathFragment += ".png";
    char* path = new char[pathFragment.size() + 1];
    std::copy(pathFragment.begin(), pathFragment.end(), path);
    path[pathFragment.size()] = '\0';
    //odzadje.ini(igra, path); // klic
    delete[] path; // konec    
}

void GameManager::updateMap() {
    SDL_RenderClear(okno.ren);
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


void GameManager::haltEnter(short nivo) {
    cout << "Waiting for Enter keystroke" << endl;
    Image img_enter(okno.ren, "common/img/pressreturn.png", 0, 0, okno.scaleCal(okno.returnWindowWidth()), okno.scaleCal(okno.returnWindowHeight()));
    SDL_Delay(200);
    img_enter.display(okno.ren);
    SDL_RenderPresent(okno.ren);
    SDL_PollEvent(&event);
    while (!keys[SDL_SCANCODE_RETURN]) {
        SDL_PollEvent(&event);
    }
    cout << "\"Enter\" was pressed" << endl;
}

bool GameManager::isCompleted() {
    return completed;
}

void GameManager::setCompleted(bool resnica) {
    completed = resnica;
}

short GameManager::getNivo() {
    return trenutniNivo;
}

void GameManager::setNivo(short lvl) {
    trenutniNivo = lvl;
}