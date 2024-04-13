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
#include "kiemquay.h"
#include "SOUND.h"


using namespace std;

#define TOCDOROI 0.8
#define ROITOIDA 40
//#define TOCDOCHAY 15
#define TOCDOCHAY 9
#define O_TRONG 0
#define NHAYBTH 20
#define NHAY_CAO_BAY 10
#define TOC_DO_BAY 20
#define SO_FRAME 8

#define TANG_MANG 23
#define CHO_BAY 24
#define PHUONG_HOANG 13
#define SOLANBAY 7

// khoi tao nhan vat chinh // kế thừa BaseObject
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
    void XuLiXuKienBanPhim (SDL_Event events, SDL_Renderer* screen);// xu li cac phim bam sang trai, sang phai, bay
    void Set_Clips_chay (); // ham tao clip tu nhung hinh anh lien tiep
    void DiChuyenNhanVat ( MAP & map_data );//xu li cho nhan vat di chuyen, va cham coi ban do
    void CheckToMap( MAP& map_data );// kiem tra nhan vat va cham voi ban do
    SDL_Rect GetRectFrame();

    void SetMapXY ( const int map_x, const int map_y )
    {
        map_x_ = map_x;//tao bien theo doi di chyen cua ban do theo nhan vat
        map_y_ = map_y;// vi tri cua ban do chay theo nhan vat
    }

    void MAP_DI_CHUYEN_THEO_NV ( MAP& map_data );//tinh toan thong so cua map khi nhan vat di chuyen
    void capnhattrenmatdat( SDL_Renderer* des );

    bool get_roi_xuong_vuc();// lay roi xuong vuc
    void set_bang_dan(vector<BulletObject*> bu){ bangdan_nvc = bu; }// cai dat bang dan
    vector<BulletObject*>get_bang_dan()const { return bangdan_nvc; }// lay bang dan ra

    void KHOI_TAO_DAN_1 ( BulletObject* viendan, SDL_Renderer* screen );
    void KHOI_TAO_DAN_2 ( BulletObject* viendan, SDL_Renderer* screen );
    void XU_LI_BAN_DAN  ( SDL_Renderer* des, const int& x_gioihan, const int& y_gioihan, MAP& map_data);// xu li ban dan cho nhan vat
    void khoi_tao_kiem (SDL_Renderer* des , Sword kiem );

    void loaiboviendan( const int& index );// loai bo vien dan ngoai pham vi ban
    void an_tien();     // tinh tien an duoc

    void trungdan() { solantrungdan ++;}    //  bi trung dan quai
    int get_solantrungdan() const { return solantrungdan;}

    int get_width_frame () const { return width_frame_ ; }
    int get_height_frame () const { return height_frame_ ; }

    float get_x_hientai()const {return x_now_pos ;}
    float get_y_hientai()const {return y_now_pos ;}

    int get_tienanduoc() const { return tien_an_duoc ; }

    void set_comebacktime (const int & k){ come_back_time_ = k;}


    void nhanbietchet ( const int& chet) { trang_thai_vao.chet_ = chet ;}

    void tang_mang(bool kk) { themmang = kk; } // kim cuong do
    bool get_tangmang () const { return themmang ; }

    void setchobay ( const bool& bay) { chobay = bay ;}// kim cuong xanh
    bool getchobay () const {return chobay;}

    void kichhoatchongchong( const bool & hh){ chongchong = hh ;}
    bool getchongchong()const { return chongchong; }

    void kichhoathangnong ( const bool & hh){ hangnong = hh;}
    bool gethangnong() const {return hangnong;}

    Sword getkiem() { return kiem ;}

    void loadamthanh_nvc();
    void playmusic( Mix_Chunk* kaka) { Mix_PlayChannel(-1, kaka , 0); }

    TRANG_THAI_NHAN_VAT getTRANGTHAI_main()const { return trang_thai_vao;} // lam cho con qui vuong
    int getstatus()const { return status_ ;}
    bool get_trenmatdat() const { return tren_mat_dat ;}

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

    int solantrungdan;
    bool themmang;

    bool chobay;
    int hanchebay;

    bool chongchong;
    bool hangnong;

    Sword kiem;

    Mix_Chunk* sung;
    Mix_Chunk* kiem1;
    Mix_Chunk* andohotro;
};


#endif // MAIN_OBJECT_H_


