#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_


#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>
#include<windows.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>


using namespace std;

//screen//renderer
const int SCREEN_WIDTH=1280 ;
const int SCREEN_HEIGHT=960;

const int SCREEN_BPP=32;

//thoi gian cham lai
const int FRAME_PER_SECOND =25;


// chi so ban do game
#define TILE_SIZE 64 // kich thuoc cua 1 o

#define MAX_MAP_X 60
#define MAX_MAP_Y 45

#define MONEY 4

// XAY DUNG BAN DO GAME
//typedef struct MAP
struct MAP
{
    int start_x_;//vi tri , vd dang o o thu 10 thi vi tri la 10*32=320
    int start_y_;// vi tri theo chieu dai chu ko theo o// hoac co the la 1201

    int othu_x_; // chi so cua o do// o thu bao nhieu
    int othu_y_;   // start_y_=othu_y_*TILE_SIZE

    int max_x_;//vi tr toi da cua chieu dai max
    int max_y_;

    int tile[MAX_MAP_Y][MAX_MAP_X];
    string file_name_; //  file txt chua cac so ve map
};

// cau truc trang thai di chuyen cua nhan vat
//typedef struct TRANG_THAI_NHAN_VAT
struct TRANG_THAI_NHAN_VAT
{
    int sang_trai;
    int sang_phai;
    int nhay_;
    int len_;
    int xuong_;
    int bay_;
    int can_chien_;
};


#endif // COMMON_FUNCTION_H_
