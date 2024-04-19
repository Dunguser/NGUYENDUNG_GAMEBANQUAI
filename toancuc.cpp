#include "toancuc.h"

// Khởi tạo các biến toàn cục
BaseObject tamdung;
BaseObject tamdung2;
SDL_Rect nutdung = {SCREEN_WIDTH - 80, 0, 80, 78};
SDL_Rect tieptuc = {625, 460 - 32, 115, 40};
SDL_Rect playagain = {450, 800, 120, 71};
SDL_Rect restart = {600, 740, 160 - 32, 60};
SDL_Rect cut = {625, 670 - 32, 120, 30};
BaseObject anhdau;
BaseObject anhcho;
BaseObject gameover;
BaseObject gBackground;
GAMEMAP game_map;
MainObject player_nvc;
Sword kiem;
SDL_Window * gWindow = nullptr;
SDL_Renderer * gRenderer = nullptr;
SDL_Event gEvent;
