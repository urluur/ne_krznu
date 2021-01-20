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
    igra.okno.window = SDL_CreateWindow("NE krznu -urlu",
                                        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                        igra.okno.scalerCalculator(igra.okno.returnWindowWidth()), igra.okno.scalerCalculator(igra.okno.returnWindowHeight()),
                                        SDL_WINDOW_SHOWN);
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

void GameManager::level(int &nivo) {
    cout << igralec.getName() << " zacenja " << nivo << " level" << endl;
    pripraviPolje();
    if (nivo < 5) {
        nivo++;
        //tuki gre igra
    }
    else {
        nivo = -1;
    }
}

void GameManager::pripraviPolje() {
    //postauljanje usega na pravo mesto
}

void GameManager::haltEnter(int nivo) {
    Image img_press_enter(okno.renderer, "common/images/pressreturn.png", 0, 0, okno.scalerCalculator(okno.returnWindowWidth()), okno.scalerCalculator(okno.returnWindowHeight()));
    SDL_Delay(200);
    SDL_PollEvent(&event);
    SDL_PumpEvents();
    while (!keys[SDL_SCANCODE_RETURN]) {
        SDL_PollEvent(&event);
        SDL_PumpEvents();
        img_press_enter.display(okno.renderer);
        SDL_RenderPresent(okno.renderer);
    }
}