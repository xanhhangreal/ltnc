#ifndef TEXT_OBJECT_H_
#define TEXT_OBJECT_H_
#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_ttf.h>

using namespace std;

class TextObject
{
public:
    enum TextColor
    {
        RED_TEXT = 0,
        WHITE_TEXT = 1,
        BLACK_TEXT = 2
    };
    TextObject()
    {

    }
    ~TextObject()
    {

    }

    void SetText(const string& text) {str_val = text;}
    void SetColor(const int& type)
    {
        if(type == 0)
        {
            SDL_Color color = {255, 0, 0};
            text_color = color;
        }
        else if(type == 1)
        {
            SDL_Color color = {255, 255, 255};
            text_color = color;
        }
        else
        {
            SDL_Color color = {0, 0, 0};
            text_color = color;
        }
    }
    void CreateText(TTF_Font* font, SDL_Surface* des)
    {
//        des = TTF_RenderText_Solid(font, str_val.c_str(), text_color);
//        Show(des);
    }

private:
    string str_val;
    SDL_Color text_color;
};
#endif // TEXT_OBJECT_H_
