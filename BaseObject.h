
#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "commonfunction.h"
#include<bits/stdc++.h>

using namespace std;

// cai p_object_ trong bai cua thay la mTexture cua minh
class BaseObject
{
public:
    BaseObject();
    ~BaseObject();

    void SetRect( const int &x, const int &y)
    // chon vi tri tren man hinh de in  mTexture o protect// toa do(x,y)
    {
        rect_.x=x;
        rect_.y=y;
    }
    SDL_Rect GetRect() const // lay ra kich thuoc cua rect_
    {
        return rect_;
    }
    SDL_Texture* GetTexture() const
    {
        return mTexture;
    }
    void free();// giai phong
    virtual bool LoadImage( const string& path, SDL_Renderer*screen);//tai anh
    void Render(SDL_Renderer*des,SDL_Rect*clip=NULL);// in anh ra o dau, kich thuoc bao nhieu



protected:
    SDL_Texture* mTexture;
    SDL_Rect rect_;
};


#endif // BASE_OBJECT_H_
