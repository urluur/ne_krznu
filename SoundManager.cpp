#include "SoundManager.h"
using namespace std;
SoundManager::SoundManager() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        cout << "Mixer error: " << Mix_GetError() << endl;
    }
    bgm = Mix_LoadMUS("common/sounds/soundtrack.wav");
    if (!Mix_PlayingMusic()) {
        Mix_PlayMusic(bgm, -1);
    }
    mute = 0;
}

void SoundManager::toggle() {
    if (mute == 0) {
        mute = 1;
        Mix_PauseMusic();
        cout << "Glasba se je ustavila .." << endl;
    }
    else {
        mute = 0;
        Mix_ResumeMusic();
        cout << "Glasba se nadaljuje.." << endl;
    }

}
void SoundManager::cursorMove() {
    if (mute == 0)
        played = PlaySound(TEXT("common/sounds/cur_mov.wav"), NULL, SND_ASYNC);
}
void SoundManager::oof() {
    if (mute == 0)
        played = PlaySound(TEXT("common/sounds/oof.wav"), NULL, SND_SYNC);
}
void SoundManager::dimenzije(){
    if (mute == 0)
        played = PlaySound(TEXT("common/sounds/dimenzije.wav"), NULL, SND_ASYNC);
}
void SoundManager::izhod() {
    if (mute == 0)
        played = PlaySound(TEXT("common/sounds/izhod.wav"), NULL, SND_SYNC);
}
void SoundManager::nastavitve() {
    if (mute == 0)
        played = PlaySound(TEXT("common/sounds/nastavitve.wav"), NULL, SND_SYNC);
}
void SoundManager::nasvidenje() {
    if (mute == 0)
        played = PlaySound(TEXT("common/sounds/nasvidenje.wav"), NULL, SND_SYNC);
}
void SoundManager::nazaj() {
    if (mute == 0)
        played = PlaySound(TEXT("common/sounds/nazaj.wav"), NULL, SND_SYNC);
}
void SoundManager::spremeni_ime() {
    if (mute == 0)
        played = PlaySound(TEXT("common/sounds/spremeni_ime.wav"), NULL, SND_ASYNC);
}
void SoundManager::spremeni_zvok() {
    played = PlaySound(TEXT("common/sounds/spremeni_zvok.wav"), NULL, SND_ASYNC);
}
void SoundManager::vec() {
    if (mute == 0)
        played = PlaySound(TEXT("common/sounds/vec.wav"), NULL, SND_SYNC);
}
void SoundManager::zacni() {
    if (mute == 0)
        played = PlaySound(TEXT("common/sounds/zacni.wav"), NULL, SND_SYNC);
}
void SoundManager::lestvica() {
    if (mute == 0)
        played = PlaySound(TEXT("common/sounds/lestvica.wav"), NULL, SND_ASYNC);
}
void SoundManager::izvorna() {
    if (mute == 0)
        played = PlaySound(TEXT("common/sounds/izvorna.wav"), NULL, SND_ASYNC);
}
void SoundManager::izbris() {
    if (mute == 0)
        played = PlaySound(TEXT("common/sounds/izbris.wav"), NULL, SND_ASYNC);
}
void SoundManager::animacija1() {
    if (mute == 0)
        played = PlaySound(TEXT("common/sounds/animacija1.wav"), NULL, SND_SYNC);
}
void SoundManager::animacija2() {
    if (mute == 0)
        played = PlaySound(TEXT("common/sounds/animacija2.wav"), NULL, SND_SYNC);
}
void SoundManager::animacija3() {
    if (mute == 0)
        played = PlaySound(TEXT("common/sounds/animacija3.wav"), NULL, SND_SYNC);
}
void SoundManager::animacija4() {
    if (mute == 0)
        played = PlaySound(TEXT("common/sounds/animacija4.wav"), NULL, SND_SYNC);
}
void SoundManager::animacija5() {
    if (mute == 0)
        played = PlaySound(TEXT("common/sounds/animacija5.wav"), NULL, SND_SYNC);
}


SoundManager::~SoundManager() {
    bgm = nullptr;
    Mix_Quit();
}