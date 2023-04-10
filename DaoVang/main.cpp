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
	Mix_Chunk* mouseIn;
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
    Mix_Chunk* level = Mix_LoadWAV(sodFile[ID_LEVEL]);
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

    Mix_PlayChannel(-1, level, 0);
    while(running)
    {
        while(SDL_PollEvent(&g_event))
            running = (g_event.type == SDL_QUIT);

        SDL_RenderClear(g_screen);
        goalBg.Render(g_screen, NULL);
        goalGrade.RenderText(g_screen, SCREEN_WIDTH / 2 + 45, SCREEN_HEIGHT / 2 - 30);
        SDL_RenderPresent(g_screen);

        if(++frames >= FPS) running = false;

    }

    SDL_Delay(1800);
    goalBg.Free();
    goalGrade.Free();
    Mix_FreeChunk(level);
}
levelInfo* getLevel(int lvl)
{
    if(lvl == 1)
    {
        levelInfo* currentLvl = (levelInfo *)malloc(sizeof(levelInfo));
        currentLvl->level = lvl;
        currentLvl->levelGoal = 650;
        currentLvl->totalRes = 8;

        resPos* res = (resPos* )malloc(sizeof(resPos) * currentLvl->totalRes);
        res[0].id = ID_BSTONE;
        res[0].position = {900, 300};
        res[1].id = ID_BGOLD;
        res[1].position = {1000, 450};
        res[2].id = ID_SGOLD;
        res[2].position = {300, 500};
        res[3].id = ID_SSTONE;
        res[3].position = {250, 250};
        res[4].id = ID_BGOLD;
        res[4].position = {100, 400};
        res[5].id = ID_SGOLD;
        res[5].position = {350, 200};
        res[6].id = ID_SGOLD;
        res[6].position = {500, 230};
        res[7].id = ID_SSTONE;
        res[7].position = {700, 400};

        currentLvl->reses = res;

        currentLvl->idBg = ID_GAMEBG1;
        return currentLvl;
    }
    else if(lvl == 2)
    {
        levelInfo* currentLvl = (levelInfo *)malloc(sizeof(levelInfo));
        currentLvl->level = lvl;
        currentLvl->levelGoal = 1200;
        currentLvl->totalRes = 13;

        resPos* res = (resPos* )malloc(sizeof(resPos) * currentLvl->totalRes);
        res[0].id = ID_BSTONE;
        res[0].position = {900, 300};
        res[1].id = ID_BGOLD;
        res[1].position = {1000, 450};
        res[2].id = ID_SGOLD;
        res[2].position = {300, 500};
        res[3].id = ID_SSTONE;
        res[3].position = {250, 250};
        res[4].id = ID_BGOLD;
        res[4].position = {100, 400};
        res[5].id = ID_DIAMOND;
        res[5].position = {150, 600};
        res[6].id = ID_SGOLD;
        res[6].position = {500, 230};
        res[7].id = ID_SSTONE;
        res[7].position = {600, 200};
        res[8].id = ID_BSTONE;
        res[8].position = {400, 300};
        res[9].id = ID_BAG;
        res[9].position = {650, 650};
        res[10].id = ID_SGOLD;
        res[10].position = {600, 550};
        res[11].id = ID_SGOLD;
        res[11].position = {650, 580};
        res[12].id = ID_SGOLD;
        res[12].position = {580, 490};

        currentLvl->reses = res;

        currentLvl->idBg = ID_GAMEBG2;
        return currentLvl;
    }
    return NULL;
}
unsigned int userGrade = 0;
void gameOver(bool win, int levelNum)
{
    TTF_Font* font_game = TTF_OpenFont("Font/VTIMESI.TTF", 70);
    BaseObject nextLevel, bangLevel;
    TextObject Score, level;

    Score.SetText("Your score: " + to_string(userGrade));
    Score.SetColor(TextObject::WHITE_TEXT);
    Score.LoadFromRenderText(font_game, g_screen);
    Score.SetValue(20 * (getNumDigit(userGrade) + 13), 70);

    level.SetText("Level: " + to_string(levelNum));
    level.SetColor(TextObject::RED_TEXT);
    level.LoadFromRenderText(font_game, g_screen);
    level.SetValue(20 * (getNumDigit(levelNum) + 8), 70);

    bangLevel.LoadImg(imgFile[ID_BANGLEVEL], g_screen);
    bangLevel.SetRect(SCREEN_WIDTH / 2 - 60, 0);

    if(win == 0)
    {
        nextLevel.LoadImg(imgFile[ID_BGFAIL], g_screen);
    }
    else
    {
        nextLevel.LoadImg(imgFile[ID_BGWIN], g_screen);
    }
    Mix_Chunk* finish = Mix_LoadWAV(sodFile[ID_FINISH]);
    Mix_PlayChannel(-1, finish, 0);
    nextLevel.Render(g_screen, NULL);
    Score.RenderText(g_screen, SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2);
    bangLevel.Render(g_screen, NULL);
    level.RenderText(g_screen, SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 100);
    SDL_RenderPresent(g_screen);
    waitUntilKeyPressed();
    bangLevel.Free();
    Score.Free();
    nextLevel.Free();
    Mix_FreeChunk(finish);
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
    TTF_Font* font_game = TTF_OpenFont("Font/VTIMESI.TTF", 40);
    BaseObject gameBg, resTexture[level->totalRes], hook, line, duongray, cot1, cot2, obj[30];
    TextObject timeText, levelText, goalText, gradeText;
    SDL_Point minerPin, hookPin, linePin;
    resProperties resProp;
    int startTime, levelTime, hookTimer, lineTimer, objTimer;
    int catchedRes = 0;
    bool running = true, hookDown = false, hookGoRight = true, hookBack = false;
    levelTime = objTimer = SDL_GetTicks();
    std::string levelStr = "", goalStr = "$" + std::to_string(level->levelGoal);
    double hookAngle = 20.0, lineLen = 0.0;

    gameBg.LoadImg(imgFile[level->idBg], g_screen);
    hook.LoadImg(imgFile[ID_HOOK], g_screen);
    SDL_Rect hookRect = hook.GetRect();
    line.LoadImg(imgFile[ID_LINE], g_screen);
    duongray.LoadImg(imgFile[ID_DUONGRAY], g_screen);
    duongray.SetRect(0, 140);
    cot1.LoadImg(imgFile[ID_COT1], g_screen);
    cot2.LoadImg(imgFile[ID_COT2], g_screen);
    cot1.SetRect(150, 20, 150, 140);
    cot2.SetRect(980, 0, 150, 135);

    levelText.SetText(std::to_string(level->level));
    levelText.SetColor(TextObject::RED_TEXT);
    levelText.LoadFromRenderText(font_game, g_screen);
    goalText.SetText(goalStr);
    goalText.SetColor(TextObject::RED_TEXT);
    goalText.LoadFromRenderText(font_game, g_screen);

    for(int i = 0; i <= 11; i++)
    {
        obj[i].LoadImg(imgFile[ID_ONGLAO + i], g_screen);
        obj[i].SetRect(SCREEN_WIDTH / 2 - 55, 30);
        obj[i + 12].LoadImg(imgFile[ID_ONGLAO + i], g_screen);
        obj[i + 12].SetRect(SCREEN_WIDTH / 2 - 55, 30);
    }
    for(int i = 0; i < level->totalRes; i++)
    {
        resTexture[i].LoadImg(imgFile[level->reses[i].id], g_screen);
        resTexture[i].SetRect(level->reses[i].position.x, level->reses[i].position.y);
    }

	levelText.SetValue(13 * getNumDigit(level->level), 45);
	goalText.SetValue(15 * (1 + getNumDigit(level->levelGoal)), 45);

	minerPin.x = SCREEN_WIDTH / 2;
	minerPin.y = 140;
	hookRect.x = minerPin.x - hookRect.w;
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

    Mix_Chunk* lastart = Mix_LoadWAV(sodFile[ID_LASTART]);
    Mix_Chunk* laregeGold = Mix_LoadWAV(sodFile[ID_LARGEGOLD]);
    Mix_Chunk* select = Mix_LoadWAV(sodFile[ID_SELECT]);
    Mix_Chunk* lowValue = Mix_LoadWAV(sodFile[ID_LOWVALUE]);
    Mix_Chunk* norValue = Mix_LoadWAV(sodFile[ID_NORVALUE]);
    Mix_Chunk* score = Mix_LoadWAV(sodFile[ID_SCORE]);
    Mix_Chunk* kimCuong = Mix_LoadWAV(sodFile[ID_KC]);

    int id_O = 0;
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
            id_O = 0;
            if(SDL_GetTicks() - hookTimer > 15)
            {
                hookTimer = SDL_GetTicks();
                if(hookGoRight)
                {
                    hookAngle += 2;
                    if(hookAngle >= 165.0) hookGoRight = false;
                }
                else
                {
                    hookAngle -= 2;
                    if(hookAngle <= 15.0) hookGoRight = true;
                }
            }
        }
        else
        {
            if(SDL_GetTicks() - objTimer > 120 && hookBack)
                {
                    objTimer = SDL_GetTicks();
                    id_O++;
                    if(id_O > 23) id_O = 0;
                }
            else if(!hookBack) id_O = 8;

            if(SDL_GetTicks() - lineTimer > 15)
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
            if(!hookBack && hookDown && Mix_Playing(0) == 0) Mix_PlayChannel(0, lastart, 0);
            if(lineLen <= 1.0)
            {
                hookDown = hookBack = false;
                userGrade += resProp.score;
                resProp.setId(-1);
                if(catchedRes != -1) {
                        resTexture[catchedRes].Free();
                        Mix_PlayChannel(0, score, 0);
                }
                catchedRes = -1;
            }
            if(lineLen >= 650.0) hookBack = true;
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
        gradeText.SetColor(TextObject::BLACK_TEXT);
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
        duongray.Render(g_screen, NULL);
        cot1.Render(g_screen, NULL);
        cot2.Render(g_screen, NULL);
        obj[id_O].Render(g_screen, NULL);
        levelText.RenderText(g_screen, 1050, 25);
        timeText.RenderText(g_screen, 1020, 80);
        goalText.RenderText(g_screen, 200, 80);
        gradeText.RenderText(g_screen, 200, 30);
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
					if(level->reses[i].id == ID_BGOLD) Mix_PlayChannel(1, laregeGold, 0);
					if(level->reses[i].id == ID_BSTONE) Mix_PlayChannel(1, lowValue, 0);
					if(level->reses[i].id == ID_DIAMOND) Mix_PlayChannel(1, kimCuong, 0);
					if(Mix_Playing(1) == 0) Mix_PlayChannel(1, norValue, 0);
					hookBack = true;
					printf("Catched!\n");
					break;
                }
            }
        }
    }

    for(int i = 0; i < level->totalRes; i++) resTexture[i].Free();
    for(int i = 0; i < 24; i++) obj[i].Free();
    line.Free();
    hook.Free();
    gameBg.Free();
    duongray.Free();
    cot1.Free();
    cot2.Free();
    timeText.Free();
    levelText.Free();
    Mix_FreeChunk(lastart);
    Mix_FreeChunk(lowValue);
    Mix_FreeChunk(kimCuong);
    Mix_FreeChunk(laregeGold);
    Mix_FreeChunk(lastart);
    Mix_FreeChunk(select);
    Mix_FreeChunk(score);
    return userGrade;
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
            gameOver(win, lvlNum - 1);
            break;
        }
        setGoal(lvl->levelGoal);
        if(gameMain(lvl) <= lvl->levelGoal)
        {
            gameOver(win, lvlNum);
            break;
        }
        else {
            gameOver(true, lvlNum);
        }
        destroyLevel(lvl);
    }
}
int main(int argc, char* argv[]){
    initSDL();

    SDL_Surface* icon = IMG_Load("Textures/icon.png");
    SDL_SetWindowIcon(g_window, icon);
    if(!readyAnimation()) return 0;
    else startGame();

    SDL_FreeSurface(icon);
    quitSDL();
    return 0;
}


