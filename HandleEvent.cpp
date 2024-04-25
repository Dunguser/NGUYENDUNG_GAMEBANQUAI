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

                else if ( win_game )
                {
                    if (SDLCommonFunc::check_chuot_chon(xc, yc, win_nghi)) quit = true;
                    else if (SDLCommonFunc::check_chuot_chon(xc, yc, level2))
                    {
                        level_2 = true;
                        level_1 = false;
                        win_game = false;

                        quivuong.set_solan_boss_andan (0);
                        quivuong.sethanglanh ( false );

                        player_nvc.kichhoathangnong ( false );
                        player_nvc.kichhoatchongchong ( true );
                        player_nvc.setchobay ( true );
                        player_nvc.set_vitri_nvc ( 6800, 2700 );

                        quivuong.set_x_bosspos ( 7800 );
                        quivuong.set_y_bosspos ( 2500 );
                    }
                }

            }
        }
        player_nvc.XuLiXuKienBanPhim(gEvent, gRenderer); // Xử lí sự kiện bàn phím cho nhân vật chính
    }
}
