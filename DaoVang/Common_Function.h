
#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <iostream>
#include <windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

/// Screen
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const std::string WINDOW_TITLE = "Đào vàng";
const int SCREEN_BPP = 32;

void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal);
void quitSDL();
void waitUntilKeyPressed();
void initSDL();

#endif // COMMON_FUNCTION_H_
