#ifndef  TOAN_CUC_
#define TOAN_CUC

#include <SDL.h>
#include "BaseObject.h"
#include "GAMEMAP.h"
#include "MainObject.h"
//#include "Sword.h"

extern BaseObject tamdung;
extern BaseObject tamdung2;
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

#endif // TOAN_CUC_
