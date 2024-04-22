#include "HandleEvent.h"

using namespace std;

void handleEvents()
{
    while (SDL_PollEvent(&gEvent) != 0)
    {
        if (gEvent.type == SDL_QUIT) quit = true;

        else if (gEvent.type == SDL_KEYDOWN && gEvent.key.keysym.sym == SDLK_x)
        {
            thoigianhientai = SDL_GetTicks();
            ho = true;
        }
        else if ( gEvent.type == SDL_MOUSEBUTTONDOWN )
        {
            if ( gEvent.button.button == SDL_BUTTON_LEFT )
            {
                int xc = gEvent.motion.x, yc = gEvent.motion.y;

                if (SDLCommonFunc::check_chuot_chon(xc, yc, nutdung)) isPaused = true;    // tam dung
                else if (SDLCommonFunc::check_chuot_chon(xc, yc, tieptuc )) isPaused = false; // het tam dung

                else if (SDLCommonFunc::check_chuot_chon(xc, yc, restart) && isPaused == true) restartGame2(); // restart game ma khong phai choi lai

                else if (SDLCommonFunc::check_chuot_chon(xc, yc, cut)) quit = true;

                if ( gameOver )
                {
                    if (SDLCommonFunc::check_chuot_chon(xc, yc, playagain)) restartGame();
                    else if (SDLCommonFunc::check_chuot_chon(xc, yc, not_playagain)) quit = true;

                }
            }
        }
        player_nvc.XuLiXuKienBanPhim(gEvent, gRenderer); // Xử lí sự kiện bàn phím cho nhân vật chính
    }
}
