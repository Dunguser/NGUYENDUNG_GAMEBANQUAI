
#include "ThreatsObject.h"
#include <SDL_image.h>


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
    come_back_time_=0;

    gioihan_trai=0;
    gioihan_phai=0;
    trang_thai_qui.sang_trai=0;

}

ThreatsObject::~ThreatsObject()
{

}

bool ThreatsObject:: LoadImage(const string& path, SDL_Renderer* screen)
{
    bool ret=BaseObject::LoadImage(path,screen);
    if(ret)
    {
        width_frame_=rect_.w/THREATS_FRAME_NUM;
        height_frame_=rect_.h;
    }
    return ret;
}

void ThreatsObject::set_clips()// tao clip chuyen dong
{
    if(width_frame_>0&&height_frame_>0)
    {
        for(int i=0; i<THREATS_FRAME_NUM; i++)
        {
            frame_clips[i].w=width_frame_;
            frame_clips[i].h=height_frame_;
            frame_clips[i].y=0;
            frame_clips[i].x=i*width_frame_;
        }
    }
}

void ThreatsObject::ShowQui(SDL_Renderer*des)// in ra man hinh
{
    if(come_back_time_==0)
    {
        rect_.x=x_qui_pos-map_x_qui;
        rect_.y=y_qui_pos-map_y_qui;

        frame_++;// tang lien tuc

        if(frame_>=THREATS_FRAME_NUM)
        {
            frame_=0;
        }

        SDL_Rect*currentClip=&frame_clips[frame_];
        SDL_Rect quad = {rect_.x, rect_.y, width_frame_, height_frame_};
        SDL_RenderCopy( des, mTexture, currentClip, &quad);
    }
}


void ThreatsObject:: DICHUYEN_QUI( MAP& map_data )
// xu li di chuyen cho qui
{
    if(come_back_time_==0)
    {
        x_change=0;
        y_change+=0.8;// toc do roi cua qui

        if( y_change >=30 )
        {
            y_change=30;
        }

        if(trang_thai_qui.sang_trai==1)
        {
            x_change-= TOC_DO_QUI;
        }
        else if(trang_thai_qui.sang_phai==1)
        {
            x_change+= TOC_DO_QUI;
        }
        checktomap_qui( map_data );
    }
    else if(come_back_time_>0)
    {
        come_back_time_--;
        if(come_back_time_==0)
        {
            khoitaoqui();
        }
    }
}

void ThreatsObject::khoitaoqui()
{
    x_change=0;
    y_change=0;
    x_qui_pos-=256;
    y_qui_pos=0;
    gioihan_trai-=256;
    gioihan_phai-=256;
    trang_thai_qui.sang_trai=1;
}

//kiem tra va cham voi ban do
void ThreatsObject::checktomap_qui( MAP&map_data )
{
    int x1=0,x2=0; // gioi han kiem tra ngang // theo o vuong
    int y1=0,y2=0;                     //doc

    // kiem tra theo chieu ngang--------------------------

    // chieu cao nho nhat // chieu cao frame hay chieu cao o=64
    int height_min=min(height_frame_,TILE_SIZE);

    // tim o hien tai dang dung la oo bao nhieu
    x1=(x_qui_pos+x_change)/TILE_SIZE;
    int sai_so_can_co=1;
    x2=(x_qui_pos+x_change+width_frame_ -sai_so_can_co)/TILE_SIZE;

    y1=(y_qui_pos+y_change)/TILE_SIZE;
    y2=(y_qui_pos+y_change+height_min-sai_so_can_co)/TILE_SIZE;

    //kiem tra theo x1,x2,y1,y2 co o trong ban do hay ko
    if( x1>=0 && x2<MAX_MAP_X && y1>=0 && y2<MAX_MAP_Y ) // nhan vat o trong ban do
    {
        if(x_change>0)//di sang phai
        {
            int val1=map_data.tile[y1][x2];
            int val2=map_data.tile[y2][x2];

            if((val1!=O_TRONG&&val1!=4)||(val2!=O_TRONG&&val2!=4))// kiem tra xem ban do cho do co trong hay ko
            {
                x_qui_pos=x2*TILE_SIZE-width_frame_-sai_so_can_co;//khi va cham thi phai tra lai vi tri cu
                // x_change=0;//ko the tang dc nua//ko cho di chuyen nua
                va_bando=cham_phai;
            }
        }
        else if(x_change<0)//sang trai
        {
            int val1=map_data.tile[y1][x1];
            int val2=map_data.tile[y2][x1];

            if((val1!=O_TRONG&&val1!=4)||(val2!=O_TRONG&&val2!=4))
            {
                x_qui_pos=(x1+sai_so_can_co)*TILE_SIZE;
                //x_change=0;
                va_bando=cham_trai;
            }
        }
    }

    // kiem tra theo chieu doc--------------------------------
    int width_min=min(width_frame_,TILE_SIZE);

    x1=( x_qui_pos + 27 )/TILE_SIZE;
    x2=( x_qui_pos + width_min - 27)/TILE_SIZE;

    y1=(y_qui_pos+y_change)/TILE_SIZE;
    y2=(y_qui_pos+y_change+height_frame_-sai_so_can_co)/TILE_SIZE;

    if( x1>=0 && x2 < MAX_MAP_X && y1>=0 && y2 < MAX_MAP_Y)
    {
        if(y_change>0)// di xuong //roi xuong
        {
            int val1 = map_data.tile[y2][x1];
            int val2 = map_data.tile[y2][x2];

            if((val1!=O_TRONG&&val1!=4)||(val2!=O_TRONG&&val2!=4))
            {
                y_qui_pos=y2*TILE_SIZE-height_frame_-sai_so_can_co;
                y_change=0;
                tren_mat_dat=true;
            }
        }
        else if(y_change<0)// nhay len
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y1][x2];

            if((val1!=O_TRONG&&val1!=4)||(val2!=O_TRONG&&val2!=4))
            {
                y_qui_pos=(y1+sai_so_can_co)*TILE_SIZE;
                y_change=0;
            }
        }
    }

    // neu ko xay ra va cham voi cai nao
    x_qui_pos+=x_change;
    y_qui_pos+=y_change;

    if(x_qui_pos<0)
    {
        x_qui_pos=0;
    }
    if(x_qui_pos+width_frame_>map_data.max_x_)
    {
        x_qui_pos=map_data.max_x_-width_frame_-sai_so_can_co;
    }


    if(y_qui_pos >= map_data.max_y_)
    {
        come_back_time_=10;
    }
}


