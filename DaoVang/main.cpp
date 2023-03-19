#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "Dao Vang";

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);

void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal = false);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void waitUntilKeyPressed();
SDL_Texture* loadTexture(string path, SDL_Renderer* renderer);
/// Lấy đường dẫn file ảnh "path", renderer
void draw(SDL_Renderer* renderer, int x, int y){
    SDL_Rect rect;
    const int Rect_Size = 10;
    rect.x = x;
    rect.y = y;
    rect.h = Rect_Size;
    rect.w = Rect_Size;
    SDL_SetRenderDrawColor(renderer, 255, 255 , 0, 0);
    SDL_RenderDrawRect(renderer, &rect);
}
void Pic_Event(SDL_Renderer* renderer){
    int step = 5;
    int x = SCREEN_WIDTH/2;
    int y = SCREEN_HEIGHT/2;
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) == 0 ) SDL_Delay(100);
        else if (e.type == SDL_QUIT) break;
        else if (e.type == SDL_KEYDOWN){
            cerr << "_" << SDL_GetKeyName(e.key.keysym.sym) << "_" << endl;
            switch (e.key.keysym.sym){
                //case SDLK_SPACE:
                case SDLK_DOWN: y += step; break;
                case SDLK_UP: y -= step; break;
                case SDLK_LEFT: x -= step; break;
                case SDLK_RIGHT: x += step; break;
            }
        }
        draw(renderer, x, y);
        SDL_RenderPresent( renderer );
    }
}
int main(int argc, char* argv[]){
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL( window, renderer );

//     Your drawing code here
//     use SDL_RenderPresent(renderer) to show it
//    SDL_Texture* background = loadTexture( "ingame.png", renderer );
//    SDL_RenderCopy( renderer, background, NULL, NULL );
//    SDL_RenderPresent( renderer );
//    waitUntilKeyPressed();
    Pic_Event(renderer);
//    SDL_Texture* spongesBob = loadTexture( "ingame2.jpg", renderer );
//    SDL_RenderCopy( renderer, spongesBob, NULL, NULL );
//    SDL_RenderPresent( renderer );
//
    waitUntilKeyPressed();

    quitSDL( window, renderer );
    return 0;
}

SDL_Texture* loadTexture(string path, SDL_Renderer* renderer){
    SDL_Texture* newTexture = nullptr; /// Lưu lại địa chỉ của Texture được tạo ra
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == nullptr )
        cout << "Unable to load image " << path << " SDL_image Error: "
             << IMG_GetError() << endl;
    else {
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == nullptr )
            cout << "Unable to create texture from " << path << " SDL Error: "
                 << SDL_GetError() << endl;
        SDL_FreeSurface( loadedSurface );
    }
    return newTexture;
}
void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal){
    os << msg << " Error: " << SDL_GetError() << std:: endl;
    if(fatal){
        SDL_Quit();
        exit(1);
    }
}
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
       //SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);

    //Khi chạy trong môi trường bình thường (không chạy trong máy ảo)
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
    //Khi chạy ở máy ảo (ví dụ tại máy tính trong phòng thực hành ở trường)
    //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}
void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}
