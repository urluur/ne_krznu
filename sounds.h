#pragma once
#include <SDL_mixer.h>
#include <iostream>
#include <windows.h>
#include <MMSystem.h>

class Sounds {
private:
    Mix_Music* bgm;
    int mute;
    bool played;
public:
    Sounds();
    void toggle();
    void oof();
    void cursorMove();
    void dimenzije();
    void izhod();
    void nastavitve();
    void nasvidenje();
    void nazaj();
    void spremeni_ime();
    void spremeni_zvok();
    void vec();
    void zacni();
    ~Sounds();
};

