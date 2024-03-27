#ifndef THREATS_OBJECT_H_
#define THREATS_OBJECT_H


#include "commonfunction.h"
#include "BaseObject.h"


#define THREATS_FRAME_NUM 6

class ThreatsObject:public BaseObject
{
public:
    ThreatsObject();
    ~ThreatsObject();

    void set_x_change(const float kk)// cai dat toc do
    {
        x_change=kk;
    }
    void set_y_change(const float hh)
    {
        y_change=hh;
    }
    void set_x_quipos(const int&ll)// cai dat vi tri //chieu ngang
    {
        x_qui_pos=ll;
    }
    void set_y_quipos(const int&gg)
    {
        y_qui_pos=gg;
    }
    // cac ham lay ra
    int get_x_quipos()const
    {
        return x_qui_pos;
    }
    int get_y_quipos()const
    {
        return y_qui_pos;
    }
    float get_x_change()const
    {
        return x_change;
    }
    float get_y_change()const
    {
        return y_change;
    }


    void SetMapXY(const int map_x,const int map_y)
    //tao bien theo doi di chyen cua ban do theo nhan vat// vi tri cua ban do chay theo nhan vat
    {
        map_x_qui=map_x;
        map_y_qui=map_y;
    }

    void set_clips();// tao clip chuyen dong
    bool LoadQuiImg(const string &path,SDL_Renderer*screen);

    void ShowQui(SDL_Renderer*des);// in ra man hinh

    int get_width_frame()const {return width_frame_;}
    int get_height_frame()const {return height_frame_;}

    void DICHUYEN_QUI(MAP&gMap);// xu li di chuyen cho qui
    void checktomap(MAP&gMap);//kiem tra va cham





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




};
















#endif // THREATS_OBJECT_H_
