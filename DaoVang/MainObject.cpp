
#include "MainObject.h"

MainObject::MainObject()
{
    x_val_ = 0;
    y_val_ = 0;

    x_pos_ = 0;
    y_pos_ = 0;

    size_Object = 0;
    for(int i = 0; i <= 19; i++)
    {
        object_[i] = NULL;
        rect_Object_[i].x = 0;
        rect_Object_[i].y = 0;
        rect_Object_[i].w = 0;
        rect_Object_[i].h = 0;
    }

    status_ = -1;
}

MainObject::~MainObject()
{
    for(int i = 0; i <= 19; i++)
        if(object_[i] != NULL)
        {
            delete object_[i];
            object_[i] = NULL;
        }
}

void MainObject::LoadImg(std::string path, SDL_Renderer* screen)
{
    BaseObject::LoadImg(path, screen);
    object_[size_Object++] =  p_object_;
    rect_Object_[size_Object].w = rect_.w;
    rect_Object_[size_Object].h = rect_.h;
}
void MainObject::Show(SDL_Renderer* des)
{
    if(status_ == -1) /// Chưa làm gì
    {
        LoadImg("Textures/img_obj1.png", des);
    }
    else if(status_ == 0) /// Thả câu
    {
        LoadImg("Textures/img_obj2.png", des);
        LoadImg("Text ures/img_obj3.png", des);
        LoadImg("Textures/img_obj4.png", des);
        LoadImg("Textures/img_obj5.png", des);
        LoadImg("Textures/img_obj6.png", des);
        LoadImg("Textures/img_obj7.png", des);
        LoadImg("Textures/img_obj8.png", des);
        LoadImg("Textures/img_obj9.png", des);
        LoadImg("Textures/img_obj10.png", des);
        LoadImg("Textures/img_obj11.png", des);
        LoadImg("Textures/img_obj12.png", des);
    }
    else                    /// Kéo câu
    {
        LoadImg("Textures/img_obj13.png", des);
        LoadImg("Textures/img_obj14.png", des);
        LoadImg("Textures/img_obj15.png", des);
        LoadImg("Textures/img_obj16.png", des);
        LoadImg("Textures/img_obj17.png", des);
        LoadImg("Textures/img_obj18.png", des);
        LoadImg("Textures/img_obj19.png", des);
        LoadImg("Textures/img_obj20.png", des);
        LoadImg("Textures/img_obj21.png", des);
        LoadImg("Textures/img_obj22.png", des);
        LoadImg("Textures/img_obj23.png", des);
        LoadImg("Textures/img_obj24.png", des);
    }
    rect_.x = x_pos_;
    rect_.y = y_pos_;
    for(int i = 0; i < size_Object; i++)
    {
        SDL_Rect renderQuad = {rect_.x, rect_.y, rect_Object_[i].w, rect_Object_[i].h};
        SDL_RenderCopy(des, object_[i], NULL, &renderQuad);

        SDL_RenderPresent(des);
        SDL_Delay(100);
    }
    size_Object = 0;
}

void MainObject::HandleInputAction(SDL_Event events, SDL_Renderer* screen)
{
    if(events.type == SDL_KEYDOWN)
    {
        switch (events.key.keysym.sym)
        {
            case SDLK_DOWN:
            case SDLK_SPACE:
                {
                    status_ = 0;
                }
                break;
        }
    }
    else if(events.type == SDL_KEYUP)
    {
        switch (events.key.keysym.sym)
        {
            case SDLK_DOWN:
            case SDLK_SPACE:
                {
                    status_ = -1;
                }
                break;
        }
    }
}
