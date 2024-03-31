#ifndef THREATS_OBJECT_H_
#define THREATS_OBJECT_H


#include "commonfunction.h"
#include "BaseObject.h"

using namespace std;

#define THREATS_FRAME_NUM 7
#define O_TRONG 0
#define TOC_DO_QUI 4

class ThreatsObject:public BaseObject
{
public:
    ThreatsObject();
    virtual ~ThreatsObject();

    enum dung_dau
    {
        cham_trai=60,
        cham_phai=61
    };

    // cai dat toc do
    void set_x_change( const float kk ) { x_change = kk ;}
    void set_y_change( const float hh ) { y_change = hh ;}

    // cai dat vi tri //chieu ngang
    void set_x_quipos ( const int&ll ) { x_qui_pos = ll ;}
    void set_y_quipos ( const int&gg ) { y_qui_pos = gg ;}

    // cac ham lay ra
    float get_x_quipos () const { return x_qui_pos ; }
    float get_y_quipos () const { return y_qui_pos ; }
    float get_x_change () const { return x_change ; }
    float get_y_change () const { return y_change ; }


    //tao bien theo doi di chyen cua ban do theo nhan vat
    // vi tri cua ban do chay theo nhan vat
    void SetMapXY( const int map_x, const int map_y )
    {
        map_x_qui = map_x;
        map_y_qui = map_y;
    }

    void set_clips();// tao clip chuyen dong
    bool LoadImage( const string &path, SDL_Renderer* screen );

    void ShowQui(SDL_Renderer*des);// in ra man hinh

    int get_width_frame () const { return width_frame_ ;}
    int get_height_frame () const { return height_frame_ ;}

    void DICHUYEN_QUI( MAP& map_data );// xu li di chuyen cho qui
    void checktomap_qui( MAP& map_data );//kiem tra va cham


    void khoitaoqui();

    // set gioi han di chuyen
    void set_gioi_han_dichuyen ( const int& pos_a, const int & pos_b )
    {
        gioihan_trai=pos_a;
        gioihan_phai=pos_b;
    }
    // khi den gioi han thi no quay lai
    void set_trang_thai_trai( const int& tttrai) { trang_thai_qui.sang_trai = tttrai ;}
    //xu li van de di chuyen trong pham vi a,b
    void Di_chuyen_trong_pham_vi( SDL_Renderer* screen, MAP& map_data );

    //===
    int quay_dau_lam_bo( MAP & map_data );

//    enum anh_qui
//    {
//        ditrai,
//        diphai,
//        dem
//    };
//
//    BaseObject tat_ca_anh_qui[2];
//    void load_tat_ca_qui(SDL_Renderer* des);
private:
    int frame_; // so luong hinh anh trong cai anh qui
    int width_frame_; // chieu dai 1 frame
    int height_frame_;

    SDL_Rect frame_clips[THREATS_FRAME_NUM];

    bool tren_mat_dat;// co tren mat dat ko

    float x_qui_pos;//vi tri hien tai
    float y_qui_pos;

    float x_change;// bien doi khi di chuyen
    float y_change;

    int map_x_qui;// 2 bien luu vi tri qui so voi map
    int map_y_qui;// kiem tra roi xuong vuc

    int come_back_time_;

    int gioihan_trai;
    int gioihan_phai;

    TRANG_THAI_NHAN_VAT trang_thai_qui;// ben trai hay ben phai

    int va_bando;
};
















#endif // THREATS_OBJECT_H_
