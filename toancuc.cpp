#include "toancuc.h"

// Khởi tạo các biến toàn cục
BaseObject tamdung;
BaseObject tamdung2;
BaseObject anh_win;
BaseObject messi;

SDL_Rect nutdung = {SCREEN_WIDTH - 80, 0, 80, 78};
SDL_Rect tieptuc = {625, 460 - 32, 115, 40};
SDL_Rect playagain = {460, 800, 130, 71};
SDL_Rect not_playagain = { 700, 800, 130, 70 };
SDL_Rect restart = {600, 740 -30, 160, 60};
SDL_Rect cut = {625, 670 - 32, 120, 30};
SDL_Rect tatam = {622,571,117,35};

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


SDL_Rect win_nghi = { 105, 795, 85, 80};
SDL_Rect level2 = { 1133, 805, 85, 80};

bool level_1 = true;
bool level_2 = false;
BaseObject gBackground2 ;
GAMEMAP game_map_2;
MAP map_data_2;

bool level_3 =false ;
BaseObject gBackground3 ;
GAMEMAP game_map_3;
MAP map_data_3;

int xc = gEvent.motion.x;
int yc = gEvent.motion.y;

int deadline_man2  = 180 ;
Uint32 starttime;


int demdem = 0;

BaseObject bangthongbao ;

int giaidoansau_win = 1;
int giaidoansau_lose = 1;


SDL_Rect bo_bang = {756 , 388 , 17 , 20};

int sau_lose = 1;

BaseObject mo_am;
BaseObject tat_am;


bool amthanh = false;
int chinham = 1;
int hien_bang_am = 1 ;
SDL_Rect loa = {614, 451 , 55 , 55 };

int kich_chuot_sound = 0;


