#include "win_or_lose.h"


void win()
{
    messi.SetRect ( 164, 0 );
    messi.Render( gRenderer );
    SDL_RenderPresent ( gRenderer );
    SDL_Delay ( 1000 );
    //messi.free();
    anh_win.Render(gRenderer, nullptr);
}
void lose()
{
    penaldo.SetRect(0,0);
    penaldo.Render( gRenderer, nullptr );
    SDL_RenderPresent( gRenderer );
    SDL_Delay ( 1000 );
    //penaldo.free();
    gameover.Render( gRenderer, nullptr );
}
