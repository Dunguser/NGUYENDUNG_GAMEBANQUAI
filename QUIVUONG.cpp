#include "QUIVUONG.h"
#include "BaseObject.h"
using namespace std;

QUIVUONG::QUIVUONG ()
{
    width_frame_= 0;
    height_frame_ = 0;
    tren_mat_dat = false;

    x_boss_pos = 4500 ;//vi tri hien tai
    y_boss_pos = 2700 ;

    x_change = 0.0 ;// bien doi khi di chuyen
    y_change = 0.0 ;

    frame_ = 0 ;
    trang_thai_boss.sang_trai = 1;

    solantrungdan = 0 ;
    frame_mau_boss = 0;
    hanglanh = false;

    cung = nullptr;
    dau = nullptr;
}
QUIVUONG::~QUIVUONG()
{

}

bool QUIVUONG::LoadImg_boss( const string& path, SDL_Renderer* des)
{
    bool ret = BaseObject :: LoadImage(path,des);
    if(ret)
    {
        width_frame_ = rect_.w / SO_FRAME ;//cout<<"rect_.w " <<rect_.w<<endl;
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

    frame_ ++;// tang lien tuc
    if( frame_ >= SO_FRAME ) frame_=0;

    SDL_Rect* currentClip = &frame_clips[frame_];
    SDL_Rect quad = { rect_.x, rect_.y, width_frame_, height_frame_};

    if ( trang_thai_boss.sang_phai == 1 ) SDL_RenderCopy ( des, all_anh_boss[boss_run_phai].GetTexture(), currentClip, &quad);
    else if ( trang_thai_boss.sang_trai == 1 ) SDL_RenderCopy ( des, all_anh_boss[boss_run_trai].GetTexture(), currentClip, &quad );
    else if ( trang_thai_boss.dam_trai == 1 ) SDL_RenderCopy ( des, all_anh_boss[boss_dam_trai].GetTexture(), currentClip, &quad );
    else if ( trang_thai_boss.dam_phai == 1 ) SDL_RenderCopy ( des, all_anh_boss[boss_dam_phai].GetTexture(), currentClip, &quad );
    else if ( trang_thai_boss.ban_trai == 1 ) SDL_RenderCopy ( des, all_anh_boss[boss_ban_trai].GetTexture(), currentClip, &quad );
    else if ( trang_thai_boss.ban_phai == 1 ) SDL_RenderCopy ( des, all_anh_boss[boss_ban_phai].GetTexture(), currentClip, &quad );
    else if ( trang_thai_boss.lon_trai == 1 ) SDL_RenderCopy ( des, all_anh_boss[boss_lon_trai].GetTexture(), currentClip, &quad );
    else if ( trang_thai_boss.lon_phai == 1 ) SDL_RenderCopy ( des, all_anh_boss[boss_lon_phai].GetTexture(), currentClip, &quad );

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

void QUIVUONG::DICHUYENTHEO_NVC( MainObject &kaka, SDL_Renderer* screen)
{
    if(  kaka.get_x_hientai() >= 5000)
    {
        if( abs(kaka.get_y_hientai() - y_boss_pos ) >= 50 )
        {
            int khoangcach = abs( kaka.get_x_hientai() - x_boss_pos );
            if( khoangcach >= 400 )
            {
                if( kaka.get_x_hientai() > x_boss_pos )
                {
                    trang_thai_boss.sang_phai = 1;
                    trang_thai_boss.sang_trai = 0;
                    trang_thai_boss.dam_trai = 0;
                    status_boss = phai;
                }
                else if( kaka.get_x_hientai() < x_boss_pos )
                {
                    trang_thai_boss.sang_trai = 1 ;
                    trang_thai_boss.sang_phai = 0 ;
                    trang_thai_boss.dam_phai = 0;
                    status_boss = trai ;
                }
            }
            else if(khoangcach > 300 && khoangcach < 400)
            {
                if( kaka.getstatus() == MainObject :: ben_phai_ )
                {
                    if(kaka.get_x_hientai() < x_boss_pos)
                    {
                        trang_thai_boss.lon_trai = 1;
                        trang_thai_boss.lon_phai = 0;
                        trang_thai_boss.dam_phai = 0;
                    }
                    else
                    {
                        trang_thai_boss.lon_phai = 1;
                        trang_thai_boss.lon_trai = 0;
                        trang_thai_boss.dam_trai = 0;
                    }

                    trang_thai_boss.sang_phai = 0;
                    trang_thai_boss.sang_trai = 0;
                    trang_thai_boss.ban_trai = 0;
                }
                else if( kaka.getstatus() == MainObject :: ben_trai_ )
                {
                    if( kaka.get_x_hientai() < x_boss_pos)
                    {
                        trang_thai_boss.lon_trai = 1;
                        trang_thai_boss.lon_phai = 0;
                        trang_thai_boss.dam_phai = 0;
                    }
                    else
                    {
                        trang_thai_boss.lon_phai = 1;
                        trang_thai_boss.lon_trai = 0;
                        trang_thai_boss.dam_trai = 0;
                    }

                    trang_thai_boss.sang_phai = 0;
                    trang_thai_boss.sang_trai = 0;
                    trang_thai_boss.ban_phai = 0;
                }

            }
            else if( khoangcach <300 && khoangcach > 100)
            {
                if(kaka.get_x_hientai() > x_boss_pos )
                {
                    trang_thai_boss.ban_phai = 1;
                    trang_thai_boss.sang_phai = 0;
                    trang_thai_boss.ban_trai = 0;
                    trang_thai_boss.dam_trai = 0;
                    trang_thai_boss.dam_phai = 0;
                    status_boss = phai;
                }
                else if( kaka.get_x_hientai() < x_boss_pos )
                {
                    trang_thai_boss.ban_trai = 1;
                    trang_thai_boss.sang_trai = 0;
                    trang_thai_boss.ban_phai = 0;
                    trang_thai_boss.dam_phai = 0;
                    trang_thai_boss.dam_trai = 0;
                    status_boss = trai ;
                }
            }
            else
            {
                if( kaka.get_y_hientai() - y_boss_pos < 0)
                {
                    if( kaka.getstatus() == MainObject :: ben_phai_ )
                    {
                        if(kaka.get_x_hientai() < x_boss_pos)
                        {
                            trang_thai_boss.dam_trai = 1;
                            trang_thai_boss.dam_phai = 0;
                            trang_thai_boss.ban_phai = 0;
                        }
                        else
                        {
                            trang_thai_boss.dam_phai = 1;
                            trang_thai_boss.dam_trai = 0;
                            trang_thai_boss.dam_trai = 0;
                        }

                        trang_thai_boss.sang_phai = 0;
                        trang_thai_boss.sang_trai = 0;

                    }
                    else if( kaka.getstatus() == MainObject :: ben_trai_ )
                    {
                        if( kaka.get_x_hientai() < x_boss_pos)
                        {
                            trang_thai_boss.dam_trai = 1;//cout<<"lon trai"<<endl;
                            trang_thai_boss.dam_phai = 0;
                        }
                        else
                        {
                            trang_thai_boss.dam_phai = 1;
                            trang_thai_boss.dam_trai = 0;
                        }

                        trang_thai_boss.sang_phai = 0;
                        trang_thai_boss.sang_trai = 0;
                        trang_thai_boss.ban_phai = 0;
                    }
                    y_boss_pos = 64*45 - 350;
                }
            }
        }
        else if ( abs(kaka.get_y_hientai() - y_boss_pos ) < 50  )
        {
            int khoangcach = abs( kaka.get_x_hientai() - x_boss_pos );
            if( khoangcach >= 400 )
            {
                if( kaka.get_x_hientai() > x_boss_pos )
                {
                    trang_thai_boss.sang_phai = 1;
                    trang_thai_boss.sang_trai = 0;
                    status_boss = phai;
                }
                else if( kaka.get_x_hientai() < x_boss_pos )
                {
                    trang_thai_boss.sang_trai = 1 ;
                    trang_thai_boss.sang_phai = 0 ;
                    status_boss = trai ;
                }
            }
            else if ( khoangcach >= 300 && khoangcach < 400)
            {
                int y_distance = abs(kaka.get_y_hientai() - y_boss_pos );
                if( y_distance <= 100)
                {
                    if(kaka.get_x_hientai() > x_boss_pos )
                    {
                        trang_thai_boss.lon_phai = 1;
                        trang_thai_boss.sang_phai = 0;
                        trang_thai_boss.ban_trai = 0;
                        trang_thai_boss.dam_trai = 0;
                        trang_thai_boss.dam_phai = 0;
                        status_boss = phai;
                    }
                    else if( kaka.get_x_hientai() < x_boss_pos )
                    {
                        trang_thai_boss.lon_trai = 1;
                        trang_thai_boss.sang_trai = 0;
                        trang_thai_boss.ban_phai = 0;
                        trang_thai_boss.dam_phai = 0;
                        trang_thai_boss.dam_trai =0;
                        status_boss = trai ;
                    }
                    BulletObject* dan_boss = new BulletObject();
                    init_dan_qui(dan_boss,screen );
                }
            }
            else if ( khoangcach >= 100 && khoangcach < 300)
            {
                int y_distance = abs(kaka.get_y_hientai() - y_boss_pos );
                if( y_distance <= 100)
                {
                    if(kaka.get_x_hientai() > x_boss_pos )
                    {
                        trang_thai_boss.ban_phai = 1;
                        trang_thai_boss.sang_phai = 0;
                        trang_thai_boss.ban_trai = 0;
                        trang_thai_boss.dam_trai = 0;
                        trang_thai_boss.dam_phai = 0;
                        status_boss = phai;
                    }
                    else if( kaka.get_x_hientai() < x_boss_pos )
                    {
                        trang_thai_boss.ban_trai = 1;
                        trang_thai_boss.sang_trai = 0;
                        trang_thai_boss.ban_phai = 0;
                        trang_thai_boss.dam_phai = 0;
                        trang_thai_boss.dam_trai =0;
                        status_boss = trai ;
                    }
                    BulletObject* dan_boss = new BulletObject();
                    init_dan_qui(dan_boss,screen );
                }
            }
            else
            {
                if( kaka.get_x_hientai() > x_boss_pos )
                {
                    trang_thai_boss.dam_phai = 1;
                    trang_thai_boss.dam_trai = 0 ;
                }
                else
                {
                    trang_thai_boss.dam_trai = 1;
                    trang_thai_boss.dam_phai = 0;
                }
            }
        }
    }
}

void QUIVUONG::DICHUYEN_BOSS( MAP& map_data )
{
    y_change += TOCDOROI_BOSS;
    x_change = 0;
    if ( y_change >= ROITOIDA ) y_change = ROITOIDA_BOSS;

    if ( trang_thai_boss.sang_phai == 1 ) x_change += TOCDOCHAY_BOSS ;
    else if (trang_thai_boss.sang_trai == 1) x_change -= TOCDOCHAY_BOSS ;
    else if ( trang_thai_boss.ban_phai == 1)
    {
        x_change += TOCDOCHAY_BOSS / 2;
        playmusic(cung);
    }
    else if ( trang_thai_boss.ban_trai == 1)
    {
        x_change -= TOCDOCHAY_BOSS / 2;
        playmusic(cung);
    }
    else if (trang_thai_boss.lon_phai == 1)
    {
        if( tren_mat_dat == true)
        {
            x_change += TOCDOCHAY_BOSS ;//cout<< "nhay  mua di "<<endl;
            y_change = - NHAYBTH_BOSS /1.2;
        }
        tren_mat_dat = false;
        trang_thai_boss.lon_phai = 0;
    }
    else if( trang_thai_boss.lon_trai == 1)
    {
        if( tren_mat_dat == true)
        {
            x_change -= TOCDOCHAY_BOSS ;
            y_change = - NHAYBTH_BOSS /1.2;
        }
        tren_mat_dat = false;
        trang_thai_boss.lon_trai = 0;
    }
    checktomap_boss ( map_data );
}

void QUIVUONG::checktomap_boss( MAP& map_data )
{
    int x1=0,x2=0; // gioi han kiem tra ngang // theo o vuong
    int y1=0,y2=0;                     //doc

    // kiem tra theo chieu ngang--------------------------
    int height_min = min(height_frame_,TILE_SIZE);// chieu cao nho nhat // chieu cao frame hay chieu cao o=64

    // tim o hien tai dang dung la oo bao nhieu
    int sai_so_can_co=1;
    x1 = ( x_boss_pos + x_change )/TILE_SIZE;
    x2 = ( x_boss_pos + x_change + width_frame_ - sai_so_can_co)/TILE_SIZE;
    y1 = ( y_boss_pos + y_change )/TILE_SIZE;
    y2 = ( y_boss_pos + y_change + height_min - sai_so_can_co )/TILE_SIZE;

    //kiem tra theo x1,x2,y1,y2 co o trong ban do hay ko
    if( x1>=0 && x2 < MAX_MAP_X && y1>=0 && y2 < MAX_MAP_Y ) // nhan vat o trong ban do
    {
        if(x_change>0)//di sang phai
        {
            int val1 = map_data.tile[y1][x2];
            int val2 = map_data.tile[y2][x2];
            if((val1 != O_TRONG )||(val2 != O_TRONG ))// kiem tra xem ban do cho do co trong hay ko
            {
                x_boss_pos = x2 * TILE_SIZE - width_frame_ - sai_so_can_co;//khi va cham thi phai tra lai vi tri cu
                va_bando = cham_phai;
            }
        }
        else if(x_change < 0)//sang trai
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y2][x1];
            if(( val1!= O_TRONG )||(val2!= O_TRONG))
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
            if((val1!=O_TRONG)||(val2!=O_TRONG))
            {
                y_boss_pos = y2 * TILE_SIZE - height_frame_ - sai_so_can_co;
                y_change = 0;
                tren_mat_dat = true;
            }
        }
        else if(y_change<0)// nhay len
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y1][x2];
            if((val1!=O_TRONG)||(val2!=O_TRONG))
            {
                y_boss_pos =(y1+sai_so_can_co)*TILE_SIZE;
                y_change = 0;
            }
        }
    }
    // neu ko xay ra va cham voi cai nao
    x_boss_pos += x_change;
    y_boss_pos += y_change;

    if(x_boss_pos+width_frame_>map_data.max_x_)
    {
        x_boss_pos = map_data.max_x_ - width_frame_ - sai_so_can_co;
    }

}

