#include "BaseObject.h"
using namespace std;

BaseObject::BaseObject()
{
    mTexture=nullptr;
    rect_.x=0;
    rect_.y=0;
    rect_.h=0;
    rect_.w=0;
}
BaseObject::~BaseObject()
{
    free();
}

bool BaseObject :: LoadImage( const string& path, SDL_Renderer* screen )
{
    free();
    SDL_Texture* cuoicung = nullptr;
    SDL_Surface* kaka = IMG_Load ( path.c_str() );
    if( kaka == nullptr )
    {
        cout<<"failed to load image " << path.c_str()<<"  "<< IMG_GetError() << endl;
        return false;
    }

    const Uint32 colorKey = SDL_MapRGB ( kaka->format, 255, 255, 255);
    SDL_SetColorKey ( kaka, SDL_TRUE, colorKey );
    cuoicung = SDL_CreateTextureFromSurface (screen,kaka);

    if ( cuoicung == nullptr )
    {
        cout <<"failed to create Texture from surface (baseobject) "<< path.c_str()<<"  "<<SDL_GetError()<< endl;
        SDL_FreeSurface(kaka);
        return false;
    }

    rect_.w = kaka->w;
    rect_.h = kaka->h;

    SDL_FreeSurface(kaka);
    mTexture = cuoicung;
    return mTexture != nullptr;
}
void BaseObject::Render(SDL_Renderer* des,SDL_Rect* clip)// in anh ra o dau, kich thuoc bao nhieu
{
    SDL_Rect quad = {rect_.x,rect_.y,rect_.w,rect_.h};
    //assert(mTexture != nullptr);
    SDL_RenderCopy( des, mTexture ,clip,&quad);
}

void BaseObject::free()
{
    if(mTexture != nullptr)
    {
        SDL_DestroyTexture ( mTexture );
        mTexture = nullptr;
        rect_.x=0;
        rect_.y=0;
        rect_.w=0;
        rect_.h=0;
        //cout<<"free"<<endl;
    }
}
