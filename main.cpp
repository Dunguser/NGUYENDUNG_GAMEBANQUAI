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
#include "ThreatsObject.h"


using namespace std;

// 3 con co so
bool Init();
bool LoadMedia();
void close();
//window
SDL_Window* gWindow=NULL;
SDL_Renderer* gRenderer=NULL;
SDL_Event gEvent;
// khai bao 1 em background
BaseObject gBackground;
//khai bao 1 em gamemap
GAMEMAP game_map;
//khai bao nhan vat chin
MainObject player_nvc;



void load_tat_ca_qui(SDL_Renderer* des);

//tạo lập lớp threart object // lớp quỉ
vector<ThreatsObject*>Make_Threat_List()
{
    vector<ThreatsObject*> list_threats;
    ThreatsObject* qui_tuan_tra = new ThreatsObject[30];

    for(int i=0; i< 30; i++)
    {
        ThreatsObject* p_qui = qui_tuan_tra + i ;
        if(p_qui!=nullptr)
        {
            p_qui->LoadImage( "IMG/quai_di_trai.png", gRenderer );
            p_qui->set_clips();
            // cai dat vi tri xuat hien
            if(i<10)
            {
                p_qui->set_x_quipos(350+i*200);
                p_qui->set_y_quipos(100) ;
            }
            else if(i>=10&&i<20)
            {
                p_qui->set_x_quipos(600+i*200);
                p_qui->set_y_quipos(500) ;
            }
            else
            {
                p_qui->set_x_quipos(100+i*50);
                p_qui->set_y_quipos(800) ;
            }

            // gioi han trai,phai
            int gioi_han_trai = p_qui->get_x_quipos()-120;
            int gioi_han_phai = p_qui->get_x_quipos()+120;

            p_qui->set_gioi_han_dichuyen( gioi_han_trai, gioi_han_phai );
            p_qui->set_trang_thai_trai(1);
            list_threats.push_back( p_qui );
        }
    }
    return list_threats;
}



int main(int messi,char*kaka[])
{
    //kiem tra khoi tao
    if(!Init()||!LoadMedia())
    {
        return -1000;
    }

    //xu li ban do: map
    game_map.LoadMap("MAP/map02.dat");
    game_map.LoadTiles(gRenderer);

    //xu li nhan vat chinh
    player_nvc.LoadMainImg("IMG/CHAY_PHAI_SUNG1.png",gRenderer);
    player_nvc.Set_Clips_chay();

    // khai bao 1 dong quai vat
    vector<ThreatsObject*>threats_list = Make_Threat_List();
    load_tat_ca_qui(gRenderer);
    // vong lap chinh
    bool quit=false;
    while(!quit)
    {
        while( SDL_PollEvent( &gEvent ) != 0 )
        {
            if( gEvent.type == SDL_QUIT)
            {
                quit=true;
            }
            //nhan vat chinh, ban phim
            player_nvc.XuLiXuKienBanPhim( gEvent, gRenderer );
        }
        // clear renderer
        SDL_SetRenderDrawColor( gRenderer, 255, 255, 255, 255);
        SDL_RenderClear( gRenderer );
        // in anh background
        gBackground.Render( gRenderer, NULL );

        //xu li di chuyen, va cham map
        MAP map_data=game_map.GetMap();

        // xu li ban dan
        player_nvc.XU_LI_BAN_DAN( gRenderer, SCREEN_WIDTH/2.5, SCREEN_HEIGHT/2.5, map_data);


        //

        //xu li map di chuyen theo nhan vat
        player_nvc.SetMapXY( map_data.start_x_, map_data.start_y_);

        //hien nhan vat chinh
        player_nvc.ShowMain( gRenderer ) ;
        player_nvc.DiChuyenNhanVat( map_data );

        // cap nhat vi tri moi cho start_x_, start_y_
        game_map.SetMap( map_data );
        //ve ban do
        game_map.DrawMap( gRenderer );

        // xu li quai vat
        for(int i=0; i< (int)threats_list.size(); i++)
        {
            ThreatsObject* p_qui=threats_list.at(i);
            if(p_qui!=nullptr)
            {
                p_qui->SetMapXY( map_data.start_x_, map_data.start_y_ );
                p_qui->Di_chuyen_trong_pham_vi( gRenderer, map_data );
                p_qui->DICHUYEN_QUI( map_data );

                p_qui->ShowQui( gRenderer );
            }
        }



        SDL_RenderPresent(gRenderer);//xuat ra man hinh hien tai




        // thoi gian cham lai ---------------------------------------------------------
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
        }
        //------------------------------------------------------------------------------
    }

    //giai phong bo nho da cap phat
    for (auto obj : threats_list)
    {
        //delete obj;
        obj->free();
        obj = nullptr;
    }
    // xóa vector
    threats_list.clear();

    close();

    return 0;
}

 void load_tat_ca_qui(SDL_Renderer* des)
 {
     tat_ca_anh_qui[ditrai].LoadImage("IMG/quai_di_trai.png",des);
     tat_ca_anh_qui[diphai].LoadImage("IMG/quai_di_phai.png",des);

 }


