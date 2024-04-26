#include "win_or_lose.h"


void win()
{
    if(giaidoansau_win == 1)
    {
        messi.SetRect ( 164, 0 );
        messi.Render( gRenderer );
        SDL_RenderPresent ( gRenderer );
        SDL_Delay ( 500 );
        giaidoansau_win++;
    }
    if ( giaidoansau_win == 2 )
    {
        bangthongbao.SetRect ( 490, 380 );
        bangthongbao.Render( gRenderer, nullptr);
        SDL_RenderPresent ( gRenderer );

        giaidoansau_win ++ ;
    }
    if(giaidoansau_win == 3)
    {
        SDL_Color kaka = { 255, 255, 255 };
        if(!level_2)
        {
            string a = "KILL : " + to_string(so_qui_bi_giet);
            string b = "MONEY : " + to_string(tong_tien);
            string c = "TIME : "+ to_string ( time_play);
            soquaidie.loadFromRenderedText(a,kaka );
            sotienanduoc.loadFromRenderedText(b, kaka);
            tongthoigianchoi.loadFromRenderedText(c, kaka);

            soquaidie.render ( 520, 410 );
            sotienanduoc.render ( 520, 465 );
            tongthoigianchoi.render (520, 515 );
        }
        else
        {
            string b = "TIME : " + to_string ( 180 - time_play);
            tongthoigianchoi.loadFromRenderedText (b,kaka);
            tongthoigianchoi.render(520,410);
        }
        SDL_RenderPresent(gRenderer);
        SDL_Delay ( 1000);
        giaidoansau_win ++ ;

    }
    if(giaidoansau_win == 4)
    {
        anh_win.Render( gRenderer, nullptr );
        SDL_RenderPresent ( gRenderer );
    }

}
void lose()
{
    if(giaidoansau_lose == 1)
    {
        penaldo.SetRect(0,0);
        penaldo.Render( gRenderer, nullptr );
        SDL_RenderPresent( gRenderer );
        SDL_Delay ( 500 );
        giaidoansau_lose ++;
    }
    if ( giaidoansau_lose == 2 )
    {
        bangthongbao.SetRect ( 490, 380 );
        bangthongbao.Render( gRenderer, nullptr);
        SDL_RenderPresent ( gRenderer );

        giaidoansau_lose ++ ;
    }
    if(giaidoansau_lose == 3)
    {
        SDL_Color kaka = { 255, 255, 255 };
        if(!level_2)
        {
            string a = "KILL : " + to_string(so_qui_bi_giet);
            string b = "MONEY : " + to_string(tong_tien);
            string c = "TIME : "+ to_string ( time_play);
            soquaidie.loadFromRenderedText(a,kaka );
            sotienanduoc.loadFromRenderedText(b, kaka);
            tongthoigianchoi.loadFromRenderedText(c, kaka);

            soquaidie.render ( 520, 410 );
            sotienanduoc.render ( 520, 465 );
            tongthoigianchoi.render (520, 515 );
        }
        else
        {
            string b = "TIME : " + to_string ( 180 - time_play);
            tongthoigianchoi.loadFromRenderedText (b,kaka);
            tongthoigianchoi.render(520,410);
        }
        SDL_RenderPresent(gRenderer);
        SDL_Delay ( 1000);
    }
    if(giaidoansau_lose == 4)
    {
        gameover.Render( gRenderer, nullptr );
        SDL_RenderPresent (gRenderer);
    }
}
