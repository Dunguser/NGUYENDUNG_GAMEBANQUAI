
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

    // chon vi tri tren man hinh de in  mTexture o protect// toa do(x,y)
    void SetRect( const int &x, const int &y)
    {
        rect_.x = x;
        rect_.y = y;
    }
    SDL_Rect GetRect() const { return rect_;  }// lay ra kich thuoc cua rect_
    SDL_Texture* GetTexture() const { return mTexture; }

    void free();// giai phong
    virtual bool LoadImage( const string& path, SDL_Renderer* screen);//tai anh
    void Render ( SDL_Renderer* des,SDL_Rect* clip = nullptr );// in anh ra o dau, kich thuoc bao nhieu

protected:

    SDL_Texture* mTexture;
    SDL_Rect rect_;

};
#endif // BASE_OBJECT_H_
