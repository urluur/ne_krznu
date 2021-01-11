#include "main_menu.h"
using namespace std;


void nastavitve(GameManager& igra) {
    SDL_RenderClear(igra.okno.renderer);
    SDL_Event ev_nastavitve;
    int main = 0;
    int pozicija_cursorja = 1;
    Image img_nastavitve(igra.okno.renderer, "common/images/nastavitve.png", 0, 0, igra.okno.returnWindow_width(), igra.okno.returnWindow_height());
    Image cursor;
    while (main == 0)
    {
        SDL_PollEvent(&ev_nastavitve);
        SDL_PumpEvents();
        SDL_RenderClear(igra.okno.renderer);
        img_nastavitve.display(igra.okno.renderer);
        if (igra.keys[SDL_SCANCODE_UP])
        {
            igra.sound.cursorMove();
            if (pozicija_cursorja == 1) {
                pozicija_cursorja = 4;
            }
            else {
                pozicija_cursorja--;
            }
        }
        else if (igra.keys[SDL_SCANCODE_DOWN])
        {
            igra.sound.cursorMove();
            if (pozicija_cursorja == 4) { pozicija_cursorja = 1; }
            else { pozicija_cursorja++; }
        }

        SDL_FreeSurface(igra.okno.image);

        switch (pozicija_cursorja)
        {
        case 1:
            cursor.init(igra.okno.renderer, "common/images/cursor.png", 20, 210, 98, 49);
            cursor.display(igra.okno.renderer);
            if (igra.keys[SDL_SCANCODE_RETURN]) {
                igra.sound.dimenzije();

            }
            break;
        case 2:
            cursor.init(igra.okno.renderer, "common/images/cursor.png", 20, 310, 98, 49);
            cursor.display(igra.okno.renderer);
            if (igra.keys[SDL_SCANCODE_RETURN]) {
                igra.sound.spremeni_ime();
                igra.igralec.setName();
            }
            break;
        case 3:
            cursor.init(igra.okno.renderer, "common/images/cursor.png", 20, 420, 98, 49);
            cursor.display(igra.okno.renderer);
            if (igra.keys[SDL_SCANCODE_RETURN]) {
                igra.sound.spremeni_zvok();
                igra.sound.toggle();
            }

            break;
        case 4:
            cursor.init(igra.okno.renderer, "common/images/cursor.png", 20, 510, 98, 49);
            cursor.display(igra.okno.renderer);
            if (igra.keys[SDL_SCANCODE_RETURN]) {
                igra.sound.nazaj();
                main = 1;
            }
            break;
        }

        if (!(!igra.keys[SDL_SCANCODE_ESCAPE] || ev_nastavitve.type != SDL_QUIT)) {
            main = 1;
        }

        SDL_RenderPresent(igra.okno.renderer);
        SDL_Delay(75);
    }

    igra.sound.oof();
}
void vec(GameManager& igra) {
    SDL_Event ev_vec;
    int main = 0;
    int pozicija_cursorja = 1;
    Image img_vec(igra.okno.renderer, "common/images/vec.png", 0, 0, igra.okno.returnWindow_width(), igra.okno.returnWindow_height());
    Image cursor;
    Image github(igra.okno.renderer, "common/images/github.png", 20, 20, 279, 66);
    while (main == 0)
    {
        SDL_PollEvent(&ev_vec);
        SDL_PumpEvents();
        SDL_RenderClear(igra.okno.renderer);
        img_vec.display(igra.okno.renderer);
        if (igra.keys[SDL_SCANCODE_UP])
        {
            igra.sound.cursorMove();
            if (pozicija_cursorja == 1) {
                pozicija_cursorja = 4;
            }
            else {
                pozicija_cursorja--;
            }
        }
        else if (igra.keys[SDL_SCANCODE_DOWN])
        {
            igra.sound.cursorMove();
            if (pozicija_cursorja == 4) { pozicija_cursorja = 1; }
            else { pozicija_cursorja++; }
        }

        SDL_FreeSurface(igra.okno.image);

        switch (pozicija_cursorja)
        {
        case 1:
            cursor.init(igra.okno.renderer, "common/images/cursor.png", 20, 210, 98, 49);
            cursor.display(igra.okno.renderer);
            if (igra.keys[SDL_SCANCODE_RETURN]) {
                igra.sound.lestvica();

            }
            break;
        case 2:
            github.display(igra.okno.renderer);
            cursor.init(igra.okno.renderer, "common/images/cursor.png", 20, 310, 98, 49);
            cursor.display(igra.okno.renderer);
            if (igra.keys[SDL_SCANCODE_RETURN]) {
                igra.sound.izvorna();
                system("start https://github.com/urluur/ne_krznu");
            }
            break;
        case 3:
            cursor.init(igra.okno.renderer, "common/images/cursor.png", 20, 420, 98, 49);
            cursor.display(igra.okno.renderer);
            if (igra.keys[SDL_SCANCODE_RETURN]) {
                igra.sound.izbris();
            }

            break;
        case 4:
            cursor.init(igra.okno.renderer, "common/images/cursor.png", 20, 520, 98, 49);
            cursor.display(igra.okno.renderer);
            if (igra.keys[SDL_SCANCODE_RETURN]) {
                igra.sound.nazaj();
                main = 1;
            }
            break;
        }

        if (!(!igra.keys[SDL_SCANCODE_ESCAPE] || ev_vec.type != SDL_QUIT)) {
            main = 1;
        }

        SDL_RenderPresent(igra.okno.renderer);
        SDL_Delay(75);
    }

    igra.sound.oof();
}