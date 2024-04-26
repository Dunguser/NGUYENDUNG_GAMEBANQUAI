#ifndef  TOAN_CUC_
#define TOAN_CUC

#include<bits/stdc++.h>
#include<windows.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include <SDL.h>

#include "BaseObject.h"
#include "GAMEMAP.h"
#include "MainObject.h"
#include "vuno.h"
#include "QUIVUONG.h"
#include "TextObject.h"
#include "PlayerPower.h"
#include "commonfunction.h"
#include "all_anh_qui.h"
#include "MENU.h"
#include "kiemquay.h"
#include "all_anh_nvc.h"



extern BaseObject tamdung;
extern BaseObject tamdung2;
extern BaseObject anh_win;
extern BaseObject messi;

extern SDL_Rect nutdung;
extern SDL_Rect tieptuc;
extern SDL_Rect playagain;
extern SDL_Rect not_playagain ;

extern SDL_Rect restart;
extern SDL_Rect cut;
extern SDL_Rect tatam;

extern BaseObject anhdau;
extern BaseObject anhcho;
extern BaseObject gameover;
extern BaseObject gBackground;

extern GAMEMAP game_map;
extern MainObject player_nvc;
extern QUIVUONG quivuong;

extern Sword kiem;
extern Sword uatuc;

extern VUNO qui_no ;
extern VUNO nvc_no;
extern VUNO daulau ;
extern VUNO boss_tan_xac ;
extern VUNO no_dam ;

extern BaseObject penaldo;


extern  TextObject thoi_gian_choi ;                                     // khai báo phông chữ thời gian chơi gamme
extern  TextObject da_giet;
extern  TextObject antien ;


extern  PlayerPower so_mang;                                            // hien thi so trai tym ung voi so mang
extern  Hotrobay phung;
extern  Hotrobay duocbay;

extern MENU menu_;


extern UINT so_qui_bi_giet;
extern UINT tong_tien;
extern int solanchet;
extern Uint32 thoigianhientai;
extern bool ho;

extern bool quit;
extern bool gameOver;
extern bool isPaused;
extern bool win_game;
extern bool cai_time;


extern Uint32 last_time;

extern int dem222;
extern int dem2221;
extern int dem_dam;
extern int bi_uatuc_chem;
extern int qui_vuong_bichem;
extern int boss_andan;
extern int maumau;
extern int mauboss;


extern int solanchetmax ;


extern Uint32 thoi_gian;
extern Uint32 time_play  ;
extern int real_imp_time ;
extern int time_one_frame ;

extern MAP map_data ;
extern MAP map_data_2;

extern SDL_Rect win_nghi;
extern SDL_Rect level2;

extern bool level_1 ;
extern bool level_2 ;
extern BaseObject gBackground2 ;
extern GAMEMAP game_map_2;

extern bool level_3 ;
extern BaseObject gBackground3 ;
extern GAMEMAP game_map_3;
extern MAP map_data_3;

extern int xc ;
extern int yc ;

extern int deadline_man2 ;
extern Uint32 starttime;

extern int demdem ;


extern BaseObject bangthongbao ;

extern int giaidoansau_win;
extern int giaidoansau_lose;

extern int sau_lose;



extern SDL_Rect bo_bang;
extern BaseObject mo_am;
extern BaseObject tat_am;

extern bool amthanh ;
extern int chinham ;

extern int hien_bang_am ;
extern SDL_Rect loa;

extern int kich_chuot_sound ;









#endif // TOAN_CUC_






