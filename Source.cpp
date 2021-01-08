#include "function_definitions.h"
#undef main
using namespace std;

const Uint8* keys = SDL_GetKeyboardState(NULL);

void nastavitve(GameManager &igra);
void vec(GameManager& igra);

int main() {
    GameManager igra;
    igra.init(igra);
    igra.igralec.setName();
    SDL_Event event;
    SDL_PollEvent(&event);
    int pozicija_cursorja = 1;
    int izhod_switch = 0;
    while (!keys[SDL_SCANCODE_ESCAPE] && event.type != SDL_QUIT) {
        SDL_PollEvent(&event);
        SDL_PumpEvents();
        if (keys[SDL_SCANCODE_UP]) {
            igra.sound.cursorMove();
            if (pozicija_cursorja == 1) {
                pozicija_cursorja = 4;
            }
            else { pozicija_cursorja--; }
        }
        else if (keys[SDL_SCANCODE_DOWN]) {
            igra.sound.cursorMove();
            if (pozicija_cursorja == 4) { pozicija_cursorja = 1; }
            else { pozicija_cursorja++;}
        }
        SDL_FreeSurface(igra.okno.image);
        switch (pozicija_cursorja) {
        case 1:
            igra.okno.image = SDL_LoadBMP("common/images/main_zacni.bmp");
            if (keys[SDL_SCANCODE_RETURN]) {
                igra.sound.zacni();

            }
            break;
        case 2:
            igra.okno.image = SDL_LoadBMP("common/images/main_vec.bmp");
            if (keys[SDL_SCANCODE_RETURN]) {
                igra.sound.vec();
                SDL_Delay(10);
                vec(igra);
            }
            break;
        case 3:
            igra.okno.image = SDL_LoadBMP("common/images/main_nastavitve.bmp");
            if (keys[SDL_SCANCODE_RETURN]) {
                igra.sound.nastavitve();
                SDL_Delay(10);
                nastavitve(igra);
                pozicija_cursorja = 1;
            }
            break;
        case 4:
            if (keys[SDL_SCANCODE_RETURN]) {
                igra.sound.izhod();
                izhod_switch = 1;
            }
            igra.okno.image = SDL_LoadBMP("common/images/main_izhod.bmp");
            break;
        }
        SDL_UpdateWindowSurface(igra.okno.window);
        SDL_BlitSurface(igra.okno.image, NULL, igra.okno.surface, NULL);
        SDL_Delay(80);
        if (izhod_switch == 1) {
            break;
        }
    }
    igra.sound.nasvidenje();
    SDL_DestroyWindow(igra.okno.window);
    SDL_FreeSurface(igra.okno.image);
    SDL_Quit();
    return 0;
}

void nastavitve(GameManager &igra) {
    SDL_Event ev_nastavitve;
    int main = 0;
    int pozicija_cursorja = 1;

    while (main == 0)
    {
        SDL_PollEvent(&ev_nastavitve);
        SDL_PumpEvents();
        if (keys[SDL_SCANCODE_UP])
        {
            igra.sound.cursorMove();
            if (pozicija_cursorja == 1){
                pozicija_cursorja = 4;
            }
            else {
                pozicija_cursorja--;
            }
        }
        else if (keys[SDL_SCANCODE_DOWN])
        {
            igra.sound.cursorMove();
            if (pozicija_cursorja == 4) { pozicija_cursorja = 1; }
            else { pozicija_cursorja++; }
        }

        SDL_FreeSurface(igra.okno.image);

        switch (pozicija_cursorja)
        {
        case 1:
            igra.okno.image = SDL_LoadBMP("common/images/set_dimenzije.bmp");
            if (keys[SDL_SCANCODE_RETURN]) {
                igra.sound.dimenzije();

            }
            break;
        case 2:
            igra.okno.image = SDL_LoadBMP("common/images/set_ime.bmp");
            if (keys[SDL_SCANCODE_RETURN]) {
                igra.sound.spremeni_ime();
                igra.igralec.setName();
            }
            break;
        case 3:
            igra.okno.image = SDL_LoadBMP("common/images/set_zvok.bmp");
            if (keys[SDL_SCANCODE_RETURN]) {
                igra.sound.spremeni_zvok();
                igra.sound.toggle();
            }
            
            break;
        case 4:
            igra.okno.image = SDL_LoadBMP("common/images/set_nazaj.bmp");
            if (keys[SDL_SCANCODE_RETURN]) {
                igra.sound.nazaj();
                main = 1;
            }
            break;
        }

        if (!(!keys[SDL_SCANCODE_ESCAPE] || ev_nastavitve.type != SDL_QUIT)) {
            main = 1;
        }

        SDL_UpdateWindowSurface(igra.okno.window);
        SDL_BlitSurface(igra.okno.image, NULL, igra.okno.surface, NULL);
        SDL_Delay(75);
    }

    igra.sound.oof();
}
void vec(GameManager& igra) {
    SDL_Event ev_vec;
    int main = 0;
    int pozicija_cursorja = 1;

    while (main == 0)
    {
        SDL_PollEvent(&ev_vec);
        SDL_PumpEvents();
        if (keys[SDL_SCANCODE_UP])
        {
            igra.sound.cursorMove();
            if (pozicija_cursorja == 1) {
                pozicija_cursorja = 4;
            }
            else {
                pozicija_cursorja--;
            }
        }
        else if (keys[SDL_SCANCODE_DOWN])
        {
            igra.sound.cursorMove();
            if (pozicija_cursorja == 4) { pozicija_cursorja = 1; }
            else { pozicija_cursorja++; }
        }

        SDL_FreeSurface(igra.okno.image);

        switch (pozicija_cursorja)
        {
        case 1:
            igra.okno.image = SDL_LoadBMP("common/images/vec_lestvica.bmp");
            if (keys[SDL_SCANCODE_RETURN]) {
                igra.sound.lestvica();

            }
            break;
        case 2:
            igra.okno.image = SDL_LoadBMP("common/images/vec_izvorna.bmp");
            if (keys[SDL_SCANCODE_RETURN]) {
                igra.sound.izvorna();
                system("start https://github.com/urluur/ne_krznu");
            }
            break;
        case 3:
            igra.okno.image = SDL_LoadBMP("common/images/vec_izbris.bmp");
            if (keys[SDL_SCANCODE_RETURN]) {
                igra.sound.izbris();
            }

            break;
        case 4:
            igra.okno.image = SDL_LoadBMP("common/images/vec_nazaj.bmp");
            if (keys[SDL_SCANCODE_RETURN]) {
                igra.sound.nazaj();
                main = 1;
            }
            break;
        }

        if (!(!keys[SDL_SCANCODE_ESCAPE] || ev_vec.type != SDL_QUIT)) {
            main = 1;
        }

        SDL_UpdateWindowSurface(igra.okno.window);
        SDL_BlitSurface(igra.okno.image, NULL, igra.okno.surface, NULL);
        SDL_Delay(75);
    }

    igra.sound.oof();
}