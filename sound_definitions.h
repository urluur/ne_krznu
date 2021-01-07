#pragma once
using namespace std;

class Sounds {
private:
    Mix_Music* bgm;
    int mute = 0;
    bool played;
public:
    Sounds();
    void toggle();
    void oof();
    void cursorMove();
    ~Sounds(){
        bgm = nullptr;
        Mix_Quit();
    }
};

Sounds::Sounds(){
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
            cout << "Mixer error: " << Mix_GetError() << endl;
        }
        bgm = Mix_LoadMUS("common/sounds/soundtrack.wav");
        if (!Mix_PlayingMusic()) {
            Mix_PlayMusic(bgm, -1);
        }
}

void Sounds::toggle() {
    if (!Mix_PlayingMusic) {
        Mix_ResumeMusic();
        mute = 0;
    }
    else {
        Mix_HaltMusic();
        mute = 1;
    }
}

void Sounds::cursorMove() {
    if(mute == 0)
        played = PlaySound(TEXT("common/sounds/cur_mov.wav"), NULL, SND_ASYNC);
}
void Sounds::oof() {
    if (mute == 0)
        played = PlaySound(TEXT("common/sounds/oof.wav"), NULL, SND_SYNC);
}