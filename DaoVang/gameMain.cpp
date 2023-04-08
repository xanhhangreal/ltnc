#include "gameMain.h"


SDL_Texture* loadRenderText(const char* text, int ID_COLOR)
{
    TTF_Font* gameFont = TTF_OpenFont("uvndaLat.ttf", 40);
    SDL_Color color;
    if(ID_COLOR == RED_TEXT) color = {255, 0, 0};
    else if(ID_COLOR == WHITE_TEXT) color = {255, 255, 255};
    else if(ID_COLOR == BLACK_TEXT) color = {0, 0, 0};

    SDL_Surface* textSurface = TTF_RenderText_Solid(gameFont, text, color);
	if(textSurface == NULL) {
		printf("Failed to render text surface! %s\n", TTF_GetError());
		return NULL;
	}
	SDL_Texture* Tex = SDL_CreateTextureFromSurface(g_screen, textSurface);
	if(Tex == NULL) std:: cout << SDL_GetError();
    return Tex;
}
bool rectImpact(SDL_Rect a, SDL_Rect b, double alw)
{
    return true;
}

int gameMain(levelInfo* level)
{
    return 0;
}
