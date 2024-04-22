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
            if(!gameOver && !win_game )
            {
                render_game();
                check_va_cham1();
                ho_tro();
            }

            else if( gameOver && !win_game )
            {
                penaldo.Render( gRenderer, nullptr );
                SDL_RenderPresent( gRenderer );
                SDL_Delay ( 2000 );
                penaldo.free();
                gameover.Render( gRenderer , nullptr );
                SDL_RenderPresent( gRenderer );
            }
            else if ( win_game && !gameOver )
            {

                cout<<"an mup "<<endl;
                //boss_tan_xac.free();
                messi.SetRect ( 164, 0 );
                messi.Render( gRenderer );
                SDL_RenderPresent ( gRenderer );
                SDL_Delay ( 2000 );
                messi.free();
                anh_win.Render(gRenderer, nullptr);
                SDL_RenderPresent(gRenderer);
            }
        }
        else if( isPaused )
        {
            tamdung2.Render(gRenderer,nullptr);
            SDL_RenderPresent(gRenderer);
        }
    }

    close();
    return 0;
}
