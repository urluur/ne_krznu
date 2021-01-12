#include "GameManager.h"
#include "SDL_ttf.h"
GameManager::GameManager() {
	//definiram privzete lastnosti
}

//inicializiranje sdl okna
int GameManager::init(GameManager& igra) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        cout << "SDL Init, Error: " << SDL_GetError() << endl;
        return -1;
    }
    igra.okno.window = SDL_CreateWindow("NE krznu -urlu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, igra.okno.returnWindowWidth(), igra.okno.returnWindowHeight(), SDL_WINDOW_SHOWN);
    if (igra.okno.window == NULL) {
        cout << "SDL Create Window, Error: " << SDL_GetError() << endl;
        return -1;
    }
    igra.okno.renderer = SDL_CreateRenderer(igra.okno.window, -1, 0);
    if (igra.okno.renderer == nullptr) {
        std::cout << "Could not create renderer! SDL error" << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }
    if (TTF_Init()) {
        std::cout << "TTF_Init Error: " << TTF_GetError() << std::endl;
        return EXIT_FAILURE;
    }
    igra.okno.surface = SDL_GetWindowSurface(igra.okno.window);
    if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)))
    {
        printf("IMG_Init Error: %s\n", IMG_GetError());
        return false;
    }
    srand(time(NULL));
    return EXIT_SUCCESS;
}