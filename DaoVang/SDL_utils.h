#ifndef SDL_UTILS_H_
#define SDL_UTILS_H_H
#include "Common_Function.h"

void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal){
    os << msg << " Error: " << SDL_GetError() << std:: endl;
    if(fatal){
        SDL_Quit();
        exit(1);
    }
}
void quitSDL()
{
	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;

	SDL_DestroyWindow(g_window);
	g_window = NULL;

	Mix_CloseAudio();
	IMG_Quit();
	SDL_Quit();
}
void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT || e.type == SDL_MOUSEBUTTONDOWN) )
            return;
        SDL_Delay(100);
    }
}
void initSDL()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    g_window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
       //SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (g_window == nullptr) logSDLError(std::cout, "CreateWindow", true);

    //Khi chạy trong môi trường bình thường (không chạy trong máy ảo)
    g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
    //Khi chạy ở máy ảo (ví dụ tại máy tính trong phòng thực hành ở trường)
    //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

    if (g_screen == nullptr) logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);


	if(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) < 0) {
		printf("SDL image initialize failed! %s\n", IMG_GetError());
	}

	if(TTF_Init() == -1) {
		printf("SDL ttf initialize failed! %s\n", TTF_GetError());
	}

	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		printf("SDL_mixer could not initialize! %s\n", Mix_GetError());
	}
}


#endif // SDL_UTILS.H
