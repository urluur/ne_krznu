#include "main_menu.h"
using namespace std;

void overworld(GameManager& igra) {
    SDL_RenderClear(igra.okno.ren);
    int main = 0;
    short level_igralca = 1;
    Image img_overworld;
    Image img_player;
    Image img_drevo;
    Image imgs_farma[5];
    Image img_zastavica_fullscreen;
    short blink = 0;

    short level_clear=0;
    img_overworld.ini(igra, "common/img/overworld.png");
    img_overworld.display(igra.okno.ren);
     
    int x=90, y=160;
    int final_x, final_y;
    bool x_bool=false, y_bool=false;

    //previrjanje iz filov zasilnega shranjevanja

    while (main == 0) {
        SDL_Delay(500);
        SDL_PollEvent(&igra.event);
        SDL_PumpEvents();
        SDL_RenderClear(igra.okno.ren);
        img_overworld.ini(igra, "common/img/overworld.png");
        img_overworld.display(igra.okno.ren);
        narisiFarmeAliDosezke(igra, level_clear);
        SDL_RenderPresent(igra.okno.ren);

        switch (level_clear) {
        case 0:
            img_player.init(igra, "common/img/player.png", 55, 160, 29, 64);
            img_player.display(igra.okno.ren);
            igra.haltEnter(0); // takoj ko odpremo in je na ladji
            animacija(igra, 1);

            premakniNaXY(igra, x, y, 180, 160, img_overworld, img_player, 0);
            igra.haltEnter(0); // prej ko se zacne prvi level in smo zravn hiske 

            cout << "Prvi nivo" << endl;
            igra.level(level_clear);
            break;
        case 1:
            premakniNaXY(igra, x, y, 90, 250, img_overworld, img_player, level_clear);
            igra.haltEnter(1); // stojimo pred mostom
            animacija(igra, 2);
            premakniNaXY(igra, x, y, 165, 350, img_overworld, img_player, level_clear);
            igra.haltEnter(1); // stojimo pred 2. levelom

            cout << "Drugi nivo" << endl;
            igra.level(level_clear);
            break;
        case 2:
            premakniNaXY(igra, x, y, 200, 450, img_overworld, img_player, level_clear);
            premakniNaXY(igra, x, y, 275, 500, img_overworld, img_player, level_clear);
            premakniNaXY(igra, x, y, 325, 500, img_overworld, img_player, level_clear);
            igra.haltEnter(level_clear); //stojimo na kotu
            animacija(igra, 3);
            premakniNaXY(igra, x, y, 350, 450, img_overworld, img_player, level_clear);
            igra.haltEnter(level_clear); //stojimo na 3. levelu

            cout << "Tretji nivo" << endl;
            igra.level(level_clear);
            break;
        case 3:
            premakniNaXY(igra, x, y, 445, 320, img_overworld, img_player, level_clear);
            igra.haltEnter(level_clear); // stojimo na lojtri
            animacija(igra, 4);
            premakniNaXY(igra, x, y, 460, 240, img_overworld, img_player, level_clear);
            igra.haltEnter(level_clear); //stojimo na 4. levelu
            cout << "Cetrti nivo" << endl;
            igra.level(level_clear);
            premakniNaXY(igra, x, y, 420, 150, img_overworld, img_player, level_clear); //testing d se pokaze
            igra.haltEnter(level_clear);
            break;
        case 4:
            animacija(igra, 5);
            premakniNaXY(igra, x, y, 420, 100, img_overworld, img_player, level_clear);
            igra.haltEnter(4);
            animacija(igra, 6);
            cout << "Peti nivo" << endl;
            igra.level(level_clear);
            break;
        case 5:
            premakniNaXY(igra, x, y, 425, 30, img_overworld, img_player, level_clear);
            igra.haltEnter(4);

            cout << "Zmaga!" << endl;
            animacija(igra, 7);
            img_overworld.ini(igra, "common/img/overworld.png");
            img_overworld.display(igra.okno.ren);
            img_player.init(igra, "common/img/player.png", x, y, 29, 64);
            img_player.display(igra.okno.ren);
            img_zastavica_fullscreen.ini(igra, "common/img/zastavica_fullscreen.png");
            img_zastavica_fullscreen.display(igra.okno.ren);
            narisiFarmeAliDosezke(igra, level_clear);
            SDL_RenderPresent(igra.okno.ren);

            //prikaz rekordov
            SDL_Delay(3000);
            main = 1;
            igra.setCompleted();
            break;
        default:
            cout << "Error: level_clear" << endl;
        }
        SDL_RenderPresent(igra.okno.ren);

        if ((igra.keys[SDL_SCANCODE_ESCAPE] || igra.event.type == SDL_QUIT)) {
            main = 1;
        }
    }
    SDL_RenderClear(igra.okno.ren);
    //shranjevanje recordov
}

