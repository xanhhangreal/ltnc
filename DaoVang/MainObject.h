#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_H

#include "Common_Function.h"
#include "BaseObject.h"

class MainObject : public BaseObject
{
public:
    MainObject();
    ~MainObject();

    virtual void LoadImg(std::string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
    //void set_clips();
private:
    double x_val_;
    double y_val_;

    double x_pos_;
    double y_pos_;

    SDL_Texture* object_[20];
    SDL_Rect rect_Object_[20];
    int size_Object;

    int status_;
};
#endif // MAIN_OBJECT_H_