void QUIVUONG::init_dan_qui ( BulletObject* dan_qui, SDL_Renderer* screen)
{
    if(dan_qui != nullptr)
    {
        if(status_boss == phai)
        {
            dan_qui->set_loai_dan ( BulletObject :: DAN_QUI_PHAI);
            dan_qui->TAI_ANH_DAN(screen);
            dan_qui->set_huongdan( BulletObject :: ban_dan_phai);
            dan_qui->SetRect( this->rect_.x + 35, this->rect_.y + 36);//cout<<"kaka"<<endl;
        }
        else if( status_boss == trai )
        {
            dan_qui->set_loai_dan(BulletObject :: DAN_QUI_TRAI);
            dan_qui->TAI_ANH_DAN ( screen );
            dan_qui->set_huongdan( BulletObject :: ban_dan_trai);
            dan_qui->SetRect( this->rect_.x, this->rect_.y + 36);  //cout<<"kaka2"<<endl;
        }
        dan_qui->settrongmanhinh(true);
        dan_qui->set_x_biendoi( 45 );
        bang_dan_boss.push_back( dan_qui );
    }
    else cout<<"failed to load anh trai qui"<<endl;
}

void QUIVUONG::xulibossbandan (SDL_Renderer* screen )
{
    for(int i = 0; i< (int)bang_dan_boss.size(); i++)
    {
        BulletObject * dan = bang_dan_boss.at(i);
        if( dan != nullptr )
        {
            if(dan->gettrongmanhinh())
            {
                dan->phamvidanboss( SCREEN_WIDTH, SCREEN_HEIGHT );
                dan->Render(screen);
            }
            else
            {
                dan->settrongmanhinh(false);
                loaiboviendan(i);
            }
        }
    }
}
void QUIVUONG::loaiboviendan( const int& index )
{
    int size1 = bang_dan_boss.size();
    if( size1 > 0 && index < size1)
    {
        BulletObject* viendan = bang_dan_boss.at(index);
        bang_dan_boss.erase( bang_dan_boss.begin() + index);
        bang_dan_boss[index]->free();
        if( viendan)
        {
            delete viendan;
            viendan = nullptr;
        }
    }
}

