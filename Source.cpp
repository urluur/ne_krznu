#include "function_definitions.h"
#undef main
using namespace std;

SDL_Window* window=NULL;
SDL_Surface* surface=NULL;
SDL_Surface* image=NULL;

const int Window_width = 720;
const int Window_height = 640;
const Uint8* keys = SDL_GetKeyboardState(NULL);

void nastavitve(Mix_Music *bgm);

int init() {
    
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("SDL Init, Error: %d", SDL_GetError());
        return -1;
    }

    window = SDL_CreateWindow("NE krznu -urlu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Window_width, Window_height, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        printf("SDL Create Window, Error: %d", SDL_GetError());
        return -1;
    }

    surface = SDL_GetWindowSurface(window);
    srand(time(NULL));
    return 0;
}

void cleanUp() {
    SDL_DestroyWindow(window);
    SDL_FreeSurface(image);
    Mix_Quit();
    SDL_Quit();
}

int main() {
    cout << "Vpisi svoje ime, bumbar!" << endl;
    string ime;
    getline(cin, ime);
    cout << "Pozdravljen/a " << ime << "!" << endl;
    init();
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        cout << "Mixer error: " << Mix_GetError() << endl;
    }
    Mix_Music* bgm = Mix_LoadMUS("common/sounds/soundtrack.wav");


    SDL_Event event;
    SDL_PollEvent(&event);
    int pozicija_cursorja = 1;
    int izhod_switch = 0;
    while (!keys[SDL_SCANCODE_ESCAPE] && event.type != SDL_QUIT) {
        SDL_PollEvent(&event);
        SDL_PumpEvents();
        if (keys[SDL_SCANCODE_UP]) {
            sound_cursorMove();
            if (pozicija_cursorja == 1) {
                pozicija_cursorja = 4;
            }
            else { pozicija_cursorja--; }
        }
        else if (keys[SDL_SCANCODE_DOWN]) {
            sound_cursorMove();
            if (pozicija_cursorja == 4) { pozicija_cursorja = 1; }
            else { pozicija_cursorja++;}
        }
        SDL_FreeSurface(image);
        switch (pozicija_cursorja) {
        case 1:
            image = SDL_LoadBMP("common/images/main_zacni.bmp");
            break;
        case 2:
            image = SDL_LoadBMP("common/images/main_vec.bmp");
            break;
        case 3:
            image = SDL_LoadBMP("common/images/main_nastavitve.bmp");
            if (keys[SDL_SCANCODE_RETURN]) {
                nastavitve(bgm);
                pozicija_cursorja = 1;
            }
            break;
        case 4:
            if (keys[SDL_SCANCODE_RETURN]) {
                izhod_switch = 1;
            }
            image = SDL_LoadBMP("common/images/main_izhod.bmp");
            break;
        }
        SDL_UpdateWindowSurface(window);
        SDL_BlitSurface(image, NULL, surface, NULL);
        SDL_Delay(80);
        if (izhod_switch == 1) {
            break;
        }

        if (!Mix_PlayingMusic()) {
            Mix_PlayMusic(bgm, -1);
        }
    }
    sound_oof();
    bgm = nullptr;
    Mix_Quit();
    cleanUp();
    return 0;
}

void nastavitve(Mix_Music* bgm) {
    SDL_Event ev_nastavitve;
    int main = 0;
    int pozicija_cursorja = 1;
    while (main == 0) {
        SDL_PollEvent(&ev_nastavitve);
        SDL_PumpEvents();
        if (keys[SDL_SCANCODE_UP]) {
            sound_cursorMove();
            if (pozicija_cursorja == 1) {
                pozicija_cursorja = 4;
            }
            else { pozicija_cursorja--; }
        }
        else if (keys[SDL_SCANCODE_DOWN]) {
            sound_cursorMove();
            if (pozicija_cursorja == 4) { pozicija_cursorja = 1; }
            else { pozicija_cursorja++; }
        }
        SDL_FreeSurface(image);
        switch (pozicija_cursorja) {
        case 1:
            image = SDL_LoadBMP("common/images/set_dimenzije.bmp");
            break;
        case 2:
            image = SDL_LoadBMP("common/images/set_ime.bmp");
            break;
        case 3:
            image = SDL_LoadBMP("common/images/set_zvok.bmp");
            if (keys[SDL_SCANCODE_RETURN]) {
                if (!Mix_PlayingMusic()) {
                    Mix_PlayMusic(bgm, -1);
                }
                else {
                    Mix_HaltMusic();
                }
            }
            break;
        case 4:
            image = SDL_LoadBMP("common/images/set_nazaj.bmp");
            if (keys[SDL_SCANCODE_RETURN]) {
                main = 1;
            }
            break;
        }
        SDL_UpdateWindowSurface(window);
        SDL_BlitSurface(image, NULL, surface, NULL);
        SDL_Delay(80);
    }
    sound_oof();
}