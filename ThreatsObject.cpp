
#include "ThreatsObject.h"


using namespace std;

ThreatsObject::ThreatsObject()
{
    width_frame_=0;
    height_frame_=0;
    x_change=0.0;
    y_change=0.0;

    x_qui_pos=0.0;
    y_qui_pos=0.0;

    tren_mat_dat=false;

    frame_=0;

}

ThreatsObject::~ThreatsObject()
{

}
bool ThreatsObject:: LoadQuiImg(const string &path,SDL_Renderer*screen)
{
    bool ret=BaseObject::LoadImage(path,screen);
    if(ret)
    {
        width_frame_=rect_.w/6;
        height_frame_=rect_.h;
    }
    return ret;
}

void ThreatsObject::set_clips()
// tao clip chuyen dong
{
    if(width_frame_>0&&height_frame_>0)
    {
        for(int i=0; i<6; i++)
        {
            frame_clips[i].w=width_frame_;
            frame_clips[i].h=height_frame_;
            frame_clips[i].y=0;
            frame_clips[i].x=i*width_frame_;
        }
    }
}

void ThreatsObject::ShowQui(SDL_Renderer*des)
// in ra man hinh
{
    rect_.x=x_qui_pos-map_x_qui;
    rect_.y=y_qui_pos-map_y_qui;

    frame_++;// tang lien tuc
    if(frame_>=6)
    {
        frame_=0;
    }

    SDL_Rect*currentClip=&frame_clips[frame_];
    SDL_Rect quad={rect_.x,rect_.y,width_frame_,height_frame_};
    SDL_RenderCopy(des,mTexture,currentClip,&quad);


}


void ThreatsObject::DICHUYEN_QUI(MAP&gMap)
// xu li di chuyen cho qui
{
    x_change=0;
    y_change=0.8;// toc do roi cua qui

    if(y_change>=45)
    {
        y_change=45;
    }

}
void checktomap(MAP&gMap);//kiem tra va cham

