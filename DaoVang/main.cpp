#include "Data.h"
#include "Common_Function.h"
#include "BaseObject.h"
#include "TextObject.h"
#include "gameMain.h"
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

	mouseIn = Mix_LoadWAV(sodFile[ID_MOUSEIN]);
	light.LoadImg(imgFile[ID_LIGHT], g_screen);
	startBg.LoadImg(imgFile[ID_STARTBG], g_screen);
	startButton.LoadImg(imgFile[ID_STARTBUTTON], g_screen);

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

void destroyLevel(levelInfo* lvl)
{
	free(lvl->reses);
	free(lvl);
	lvl = NULL;
}
unsigned int getNumDigit(int num)
{
    if(!num) return 1;
    unsigned int Count = 0;
    while(num)
    {
        num /= 10;
        Count++;
    }
    return Count;
}
void setGoal(int goal)
{
    bool running = true;
    char goalString[10];
    BaseObject goalDia, goalBg;
    SDL_Texture* goalGrade;
    SDL_Rect textRect;
    unsigned int frames = 0;

    goalBg.LoadImg("Textures/goalBg.png", g_screen);
    goalDia.LoadImg("Textures/goalDia.png", g_screen);

    goalString[0] = '$';
    SDL_itoa(goal, &goalString[1], 10);
    goalGrade = loadRenderText(goalString, BLACK_TEXT);

	textRect.x = 10;//SCREEN_WIDTH / 2;
	textRect.y = 10;//SCREEN_HEIGHT / 2 - 30;
	textRect.w = 20 * (getNumDigit(goal) + 1);
	textRect.h = 70;

    goalDia.SetRect(SCREEN_WIDTH/2 - 320, SCREEN_HEIGHT/2 - 180, 640, 340);

//    while(running)
//    {
//        while(SDL_PollEvent(&g_event))
//            running = (g_event.type == SDL_QUIT);
//
//        SDL_RenderClear(g_screen);
//        goalBg.Render(g_screen, NULL);
//        //goalDia.Render(g_screen, NULL);
//        SDL_RenderCopy(g_screen, goalGrade, NULL, &textRect);
//        SDL_RenderPresent(g_screen);
//
//
//        if(++frames >= FPS) running = false;
//
//    }
    SDL_RenderCopy(g_screen, goalGrade, NULL, &textRect);
        SDL_RenderPresent(g_screen);
    if(goalGrade == NULL) cout << "?";
    waitUntilKeyPressed();
    goalBg.Free();
    goalDia.Free();
    SDL_DestroyTexture(goalGrade);
}
levelInfo* getLevel(int lvl)
{
    if(lvl == 1)
    {
        levelInfo* currentLvl = (levelInfo *)malloc(sizeof(levelInfo));
        currentLvl->level = lvl;
        currentLvl->levelGoal = 650;
        currentLvl->totalRes = 2;

        resPos* res = (resPos* )malloc(sizeof(resPos) * currentLvl->totalRes);
        res[0].id = ID_BSTONE;
        res[0].position.x = 600; res[0].position.y = 300;
        res[1].id = ID_DIAMOND;
        res[1].position.x = 100; res[1].position.y = 400;

        currentLvl->reses = res;
        return currentLvl;
    }
    return NULL;
}
void gameOver(bool win)
{
    if(win == true) std::cout << "You Win " << userGrade;
    else std::cout << "You Lost " << userGrade;
}
void startGame()
{
    int lvlNum = 0;
	bool win = false;
	levelInfo* lvl = NULL;

    while(true)
    {
        lvl = getLevel(++lvlNum);
        if(lvl == NULL)
        {
            win = true;
            gameOver(win);
            break;
        }
        setGoal(lvl->levelGoal);
        if(gameMain(lvl) <= lvl->levelGoal)
        {
            gameOver(win);
            break;
        }
        destroyLevel(lvl);
    }
}
int main(int argc, char* argv[]){
    initSDL();

    SDL_Surface* icon = IMG_Load("Textures/icon.png");
    SDL_SetWindowIcon(g_window, icon);
    //if(!readyAnimation()) return 0;
    //else
    startGame();
    SDL_FreeSurface(icon);
    quitSDL();
    return 0;
}


