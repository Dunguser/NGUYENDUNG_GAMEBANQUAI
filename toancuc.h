#ifndef  TOAN_CUC_
#define TOAN_CUC

#include <SDL.h>
#include "BaseObject.h"
#include "GAMEMAP.h"
#include "MainObject.h"
#include "vuno.h"
//#include "Sword.h"

extern BaseObject tamdung;
extern BaseObject tamdung2;
extern BaseObject anh_win;
extern SDL_Rect nutdung;
extern SDL_Rect tieptuc;
extern SDL_Rect playagain;
extern SDL_Rect restart;
extern SDL_Rect cut;
extern BaseObject anhdau;
extern BaseObject anhcho;
extern BaseObject gameover;
extern BaseObject gBackground;
extern GAMEMAP game_map;
extern MainObject player_nvc;
extern Sword kiem;

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern SDL_Event gEvent;


extern VUNO qui_no ;
extern VUNO nvc_no;
extern VUNO daulau ;
extern VUNO boss_tan_xac ;

#endif // TOAN_CUC_
