#include "MainObject.h"

MainObject::MainObject()
{
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = WIDTH_MAIN_OBJECT;
    rect_.h = HEIGHT_MAIN_OBJECT;
    x_val_ = 0;
    y_val_ = 0;
}

MainObject::~MainObject()
{
    ;
}

void MainObject::HandleInputAction(SDL_Event events)
{
    //vaof
}

void MainObject::HandleMove()
{
    // di chuyen
}