void nastavitve(GameManager& igra) {
    SDL_RenderClear(igra.okno.ren);
    SDL_Delay(200);
    SDL_PollEvent(&igra.event);
    int main = 0;
    int pozicija_cursorja = 1;
    Image img_nastavitve;
    Image cursor;
    while (main == 0)
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
                main = 1;
            }
            break;
        }

        if (!(!igra.keys[SDL_SCANCODE_ESCAPE] || igra.event.type != SDL_QUIT)) {
            main = 1;
        }

        SDL_RenderPresent(igra.okno.ren);
        SDL_Delay(75);
    }

    //igra.sound.oof();
}
void vec(GameManager& igra) {
    SDL_Delay(200);
    SDL_PollEvent(&igra.event);
    int main = 0;
    int pozicija_cursorja = 1;
    Image img_vec;
    Image cursor;
    Image github(igra.okno.ren, "common/img/github.png", igra.okno.scaleCal(20), igra.okno.scaleCal(20), igra.okno.scaleCal(279), igra.okno.scaleCal(66));
    while (main == 0)
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
                main = 1;
            }
            break;
        }

        if (!(!igra.keys[SDL_SCANCODE_ESCAPE] || igra.event.type != SDL_QUIT)) {
            main = 1;
        }

        SDL_RenderPresent(igra.okno.ren);
        SDL_Delay(75);
    }

    //igra.sound.oof();
}

void animacija(GameManager& igra, int stAnim) {
    SDL_RenderClear(igra.okno.ren);
    Image odzadje;

    string pathFragment = "common/img/animacija"; // zacetek
    pathFragment += to_string(stAnim);
    pathFragment += ".png";
    char* path = new char[pathFragment.size() + 1];
    std::copy(pathFragment.begin(), pathFragment.end(), path);
    path[pathFragment.size()] = '\0';
    odzadje.ini(igra, path); // klic
    delete[] path; // konec

    odzadje.display(igra.okno.ren);
    SDL_RenderPresent(igra.okno.ren);

    igra.sound.soundAnimacija(stAnim);
    SDL_Delay(500);
    
    SDL_PollEvent(&igra.event);
    SDL_PumpEvents();
    Image img_enter;
    int blink = 0;
    cout << "Animacija caka na enter" << endl;
    img_enter.ini(igra, "common/img/pressreturn.png");
    while (!igra.keys[SDL_SCANCODE_RETURN]) {
        SDL_PollEvent(&igra.event);
        SDL_PumpEvents();
        SDL_RenderClear(igra.okno.ren);
        odzadje.display(igra.okno.ren);
        if (blink < 100) {
            img_enter.display(igra.okno.ren);
        }
        else if (blink > 150) {
            blink = 0;
        }
        blink++;
        SDL_RenderPresent(igra.okno.ren);
        SDL_Delay(10);
    }
    cout << "Pritisnili ste enter :)" << endl;
}

void premakniNaXY(GameManager &igra, int &x, int &y, int final_x, int final_y, Image &img_overworld, Image &img_player, int nivo){
    int i = 0;
    while (true) {
        if (x != final_x) {
            if (x < final_x) x++;
            else x--;
        }
        if (y != final_y) {
            if (y < final_y) y++;
            else y--;
        }
        if (x == final_x && y == final_y) {
            SDL_RenderClear(igra.okno.ren);
            img_overworld.display(igra.okno.ren);
            narisiFarmeAliDosezke(igra, nivo);
            img_player.init(igra, "common/img/player_event.png", x, y, 29, 64);
            img_player.display(igra.okno.ren);
            SDL_RenderPresent(igra.okno.ren);
            break;
        }

        SDL_RenderClear(igra.okno.ren);
        img_overworld.display(igra.okno.ren);
        
        if (i < 10)
            img_player.init(igra, "common/img/player.png", x, y, 29, 64);
        else if (i > 20)
            i = 0;
        else
            img_player.init(igra, "common/img/player_noge.png", x, y, 29, 64);
        narisiFarmeAliDosezke(igra, nivo);
        img_player.display(igra.okno.ren);
        SDL_RenderPresent(igra.okno.ren);
        SDL_Delay(10);
        i+=1;
    }
}

void narisiFarmeAliDosezke(GameManager& igra, int nivo) {
    Image hisa[5];
    int x[5] = { 210, 100, 320, 460, 450 };
    int y[5] = { 160, 425, 420, 215, 100 };
    for (int i = 0; i < 5; i++) {
        if (i<nivo) {
            hisa[i].init(igra, "common/img/iglu.png", x[i], y[i], 66, 61);
        }
        else {
            hisa[i].init(igra, "common/img/farma.png", x[i], y[i], 66, 61);
        }
    }
    for (int i = 0; i < 5; i++) {
        hisa[i].display(igra.okno.ren);
    }
}