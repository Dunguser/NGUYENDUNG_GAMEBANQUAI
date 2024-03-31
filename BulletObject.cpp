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

//void BulletObject::pham_vi_dan_bay(const int&x_gioihan,const int &y_gioihan,int dotang_x,int dotang_y )
void BulletObject::pham_vi_dan_bay(const int&x_gioihan,const int &y_gioihan,int dotang_x,int dotang_y,MAP&map_data)
//xet gioi han hien thi vien dan bay
{
    x_biendoi=0;
    y_biendoi=0;
    if(huong_cua_dan==ban_dan_phai)
    {

        x_biendoi+=TOCDO_DAN;
        //x_vitri_dan+=x_biendoi;
        rect_.x+=x_biendoi;

        if(rect_.x>x_gioihan+dotang_x)
        {
            trong_man_hinh=false;
        }
    }
    else if(huong_cua_dan==ban_dan_trai)
    {

        x_biendoi-=TOCDO_DAN;
        //x_vitri_dan-=x_biendoi;
        rect_.x+=x_biendoi;

        if(rect_.x<0)
        {
            trong_man_hinh=false;
        }
        if(rect_.x-dotang_x-x_gioihan>0)
        {
            trong_man_hinh=false;
        }
    }
    else if(huong_cua_dan==ban_duoi_trai)
    {
        x_biendoi-=TOCDO_DAN;
        y_biendoi+=TOCDO_DAN;
        //x_vitri_dan-=x_biendoi;
        //y_vitri_dan+=y_biendoi;
        rect_.x+=x_biendoi;
        rect_.y+=y_biendoi;

        if(rect_.x<0)trong_man_hinh=false;
        double kk=sqrt((rect_.x-dotang_x)*(rect_.x-dotang_x)+(rect_.y-dotang_y)*(rect_.y-dotang_y));
        if(kk>650+dotang_x)
        {
            trong_man_hinh=false;
        }
    }
    else if(huong_cua_dan==ban_duoi_phai)
    {
        x_biendoi+=TOCDO_DAN;
        y_biendoi+=TOCDO_DAN;
        //x_vitri_dan+=x_biendoi;
        //y_vitri_dan+=y_biendoi;

        rect_.x+=x_biendoi;
        rect_.y+=y_biendoi;
        double kk=sqrt((rect_.x-dotang_x)*(rect_.x-dotang_x)+(rect_.y-dotang_y)*(rect_.y-dotang_y));
        if(kk>650+dotang_x)
        {
            trong_man_hinh=false;
        }
    }
    //check_va_cham_map(map_data);
//
//    if(check_va_cham_map(map_data)==true)
//    {
//        trong_man_hinh=0;
//    }
}


bool BulletObject::check_va_cham_map(MAP&map_data)
// kien tra va cham voi map
{

    int x1=0,x2=0,y1=0,y2=0;
    int saiso=1;

    cout<<"x bien doi doi == "<<x_biendoi<<endl;
    // theo chieu ngang
    int height_min=min(height_frame_dan,TILE_SIZE);
    x1=(x_vitri_dan+x_biendoi)/TILE_SIZE;
    x2=(x_vitri_dan+x_biendoi+width_frame_dan-saiso)/TILE_SIZE;

    y1=(y_vitri_dan)/TILE_SIZE;
    y2=(y_vitri_dan+height_min-saiso)/TILE_SIZE;


    if(x1>=0&&x2<MAX_MAP_X&&y1>=0&&y2<MAX_MAP_Y)
    {
        if(x_biendoi>0)//di sang phai
        {
            if(map_data.tile[y1][x2]!=0||map_data.tile[y2][x2]!=0)
            {
                cout<<"y1= "<<y1<<" ; "<<" y2= "<<y2<<endl;
                x_vitri_dan=x2*TILE_SIZE-width_frame_dan-saiso;

                return 1;
            }
        }
        else if(x_biendoi<0)
        {
            if(map_data.tile[y1][x1]!=0||map_data.tile[y2][x1]!=0)
            {
                x_vitri_dan=(x1+saiso)*TILE_SIZE;
                return 1;
            }
        }
    }

    // theo chieu doc
    int width_min=min(width_frame_dan,TILE_SIZE);
    x1=x_vitri_dan/TILE_SIZE;
    x2=(x_vitri_dan+width_min-saiso)/TILE_SIZE;

    y1=(y_vitri_dan+y_biendoi)/TILE_SIZE;
    y2=(y_vitri_dan+y_biendoi+height_frame_dan-saiso)/TILE_SIZE;

    if(x1>=0&&x2<MAX_MAP_X&&y1>=0&&y2<MAX_MAP_Y)
    {
        if(y_biendoi>0)
        {
            if(map_data.tile[y2][x1]!=O_TRONG||map_data.tile[y2][x2]!=O_TRONG)
            {
                y_vitri_dan=y2*TILE_SIZE-height_frame_dan-saiso;
                return 1;
            }
        }
        else if(y_biendoi<0)
        {
            if(map_data.tile[y1][x1]!=O_TRONG||map_data.tile[y1][x2]!=O_TRONG)
            {
                y_vitri_dan=(y1+saiso)*TILE_SIZE;
                return 1;
            }
        }
    }
    x_vitri_dan+=x_biendoi;
    y_vitri_dan+=y_biendoi;

    rect_.x+=x_biendoi;
    rect_.y+=y_biendoi;

    if(x_vitri_dan<0)
    {
        return 1;
    }

    return 0;
}



bool BulletObject::TAI_ANH_DAN(SDL_Renderer*des)
// tai cac loai dan
{
    bool ret=false;
    if(loai_dan_==DAN1_TRAI)
    {
        ret=LoadImage("IMG/DAN1_TRAI.png",des);
    }
    else if(loai_dan_==DAN1_PHAI)
    {
        ret=LoadImage("IMG/DAN1_PHAI.png",des);
    }
    return ret;
}





