#include "GameManager.h"
#include "SDL_ttf.h"
GameManager::GameManager() {
	//definiram privzete lastnosti
}

int GameManager::init(GameManager& igra) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) { //SDL_INIT_VIDEO | SDL_INIT_AUDIO
        cout << "SDL Init, Error: " << SDL_GetError() << endl;
        return -1;
    }
    igra.okno.window = SDL_CreateWindow("NE krznu -urlu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, igra.okno.returnWindow_width(), igra.okno.returnWindow_height(), SDL_WINDOW_SHOWN);
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
    srand(time(NULL));
    return EXIT_SUCCESS;
}