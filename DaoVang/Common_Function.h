
#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "Data.h"
#include "BaseObject.h"
#include "TextObject.h"
#include "resProperties.h"

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

/// Screen

const std::string WINDOW_TITLE = "Đào vàng";
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int SCREEN_BPP = 32;
const int FPS = 60;
const double PRE_FRAME_TICKS = (double)1000 / FPS;


enum resImgId
{
	ID_STARTBG = 0,
	ID_LIGHT = 1,
	ID_STARTBUTTON = 2,
	ID_SSTONE = 3,
	ID_BSTONE = 4,
	ID_DIAMOND = 5,
	ID_BGOLD = 6,
	ID_BAG = 7,
	ID_GOALBG = 8,
	ID_GAMEBG = 9,
	ID_HOOK = 10,
	ID_LINE = 11,
	ID_SGOLD = 12
};

enum resSoundId
{
	ID_MOUSEIN = 0,
	ID_DIG = 1,
	ID_EXPLOSIVE = 2,
	ID_HIGHVAL = 3,
	ID_LOWVAL = 4,
	ID_NORVAL = 5,
	ID_PULL = 6,
	ID_SCORE1 = 7,
	ID_SCORE2 = 8
};

struct resPos
{
	int id;
	SDL_Point position;
};

struct levelInfo {
	int level;
	int levelGoal;
	int totalRes;
	struct resPos* reses;
};
#endif // COMMON_FUNCTION_H_
