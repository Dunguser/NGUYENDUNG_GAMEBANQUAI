#include "HandleEvent.h"

using namespace std;

void handleEvents()
{
    while ( SDL_PollEvent (&gEvent) != 0)
    {
        if ( gEvent.type == SDL_QUIT ) quit = true;

        else if ( gEvent.type == SDL_KEYDOWN && gEvent.key.keysym.sym == SDLK_x )
        {
            thoigianhientai = SDL_GetTicks();
            ho = true;
        }
        else if ( gEvent.type == SDL_MOUSEBUTTONDOWN )
        {
            if ( gEvent.button.button == SDL_BUTTON_LEFT )
            {
                xc = gEvent.motion.x;
                yc = gEvent.motion.y;
                if (SDLCommonFunc::check_chuot_chon(xc, yc, nutdung)) isPaused = true;    // tam dung
                if (isPaused)
                {
                    if(!amthanh)
                    {
                        if (SDLCommonFunc::check_chuot_chon(xc, yc, tieptuc )) isPaused = false;    // het tam dung
                        else if (SDLCommonFunc::check_chuot_chon(xc, yc, restart) ) restartGame2(); // restart game ma khong phai choi lai
                        else if (SDLCommonFunc::check_chuot_chon(xc, yc, cut)) quit = true;
                        else if (SDLCommonFunc::check_chuot_chon(xc, yc, tatam))
                        {
                            amthanh = true;
                            hien_bang_am = 2;
                        }
                    }
                    else
                    {

                        if(SDLCommonFunc::check_chuot_chon(xc,yc, loa))
                        {
                            cout<<"kaka"<<endl;
                            if(hien_bang_am == 2)
                            {
                                hien_bang_am =3;
                                dieuChinhAmLuong(0);
                            }
                            else if( hien_bang_am == 3)
                            {
                                hien_bang_am =2;
                                dieuChinhAmLuong(MIX_MAX_VOLUME);
                            }
                        }
                        else if(SDLCommonFunc::check_chuot_chon(xc, yc, nutdung))
                        {
                            amthanh = false;
                            hien_bang_am = 1;
                        }
                    }


                }

                if ( gameOver )
                {
                    if( giaidoansau_lose == 4 )
                    {
                        if (SDLCommonFunc::check_chuot_chon(xc, yc, playagain)) restartGame();
                        else if (SDLCommonFunc::check_chuot_chon(xc, yc, not_playagain)) quit = true;
                    }
                    else if ( giaidoansau_lose == 3 )
                    {
                        if(SDLCommonFunc::check_chuot_chon(xc,yc, bo_bang))
                        {
                            sau_lose = 0;
                            giaidoansau_lose ++;
                        }
                    }

                }

                else if ( win_game ) xulikhi_win();
            }
        }
        player_nvc.XuLiXuKienBanPhim(gEvent, gRenderer);    // Xử lí sự kiện bàn phím cho nhân vật chính
    }
}


void xulikhi_win()
{
    if ( SDLCommonFunc::check_chuot_chon(xc, yc, win_nghi) ) // quay lai man 1
    {
        restartGame2();
        win_game = false;
        giaidoansau_lose = 1 ;
        sau_lose = 1;
    }
    else if ( SDLCommonFunc::check_chuot_chon(xc, yc, level2) && level_1 == true ) // man 2
    {
        level_2 = true;
        level_1 = false;
        win_game = false;

        quivuong.set_solan_boss_andan (0);
        quivuong.sethanglanh ( false );

        player_nvc.kichhoathangnong ( false );
        player_nvc.kichhoatchongchong ( true );
        player_nvc.setchobay ( true );
        player_nvc.set_vitri_nvc ( 7100, 2700 );

        quivuong.set_x_bosspos ( 7800 );
        quivuong.set_y_bosspos ( 2500 );

        giaidoansau_win = 1;
        sau_lose = 1;
    }
    else if ( SDLCommonFunc::check_chuot_chon(xc, yc, win_nghi) && level_2 == true) // quay lai man 1
    {
        restartGame2();
        win_game = false;
        giaidoansau_lose = 1;
    }
    else if ( SDLCommonFunc::check_chuot_chon(xc, yc, level2) && level_2 == true ) // man 2
    {
        level_2 = false;
        level_3 = true;
        win_game = false;

        quivuong.set_solan_boss_andan (0);
        quivuong.sethanglanh ( false );

        player_nvc.kichhoathangnong ( false );
        player_nvc.kichhoatchongchong ( false );
        player_nvc.setchobay ( false );
        player_nvc.set_vitri_nvc ( 6800, 1500 );

        quivuong.set_x_bosspos ( 7100 );
        quivuong.set_y_bosspos ( 1500 );

        giaidoansau_win = 1;
        sau_lose = 1;
    }
    else if ( SDLCommonFunc::check_chuot_chon(xc, yc, win_nghi) && level_3 == true) // quay lai man 1
    {
        restartGame2();
        win_game = false;
        giaidoansau_lose = 1;
        sau_lose = 1;
    }

}

void dieuChinhAmLuong(int volume)
{
    // Đặt âm lượng của âm thanh theo giá trị volume
    Mix_Volume(-1, volume); // -1: Tất cả các kênh
    Mix_VolumeMusic(volume);
}

void xulitatam()
{

}



