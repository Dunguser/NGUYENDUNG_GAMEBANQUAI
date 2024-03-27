#include<bits/stdc++.h>
#include<windows.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include "commonfunction.h"
#include "BaseObject.h"
#include "GAMEMAP.h"
#include "MainObject.h"
#include "ImpTimer.h"


using namespace std;

// 3con co so
bool Init();
bool LoadMedia();
void close();
//---
//window
SDL_Window* gWindow=NULL;
SDL_Renderer* gRenderer=NULL;
SDL_Event gEvent;

//-----------
// khai bao 1 em background
BaseObject gBackground;
//khai bao 1 em gamemap
GAMEMAP game_map;
//khai bao nhan vat ching
MainObject player_nvc;




int main(int messi,char*kaka[])
{

    //kiem tra khoi tao
    if(!Init()||!LoadMedia())
    {
        return -1000;
    }


    //xu li ban do: map

    // game_map.LoadMap("E:/bat_dau_game/MAP/map01.dat");
    game_map.LoadMap("E:/bat_dau_game/MAP/map02.dat");
    //game_map.LoadMap("E:/bat_dau_game/MAP/map03.dat");
    game_map.LoadTiles(gRenderer);


    //xu li nhan vat chinh
    player_nvc.LoadMainImg("E:/bat_dau_game/IMG/CHAY_PHAI_SUNG1.png",gRenderer);

    player_nvc.Set_Clips_chay();





    // vong lap chinh
    bool quit=false;

    while(!quit)
    {
        while(SDL_PollEvent(&gEvent)!=0)
        {
            if(gEvent.type==SDL_QUIT)
            {
                quit=true;
            }
            //nhan vat chinh, ban phim
            player_nvc.XuLiXuKienBanPhim(gEvent,gRenderer);
        }

        // clear renderer
        SDL_SetRenderDrawColor(gRenderer,255,255,255,255);
        SDL_RenderClear(gRenderer);
        //-----------------

        // in anh background
        gBackground.Render(gRenderer,NULL);

        //xu li di chuyen, va cham map
        MAP map_data=game_map.GetMap();

        // xu li ban dan

        player_nvc.XU_LI_BAN_DAN(gRenderer,SCREEN_WIDTH/3 ,SCREEN_HEIGHT/3,map_data);


        //

        //xu li map di chuyen theo nhan vat
        player_nvc.SetMapXY(map_data.start_x_,map_data.start_y_);

        //hien nhan vat chinh
        player_nvc.ShowMain(gRenderer);
        player_nvc.DiChuyenNhanVat(map_data);

        // cap nhat vi tri moi cho start_x_, start_y_
        game_map.SetMap(map_data);
        //ve ban do
        game_map.DrawMap(gRenderer);


        SDL_RenderPresent(gRenderer);//xuat ra man hinh hien tai





        //roi xuong ho chet luon
        if(player_nvc.get_roi_xuong_vuc()==true)
        {
            //chat gpt
            const wchar_t* wideString = L"   GameOver \nYou fall into the abyss and die";
            int bufferSize = WideCharToMultiByte(CP_UTF8, 0, wideString, -1, NULL, 0, NULL, NULL);
            char* buffer = new char[bufferSize];
            WideCharToMultiByte(CP_UTF8, 0, wideString, -1, buffer, bufferSize, NULL, NULL);
            if (MessageBox(NULL, buffer, "Info", MB_OK | MB_ICONSTOP) == IDOK)
            {
                close();
                SDL_Quit();
                delete[] buffer;
                return 0;
            }
        }//-----------------------------------------------------------------------------------

        // thoi gian cham lai
        ImpTimer fps_timer;
        int real_imp_time=fps_timer.get_ticks();
        int time_one_frame=1000/FRAME_PER_SECOND;
        if(real_imp_time<time_one_frame)
        {
            int delay_time=time_one_frame-real_imp_time;
            if(delay_time>0)
            {
                SDL_Delay(delay_time);
            }
        }//------------------------------------------------------------------------------
    }

    close();
    return 0;
}







bool Init()
{
    bool success=true;
    if(SDL_Init(SDL_INIT_EVERYTHING)<0)
    {
        cout<<"unable to initialize "<<SDL_GetError()<<endl;
        success=false;
    }
    else
    {
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");
        gWindow=SDL_CreateWindow("Nguyen Xuan Dung",
                                 SDL_WINDOWPOS_UNDEFINED,
                                 SDL_WINDOWPOS_UNDEFINED,
                                 SCREEN_WIDTH,
                                 SCREEN_HEIGHT,
                                 SDL_WINDOW_SHOWN);
        if(gWindow==NULL)
        {
            cout<<"failed0000"<<SDL_GetError()<<endl;
            success=false;
        }
        else
        {
            gRenderer=SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_ACCELERATED);
            if(gRenderer==NULL)
            {
                success=false;
            }
            else
            {
                SDL_SetRenderDrawColor(gRenderer,255,255,255,255);
                int imgflag=IMG_INIT_PNG;
                if(!(IMG_Init(imgflag)&imgflag))
                {
                    cout<<"failed111111"<<IMG_GetError();
                    success=false;
                }
                int lllll=IMG_INIT_JPG;
                if(!(IMG_Init(lllll)&lllll))
                {
                    cout<<"failed111111"<<IMG_GetError();
                    success=false;
                }
            }
        }
    }
    return success;
}

bool LoadMedia()
// tai anh nen
{
    //if(!gBackground.LoadImage("E:/bat_dau_game/IMG/G_BACK_GROUND_2.png",gRenderer))
    if(!gBackground.LoadImage("E:/bat_dau_game/IMG/G_BACK_GROUND_NET.jpg",gRenderer))
    {
        cout<<"failed to load background";
        return 0;
    }
    return 1;
}

void close()
{
    SDL_DestroyWindow(gWindow);
    gWindow=NULL;
    SDL_DestroyRenderer(gRenderer);
    gRenderer=NULL;

    SDL_Quit();
    IMG_Quit();
}
