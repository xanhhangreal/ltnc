#ifndef HAMTUDAT_H
#define HAMTUDAT_H

#include "TextObject.h"

using namespace std;

void PlayGame()
{
    SDL_Texture* background = SDLcommonFunc:: LoadTexture("Textures/NenTitle.jpg");
    SDL_Texture* onglao = SDLcommonFunc:: LoadTexture("Textures/onglao.png");
    SDL_Texture* title = SDLcommonFunc:: LoadTexture("Textures/title.png");

    SDL_RenderCopy(renderer, background, NULL, NULL);
    SDLcommonFunc:: ApplyTexture(onglao, 100, 250, 0.5);
    SDLcommonFunc:: ApplyTexture(title, 273, 50, 1.2);

    TextObject PLAY_GAME;
    PLAY_GAME.SetColor(TextObject::BLACK_TEXT);
    string val_str_st = "Play Game";

    PLAY_GAME.SetText(val_str_st);

    SDL_RenderPresent(renderer);
}
#endif // HAMTUDAT_H
