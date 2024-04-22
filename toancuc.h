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


extern   TextObject thoi_gian_choi ;                                     // khai báo phông chữ thời gian chơi gamme
extern   TextObject da_giet;
extern   TextObject antien ;


extern   PlayerPower so_mang;                                            // hien thi so trai tym ung voi so mang
extern   Hotrobay phung;
extern   Hotrobay duocbay;

extern MENU menu_;


extern UINT so_qui_bi_giet;
extern UINT tong_tien;
extern int solanchet;
extern Uint32 thoigianhientai;
extern bool ho;

extern bool quit;            // Main loop control variables
extern bool gameOver;
extern bool isPaused;
extern bool win_game;
extern bool cai_time;

// Commented out because you can't declare a static variable extern
// extern static Uint32 last_time;
extern Uint32 last_time;

extern int dem222;           // Variables for various checks
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

#endif // TOAN_CUC_










//extern   UINT so_qui_bi_giet = 0 ;
//extern   UINT tong_tien = 0;
//extern   int solanchet = 0;
//extern   Uint32 thoigianhientai;
//extern   bool ho = false;
//
//extern   bool quit = false;                                  // vong lap chinh
//extern    bool gameOver = false ;
//extern   bool isPaused = false ;
//extern  bool win_game = false ;
//extern   bool cai_time = false ;
////extern   static Uint32 last_time = 0;
//extern   Uint32 last_time = 0;
//extern int dem222 = 0;             // check bi trung dan quai thuong
//extern  int dem2221 = 0;            // check bi trung dan quivuong
//extern  int dem_dam = 0;            // check bi an dam
//extern  int bi_uatuc_chem = 0;
//extern int qui_vuong_bichem = 0;
//extern  int boss_andan = 0;
//extern int maumau = 0;
//extern   int mauboss = 0;

