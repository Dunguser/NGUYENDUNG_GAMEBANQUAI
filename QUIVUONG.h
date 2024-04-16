#ifndef QUIVUONG_
#define QUIVUONG_

#include <bits/stdc++.h>
#include "commonfunction.h"
#include "BaseObject.h"
#include "GAMEMAP.h"
#include <SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include "BulletObject.h"
#include "MainObject.h"
#include "all_anh_qui.h"

using namespace std;

//#define TOCDOROI 0.8
#define TOCDOROI_BOSS 0.8
#define ROITOIDA_BOSS 40
#define TOCDOCHAY_BOSS 7
#define O_TRONG 0
#define NHAYBTH_BOSS 30
#define NHAY_CAO_BAY 10
#define TOC_DO_BAY 20
#define SO_FRAME 8


class QUIVUONG : public BaseObject
{
public :
    QUIVUONG ();
    ~QUIVUONG();

    enum di_chuyen
    {
        trai,
        phai,
    };
    enum dung_dau
    {
        cham_trai,
        cham_phai,
    };
     // cai dat toc do
    void set_x_change( const float& kk ) { x_change = kk ;}
    void set_y_change( const float& hh ) { y_change = hh ;}

    // cai dat vi tri
    void set_x_bosspos ( const int& ll ) { x_boss_pos = ll ;}
    void set_y_bosspos ( const int& gg ) { y_boss_pos = gg ;}

    // cac ham lay ra
    float get_x_bosspos () const { return x_boss_pos ; }
    float get_y_bosspos () const { return y_boss_pos ; }
    float get_x_change () const { return x_change ; }
    float get_y_change () const { return y_change ; }

    bool LoadImg_boss( const string& path , SDL_Renderer* des);
    void set_clips();
    void showboss( SDL_Renderer* des );
    void SetMapXY( const int map_x, const int map_y )
    {
        map_x_boss = map_x;
        map_y_boss = map_y;
    }

    SDL_Rect getrectframe();
    int get_width_frame () const { return width_frame_ ;}
    int get_height_frame () const { return height_frame_ ;}

    void DICHUYEN_BOSS( MAP& map_data, MainObject kaka );
    void checktomap_boss( MAP& map_data );

    vector <BulletObject*> get_bang_dan_boss() { return bang_dan_boss ;}
    void set_bang_dan_boss( const vector< BulletObject*>& bdan) { bang_dan_boss = bdan ; }

    void init_dan_qui ( BulletObject* dan_qui, SDL_Renderer* screen);
    void loaiboviendan( const int& index );

    void set_doithu ( const MainObject kaka1 ){ kaka = kaka1;}
    MainObject get_doithu () const {return kaka;}

    void DICHUYENTHEO_NVC ( MainObject& kaka);

private:

    int frame_; // so luong hinh anh trong cai anh qui
    int width_frame_; // chieu dai 1 frame
    int height_frame_;

    SDL_Rect frame_clips[SO_FRAME];

    bool tren_mat_dat;

    float x_boss_pos;//vi tri hien tai
    float y_boss_pos;

    float x_change;// bien doi khi di chuyen
    float y_change;

    int map_x_boss;// 2 bien luu vi tri qui so voi map
    int map_y_boss;// kiem tra roi xuong vuc

    TRANG_THAI_BOSS trang_thai_boss;// ben trai hay ben phai

    int va_bando;

    vector <BulletObject*> bang_dan_boss;// xu li qui ban dan

    MainObject kaka;
};













#endif // QUIVUONG_
