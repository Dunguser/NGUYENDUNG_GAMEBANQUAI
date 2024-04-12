#ifndef THREATS_OBJECT_H_
#define THREATS_OBJECT_H


#include "commonfunction.h"
#include "BaseObject.h"
#include "BulletObject.h"

using namespace std;

#define THREATS_FRAME_NUM 6
#define O_TRONG 0
#define TOC_DO_QUI 7

class ThreatsObject : public BaseObject
{
public:
    ThreatsObject();
    virtual ~ThreatsObject();

    enum dung_dau
    {
        cham_trai,
        cham_phai,
    };

    // cai dat toc do
    void set_x_change( const float& kk ) { x_change = kk ;}
    void set_y_change( const float& hh ) { y_change = hh ;}

    // cai dat vi tri //chieu ngang
    void set_x_quipos ( const int& ll ) { x_qui_pos = ll ;}
    void set_y_quipos ( const int& gg ) { y_qui_pos = gg ;}

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

    SDL_Rect GetRectFrame();
    int get_width_frame () const { return width_frame_ ;}
    int get_height_frame () const { return height_frame_ ;}

    void DICHUYEN_QUI( MAP& map_data );// xu li di chuyen cho qui
    void checktomap_qui( MAP& map_data );//kiem tra va cham

    void khoitaoqui();

    // set gioi han di chuyen
    void set_gioi_han_dichuyen ( const int& pos_a, const int & pos_b )
    {
        gioihan_trai = pos_a;
        gioihan_phai = pos_b;
    }
    // khi den gioi han thi no quay lai
    void set_trang_thai_trai( const int& tttrai) { trang_thai_qui.sang_trai = tttrai ;}
    void set_trang_thai_phai( const int& ttphai) { trang_thai_qui.sang_phai = ttphai; }
    //xu li van de di chuyen trong pham vi a,b
    void Di_chuyen_trong_pham_vi( SDL_Renderer* screen, MAP& map_data );

    //dam vao map thi quay lai
    int quay_dau_lam_bo( MAP & map_data );

    //cac ham set, get cho bang dan
    vector<BulletObject*> get_bang_dan_qui() { return bang_dan_qui ;}
    void set_bang_dan_qui( const vector< BulletObject* > & bdan) { bang_dan_qui = bdan ; }

    void init_dan_qui ( BulletObject* dan_qui, SDL_Renderer* screen);// khoi tao vien dan
    void pham_vi_bay_dan_qui( SDL_Renderer* des, const int& x_gioihan, const int& y_gioihan ,MAP& map_data);

    void trungdan() { solantrungdan ++;} // quai bi trung dan
    int get_solantrungdan()const { return solantrungdan;}

    void loaiboviendan( const int& index );

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

    vector<BulletObject*> bang_dan_qui;// xu li qui ban dan
    int solantrungdan;
};



#endif // THREATS_OBJECT_H_