bool Init()
{
    bool success=true;

    if(SDL_Init(SDL_INIT_EVERYTHING)<0)
    {
        cout<<" unable to initialize "<<SDL_GetError()<<endl;
        success=false;
    }
    else
    {
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");
        gWindow=SDL_CreateWindow("NGUYEN XUAN DUNG 009 ",
                                 SDL_WINDOWPOS_UNDEFINED,
                                 SDL_WINDOWPOS_UNDEFINED,
                                 SCREEN_WIDTH,
                                 SCREEN_HEIGHT,
                                 SDL_WINDOW_SHOWN);
        if(gWindow==NULL)
        {
            cout<<" failed0000 " << SDL_GetError() <<endl;
            success=false;
        }
        else
        {
            gRenderer=SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_ACCELERATED);
            if(gRenderer==NULL)
            {
                cout<<"-------failed to create RENDERER "<<SDL_GetError()<<endl;
                success=false;
            }
            else
            {
                SDL_SetRenderDrawColor(gRenderer,255,255,255,255);
                int imgflag=IMG_INIT_PNG;
                if(!(IMG_Init(imgflag)&imgflag))
                {
                    cout<<"failed111111" <<IMG_GetError()<<endl;
                    success=false;
                }
                int lllll=IMG_INIT_JPG;
                if(!(IMG_Init(lllll)&lllll))
                {
                    cout<<"failed o" <<IMG_GetError()<<endl;
                    success=false;
                }
            }
        }
    }
    return success;
}
bool LoadMedia()// tai anh nen
{
    if(!gBackground.LoadImage("IMG/G_BACK_GROUND_NET.jpg",gRenderer))
    {
        cout<<"failed to load background";
        return 0;
    }
    return 1;
}
void close()
{
    SDL_DestroyWindow(gWindow);
    gWindow=nullptr;
    SDL_DestroyRenderer(gRenderer);
    gRenderer=nullptr;

    SDL_Quit();
    IMG_Quit();
}
//roi xuong ho chet luon
//        if(player_nvc.get_roi_xuong_vuc()==true)
//        {
//            //chat gpt
//            const wchar_t* wideString = L"   GameOver \nYou fall into the abyss and die";
//            int bufferSize = WideCharToMultiByte(CP_UTF8, 0, wideString, -1, NULL, 0, NULL, NULL);
//            char* buffer = new char[bufferSize];
//            WideCharToMultiByte(CP_UTF8, 0, wideString, -1, buffer, bufferSize, NULL, NULL);
//            if (MessageBox(NULL, buffer, "Info", MB_OK | MB_ICONSTOP) == IDOK)
//            {
//                close();
//                SDL_Quit();
//                delete[] buffer;
//                return 0;
//            }
//        }//-----------------------------------------------------------------------------------
