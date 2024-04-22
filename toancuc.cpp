#include "toancuc.h"

// Khởi tạo các biến toàn cục
BaseObject tamdung;
BaseObject tamdung2;
BaseObject anh_win;
BaseObject messi;

SDL_Rect nutdung = {SCREEN_WIDTH - 80, 0, 80, 78};
SDL_Rect tieptuc = {625, 460 - 32, 115, 40};
SDL_Rect playagain = {460 , 800 , 130 , 71};
SDL_Rect not_playagain = { 700 , 800 , 130 , 70 };
SDL_Rect restart = {600, 740 -30 , 160 , 60};
SDL_Rect cut = {625 , 670 - 32, 120, 30};

BaseObject anhdau;
BaseObject anhcho;
BaseObject gameover;
BaseObject gBackground;

GAMEMAP game_map;
MainObject player_nvc;
QUIVUONG quivuong;
Sword kiem;
Sword uatuc;

VUNO qui_no ;
VUNO nvc_no;
VUNO daulau ;
VUNO boss_tan_xac ;
VUNO no_dam ;

BaseObject penaldo  ;


TextObject thoi_gian_choi ;                                     // khai báo phông chữ thời gian chơi gamme
TextObject da_giet;
TextObject antien ;


PlayerPower so_mang;                                            // hien thi so trai tym ung voi so mang
Hotrobay phung;
Hotrobay duocbay;

MENU menu_;


UINT so_qui_bi_giet = 0;
UINT tong_tien = 0;
int solanchet = 0;
Uint32 thoigianhientai;
bool ho = false;

bool quit = false;            // Main loop control variables
bool gameOver = false;
bool isPaused = false;
bool win_game = false;
bool cai_time = false;
Uint32 last_time = 0;

int dem222 = 0;               // Variables for various checks
int dem2221 = 0;
int dem_dam = 0;
int bi_uatuc_chem = 0;
int qui_vuong_bichem = 0;
int boss_andan = 0;
int maumau = 0;
int mauboss = 0;

int solanchetmax = so_mang.get_chi_so_mang();


Uint32 thoi_gian;
Uint32 time_play  ;
int real_imp_time ;
int time_one_frame ;

MAP map_data ;