void ThreatsObject::Di_chuyen_trong_pham_vi( SDL_Renderer* screen, MAP&map_data )
{
    if(tren_mat_dat==true)
    {
        if(x_qui_pos > gioihan_phai||va_bando==cham_phai)
        {
            trang_thai_qui.sang_phai=0;
            trang_thai_qui.sang_trai=1;
            set_trang_thai_trai(1);
            LoadImage("IMG/quai_di_trai.png",screen);
        }
        if(x_qui_pos < gioihan_trai||va_bando==cham_trai)
        {
            trang_thai_qui.sang_phai=1;
            trang_thai_qui.sang_trai=0;
            set_trang_thai_trai(0);
            LoadImage("IMG/quai_di_phai.png",screen);
        }
    }
    else
    {
        if(trang_thai_qui.sang_trai == 1)
        {

        }
    }
}






//int ThreatsObject::quay_dau_lam_bo( MAP& map_data )
//{
//    int x1=0,x2=0; // gioi han kiem tra ngang // theo o vuong
//    int y1=0,y2=0;                     //doc
//
//    // kiem tra theo chieu ngang--------------------------
//
//    // chieu cao nho nhat // chieu cao frame hay chieu cao o=64
//    int height_min=min(height_frame_,TILE_SIZE);
//
//    // tim o hien tai dang dung la oo bao nhieu
//    x1=(x_qui_pos+x_change)/TILE_SIZE;
//    int sai_so_can_co=1;
//    x2=(x_qui_pos+x_change+width_frame_ -sai_so_can_co)/TILE_SIZE;
//
//    y1=(y_qui_pos+y_change)/TILE_SIZE;
//    y2=(y_qui_pos+y_change+height_min-sai_so_can_co)/TILE_SIZE;
//
//    //kiem tra theo x1,x2,y1,y2 co o trong ban do hay ko
//    if( x1>=0 && x2<MAX_MAP_X && y1>=0 && y2<MAX_MAP_Y ) // nhan vat o trong ban do
//    {
//        if(x_change>0)//di sang phai
//        {
//            int val1=map_data.tile[y1][x2];
//            int val2=map_data.tile[y2][x2];
//
//            if((val1!=O_TRONG&&val1!=4)||(val2!=O_TRONG&&val2!=4))
//            {
//                x_qui_pos=x2*TILE_SIZE-width_frame_-sai_so_can_co;//khi va cham thi phai tra lai vi tri cu
//                x_change=0;
//                return true;
//            }
//        }
//        else if( x_change < 0)//sang trai
//        {
//            int val1=map_data.tile[y1][x1];
//            int val2=map_data.tile[y2][x1];
//
//            if((val1!=O_TRONG&&val1!=4)||(val2!=O_TRONG&&val2!=4))
//            {
//                x_qui_pos=(x1+sai_so_can_co)*TILE_SIZE;
//                x_change=0;
//                va_bando=cham_trai;
//            }
//        }
//    }
//    return va_bando;
//
//}
