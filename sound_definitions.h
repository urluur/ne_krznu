#pragma once
void sound_cursorMove() {
    bool played = PlaySound(TEXT("cur_mov.wav"), NULL, SND_ASYNC);
}
void sound_oof() {
    bool played = PlaySound(TEXT("oof.wav"), NULL, SND_ASYNC);
    SDL_Delay(300);
}