#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "SDL_init.h" /// sửa tên, chiều dài và chiều rộng của cửa sổ
#include "SDL_utils.h" /// những câu lệnh cơ bản

using namespace std;

void Pic_Event(SDL_Renderer* renderer){
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) == 0 ) SDL_Delay(100);
        else if (e.type == SDL_QUIT) break;
        else if (e.type == SDL_KEYDOWN){
            cerr << "_" << SDL_GetKeyName(e.key.keysym.sym) << "_\n";
            switch (e.key.keysym.sym){
                case SDLK_SPACE:
                case SDLK_DOWN: {
                    cerr << "Keo\n";
                    /// xử lí móc câu kéo xuống
                } break;
            }
        }
    }
}
void Solve(SDL_Window* window, SDL_Renderer* renderer){

//     Your drawing code here
//     use SDL_RenderPresent(renderer) to show it
    PlayGame(window, renderer);
    Pic_Event(renderer);
    waitUntilKeyPressed();
}
int main(int argc, char* argv[]){
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL( window, renderer );
    Solve( window, renderer );
    quitSDL( window, renderer );
    return 0;
}



