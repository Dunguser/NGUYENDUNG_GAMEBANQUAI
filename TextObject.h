
#ifndef TEXT_OBJECT_
#define TEXT_OBJECT_

#include "commonfunction.h"
#include <bits/stdc++.h>
#include <SDL_ttf.h>

using namespace std;

class TextObject
{
public:
    TextObject();
    ~TextObject();

    enum TexColor  // dinh nghia 1 so mau co ban
    {
        RED_TEXT ,
        WHITE_TEXT,
        BLACK_TEXT,
    };

    bool LoadFromRenderText (TTF_Font *font, SDL_Renderer* screen);
    void Free();

    void setcolor( Uint8 red, Uint8 green, Uint8 blue);
    void setcolor(int type);

    void RenderText (SDL_Renderer* screen, int xp , int yp,
                      SDL_Rect* clip = nullptr, double angle = 0.0 ,
                      SDL_Point* center =nullptr,
                      SDL_RendererFlip flip =SDL_FLIP_NONE);

    int get_width() const { return width_; }
    int get_height() const { return height_ ;}

    void SetText ( const string& text ) { noidung = text ;}
    string gettext() const { return noidung; }

    SDL_Rect text(int x,int y);

private:
    string noidung;
    SDL_Color text_color_;

    SDL_Texture * texture_;

    int width_;
    int height_;

};





#endif // TEXT_OBJECT_
