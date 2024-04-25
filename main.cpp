#include "toancuc.h"
#include "game_functions.h"
#include "Game_Object.h"
#include "Init_Game.h"
#include "HandleEvent.h"
#include "Ho_tro.h"
#include "game_render.h"
#include "CHECK_VA_CHAM.h"
#include "CHE_DO_GAME.h"

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
            else if( gameOver && !win_game )
            {
                penaldo.Render( gRenderer, nullptr );
                SDL_RenderPresent( gRenderer );
                SDL_Delay ( 1000 );
                penaldo.free();
                gameover.Render( gRenderer, nullptr );
            }
            else if ( win_game && !gameOver )
            {
                messi.SetRect ( 164, 0 );
                messi.Render( gRenderer );
                SDL_RenderPresent ( gRenderer );
                SDL_Delay ( 1000 );
                messi.free();
                anh_win.Render(gRenderer, nullptr);
            }
        }
        else if( isPaused )
        {
            tamdung2.Render ( gRenderer,nullptr );
            SDL_RenderPresent ( gRenderer );
        }
    }
    close();
    return 0;
}