bool QUIVUONG :: trangthaidam()
{
    if(trang_thai_boss.dam_phai == 1|| trang_thai_boss.dam_trai == 1) return true;
    return false;
}

void QUIVUONG::load_cucmau_boss ( SDL_Renderer * des )
{
    bool ret1 = mau_boss[0].LoadImage( "IMG/mau/mau_qui1.png", des);
    bool ret2 = mau_boss[1].LoadImage( "IMG/mau/mau_qui2.png", des);
    bool ret3 = mau_boss[2].LoadImage( "IMG/mau/mau_qui3.png", des);
    bool ret4 = mau_boss[3].LoadImage( "IMG/mau/mau_qui4.png", des);
    bool ret5 = mau_boss[4].LoadImage( "IMG/mau/mau_qui5.png", des);
    if( ret1 == 0 || ret2 == 0 || ret3 == 0 || ret4 == 0 || ret5 == 0) cout<<"failed to load mau qui"<<endl;
}
void QUIVUONG::show_mau_boss ( SDL_Renderer* des, int index)
{
    index = solantrungdan ;
    mau_boss[index].SetRect ( 20, 95 );
    mau_boss[index].Render ( des, nullptr ); //cout<<"mau boss"<<endl;
}

void QUIVUONG::trungdan ()
{
    solantrungdan ++;
    playmusic(dau);
    if(solantrungdan == 2)hanglanh = true;
}

void QUIVUONG:: loadamthanh_boss()
{
    //cung = Mix_LoadWAV("sound/cung.mp3");
    dau = Mix_LoadWAV("sound/dau.mp3");
    if(cung == nullptr || dau == nullptr )cout<< Mix_GetError();
    if(dau == nullptr){ cout<<"dau ";}
}











//cout<<x_boss_pos << " " << y_boss_pos <<endl;
//mau_boss[index].SetRect ( x_boss_pos , y_boss_pos - 50);
//cout<<"mau " << mau_boss[index].GetRect().x << " "<< mau_boss[index].GetRect().y<<endl;
