#include "main_menu.h"
using namespace std;

void nastavitve(GameManager& igra) {
    SDL_RenderClear(igra.okno.ren);
    SDL_Delay(200);
    SDL_PollEvent(&igra.event);
    bool stay = true;
    int pozicija_cursorja = 1;
    Image img_nastavitve;
    Image cursor;
    while (stay)
    {
        SDL_PollEvent(&igra.event);
        SDL_PumpEvents();
        SDL_RenderClear(igra.okno.ren);
        img_nastavitve.ini(igra, "common/img/nastavitve.png");
        img_nastavitve.display(igra.okno.ren);
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
            cursor.init(igra, "common/img/cursor.png", 20, 210, 98, 49);
            cursor.display(igra.okno.ren);
            if (igra.keys[SDL_SCANCODE_RETURN]) {
                igra.sound.dimenzije();
                cout << "spreminjam velikost okna na ";
                igra.okno.toggleScaler();
                SDL_SetWindowSize(igra.okno.window, igra.okno.scaleCal(igra.okno.returnWindowWidth()), igra.okno.scaleCal(igra.okno.returnWindowHeight()));
                if (igra.okno.vrniScaler() == 100) {
                    SDL_SetWindowFullscreen(igra.okno.window, SDL_WINDOW_FULLSCREEN_DESKTOP);
                }
                else {
                    SDL_SetWindowFullscreen(igra.okno.window, 0);
                }
                
                
            }
            break;
        case 2:
            cursor.init(igra, "common/img/cursor.png", 20, 310, 98, 49);
            cursor.display(igra.okno.ren);
            if (igra.keys[SDL_SCANCODE_RETURN]) {
                igra.sound.spremeni_ime();
                igra.igralec.setName();
            }
            break;
        case 3:
            cursor.init(igra, "common/img/cursor.png", 20, 420, 98, 49);
            cursor.display(igra.okno.ren);
            if (igra.keys[SDL_SCANCODE_RETURN]) {
                igra.sound.spremeni_zvok();
                igra.sound.toggle();
                SDL_Delay(50);
            }

            break;
        case 4:
            cursor.init(igra, "common/img/cursor.png", 20, 510, 98, 49);
            cursor.display(igra.okno.ren);
            if (igra.keys[SDL_SCANCODE_RETURN]) {
                igra.sound.nazaj();
                stay = false;
            }
            break;
        }

        if (!(!igra.keys[SDL_SCANCODE_ESCAPE] || igra.event.type != SDL_QUIT)) {
            stay = false; // se ne dela
        }

        SDL_RenderPresent(igra.okno.ren);
        SDL_Delay(75);
    }

    //igra.sound.oof();
}
void vec(GameManager& igra) {
    SDL_Delay(200);
    SDL_PollEvent(&igra.event);
    bool stay = true;
    int pozicija_cursorja = 1;
    Image img_vec;
    Image cursor;
    Image github(igra.okno.ren, "common/img/github.png", igra.okno.scaleCal(20), igra.okno.scaleCal(20), igra.okno.scaleCal(279), igra.okno.scaleCal(66));
    while (stay)
    {
        SDL_PollEvent(&igra.event);
        SDL_PumpEvents();
        SDL_RenderClear(igra.okno.ren);
        img_vec.ini(igra, "common/img/vec.png");
        img_vec.display(igra.okno.ren);
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
            cursor.init(igra, "common/img/cursor.png", 20, 210, 98, 49);
            cursor.display(igra.okno.ren);
            if (igra.keys[SDL_SCANCODE_RETURN]) {
                igra.sound.lestvica();

            }
            break;
        case 2:
            github.display(igra.okno.ren);
            cursor.init(igra, "common/img/cursor.png", 20, 310, 98, 49);
            cursor.display(igra.okno.ren);
            if (igra.keys[SDL_SCANCODE_RETURN]) {
                igra.sound.izvorna();
                system("start https://github.com/urluur/ne_krznu");
            }
            break;
        case 3:
            cursor.init(igra, "common/img/cursor.png", 20, 420, 98, 49);
            cursor.display(igra.okno.ren);
            if (igra.keys[SDL_SCANCODE_RETURN]) {
                igra.sound.izbris();
            }

            break;
        case 4:
            cursor.init(igra, "common/img/cursor.png", 20, 530, 98, 49);
            cursor.display(igra.okno.ren);
            if (igra.keys[SDL_SCANCODE_RETURN]) {
                igra.sound.nazaj();
                stay = false;
            }
            break;
        }

        if (!(!igra.keys[SDL_SCANCODE_ESCAPE] || igra.event.type != SDL_QUIT)) {
            stay = false;
        }

        SDL_RenderPresent(igra.okno.ren);
        SDL_Delay(75);
    }

    //igra.sound.oof();
}