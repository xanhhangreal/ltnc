#include "Common_Function.h"
#include "BaseObject.h"
#include "SDL_utils.h"


using namespace std;

void PlayGame(){

}
void Pic_Event(){
    while (true) {
        if ( SDL_WaitEvent(&g_event) == 0 ) SDL_Delay(100);
        else if (g_event.type == SDL_QUIT) break;
        else if (g_event.type == SDL_KEYDOWN){
            cerr << "_" << SDL_GetKeyName(g_event.key.keysym.sym) << "_\n";
            switch (g_event.key.keysym.sym){
                case SDLK_SPACE:
                case SDLK_DOWN: {
                    cerr << "Keo\n";
                    /// xử lí móc câu kéo xuống
                } break;
            }
        }
    }
}
void Solve(){

//     Your drawing code here
//     use SDL_RenderPresent(renderer) to show it
    PlayGame();
    Pic_Event();
    waitUntilKeyPressed();
}
int main(int argc, char* argv[]){
    initSDL();
    Solve();
    quitSDL();
    return 0;
}


