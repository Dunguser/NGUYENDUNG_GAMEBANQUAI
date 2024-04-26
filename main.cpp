#include "toancuc.h"
#include "game_functions.h"
#include "Game_Object.h"
#include "Init_Game.h"
#include "HandleEvent.h"
#include "Ho_tro.h"
#include "game_render.h"
#include "CHECK_VA_CHAM.h"
#include "CHE_DO_GAME.h"
#include "win_or_lose.h"

using namespace std;

int main(int argc,char* argv[] )
{
    InitGame();
    while(!quit)
    {
        handleEvents();
        if(!isPaused )
        {
            if( !gameOver && !win_game )
            {
                if( level_1 == true )
                {
                    render_game();
                    check_va_cham1();
                    ho_tro();
                }
                else if ( level_2 == true )
                {
                    render_game_2();
                    check_va_cham2();
                    ho_tro_2();
                }
                else if ( level_3 == true )
                {
                    render_game_3();
                    check_va_cham3();
                    ho_tro_3();
                }
            }
            else if ( win_game ) win();
            else if ( gameOver ) lose();
        }
        else if( isPaused )
        {
            if( hien_bang_am == 1)
            {
                tamdung2.Render ( gRenderer,nullptr );
                SDL_RenderPresent ( gRenderer );
            }
            else if (hien_bang_am == 2)
            {
                mo_am.SetRect((SCREEN_WIDTH - 260)/2, (SCREEN_HEIGHT-260)/2);
                mo_am.Render ( gRenderer);
                SDL_RenderPresent (gRenderer);
            }
            else if (hien_bang_am == 3)
            {
                tat_am.SetRect((SCREEN_WIDTH - 260)/2, (SCREEN_HEIGHT-260)/2);
                tat_am.Render ( gRenderer);
                SDL_RenderPresent (gRenderer);
            }

        }
    }
    close();
    return 0;
}
