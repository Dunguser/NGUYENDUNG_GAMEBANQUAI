#include "BulletObject.h"


using namespace std;
BulletObject::BulletObject()
{
    x_vitri_dan=0.0;
    y_vitri_dan=0.0;
    x_biendoi=0.0;
    y_biendoi=0.0;
    trong_man_hinh=false;
}
BulletObject::~BulletObject()
{

}
//xet gioi han hien thi vien dan bay
void BulletObject::pham_vi_dan_bay( const int& x_gioihan, const int& y_gioihan, int dotang_x, int dotang_y, MAP& map_data)
{
    x_biendoi=0;
    y_biendoi=0;
    if(huong_cua_dan == ban_dan_phai)
    {
        x_biendoi += TOCDO_DAN;
        rect_.x += x_biendoi;

        if(rect_.x > x_gioihan + dotang_x) trong_man_hinh = false ;
    }
    else if(huong_cua_dan == ban_dan_trai)
    {
        x_biendoi -= TOCDO_DAN;
        rect_.x += x_biendoi;

        if(rect_.x<0) trong_man_hinh = false;
        if( rect_.x - dotang_x - x_gioihan>0) trong_man_hinh = false;
    }
    else if(huong_cua_dan == ban_duoi_trai)
    {
        x_biendoi -= TOCDO_DAN;
        y_biendoi += TOCDO_DAN;

        rect_.x += x_biendoi;
        rect_.y += y_biendoi;

        if(rect_.x<0)  trong_man_hinh = false;
        double kk = sqrt((rect_.x-dotang_x)*(rect_.x-dotang_x)+(rect_.y-dotang_y)*(rect_.y-dotang_y));
        if( kk > 1000+ dotang_x ) trong_man_hinh=false;
    }
    else if(huong_cua_dan == ban_duoi_phai)
    {
        x_biendoi += TOCDO_DAN;
        y_biendoi += TOCDO_DAN;

        rect_.x += x_biendoi;
        rect_.y += y_biendoi;
        double kk=sqrt((rect_.x-dotang_x)*(rect_.x-dotang_x)+(rect_.y-dotang_y)*(rect_.y-dotang_y));
        if(kk > 1000+dotang_x)trong_man_hinh=false;
    }
}

bool BulletObject::TAI_ANH_DAN(SDL_Renderer*des)// tai cac loai dan
{
    bool ret=false;
    if(loai_dan_ == DAN1_TRAI) ret=LoadImage("IMG/DAN1_TRAI.png",des);
    else if(loai_dan_==DAN1_PHAI) ret=LoadImage("IMG/DAN1_PHAI.png",des);
    else if(loai_dan_ == DAN_QUI_PHAI) ret=LoadImage("IMG/dan_qui_phai.png",des);
    else if(loai_dan_  == DAN_QUI_TRAI)ret=LoadImage("IMG/dan_qui_trai.png",des);
    else if(loai_dan_ == DAN_QUI_THUONG) ret=LoadImage("IMG/dan_qui_thuong.png",des);

    return ret;
}

