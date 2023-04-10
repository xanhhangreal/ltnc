#include "Common_Function.h"
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
    TTF_Font* font_game = TTF_OpenFont("Font/uvndaLat.ttf", 100);
    bool running = true;
    BaseObject goalBg;
    TextObject goalGrade;
    unsigned int frames = 0;

    goalBg.LoadImg(imgFile[ID_GOALBG], g_screen);

    /// Text
    string str_goal = to_string(goal);
    str_goal = str_goal + "$";
    goalGrade.SetColor(0x21, 0xd0, 0x1d);
    goalGrade.SetText(str_goal);
    goalGrade.LoadFromRenderText(font_game, g_screen);
    goalGrade.SetValue(20 * (getNumDigit(goal) + 1), 70);

    while(running)
    {
        while(SDL_PollEvent(&g_event))
            running = (g_event.type == SDL_QUIT);

        SDL_RenderClear(g_screen);
        goalBg.Render(g_screen, NULL);
        goalGrade.RenderText(g_screen, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 30);
        SDL_RenderPresent(g_screen);

        if(++frames >= FPS) running = false;

    }

    SDL_Delay(1400);
    goalBg.Free();
    goalGrade.Free();
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
    if(win == true) std::cout << "You Win ";
    else std::cout << "You Lost ";
}
bool rectImpact(SDL_Rect a, SDL_Rect b, double alw)
{
    SDL_Point r1, r2;
	r1.x = a.x + a.w / 2;
	r1.y = a.y + a.h / 2;
	r2.x = b.x + b.w / 2;
	r2.y = b.y + b.h / 2;
	double r = sqrt((r1.x - r2.x)*(r1.x - r2.x) + (r1.y - r2.y)*(r1.y - r2.y));
	if( r <= (a.w + b.w) / (2.0 * alw) && r <= (a.h + b.h) / (2.0 * alw))
    {
        //cout << alw;
        return true;
    }
	else
		return false;
}
double getAlw(int resId)
{
	double alw = 0;
	switch(resId) {
	case ID_BSTONE:
		alw = ID_BSTONE_ALW;
		break;
	case ID_SSTONE:
		alw = ID_SSTONE_ALW;
		break;
	case ID_BGOLD:
		alw = ID_BGOLD_ALW;
		break;
    case ID_SGOLD:
        alw = ID_SGOLD_ALW;
		break;
	case ID_DIAMOND:
		alw = ID_DIAMOND_ALW;
		break;
	case ID_BAG:
		alw = ID_BAG_ALW;
		break;

	}
	return alw;
}

