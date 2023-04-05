#include "Common_Function.h"
#include "BaseObject.h"
#include "SDL_utils.h"
#include "LuoiCau.h"
#include "MainObject.h"

using namespace std;

void Solve()
{

    //PlayGame();
    //Pic_Event();
    MainObject p_player;
    p_player.LoadImg("Textures/img_obj1.png", g_screen);

    bool is_quit = false;
    while(!is_quit)
    {
        while(SDL_PollEvent(&g_event) != 0)
        {
            if(g_event.type == SDL_QUIT)
            {
                is_quit = true;
                break;
            }
            p_player.HandleInputAction(g_event, g_screen);
        }
        SDL_SetRenderDrawColor(g_screen, 0, 0, 0, 0);
        SDL_RenderClear(g_screen);

        p_player.Show(g_screen);

        SDL_RenderPresent(g_screen);
    }
}
int main(int argc, char* argv[]){
    initSDL();
    Solve();
    quitSDL();
    return 0;
}


