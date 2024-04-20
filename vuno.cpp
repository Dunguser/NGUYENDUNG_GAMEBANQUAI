
#include "vuno.h"

VUNO:: VUNO()
{
    frame_height = 0;
    frame_width = 0;
    frame_ = 0;
}
VUNO :: ~VUNO()
{

}

bool VUNO:: LoadImage (const string& path, SDL_Renderer* screen)
{
    bool ret = BaseObject :: LoadImage (path , screen );
    if(ret)
    {
        frame_width = rect_.w / num_frame_no;
        frame_height = rect_.h;
    }
    return ret;
}

void VUNO::set_clip()
{
    if( frame_width>0 && frame_height>0)
    {
        for(int i=0; i<num_frame_no; i++)
        {
            frame_clip_[i].w = frame_width;
            frame_clip_[i].h = frame_height;
            frame_clip_[i].y = 0;
            frame_clip_[i].x = i*frame_width;
        }
    }
}

void VUNO :: show(SDL_Renderer* screen)
{
    SDL_Rect* hientai = &frame_clip_[frame_];
    SDL_Rect quad = { rect_.x ,rect_.y ,frame_width , frame_height };
    if(hientai != nullptr)
    {
        quad.w = hientai->w;
        quad.h = hientai->h;
    }
    SDL_RenderCopy( screen, mTexture , hientai, &quad);
}





