
#include "kiemquay.h"

using namespace std;

Sword::Sword()
{
    Texture_kiem = nullptr;
    rect_kiem.h= 0;
    rect_kiem.w= 0;
    rect_kiem.x= 0;
    rect_kiem.y= 0;
    gocquay =0.0;
}
Sword::~Sword()
{
    free();
}

void Sword::free()
{
    if(Texture_kiem != nullptr)
    {
        SDL_DestroyTexture(Texture_kiem);
        Texture_kiem = nullptr;
        rect_kiem.h= 0;
        rect_kiem.w= 0;
        rect_kiem.x= 0;
        rect_kiem.y= 0;
    }
}
bool Sword::Loadkiem( const string& path, SDL_Renderer*screen)
{
    SDL_Texture* cuoicung = nullptr;
    SDL_Surface* kaka = IMG_Load (path.c_str());
    if(kaka == nullptr)
    {
        cout<<"failed to load image " << path.c_str()<<"  "<< IMG_GetError() << endl;
        return false;
    }

    const Uint32 colorKey = SDL_MapRGB ( kaka->format, 255, 255, 255);
    SDL_SetColorKey ( kaka, SDL_TRUE, colorKey );
    cuoicung = SDL_CreateTextureFromSurface (screen,kaka);
    if(cuoicung == nullptr)
    {
        cout <<"failed to create Texture from surface (baseobject) "<< path.c_str()<<"  "<<SDL_GetError()<< endl;
        SDL_FreeSurface(kaka);
        return false;
    }

    rect_kiem.w = kaka->w;
    rect_kiem.h = kaka->h;

    SDL_FreeSurface(kaka);
    Texture_kiem = cuoicung;
    return Texture_kiem != nullptr;
}
void Sword::render_kiem(SDL_Renderer* des, int x,int y, SDL_Rect*clip
                   ,SDL_Point* center, SDL_RendererFlip flip )
{
     SDL_Rect quad = { x, y, rect_kiem.w, rect_kiem.h };
     //cout<<rect_kiem.w << " "<<rect_kiem.h<<endl;;
     if(clip!=nullptr)
     {
         quad.w = clip->w;
         quad.h = clip->h;
     }
     SDL_RenderCopyEx(des, Texture_kiem, clip,&quad,gocquay,center,flip) ;
}
