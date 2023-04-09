#include "BaseObject.h"

BaseObject:: BaseObject()
{
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 0;
    rect_.h = 0;
    p_object_ = NULL;
}

BaseObject:: ~BaseObject()
{
    if(p_object_ != NULL)
    {
        delete p_object_;
        p_object_ = NULL;
    }
}

void BaseObject::LoadImg(const char* path, SDL_Renderer* screen)

{
    //std::cout << path << '/n';
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path );
    if( loadedSurface == NULL )
        std::cout << "Unable to load image " << path << " SDL_image Error: " << IMG_GetError() << '\n';
    else
    {
        newTexture = SDL_CreateTextureFromSurface( screen, loadedSurface );
        if( newTexture == NULL)
            std::cout << "Unable to create texture from " << path << " SDL Error: " << SDL_GetError() << '\n';
        else
        {
            rect_.w = loadedSurface->w;
            rect_.h = loadedSurface->h;
        }
        SDL_FreeSurface( loadedSurface );
    }
    p_object_ = newTexture;
}

void BaseObject::Render(SDL_Renderer* des, const SDL_Rect* clip)
{
    SDL_Rect renderquad = rect_;

    SDL_RenderCopy(des, p_object_, clip, &renderquad);
}

void BaseObject::Free()
{
    if(p_object_ != NULL)
    {
        SDL_DestroyTexture(p_object_);
        p_object_ = NULL;
        rect_.w = 0;
        rect_.h = 0;
    }
}
