#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include<bits/stdc++.h>
#include "commonfunction.h"
#include "BaseObject.h"
#include "GAMEMAP.h"
#include <SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include "BulletObject.h"


using namespace std;

#define TOCDOROI 0.8
#define ROITOIDA 40
#define TOCDOCHAY 8.5
#define O_TRONG 0
#define NHAYBTH 20
#define NHAY_CAO_BAY 10
#define TOC_DO_BAY 30


// khoi tao nhan vat chinh // ke thua BaseObject

class MainObject:public BaseObject
{
public:
    MainObject();
    ~MainObject();

    enum di_chuyen
    {
        ben_trai_,
        ben_phai_,
        bay_trai_,
        bay_phai_,
    };

    bool LoadMainImg ( const string&path, SDL_Renderer *screen );//ham load anh cua nhan vat chinh va can them cac thong so cua tam anh
    void ShowMain ( SDL_Renderer*des );// xau frame nhan vat chinh
    void XuLiXuKienBanPhim (SDL_Event events, SDL_Renderer*screen);// xu li cac phim bam sang trai, sang phai, bay
    void Set_Clips_chay (); // ham tao clip tu nhung hinh anh lien tiep
    void DiChuyenNhanVat ( MAP &map_data );//xu li cho nhan vat di chuyen, va cham coi ban do
    void CheckToMap( MAP&map_data );// kiem tra nhan vat va cham voi ban do

    void SetMapXY ( const int map_x, const int map_y )
    //tao bien theo doi di chyen cua ban do theo nhan vat
    // vi tri cua ban do chay theo nhan vat
    {
        map_x_=map_x;
        map_y_=map_y;
    }

    void MAP_DI_CHUYEN_THEO_NV ( MAP&map_data );//tinh toan thong so cua map khi nhan vat di chuyen
    void capnhattrenmatdat( SDL_Renderer*des );

    bool get_roi_xuong_vuc();// lay roi xuong vuc


    //xu li bang dan
    void set_bang_dan(vector<BulletObject*>bu)// cai dat bang dan
    {
        bangdan_nvc=bu;
    }
    // lay bang dan ra
    vector<BulletObject*>get_bang_dan()const
    {
        return bangdan_nvc;
    }

    void KHOI_TAO_DAN_1 (BulletObject*viendan,SDL_Renderer*screen);
    void KHOI_TAO_DAN_2 (BulletObject*viendan,SDL_Renderer*screen);
    //void XU_LI_BAN_DAN(SDL_Renderer*des,const int&x_gioihan,const int&y_gioihan);// xu li ban dan cho nhan vat
    void XU_LI_BAN_DAN  (SDL_Renderer*des, const int&x_gioihan, const int&y_gioihan, MAP&map_data);// xu li ban dan cho nhan vat

    void loaiboviendan( const int& index );// loai bo vien dan ngoai pham vi ban
    void an_tien();// tinh tien an duoc


private:
    float x_biendoi_;// khi di chuyen thi tang/giam bao nhieu
    float y_biendoi_; // an trai giam bao nhieu, nhay tang bao nhieu

    float x_now_pos;//vi tri x hien tai
    float y_now_pos;

    int width_frame_; // kich thuoc 1 frame vi 1 anh co 5,7,8 frame
    int height_frame_;

    SDL_Rect frame_clip_[8];// luu cac frame

    TRANG_THAI_NHAN_VAT trang_thai_vao;// luu trang thai di chuyen cua nhan vat
    int frame_; //luu chi so cua frame, frame thu may

    int status_; // luu trang thai di chuyen //enum di_chuyen
    bool tren_mat_dat;// kiem tra co o tren mat dat hay ko

    int map_x_;// mep moi cua ban do khi nhan vat di chuyen
    int map_y_;// su dung trong ham setmapXY

    bool roi_xuong_vuc;

    vector<BulletObject*> bangdan_nvc; // dan la 1 thanh phan cua nhan vat chinh

    int tien_an_duoc;

    int come_back_time_;// thoi gian sau khi chet nhan vat quay tro lai


};


enum anh_qui
{
    ditrai,
    diphai,
    dem
};

extern BaseObject tat_ca_anh_qui[2];

#endif // MAIN_OBJECT_H_


























