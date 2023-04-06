#include "Common_Function.h"
#include "BaseObject.h"
#include "SDL_utils.h"
using namespace std;

bool mouseInside(SDL_Point mouse, SDL_Rect area)
{
    if(mouse.x >= area.x && mouse.x <= area.x + area.w
       && mouse.y >= area.y && mouse.y <= area.y + area.h)
            return true;
    return false;
}
bool readyAnimation()
{
    BaseObject light, startBg, startButton;
	SDL_Rect lightRect, buttonRect, buttonClip[2];
	Mix_Chunk *mouseIn;
	double lightRadius = 200.0;
	bool running = true, increase = false;
	bool mouseOver = 0;
	Uint32 startTime;
	bool status = false;

	mouseIn = Mix_LoadWAV("Sounds/mouseIn.wav");
	light.LoadImg("Textures/light.png", g_screen);
	startBg.LoadImg("Textures/startBg.jpg", g_screen);
	startButton.LoadImg("Textures/startButton.png", g_screen);

	buttonClip[0].x = 0;
	buttonClip[0].y = 0;
	buttonClip[0].w = 160;
	buttonClip[0].h = 43;
	buttonClip[1].x = 0;
	buttonClip[1].y = 43;
	buttonClip[1].w = 160;
	buttonClip[1].h = 55;

	startButton.SetRect(265, 170, 160, 43);

	while(running)
    {
        startTime = SDL_GetTicks();

        while(SDL_PollEvent(&g_event))
        {
            if(g_event.type == SDL_QUIT) running = false;
            if(g_event.type == SDL_KEYDOWN)
                if(g_event.key.keysym.sym == SDLK_SPACE)
                {
                    status = true;
                    running = false;
                }
            if(g_event.type == SDL_MOUSEMOTION || g_event.type == SDL_MOUSEBUTTONDOWN)
            {
                SDL_Point mouse;
                SDL_GetMouseState(&mouse.x, &mouse.y);
                if(mouseInside(mouse, startButton.GetRect()))
                {
                    if(g_event.type == SDL_MOUSEBUTTONDOWN)
                    {
                        status = true;
                        running = false;
                    }
                    if(mouseOver == 0) Mix_PlayChannel(-1, mouseIn, 0);
                    startButton.SetRect(265, 170, 160, 55);
                    mouseOver = 1;
                }
                else
                {
                    startButton.SetRect(265, 170, 160, 43);
                    mouseOver = 0;
                }
            }
        }
        light.SetRect(360 - lightRadius, 208 - lightRadius, lightRadius * 2, lightRadius * 2);
        SDL_RenderClear(g_screen);
        startBg.Render(g_screen, NULL);
        light.Render(g_screen, NULL);
        startButton.Render(g_screen, &buttonClip[mouseOver]);
        SDL_RenderPresent(g_screen);

        if(increase)
        {
			lightRadius += 0.6;
			if(lightRadius > 290) increase = false;
		}
		else
        {
			lightRadius -= 0.7;
			if(lightRadius < 240) increase = true;
		}
        if(PRE_FRAME_TICKS > (SDL_GetTicks() - startTime))
			SDL_Delay(PRE_FRAME_TICKS - (SDL_GetTicks() - startTime));
    }

    light.Free();
    startBg.Free();
    startButton.Free();
    Mix_FreeChunk(mouseIn);

    return status;
}

TTF_Font* gameFont = NULL;
SDL_Color fontColor = { 0x21, 0xd0, 0x1d};
int userGrade = 0;

void startGame()
{
    int lvlNum = 1;
	bool win = false;
	//levelInfo* lvl = NULL;
	gameFont = TTF_OpenFont("VTIMESI.TTF", 40);
}
int main(int argc, char* argv[]){
    initSDL();

    SDL_Surface* icon = IMG_Load("Textures/icon.png");
    SDL_SetWindowIcon(g_window, icon);
    if(readyAnimation()) return 0;
    else startGame();

    SDL_FreeSurface(icon);
    quitSDL();
    return 0;
}