int gameMain(levelInfo* level)
{
    TTF_Font* font_game = TTF_OpenFont("Font/VTIMESI.TTF", 50);
    BaseObject gameBg, resTexture[level->totalRes], hook, line;
    TextObject timeText, levelText, goalText, gradeText;
    SDL_Point minerPin, hookPin, linePin;
    resProperties resProp;
    int startTime, levelTime, hookTimer, lineTimer;
    int catchedRes = 0, userGrade = 0;
    bool running = true, hookDown = false, hookGoRight = true, hookBack = false;
    levelTime = SDL_GetTicks();
    std::string levelStr = "", goalStr = "$" + std::to_string(level->levelGoal);
    double hookAngle = 20.0, lineLen = 0.0;

    gameBg.LoadImg(imgFile[ID_GAMEBG], g_screen);
    hook.LoadImg(imgFile[ID_HOOK], g_screen);
    SDL_Rect hookRect = hook.GetRect();
    line.LoadImg(imgFile[ID_LINE], g_screen);


    levelText.SetText(std::to_string(level->level));
    levelText.SetColor(TextObject::RED_TEXT);
    levelText.LoadFromRenderText(font_game, g_screen);
    goalText.SetText(goalStr);
    goalText.SetColor(TextObject::RED_TEXT);
    goalText.LoadFromRenderText(font_game, g_screen);

    for(int i = 0; i < level->totalRes; i++)
    {
        resTexture[i].LoadImg(imgFile[level->reses[i].id], g_screen);
        resTexture[i].SetRect(level->reses[i].position.x, level->reses[i].position.y);
    }

	levelText.SetValue(13 * getNumDigit(level->level), 45);
	goalText.SetValue(15 * (1 + getNumDigit(level->levelGoal)), 45);

	minerPin.x = 480;
	minerPin.y = 120;
	hookRect.x = minerPin.x - hookRect.w / 2;
	hookRect.y = minerPin.y - 20;
    line.SetRect(minerPin.x - hookRect.w / 2, minerPin.y - 20, 3, 0);
    SDL_Rect lineRect = line.GetRect();
	hookTimer = 0;
	lineTimer = 0;
	lineLen = 0;
	catchedRes = -1;
	hookPin.x = hookRect.w / 2;
	hookPin.y = 0;
	linePin.x = 2;
	linePin.y = 0;


    while(running)
    {
        char timeStr[3] = { 0 };
        startTime = SDL_GetTicks();
        if(startTime - levelTime > 60000) running = false;
        while(SDL_PollEvent(&g_event))
        {
            if(g_event.type == SDL_QUIT) running = false;
            if(g_event.type == SDL_KEYDOWN)
                if((g_event.key.keysym.sym == SDLK_DOWN || g_event.key.keysym.sym == SDLK_SPACE) && !hookDown)
                    hookDown = true;
        }

        if(!hookDown)
        {
            if(SDL_GetTicks() - hookTimer > 20)
            {
                hookTimer = SDL_GetTicks();
                if(hookGoRight)
                {
                    hookAngle += 1.5;
                    if(hookAngle >= 165.0) hookGoRight = false;
                }
                else
                {
                    hookAngle -= 1.5;
                    if(hookAngle <= 15.0) hookGoRight = true;
                }
            }
        }
        else
        {
            if(SDL_GetTicks() - lineTimer > 20)
            {
                lineTimer = SDL_GetTicks();
                if(!hookBack) lineLen += 5;
                else if(resProp.getId() == -1) lineLen -= 6;
                else
                {
                    lineLen -= (double)6 / resProp.getWeight();
                    if(hookAngle <= 90.0)
                    {
                        SDL_Rect rect = resTexture[catchedRes].GetRect();
						resTexture[catchedRes].SetRect(hookRect.x - rect.w / 2,
                                                       hookRect.y - rect.h / 2 + 35);
                    }
                    else
                    {
                        SDL_Rect rect = resTexture[catchedRes].GetRect();
						resTexture[catchedRes].SetRect(hookRect.x + rect.w / 2 - 30,
                                                       hookRect.y - rect.h / 2 + 35);
                    }
                }
                if(lineLen < 0.0) lineLen = 0.0;
            }
            if(lineLen <= 1.0)
            {
                hookDown = hookBack = false;
                userGrade += resProp.score;
                resProp.setId(-1);
                if(catchedRes != -1) resTexture[catchedRes].Free();
                catchedRes = -1;
            }
            if(lineLen >= 500.0) hookBack = true;
            if(hookAngle <= 90.0)
            {
                hookRect.x = minerPin.x - hookRect.w - abs(cos(hookAngle / 180.0 * M_PI) * lineLen);
                hookRect.y = minerPin.y + abs(sin(hookAngle / 180.0 * M_PI) * lineLen) - 20;
            }
            else
            {
                hookRect.x = minerPin.x - hookRect.w + abs(cos(hookAngle / 180.0 * M_PI) * lineLen);
				hookRect.y = minerPin.y + abs(sin(hookAngle / 180.0 * M_PI) * lineLen) - 20;
            }
        }
        gradeText.SetText("$" + to_string(userGrade));
        gradeText.SetColor(0x21, 0xd0, 0x1d);
        gradeText.LoadFromRenderText(font_game, g_screen);
        gradeText.SetValue(15 * (getNumDigit(userGrade) + 1), 45);
        lineRect.h = lineLen;
        line.SetRect(lineRect.x, lineRect.y, lineRect.w, lineRect.h);

        timeText.Free();
        timeText.SetText(to_string(60 - (startTime - levelTime) / 1000));
        timeText.SetColor(TextObject::RED_TEXT);
        timeText.LoadFromRenderText(font_game, g_screen);
        timeText.SetValue(26, 40);

        gameBg.Render(g_screen, NULL);
        levelText.RenderText(g_screen, 850, 80);
        timeText.RenderText(g_screen, 850, 20);
        goalText.RenderText(g_screen, 125, 80);
        gradeText.RenderText(g_screen, 130, 20);
        SDL_RenderCopyEx(g_screen, hook.GetObject(), NULL, &hookRect, 90 - hookAngle, &hookPin, SDL_FLIP_NONE);
		SDL_RenderCopyEx(g_screen, line.GetObject(), NULL, &lineRect, 90 - hookAngle, &linePin, SDL_FLIP_NONE);

		for(int i = 0; i < level->totalRes; i++)
            if(resTexture[i].GetObject() != NULL) resTexture[i].Render(g_screen, NULL);
        SDL_RenderPresent(g_screen);

        if(catchedRes == -1)
        {
            for(int i = 0; i < level->totalRes; i++)
            {
				if(resTexture[i].GetObject() == NULL) continue;
				if(rectImpact(hookRect, resTexture[i].GetRect(), getAlw(level->reses[i].id)))
				{
					catchedRes = i;
					resProp.setId(level->reses[i].id);
					hookBack = true;
					printf("Catched!\n");
					break;
                }
            }
        }
    }


    for(int i = 0; i < level->totalRes; i++) resTexture[i].Free();
    line.Free();
    hook.Free();
    gameBg.Free();
    timeText.Free();
    levelText.Free();
    return true;
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
    if(!readyAnimation()) return 0;
    else
        startGame();

    SDL_FreeSurface(icon);
    quitSDL();
    return 0;
}


