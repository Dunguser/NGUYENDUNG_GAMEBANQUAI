#include "game_functions.h"

using namespace std;

bool Init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING)<0) return false;
    else
    {
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");

        gWindow = SDL_CreateWindow("NGUYEN XUAN DUNG 009 ",
                                   SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   SCREEN_WIDTH,
                                   SCREEN_HEIGHT,
                                   SDL_WINDOW_SHOWN);

        if(gWindow==nullptr) return false;
        else
        {
            gRenderer=SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_ACCELERATED);
            if(gRenderer==nullptr) return false;
            else
            {
                SDL_SetRenderDrawColor(gRenderer,255,255,255,255);
                int imgflag=IMG_INIT_PNG;
                if(!(IMG_Init(imgflag)&imgflag)) return false;
                int lllll=IMG_INIT_JPG;
                if(!(IMG_Init(lllll)&lllll)) return false;

                if(TTF_Init()==-1)
                {
                    printf(TTF_GetError());
                    return false ;
                }
                //Initialize SDL_mixer
                if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                    return false;
                }
            }
        }
    }
    return true;
}

bool LoadMedia() // Tải tài nguyên game
{
    if(!gBackground.LoadImage("IMG/G_BACK_GROUND_NET.jpg",gRenderer))return 0;
    if(!anhdau.LoadImage("IMG/botro/anhdau.png",gRenderer))
    {
        cout<< IMG_GetError();
        return 0;
    }
    if(!tamdung.LoadImage("IMG/botro/nuttamdung.png",gRenderer))
    {
        cout<< IMG_GetError() ;
        return 0;
    }
    if(!tamdung2.LoadImage("IMG/botro/anh_exit.png",gRenderer))
    {
        cout<< IMG_GetError() ;
        return 0;
    }
    if(!anhcho.LoadImage("IMG/botro/anhcho.jpg",gRenderer))
    {
        cout<<IMG_GetError() ;
        return 0;
    }
    if(!gameover.LoadImage("IMG/botro/gameover.png",gRenderer))
    {
        cout<<IMG_GetError() ;
        return 0;
    }
    if(!anh_win.LoadImage("IMG/botro/win.png",gRenderer))
    {
        cout<<IMG_GetError();
        return 0;
    }
    if(!messi.LoadImage("IMG/botro/messi.png",gRenderer))
    {
        cout<<IMG_GetError();
        return 0;
    }
    if(!penaldo.LoadImage("IMG/botro/pen.png",gRenderer))
    {
        cout<<IMG_GetError()<<endl;
    }
    if( !gBackground2.LoadImage("MAP/G_BACK_GROUND_2.png",gRenderer))
    {
        cout<<IMG_GetError()<<endl;
        return 0;
    }
    if( !gBackground3.LoadImage("MAP/G_BACK_GROUND_3.png",gRenderer))
    {
        cout<<IMG_GetError()<<endl;
        return 0;
    }
    if( !bangthongbao.LoadImage("IMG/botro/bangthongbao.png",gRenderer))
    {
        cout<<IMG_GetError()<<endl;
        return 0;
    }

    gFont = TTF_OpenFont ("FONT/turok.ttf",28);
    font_bao = TTF_OpenFont ("FONT/iCielCadena.otf",34);
    if(font_bao == nullptr)
    {
        cout<<TTF_GetError();
        return 0;
    }
    if( gFont == nullptr )
    {
        cout<<TTF_GetError();
        return 0;
    }

    nhacnen = Mix_LoadMUS("sound/nhacnen.mp3");
    quaibichem = Mix_LoadWAV ("sound/bichem.mp3");
    if(nhacnen == nullptr || quaibichem == nullptr )
    {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
        return 0;
    }
    bom = Mix_LoadWAV("sound/Bomb1.wav");
    danquino = Mix_LoadWAV("sound/danquino.wav");
    tiengdam = Mix_LoadWAV("sound/tiengandam.mp3");
    daulauno = Mix_LoadWAV("sound/explosion.wav");
    vakiem = Mix_LoadWAV("sound/vakiem.mp3");
    return 1;
}
void close() // Đóng game
{
    SDL_DestroyWindow( gWindow );
    gWindow = nullptr;
    SDL_DestroyRenderer( gRenderer );
    gRenderer = nullptr;
    TTF_CloseFont(gFont);
    gFont = nullptr;

    Mix_FreeMusic(nhacnen);
    nhacnen = nullptr ;
    Mix_FreeChunk(bom);
    bom = nullptr;
    Mix_FreeChunk(danquino);
    danquino = nullptr;
    Mix_FreeChunk(quaibichem);
    quaibichem = nullptr ;
    Mix_FreeChunk(tiengdam);
    tiengdam = nullptr;
    Mix_FreeChunk(vakiem);
    vakiem = nullptr;

    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();

    gBackground.free();
    anhdau.free();
    player_nvc.free();
    quivuong.free();
    tamdung.free();
    tamdung2.free();
    anhcho.free();
    gameover.free();

    kiem.free();

    for ( int i = 0 ; i < 6 ; i++ ) player_nvc.cucmau[i].free();
    for ( int i = 0; i< 4 ; i++) quivuong.mau_boss[i].free();

    qui_no.free() ;
    nvc_no.free();
    so_mang.free();
    phung.free();
    duocbay.free( );

    for (auto obj : threats_list)       //giai phong bo nho da cap phat
    {
        obj->free();
        obj = nullptr;
    }
    threats_list.clear();               // xóa vector


}


