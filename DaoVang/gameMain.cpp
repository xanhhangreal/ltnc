#include "gameMain.h"

bool rectImpact(SDL_Rect a, SDL_Rect b, double alw)
{
    return true;
}

int gameMain(levelInfo* level)
{
    TTF_Font* font_game = TTF_OpenFont("Font/uvndaLat.ttf", 40);
    BaseObject resTexture[level->totalRes], hook, line;
    TextObject timeText, levelText, goalText, gradeText;
    SDL_Point minerPin, hookPin, linePin;
    resProperties resProp;
    int startTime, levelTime, hookTimer, lineTimer;
    int catchedRes = 0;
    bool running = true, hookDown = false, hookGoRight = true, hookBack = false;
    levelTime = SDL_GetTicks();
    std::string levelStr = "", goalStr = "$";
    double hookAgle = 20.0, lineLen = 0.0;


    BaseObject gameBg;
    gameBg.LoadImg(imgFile[ID_GAMEBG], g_screen);
    gameBg.Render(g_screen, NULL);
    SDL_RenderPresent(g_screen);
    gameBg.Free();
//    levelText.SetText(std::to_string(level->level));
//    levelText.SetColor(0x21, 0xd0, 0x1d);
//    levelText.LoadFromRenderText(font_game, g_screen);


   // levelText.RenderText(g_screen, 10, 10);


    return true;
}
