#ifndef BULLET_OBJECT_H_
#define BULLET_OBJECT_H_

#include "BaseObject.h"
#include "commonfunction.h"

using namespace std;

#define O_TRONG 0
#define TOCDO_DAN 30


class BulletObject:public BaseObject
{
public:
    BulletObject();
    virtual~BulletObject();

    // trang thai bay cua dan
    enum HUONG_DAN
    {
        ban_dan_trai=20,
        ban_dan_phai=21,
        ban_duoi_trai=22,
        ban_duoi_phai=23,
    };
    enum LOAI_DAN
    {
        DAN1_TRAI=50,
        DAN1_PHAI=51,
        DAN3=52,
        DAN4=53
    };

    void set_x_biendoi(const int&xBiendoi) // cai dat gia tri cho x_bien doi
    {
        x_biendoi=xBiendoi;
    }
    void set_y_biendoi(const int &yBiendoi)
    {
        y_biendoi=yBiendoi;
    }

    // lay gia tri x_biendoi
    float get_x_biendoi()const
    {
        return x_biendoi;
    }
    float get_y_biendoi()const
    {
        return y_biendoi;
    }
    // trong man hinh lam tuong tu
    void settrongmanhinh(const bool&trong)
    {
        trong_man_hinh=trong;
    }
    bool gettrongmanhinh()
    {
        return trong_man_hinh;
    }


    //xet gioi han hien thi vien dan bay, vi du vuot qua man hinh thi ko in ra nua
    void pham_vi_dan_bay(const int&x_gioihan,const int &y_gioihan,int dotang_x,int dotang_y,MAP&map_data);

    // xet huong cho dan
    void set_huongdan(const unsigned int&huong)
    {
        huong_cua_dan=huong;
    }
    unsigned int get_huongdan()// lay ra huong cua dan
    {
        return huong_cua_dan;
    }

    void set_loai_dan(const unsigned int&lieu)// cai dat loai dan
    {
        loai_dan_=lieu;
    }
    unsigned int get_loai_dan()//lay loai dan ra
    {
        return loai_dan_;
    }
    // tai cac loai dan
    bool TAI_ANH_DAN(SDL_Renderer*des);


    //phan chinh sua
    //bool check_va_cham_map(MAP&map_data,int map_x_dan,int map_y_dan);// kien tra va cham voi map
    bool check_va_cham_map(MAP&map_data);// kien tra va cham voi map
    void DI_CHUYEN_DAN(MAP&map_data);

private:

    float x_vitri_dan;
    float y_vitri_dan;

    float x_biendoi;// dan di chuyen dc bao nhieu// toc do dan
    float y_biendoi;


    bool trong_man_hinh;// xem no co o trong man hinh ko
    unsigned int huong_cua_dan;// quan li huong di chuyen cua dan
    unsigned int loai_dan_;

    int width_frame_dan;// kich thuoc frame dan
    int height_frame_dan;

    int map_x_;// mep moi cua ban do khi nhan vat di chuyen
    int map_y_;
};









#endif // BULLET_OBJECT_H_
