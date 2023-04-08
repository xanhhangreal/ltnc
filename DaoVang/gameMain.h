#ifndef GAME_MAIN_H_
#define GAME_MAIN_H_

#include "Common_Function.h"

SDL_Texture* loadRenderText(const char* text, int ID_COLOR);

bool rectImpact(SDL_Rect a, SDL_Rect b, double alw);
int gameMain(levelInfo* level);

#endif // GAME_MAIN_H_H
