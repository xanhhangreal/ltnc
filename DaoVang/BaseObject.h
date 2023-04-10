
#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_
#include "Common_Function.h"

class BaseObject
{
public:
    BaseObject();
    ~BaseObject();

    void SetRect(const int& x, const int& y, const int& w, const int& h){rect_.x = x, rect_.y = y, rect_.w = w, rect_.h = h;}
    void SetRect(const int& x, const int& y){rect_.x = x, rect_.y = y;}
    SDL_Rect GetRect() const {return rect_;}
    SDL_Texture* GetObject() const {return p_object_;}

    void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
    void LoadImg(const char* path, SDL_Renderer* screen);
    void Free();
protected:
    SDL_Rect rect_;
    SDL_Texture* p_object_;
};

#endif // BASE_OBJECT_H_
