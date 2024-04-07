#include "TextObject.h"

using namespace std;

TextObject::TextObject()
{
    text_color_.r = 255;
    text_color_.g = 255;
    text_color_.b = 255;

    texture_ = nullptr;

}
TextObject:: ~TextObject()
{

}

bool TextObject :: LoadFromRenderText (TTF_Font * font , SDL_Renderer* screen)
{
    SDL_Surface * text_surface = TTF_RenderText_Solid(font, noidung.c_str(), text_color_ );
    if(text_surface)
    {
        texture_ = SDL_CreateTextureFromSurface ( screen , text_surface );
        width_ = text_surface->w;
        height_ = text_surface->h;
    }
    else cout<<"failed font "<<endl;
    return 0;
    SDL_FreeSurface(text_surface);
    return texture_ !=nullptr;
}

void TextObject :: Free()
{
    if(texture_ != nullptr )
    {
        SDL_DestroyTexture ( texture_ );
        texture_ = nullptr;
    }
}

void TextObject :: setcolor(Uint8 red, Uint8 green, Uint8 blue)
{
    text_color_.r = red;
    text_color_.b = blue;
    text_color_.g = green;
}

void TextObject :: setcolor(int type)
{
    if( type == RED_TEXT )
    {
        SDL_Color color = { 255, 0, 0};
        text_color_ = color ;
    }
    else if( type == WHITE_TEXT)
    {
        SDL_Color color = { 255, 255, 255};
        text_color_ = color ;
    }
    else if(type == BLACK_TEXT )
    {
        SDL_Color color = { 0 , 0, 0};
        text_color_ = color ;
    }
}

void TextObject :: RenderText (SDL_Renderer* screen, int xp , int yp,
                                  SDL_Rect* clip , double angle ,
                                  SDL_Point* center , SDL_RendererFlip flip )
{
    SDL_Rect quad = { xp, yp , width_ , height_ };
    if(clip != nullptr )
    {
        quad.w = clip->w;
        quad.h = clip->h;
    }
    SDL_RenderCopyEx( screen, texture_ , clip, &quad ,angle , center , flip);
}









