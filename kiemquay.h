#ifndef KIEMQUAY_
#define KIEMQUAY_

#include "commonfunction.h"
using namespace std;
class Sword
{
public:
    Sword();
    ~Sword();
    void SetRect( const int &x, const int &y)
    {
        rect_kiem.x = x;
        rect_kiem.y = y;
    }
    SDL_Rect GetRect() const { return rect_kiem;  }
    SDL_Texture* GetTexture() const { return Texture_kiem; }
    void free();// giai phong
    virtual bool Loadkiem( const string& path, SDL_Renderer*screen);//tai anh
    void render_kiem(SDL_Renderer* des, int x,int y, SDL_Rect*clip = nullptr,
                SDL_Point*center = nullptr,
                SDL_RendererFlip flip = SDL_FLIP_NONE);
    void change_gocquay( double kaka) {gocquay += kaka ;}
    double getgocquay() {return gocquay ;}

private:

    SDL_Texture* Texture_kiem;
    SDL_Rect rect_kiem;
    double gocquay;
};


#endif // KIEMQUAY_


