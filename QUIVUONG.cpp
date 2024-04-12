#include "QUIVUONG.h"
#include "BaseObject.h"
using namespace std;

QUIVUONG::QUIVUONG ()
{
    width_frame_=0;
    height_frame_ = 0;
    tren_mat_dat = false;

    x_boss_pos = 4500 ;//vi tri hien tai
    y_boss_pos = 2100 ;

    x_change = 0.0 ;// bien doi khi di chuyen
    y_change = 0.0 ;

    frame_ = 0 ;
    trang_thai_boss.sang_phai = 1;
}
QUIVUONG::~QUIVUONG()
{

}

bool QUIVUONG::LoadImg_boss( const string& path, SDL_Renderer* des)
{
    bool ret = BaseObject :: LoadImage(path,des);
    if(ret)
    {
        width_frame_ = rect_.w/SO_FRAME;
        height_frame_ = rect_.h;
    }
    return ret;
}

void QUIVUONG::set_clips()
{
    if(width_frame_>0 && height_frame_>0)
    {
        for(int i=0; i < SO_FRAME ; i++)
        {
            frame_clips[i].w = width_frame_;
            frame_clips[i].h = height_frame_;
            frame_clips[i].y = 0;
            frame_clips[i].x = i * width_frame_;
        }
    }
}
void QUIVUONG:: showboss( SDL_Renderer* des)
{
    rect_.x = x_boss_pos - map_x_boss;
    rect_.y = y_boss_pos - map_y_boss;
    cout<<"rect x"<<rect_.x<<endl;
    frame_++;// tang lien tuc
    if( frame_ >= SO_FRAME ) frame_=0;

    SDL_Rect* currentClip = &frame_clips[frame_];
    SDL_Rect quad = {rect_.x, rect_.y, width_frame_, height_frame_};

    if ( trang_thai_boss.sang_phai == 1 ) SDL_RenderCopy( des, all_anh_boss[boss_run_phai].GetTexture(), currentClip, &quad);
    else if ( trang_thai_boss.sang_trai == 1 ) SDL_RenderCopy( des, all_anh_boss[boss_run_trai].GetTexture(), currentClip, &quad );
    else if ( trang_thai_boss.dam_trai == 1 ) SDL_RenderCopy( des, all_anh_boss[boss_dam_trai].GetTexture(), currentClip, &quad );
    else if ( trang_thai_boss.dam_phai == 1 ) SDL_RenderCopy( des, all_anh_boss[boss_dam_phai].GetTexture(), currentClip, &quad );
    else if ( trang_thai_boss.ban_trai == 1 ) SDL_RenderCopy( des, all_anh_boss[boss_ban_trai].GetTexture(), currentClip, &quad );
    else if ( trang_thai_boss.ban_phai == 1 ) SDL_RenderCopy( des, all_anh_boss[boss_ban_phai].GetTexture(), currentClip, &quad );
    else if ( trang_thai_boss.lon_trai == 1 ) SDL_RenderCopy( des, all_anh_boss[boss_lon_trai].GetTexture(), currentClip, &quad);
    else if ( trang_thai_boss.lon_phai == 1 ) SDL_RenderCopy( des, all_anh_boss[boss_lon_phai].GetTexture(), currentClip, &quad);

}

SDL_Rect QUIVUONG::getrectframe()
{
    SDL_Rect rect;
    rect.x = rect_.x;
    rect.y = rect_.y;
    rect.h = height_frame_;
    rect.w = width_frame_;
    return rect;
}

void QUIVUONG::DICHUYENTHEO_NVC( MainObject kaka)
{
    if( kaka.get_y_hientai() >= 2300 && kaka.get_x_hientai() >= 6000)
    {
        if( kaka.get_trenmatdat() == false )
        {
            if( kaka.getstatus() == MainObject :: ben_phai_ )
            {
                trang_thai_boss.lon_phai = 1;
                trang_thai_boss.lon_trai = 0;
                trang_thai_boss.sang_phai = 0;
                trang_thai_boss.sang_trai = 0;
            }
            else if( kaka.getstatus() == MainObject :: ben_trai_ )
            {
                trang_thai_boss.lon_trai = 1;
                trang_thai_boss.sang_phai = 0;
                trang_thai_boss.sang_trai = 0;
                trang_thai_boss.lon_phai = 0;
            }
        }
        else
        {
            if(kaka.get_x_hientai() > x_boss_pos)
            {
                trang_thai_boss.sang_phai = 1;
                trang_thai_boss.sang_trai = 0;
            }
            else if( kaka.get_x_hientai() < x_boss_pos )
            {
                trang_thai_boss.sang_trai = 1;
                trang_thai_boss.sang_phai = 0;
            }
        }
    }
}

void QUIVUONG::DICHUYEN_BOSS( MAP& map_data, MainObject kaka )
{
    y_change += TOCDOROI_BOSS;
    x_change = 0;
    if ( y_change >= ROITOIDA ) y_change = ROITOIDA_BOSS;

    if(trang_thai_boss.sang_phai == 1 ) x_change += TOCDOCHAY_BOSS ;
    else if (trang_thai_boss.sang_trai == 1) x_change -= TOCDOCHAY_BOSS ;

    else if (trang_thai_boss.lon_phai == 1)
    {
        if( tren_mat_dat == true)
        {
            x_change += 15 ;
            y_change = -NHAYBTH_BOSS ;
            cout<<x_change <<endl;
            cout<<"pos "<<x_boss_pos <<endl;
        }
        tren_mat_dat = false;
        trang_thai_boss.lon_phai = 0;
    }
    else if( trang_thai_boss.lon_trai == 1)
    {
        if( tren_mat_dat == true)
        {
            x_change -= 15 ;
            y_change = -NHAYBTH_BOSS;
        }
        tren_mat_dat = false;
        trang_thai_boss.lon_trai = 0;
    }
    checktomap_boss ( map_data );
    DICHUYENTHEO_NVC ( kaka );
}



void QUIVUONG::checktomap_boss( MAP& map_data )
{
    int x1=0,x2=0; // gioi han kiem tra ngang // theo o vuong
    int y1=0,y2=0;                     //doc

    // kiem tra theo chieu ngang--------------------------
    int height_min = min(height_frame_,TILE_SIZE);// chieu cao nho nhat // chieu cao frame hay chieu cao o=64

    // tim o hien tai dang dung la oo bao nhieu
    int sai_so_can_co=1;
    x1=(x_boss_pos + x_change)/TILE_SIZE;
    x2=(x_boss_pos + x_change + width_frame_ - sai_so_can_co)/TILE_SIZE;
    y1=(y_boss_pos+y_change)/TILE_SIZE;
    y2=(y_boss_pos+y_change+height_min-sai_so_can_co)/TILE_SIZE;

    //kiem tra theo x1,x2,y1,y2 co o trong ban do hay ko
    if( x1>=0 && x2 < MAX_MAP_X && y1>=0 && y2 < MAX_MAP_Y ) // nhan vat o trong ban do
    {
        if(x_change>0)//di sang phai
        {
            int val1=map_data.tile[y1][x2];
            int val2=map_data.tile[y2][x2];
            if((val1!=O_TRONG&&val1!=4)||(val2!=O_TRONG&&val2!=4))// kiem tra xem ban do cho do co trong hay ko
            {
                x_boss_pos = x2*TILE_SIZE-width_frame_-sai_so_can_co;//khi va cham thi phai tra lai vi tri cu
                va_bando = cham_phai;
            }
        }
        else if(x_change < 0)//sang trai
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y2][x1];
            if(( val1!= O_TRONG && val1!=4)||(val2!= O_TRONG && val2!=4))
            {
                x_boss_pos = (x1+sai_so_can_co)*TILE_SIZE;
                va_bando = cham_trai;
            }
        }
    }
    // kiem tra theo chieu doc--------------------------------
    int width_min = min(width_frame_,TILE_SIZE);

    x1 = ( x_boss_pos + 27 )/TILE_SIZE;
    x2 = ( x_boss_pos + width_min - 27)/TILE_SIZE;
    y1 = ( y_boss_pos + y_change )/TILE_SIZE;
    y2 = ( y_boss_pos + y_change + height_frame_ - sai_so_can_co )/TILE_SIZE;
    if( x1>=0 && x2 < MAX_MAP_X && y1>=0 && y2 < MAX_MAP_Y)
    {
        if(y_change > 0)// di xuong //roi xuong
        {
            int val1 = map_data.tile[y2][x1];
            int val2 = map_data.tile[y2][x2];
            if((val1!=O_TRONG&&val1!=4)||(val2!=O_TRONG&&val2!=4))
            {
                y_boss_pos=y2*TILE_SIZE-height_frame_-sai_so_can_co;
                y_change = 0;
                tren_mat_dat = true;
            }
        }
        else if(y_change<0)// nhay len
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y1][x2];
            if((val1!=O_TRONG&&val1!=4)||(val2!=O_TRONG&&val2!=4))
            {
                y_boss_pos =(y1+sai_so_can_co)*TILE_SIZE;
                y_change = 0;
            }
        }
    }
    // neu ko xay ra va cham voi cai nao
    x_boss_pos += x_change;
    y_boss_pos += y_change;

}

void QUIVUONG::init_dan_qui ( BulletObject* dan_qui, SDL_Renderer* screen)
{
    if(dan_qui != nullptr)
    {
        dan_qui->set_loai_dan( BulletObject::DAN_QUI_THUONG );
        dan_qui->TAI_ANH_DAN(screen);
        if( trang_thai_boss.sang_trai == 1 )
        {
            dan_qui->set_huongdan( BulletObject :: ban_dan_trai );
            dan_qui->SetRect(rect_.x-20, y_boss_pos+10);
        }
        else if( trang_thai_boss.sang_phai == 1 )
        {
            dan_qui->set_huongdan( BulletObject :: ban_dan_phai);
            dan_qui->SetRect(rect_.x+ 15, y_boss_pos+10);
        }

        dan_qui->set_x_biendoi(15);
        bang_dan_boss.push_back(dan_qui);
    }
    else cout<<"failed to load anh trai qui"<<endl;
}
void QUIVUONG::loaiboviendan( const int& index )
{
    int size1 = bang_dan_boss.size();
    if( size1 > 0 && index < size1)
    {
        BulletObject* viendan = bang_dan_boss.at(index);
        bang_dan_boss.erase( bang_dan_boss.begin() + index);
        if( viendan)
        {
            delete viendan;
            viendan = nullptr;
        }
    }
}
