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
#include "all_anh_qui.h"
#include "vuno.h"
#include "TextObject.h"
#include "PlayerPower.h"
#include "MENU.h"
#include "kiemquay.h"
#include "QUIVUONG.h"
#include "all_anh_nvc.h"
#include "toancuc.h"
using namespace std;

bool Init();
bool LoadMedia();
void close();

QUIVUONG quivuong;

void load_tat_ca_qui ( SDL_Renderer* des );         // load tat ca cac anh cua qui
vector<ThreatsObject*> Make_Threat_List();          //tạo lập lớp threart object // lớp quỉ
void load_all_boss (SDL_Renderer* des);
//void load_all_dan_ ( SDL_Renderer* des );
void load_all_main (SDL_Renderer* des);



void khoitaovuno( VUNO& qui_no);
void khoitaonhanvatchinh_no( VUNO& nvc_no );
void khoitaonodaulau ( VUNO & daulau);
void khoitaonoboss ( VUNO& boss_die);

int main(int argc,char* argv[] )
{
    if(!Init()||!LoadMedia()) return -1000;         //kiem tra khoi tao
    anhcho.SetRect(160,50);
    anhcho.Render(gRenderer,nullptr);
    SDL_RenderPresent(gRenderer);
    SDL_Delay(1000);                                // ảnh chờ đầu tiên
    anhdau.Render(gRenderer,nullptr);                // anh dau
    tamdung.SetRect(SCREEN_WIDTH - 80, 0 );
    tamdung2.SetRect(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 3) ;
    gameover.SetRect ( 240,65 );

    Mix_PlayMusic(nhacnen, -1);                     // nhac nen
    game_map.LoadMap("MAP/map04.dat");              //xu li ban do: map
    game_map.LoadTiles( gRenderer );

    player_nvc.LoadMainImg("IMG/CHAY_PHAI_SUNG.png",gRenderer);     //xu li nhan vat chinh
    player_nvc.Set_Clips_chay();
    player_nvc.loadamthanh_nvc();

    quivuong.LoadImg_boss("IMG/QUAI/qui_chay_trai.png", gRenderer);
    quivuong.set_clips();
    quivuong.set_x_bosspos ( 7400 );
    quivuong.set_y_bosspos ( 2500 );

    //load_all_dan_(gRenderer);
    vector<ThreatsObject*> threats_list = Make_Threat_List();       // khai bao 1 dong quai vat
    load_tat_ca_qui ( gRenderer );
    load_all_boss ( gRenderer );

    //load_all_main ( gRenderer );


    khoitaovuno(qui_no);
    khoitaonhanvatchinh_no(nvc_no);
    khoitaonodaulau (daulau);
    khoitaonoboss ( boss_tan_xac);


    TextObject thoi_gian_choi ;                                     // khai báo phông chữ thời gian chơi gamme
    thoi_gian_choi.setcolor (TextObject :: RED_TEXT );              //thoi_gian_choi.LoadFromRenderText( gFont, gRenderer);
    TextObject da_giet;
    da_giet.setcolor (TextObject :: RED_TEXT);                       //da_giet.LoadFromRenderText( gFont, gRenderer );
    UINT so_qui_bi_giet = 0 ;
    TextObject antien ;
    antien.setcolor (TextObject :: RED_TEXT );                      //antien.LoadFromRenderText (gFont,gRenderer );
    UINT tong_tien = 0;

    PlayerPower so_mang;                                            // hien thi so trai tym ung voi so mang
    so_mang.set_chi_so_mang(1);
    so_mang.Init( gRenderer, "IMG/tym.png" );
    int solanchetmax = so_mang.get_chi_so_mang();                   // cout<<"so mang "<<solanchetmax<<endl;

    Hotrobay phung;
    phung.init(gRenderer,"IMG/phung.png");
    phung.SetPos(800,10);

    Hotrobay duocbay;
    duocbay.init(gRenderer,"IMG/congcubay.png");
    duocbay.SetPos(900,10);

    int solanchet = 0;
    Uint32 thoigianhientai;
    bool ho = false;
    //
    Sword kiem = player_nvc.getkiem();
    if(!kiem.Loadkiem("IMG/kiem.png",gRenderer))
    {
        cout<< "haphuong" ;
        return -100000;
    }

    bool quit = false;                                  // vong lap chinh

    bool gameOver = false ;
    bool isPaused = false ;
    bool win_game = false ;
    bool cai_time = false ;

    MENU menu_;                                         //menu
    menu_.SetRect ( SCREEN_WIDTH / 2 - 180, SCREEN_HEIGHT / 3 - 60 );

    player_nvc.load_cucmau ( gRenderer);
    int maumau = 0;


    int ret_menu = menu_.showmenu ( gRenderer, gFont2 );
    if(ret_menu != 1) quit = true;



    static Uint32 last_time = 0;
    int dem222 = 0;             // check bi trung dan quai thuong
    int dem2221 = 0;            // check bi trung dan quivuong
    int dem_dam = 0;            // check bi an dam

    while(!quit)
    {
        while( SDL_PollEvent( &gEvent ) != 0 )
        {
            if( gEvent.type == SDL_QUIT) quit = true;
            else if ( gEvent.type == SDL_KEYDOWN && gEvent.key.keysym.sym == SDLK_x )
            {
                thoigianhientai = SDL_GetTicks();
                ho = true;
            }
            else if( gEvent.type == SDL_MOUSEBUTTONDOWN)
            {
                if(gEvent.button.button == SDL_BUTTON_LEFT)
                {
                    int xc = gEvent.motion.x, yc = gEvent.motion.y;
                    if(SDLCommonFunc::check_chuot_chon(xc,yc,nutdung))
                    {
                        isPaused = true;
                    }
                    else if(SDLCommonFunc :: check_chuot_chon(xc, yc, tieptuc) )
                    {
                        isPaused = false ;
                    }
                    else if( SDLCommonFunc :: check_chuot_chon(xc, yc, restart) )
                    {
                        cout<<"loi choi lai 1"<<endl;
                        gameOver = false;
                        game_map.LoadMap("MAP/map04.dat");                      //xu li ban do: map
                        player_nvc.LoadMainImg("IMG/CHAY_PHAI_SUNG.png",gRenderer);
                        game_map.LoadTiles( gRenderer );
                        Mix_PlayMusic(nhacnen, -1);                             // nhac nen
                        player_nvc.Set_Clips_chay();
                        player_nvc.loadamthanh_nvc();
                        player_nvc.set_solantrungdan(0);
                        player_nvc.set_vitri_nvc ( 500, 500);
                        quivuong.set_clips();
                        quivuong.set_x_bosspos ( 8800 );
                        quivuong.set_y_bosspos ( 2500 );

                        threats_list = Make_Threat_List();                      // khai bao 1 dong quai vat
                        so_qui_bi_giet = 0 ;
                        tong_tien = 0;
                        player_nvc.set_tienanduoc(0);
                        so_mang.set_chi_so_mang(1);
                        solanchetmax = so_mang.get_chi_so_mang();               // cout<<"so mang "<<solanchetmax<<endl;
                        solanchet = 0;
                        phung.SetPos(800,10);
                        duocbay.SetPos(900,10);
                        cai_time = true;
                        maumau = 0;
                        player_nvc.show_cucmau( gRenderer, maumau);
                        player_nvc.kichhoatchongchong( false );
                        player_nvc.kichhoathangnong( false );
                        quivuong.set_solan_boss_andan(0);
                        //isPaused = false;
                    }
                    else if (SDLCommonFunc :: check_chuot_chon(xc, yc, cut))quit = true;
                    if( gameOver )
                    {
                        if(SDLCommonFunc::check_chuot_chon(xc,yc,playagain))
                        {
                            cout<<"loi choi lai 2" <<endl ;
                            gameOver = false;
                            game_map.LoadMap("MAP/map04.dat");              //xu li ban do: map
                            game_map.LoadTiles( gRenderer );
                            player_nvc.LoadMainImg("IMG/CHAY_PHAI_SUNG.png",gRenderer);
                            Mix_PlayMusic(nhacnen, -1);                     // nhac nen
                            player_nvc.Set_Clips_chay();
                            player_nvc.loadamthanh_nvc();
                            player_nvc.set_solantrungdan(0);
                            player_nvc.set_vitri_nvc ( 500, 500);

                            quivuong.set_clips();
                            quivuong.set_x_bosspos ( 8800 );
                            quivuong.set_y_bosspos ( 2500 );

                            threats_list = Make_Threat_List();              // khai bao 1 dong quai vat
                            so_qui_bi_giet = 0 ;
                            tong_tien = 0;
                             player_nvc.set_tienanduoc(0);
                            so_mang.set_chi_so_mang(1);
                            solanchetmax = so_mang.get_chi_so_mang();       // cout<<"so mang "<<solanchetmax<<endl;
                            solanchet = 0;
                            phung.SetPos(800,10);
                            duocbay.SetPos(900,10);
                            cai_time = true;
                            maumau = 0;
                            player_nvc.show_cucmau( gRenderer, maumau);
                            player_nvc.kichhoatchongchong( false );
                            player_nvc.kichhoathangnong( false );
                            quivuong.set_solan_boss_andan(0);
                        }
                    }

                }
            }
            player_nvc.XuLiXuKienBanPhim( gEvent, gRenderer );                          //nhan vat chinh, ban phim
        }
        if(!isPaused )
        {
            if(!gameOver && !win_game )
            {
                SDL_SetRenderDrawColor( gRenderer, 255, 255, 255, 255);                 // clear renderer
                SDL_RenderClear( gRenderer );

                gBackground.Render( gRenderer, nullptr );                               // in anh background
                tamdung.Render (gRenderer, nullptr );
                MAP map_data = game_map.GetMap();                                       //xu li di chuyen, va cham map

                if(player_nvc.get_tangmang())
                {
                    so_mang.tangmang() ;                                                // an kim cuong tang mang
                    player_nvc.tang_mang ( false ) ;
                    solanchetmax ++ ;
                    cout<<"solanchetmax "<<solanchetmax <<endl;
                }

                if(player_nvc.gethangnong() == true )                                   // chong chong
                {
                    kiem.change_gocquay(35);
                    int jj = player_nvc.GetRect().x - player_nvc.get_width_frame() ;
                    int ii = player_nvc.GetRect().y - player_nvc.get_height_frame()  ;
                    kiem.render_kiem( gRenderer, jj, ii, nullptr, nullptr, SDL_FLIP_NONE );
                }

                player_nvc.XU_LI_BAN_DAN ( gRenderer, SCREEN_WIDTH/2.5, SCREEN_HEIGHT / 2.5, map_data );   // xu li ban dan
                player_nvc.SetMapXY ( map_data.start_x_, map_data.start_y_ );                           //xu li map di chuyen theo nhan vat
                player_nvc.ShowMain ( gRenderer ) ;                                                     //hien nhan vat chinh
                player_nvc.DiChuyenNhanVat( map_data );
                player_nvc.show_cucmau ( gRenderer, maumau);

                if( player_nvc.get_y_hientai() >= 1800 && player_nvc.get_x_hientai() >= 6000 && win_game == false)
                {
                    quivuong.xulibossbandan(gRenderer);
                    quivuong.SetMapXY ( map_data.start_x_, map_data.start_y_ );
                    quivuong.DICHUYENTHEO_NVC ( player_nvc,gRenderer );
                    quivuong.showboss ( gRenderer );
                    quivuong.DICHUYEN_BOSS ( map_data );
                }


                game_map.SetMap ( map_data );                               // cap nhat vi tri moi cho start_x_, start_y_
                game_map.DrawMap ( gRenderer );                             //ve ban do

                so_mang.Show( gRenderer );

                if ( player_nvc.getchongchong() ) phung.show(gRenderer);
                if ( player_nvc.getchobay() ) duocbay.show(gRenderer);

                for(int i=0; i< (int) threats_list.size(); i++)             // xu li quai vat
                {
                    ThreatsObject* p_qui = threats_list.at(i);
                    if(p_qui != nullptr)
                    {
                        p_qui->SetMapXY( map_data.start_x_, map_data.start_y_ );
                        p_qui->Di_chuyen_trong_pham_vi( gRenderer, map_data );
                        p_qui->DICHUYEN_QUI( map_data );
                        p_qui->pham_vi_bay_dan_qui(gRenderer, SCREEN_WIDTH/3,SCREEN_HEIGHT/3,map_data);
                        p_qui->ShowQui( gRenderer );
                        //

                        bool locdan = false;
                        SDL_Rect rect_nvc = player_nvc.GetRectFrame();
                        vector<BulletObject*> qui_dan = p_qui->get_bang_dan_qui();                  // nhan  vat chinh an dan //cout<<"id: " << i << " : has " << qui_dan.size()<<endl;
                        for( int j = 0; j < (int) qui_dan.size(); j ++ )
                        {
                            BulletObject* dan1 = qui_dan.at(j);
                            if( dan1 != nullptr )
                            {
                                locdan = SDLCommonFunc :: CheckCollision( dan1->GetRect(), rect_nvc );
                                if(locdan)
                                {
                                    Mix_PlayChannel(-1, danquino, 0);
                                    player_nvc.setbitrungdan(true);
                                    for(int ex = 0; ex < num_frame_no ; ex++ )
                                    {
                                        int x_no = player_nvc.GetRect().x - player_nvc.get_width_frame() * 0.5;
                                        int y_no = player_nvc.GetRect().y - player_nvc.get_height_frame() * 0.5;

                                        nvc_no.set_frame(ex);
                                        nvc_no.SetRect(x_no,y_no);
                                        nvc_no.set_clip();
                                        nvc_no.show(gRenderer);
                                    }
                                    p_qui->loaiboviendan(j);

                                    dem222 ++ ;                                                     //cout<<dem222<<endl;
                                    if(dem222 > 7 )
                                    {
                                        player_nvc.trungdan();
                                        dem222 = 0;
                                    }

                                    if( player_nvc.get_solantrungdan() >= 5 )                       // an bao nhieu vien dan - so quai roi chet
                                    {
                                        solanchet ++ ;
                                        cout<< "so lan da chet " << solanchet << endl;
                                        if( solanchet < solanchetmax )
                                        {
                                            player_nvc.set_vitri_nvc( player_nvc.get_x_hientai() - 100, player_nvc.get_y_hientai()+500 );
                                            so_mang.giammang();
                                            so_mang.Render ( gRenderer );
                                            player_nvc.set_comebacktime(10);
                                            player_nvc.set_solantrungdan (0);
                                        }
                                        else
                                        {
                                            for (auto obj : threats_list)                           //giai phong bo nho da cap phat
                                            {
                                                obj->free();
                                                obj = nullptr;
                                            }
                                            threats_list.clear();
                                            gameOver = true ;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                // xử lí viên đạn va chạm
                vector<BulletObject*> dan_nvc = player_nvc.get_bang_dan();          // lấy ra băng đạn của nhân vật chính
                for(int i=0; i<(int)dan_nvc.size(); i++)
                {
                    BulletObject* dan = dan_nvc.at(i);
                    if(dan!=nullptr)
                    {
                        for( int j = 0; j < (int)threats_list.size(); j++ )         //kiểm tra từng viên đạn với từng quái
                        {
                            ThreatsObject* qui1 = threats_list.at(j);
                            if(qui1 != nullptr)
                            {
                                SDL_Rect qui_rect = qui1->GetRectFrame();
                                SDL_Rect dan_rect = dan->GetRect();                 // dan khong co nhieu frame nen ko can get frame
                                bool qui_an_dan = SDLCommonFunc::CheckCollision( dan_rect, qui_rect);
                                if(qui_an_dan)
                                {
                                    Mix_PlayChannel( -1, bom, 0 );                        //cout<<"qui "<<qui_rect.x <<" "<< dan_rect.x<<endl;
                                    if ( player_nvc.get_x_hientai() < qui1->get_x_quipos() )
                                    {
                                        threats_list[j]->set_trang_thai_phai( 1 );
                                        threats_list[j]->set_va_bando(ThreatsObject::cham_phai);
                                    }
                                    else
                                    {
                                        threats_list[j]->set_trang_thai_trai(1);
                                        threats_list[j]->set_va_bando(ThreatsObject::cham_trai);
                                    }
                                    for(int no = 0 ; no < num_frame_no ; no ++)     // xu li anh no
                                    {
                                        int x_pos = qui1->GetRect().x ;             // vi tri no la vi tri qui
                                        int y_pos = qui1->GetRect().y ;

                                        qui_no.set_frame( no );
                                        qui_no.SetRect ( x_pos, y_pos );
                                        qui_no.show ( gRenderer );
                                    }
                                    player_nvc.loaiboviendan(i);
                                    qui1->trungdan();
                                    if ( qui1->get_solantrungdan() ==  4 )
                                    {
                                        qui1->free();
                                        threats_list.erase ( threats_list.begin() + j );
                                        so_qui_bi_giet ++;
                                    }
                                }
                            }
                        }
                    }
                }
                // xử lí va chạm quỉ với kiếm
                if((SDL_GetTicks() - thoigianhientai >= 6000) && ho == true )
                {
                    player_nvc.kichhoathangnong( false ) ;                    //cout<<"thoi diem bam x "<<thoigianhientai <<endl;cout<<SDL_GetTicks() - thoigianhientai <<endl;
                }
                if( player_nvc.gethangnong() == true )
                {
                    SDL_Rect rect_kiem1 = kiem.GetRect();
                    for(int j = 0; j< (int)threats_list.size(); j++)
                    {
                        ThreatsObject* qui1 = threats_list.at(j);
                        if(qui1 != nullptr)
                        {
                            SDL_Rect qui_rect = qui1->GetRectFrame();
                            int jj = player_nvc.GetRect().x - player_nvc.get_width_frame()  ;       //cout<<qui_rect.w <<" "<<qui_rect.h<<endl;;
                            int ii = player_nvc.GetRect().y - player_nvc.get_height_frame()  ;
                            SDL_Rect rect_kiem = {jj,ii, rect_kiem1.w, rect_kiem1.h };
                            bool qui_an_kiem = SDLCommonFunc :: CheckCollision( rect_kiem, qui_rect);
                            if(qui_an_kiem)
                            {
                                Mix_PlayChannel ( -1, quaibichem, 0);
                                for(int no = 0 ; no < num_frame_no ; no ++)                         // xu li anh no
                                {
                                    int x_pos = qui1->GetRect().x ;                                 // vi tri no la vi tri qui
                                    int y_pos = qui1->GetRect().y ;
                                    qui_no.set_frame( no );
                                    qui_no .SetRect( x_pos, y_pos );
                                    qui_no.show(gRenderer);
                                }
                                qui1->trungdan();
                                if( qui1->get_solantrungdan() ==  7 )
                                {
                                    qui1->free();
                                    threats_list.erase(threats_list.begin()+j);
                                    so_qui_bi_giet ++;
                                }
                            }
                        }
                    }
                }
                for (int i = 0; i < (int) threats_list.size(); ++ i)        // khởi tạo lại đạn quỉ
                {
                    ThreatsObject* p_qui = threats_list.at(i);
                    if (p_qui->get_bang_dan_qui().empty())
                    {
                        BulletObject* dan_qui = new BulletObject();         //them dan
                        p_qui->init_dan_qui( dan_qui, gRenderer);
                    }
                }

                // boss cho an hanh
                bool locdanboss = false ;
                SDL_Rect rect_nvc = player_nvc.GetRectFrame();
                vector<BulletObject*> dan_boss = quivuong.get_bang_dan_boss();
                for( int i = 0; i < (int)dan_boss.size(); i++)
                {
                    BulletObject* dan1 = dan_boss.at(i);
                    if( dan1 != nullptr )
                    {
                        locdanboss = SDLCommonFunc ::CheckCollision ( rect_nvc, dan1->GetRect() );
                        if( locdanboss )
                        {
                            Mix_PlayChannel ( -1, daulauno, 0 );
                            player_nvc.setbitrungdan( true);
                            for (int ex = 0; ex < num_frame_no; ex++)
                            {
                                int x_no = player_nvc.GetRect().x - player_nvc.get_width_frame() * 0.5;
                                int y_no = player_nvc.GetRect().y - player_nvc.get_height_frame() * 0.5;

                                daulau.set_frame(ex);
                                daulau.SetRect(x_no, y_no);
                                daulau.set_clip();
                                daulau.show( gRenderer );
                            }
                            quivuong.loaiboviendan(i);
                            dem2221 ++ ;
                            if ( dem2221 >= 15 )
                            {
                                player_nvc.trungdan();
                                dem2221 = 0;
                            }

                            if (player_nvc.get_solantrungdan() >= 5 )                    // an bao nhieu vien dan - so quai roi chet
                            {
                                solanchet ++ ;
                                cout << "so lan da chet " << solanchet << endl;
                                if ( solanchet < solanchetmax )
                                {
                                    player_nvc.set_vitri_nvc( player_nvc.get_x_hientai() - 100, player_nvc.get_y_hientai() + 500 );
                                    so_mang.giammang();
                                    so_mang.Render( gRenderer );
                                    player_nvc.set_comebacktime ( 10 );
                                    player_nvc.set_solantrungdan(0);
                                }
                                else
                                {
                                    for (auto obj : threats_list)                       // giai phong bo nho da cap phat
                                    {
                                        obj->free();
                                        obj = nullptr;
                                    }
                                    threats_list.clear();
                                    quivuong.free();
                                    gameOver = true;
                                }
                            }
                        }
                    }
                }

                // check an dam
                bool andam = false;
//                if(quivuong.trang_thai_boss.dam_phai == 1 || quivuong.trang_thai_boss.dam_trai == 1)
                if(quivuong.trangthaidam())
                {
                    andam = SDLCommonFunc ::CheckCollision(rect_nvc, quivuong.getrectframe());
                    if(andam)
                    {
                        Mix_PlayChannel ( -1, tiengdam, 0 ); cout<<" an dam ";
                        if ( player_nvc.get_x_hientai() < quivuong.get_x_bosspos () )
                        {
                            player_nvc.set_vitri_nvc ( player_nvc.get_x_hientai() - 5, player_nvc.get_y_hientai());
                        }
                        else player_nvc.set_vitri_nvc ( player_nvc.get_x_hientai() + 5, player_nvc.get_y_hientai() );
                        dem_dam ++ ;
                        if(dem_dam >= 25 )
                        {
                            dem_dam = 0 ;
                            player_nvc.trungdan();
                        }
                        if (player_nvc.get_solantrungdan() >= 5)                 // an bao nhieu vien dan - so quai roi chet
                        {
                            solanchet++;
                            cout << "so lan da chet " << solanchet << endl;
                            if ( solanchet < solanchetmax )
                            {
                                player_nvc.set_vitri_nvc ( player_nvc.get_x_hientai() - 100, player_nvc.get_y_hientai() + 500 );
                                so_mang.giammang();
                                so_mang.Render(gRenderer);
                                player_nvc.set_comebacktime(10);
                                player_nvc.set_solantrungdan(0);
                            }
                            else
                            {
                                for (auto obj : threats_list)                   // giai phong bo nho da cap phat
                                {
                                    obj->free();
                                    obj = nullptr;
                                }
                                threats_list.clear();
                                quivuong.free();
                                gameOver = true;
                            }
                        }
                    }
                }


                // check boss an hanh
                // vector<BulletObject*> dan_nvc = player_nvc.get_bang_dan();          // lấy ra băng đạn của nhân vật chính
                for(int i=0; i<(int)dan_nvc.size(); i++)
                {
                    BulletObject* dan = dan_nvc.at(i);
                    if(dan!=nullptr)
                    {
                        SDL_Rect boss_rect = quivuong.getrectframe();
                        SDL_Rect dan_rect = dan->GetRect();                 // dan khong co nhieu frame nen ko can get frame
                        bool qui_an_dan = SDLCommonFunc::CheckCollision( dan_rect, boss_rect);
                        if(qui_an_dan)
                        {
                            Mix_PlayChannel( -1, bom, 0 );                        //cout<<"qui "<<qui_rect.x <<" "<< dan_rect.x<<endl;
                            for(int no = 0 ; no < num_frame_no ; no ++)     // xu li anh no
                            {
                                int x_pos = quivuong.GetRect().x ;             // vi tri no la vi tri qui
                                int y_pos = quivuong.GetRect().y ;

                                qui_no.set_frame( no );
                                qui_no.SetRect ( x_pos, y_pos );
                                qui_no.show ( gRenderer );
                            }
                            player_nvc.loaiboviendan(i);
                            quivuong.trungdan();
                            if ( quivuong.get_solan_boss_andan() ==  40 )
                            {
                                Uint32 startTime = SDL_GetTicks(); // Thời gian bắt đầu hiển thị boss_tan_xac
                                Uint32 elapsedTime = 0;

                                while (elapsedTime < 1000)   // Hiển thị boss_tan_xac trong 3 giây
                                {
                                    for (int no = 0; no < num_frame_no; no++)   // xử lí ảnh nổ
                                    {
                                        int x_pos = quivuong.GetRect().x; // vị trí nổ là vị trí quái
                                        int y_pos = quivuong.GetRect().y;
                                        boss_tan_xac.set_frame(no);
                                        boss_tan_xac.SetRect(x_pos, y_pos);
                                        boss_tan_xac.show(gRenderer);
                                    }
                                    SDL_RenderPresent(gRenderer);
                                    elapsedTime = SDL_GetTicks() - startTime; // Tính thời gian đã trôi qua
                                }

                                qui_no.free();
                                quivuong.free();
                                SDL_Delay(2000);
                                SDL_RenderPresent(gRenderer);
                                win_game = true;
                            }
                        }
                    }
                }
                if( player_nvc.gethangnong() == true )
                {
                    SDL_Rect rect_kiem1 = kiem.GetRect();
                    for(int j = 0; j< (int)threats_list.size(); j++)
                    {

                        SDL_Rect boss_rect = quivuong.getrectframe();
                        int jj = player_nvc.GetRect().x - player_nvc.get_width_frame()  ;       //cout<<boss_rect.w <<" "<<boss_rect.h<<endl;;
                        int ii = player_nvc.GetRect().y - player_nvc.get_height_frame()  ;
                        SDL_Rect rect_kiem = {jj,ii, rect_kiem1.w, rect_kiem1.h };
                        bool qui_an_kiem = SDLCommonFunc :: CheckCollision( rect_kiem, boss_rect );
                        if(qui_an_kiem)
                        {
                            cout<<"an kiem"<<endl;
                            Mix_PlayChannel ( -1, quaibichem, 0);
                            for(int no = 0 ; no < num_frame_no ; no ++)                         // xu li anh no
                            {
                                int x_pos = quivuong.GetRect().x ;                                 // vi tri no la vi tri qui
                                int y_pos = quivuong.GetRect().y ;
                                qui_no.set_frame( no );
                                qui_no .SetRect( x_pos, y_pos );
                                qui_no.show(gRenderer);
                            }
                            quivuong.trungdan();
                            if( quivuong.get_solan_boss_andan() ==  10000 )
                            {
                                Uint32 startTime = SDL_GetTicks(); // Thời gian bắt đầu hiển thị boss_tan_xac
                                Uint32 elapsedTime = 0;
                                while (elapsedTime < 1000)   // Hiển thị boss_tan_xac trong 3 giây
                                {
                                    for (int no = 0; no < num_frame_no; no++)   // xử lí ảnh nổ
                                    {
                                        int x_pos = quivuong.GetRect().x; // vị trí nổ là vị trí quái
                                        int y_pos = quivuong.GetRect().y;
                                        boss_tan_xac.set_frame(no);
                                        boss_tan_xac.SetRect(x_pos, y_pos);
                                        boss_tan_xac.show(gRenderer);
                                    }
                                    SDL_RenderPresent(gRenderer);
                                    elapsedTime = SDL_GetTicks() - startTime; // Tính thời gian đã trôi qua
                                }
                                boss_tan_xac.free();
                                quivuong.free();
                                win_game = true;
                            }
                        }
                    }
                }



                // phong chu tinh thoi gian choi
                {

                string time = " TIME : ";
                Uint32 thoi_gian = SDL_GetTicks()/1000 ;
                Uint32 time_play = thoi_gian - last_time + 1 ;
                if(cai_time) //
                {
                    last_time = thoi_gian ;
                    time_play = thoi_gian - last_time + 1 ;
                    cai_time = false;
                }
                string show_time_play = to_string ( time_play ) ;
                time += show_time_play ;
                thoi_gian_choi.SetText( time ) ;
                thoi_gian_choi.LoadFromRenderText( gFont, gRenderer) ;
                thoi_gian_choi.RenderText( gRenderer, SCREEN_WIDTH - 180, 20 ) ;

                string da_diet = "KILLED : ";
                string showkill = to_string( so_qui_bi_giet );
                da_diet += showkill;
                da_giet.SetText ( da_diet );
                da_giet.LoadFromRenderText( gFont, gRenderer );
                da_giet.RenderText( gRenderer, SCREEN_WIDTH - 180, 50 );

                string tien_hientai = "MONEY : ";
                tien_hientai = "MONEY : ";
                tong_tien = player_nvc.get_tienanduoc();
                string show_tien = to_string (tong_tien);
                tien_hientai += show_tien;
                antien.SetText ( tien_hientai );
                antien.LoadFromRenderText ( gFont, gRenderer );
                antien.RenderText ( gRenderer, SCREEN_WIDTH - 180, 80 );

                SDL_RenderPresent(gRenderer);                               //xuat ra man hinh hien tai

                // thoi gian cham lai ---------------------------------------------------------
                ImpTimer fps_timer;
                int real_imp_time = fps_timer.get_ticks();
                int time_one_frame = 1000/FRAME_PER_SECOND;
                if( real_imp_time < time_one_frame)
                {
                    int delay_time = time_one_frame - real_imp_time;
                    if(delay_time > 0) SDL_Delay(delay_time);
                }
                thoi_gian_choi.Free() ;
                antien.Free() ;
            }
            }

            else if( gameOver && !win_game)
            {
                gameover.Render(gRenderer,nullptr);
                SDL_RenderPresent(gRenderer);
            }
            else if ( win_game && !gameOver)
            {
//                Mix_PlayChannel ( -1, quaibichem, 0);
//                Uint32 startTime = SDL_GetTicks(); // Thời gian bắt đầu hiển thị boss_tan_xac
//                Uint32 elapsedTime = 0;
//
//                while (elapsedTime < 1000)   // Hiển thị boss_tan_xac trong 3 giây
//                {
//                    for (int no = 0; no < num_frame_no; no++)   // xử lí ảnh nổ
//                    {
//                        int x_pos = quivuong.GetRect().x; // vị trí nổ là vị trí quái
//                        int y_pos = quivuong.GetRect().y;
//                        boss_tan_xac.set_frame(no);
//                        boss_tan_xac.SetRect(x_pos, y_pos);
//                        boss_tan_xac.show(gRenderer);
//                    }
//                    SDL_RenderPresent(gRenderer);
//
//                    elapsedTime = SDL_GetTicks() - startTime; // Tính thời gian đã trôi qua
//                }
                boss_tan_xac.free();
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
    for (auto obj : threats_list)       //giai phong bo nho da cap phat
    {
        obj->free();
        obj = nullptr;
    }
    threats_list.clear();               // xóa vector
    qui_no.free() ;
    nvc_no.free();
    so_mang.free();
    phung.free();
    duocbay.free();
    close();
    return 0;
}

void load_tat_ca_qui(SDL_Renderer* des)
{
    tat_ca_anh_qui[ditrai].LoadImage("IMG/quai_di_trai2.png",des);
    tat_ca_anh_qui[diphai].LoadImage("IMG/quai_di_phai2.png",des);
}

void load_all_boss (SDL_Renderer* des)
{
    all_anh_boss[boss_run_trai].LoadImage("IMG/QUAI/qui_chay_trai.png",des);
    all_anh_boss[boss_run_phai].LoadImage("IMG/QUAI/qui_chay_phai.png",des);
    all_anh_boss[boss_dam_phai].LoadImage("IMG/QUAI/qui_dam_phai.png",des);
    all_anh_boss[boss_dam_trai].LoadImage("IMG/QUAI/qui_dam_trai.png",des);
    all_anh_boss[boss_ban_phai].LoadImage("IMG/QUAI/qui_cung_phai.png",des);
    all_anh_boss[boss_ban_trai].LoadImage("IMG/QUAI/qui_cung_trai.png",des);
    all_anh_boss[boss_lon_trai].LoadImage("IMG/QUAI/qui_lon_trai.png",des);
    all_anh_boss[boss_lon_phai].LoadImage("IMG/QUAI/qui_lon_phai.png",des);
}

vector<ThreatsObject*> Make_Threat_List()
{
    vector<ThreatsObject*> list_threats;
    ThreatsObject* qui_tuan_tra = new ThreatsObject[40];
    for(int i=0; i< 40; i++)
    {
        ThreatsObject* p_qui = qui_tuan_tra + i ;
        if(p_qui!=nullptr)
        {
            p_qui->LoadImage( "IMG/quai_di_trai.png", gRenderer );
            p_qui->set_clips();

            if(i > 38)
            {
                p_qui->set_x_quipos( 7000 + i * 50 );
                p_qui->set_y_quipos ( 2500);
            }
            else
            {
                p_qui->set_x_quipos( 100*(i+2)+500 );            // cai dat vi tri xuat hien
                p_qui->set_y_quipos( 360);
            }

            int gioi_han_trai = p_qui->get_x_quipos()-80;        // gioi han trai,phai
            int gioi_han_phai = p_qui->get_x_quipos()+80;

            p_qui->set_gioi_han_dichuyen( gioi_han_trai, gioi_han_phai );
            p_qui->set_trang_thai_trai(1);

            BulletObject* dan_qui = new BulletObject();          //them dan
            p_qui->init_dan_qui( dan_qui, gRenderer);

            list_threats.push_back( p_qui );
        }
    }
    return list_threats;
}
bool Init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING)<0) return false;
    else
    {
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");
        gWindow=SDL_CreateWindow("NGUYEN XUAN DUNG 009 ",
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
bool LoadMedia()// tai anh nen
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

    gFont = TTF_OpenFont ("FONT/turok.ttf",24);
    gFont2 = TTF_OpenFont ("FONT/starcraft.ttf",40);
    if( gFont == nullptr || gFont2 == nullptr )
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
    return 1;
}
void close()
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

    for ( int i = 0 ; i < 6 ; i++ ) player_nvc.cucmau[i].free();

}
void khoitaovuno(VUNO &qui_no)
{
    bool tret = qui_no.LoadImage ("IMG/dan_no_1.png",gRenderer);
    if(tret == false) cout<<" falied to load explosion "<<endl;
    qui_no.set_clip();
}
void khoitaonhanvatchinh_no( VUNO& nvc_no )
{
    bool tret = nvc_no.LoadImage ("IMG/dan_qui_no_1.png",gRenderer);
    if(tret == false) cout<<" falied to load explosion nvc"<<endl;
    nvc_no.set_clip();
}
void khoitaonodaulau ( VUNO & daulau)
{
    bool tret = daulau.LoadImage ("IMG/QUAI/no.png",gRenderer);
    if(tret == false) cout<<" falied to load explosion nvc"<<endl;
    daulau.set_clip();
}

void khoitaonoboss ( VUNO& boss_die)
{
    bool tret = boss_die.LoadImage ("IMG/QUAI/nguyentu.png",gRenderer);
    if(tret == false) cout<<" falied to load explosion nvc"<<endl;
    boss_die.set_clip();
}

//
//void load_all_dan_(SDL_Renderer* gRenderer)
//{
//    //std::cout << "base_load\n";
//    dan_[LOAI_DAN_BASE::DAN1_TRAI].LoadImage("IMG/DAN1_TRAI.png",gRenderer);
//    dan_[LOAI_DAN_BASE::DAN1_PHAI].LoadImage("IMG/DAN1_PHAI.png",gRenderer);
//    dan_[LOAI_DAN_BASE::ten_phai].LoadImage("IMG/QUAI/ten_phai.png",gRenderer);
//    dan_[LOAI_DAN_BASE::ten_trai].LoadImage("IMG/QUAI/ten_trai.png",gRenderer);
//    dan_[LOAI_DAN_BASE::DAN_QUI_THUONG].LoadImage("IMG/dan_qui_thuong.png",gRenderer);
//}


//        dan_[LOAI_DAN_BASE::DAN_QUI_THUONG].SetRect(200, 800);
//        dan_[LOAI_DAN_BASE::DAN_QUI_THUONG].Render(gRenderer, nullptr);
//        std::cout << "player: " << player_nvc.get_x_hientai() << ' ' << player_nvc.get_y_hientai() << '\n';
//        std::cout << "dan: " << dan_[LOAI_DAN_BASE::DAN_QUI_THUONG].GetRect().x << ' ' << dan_[LOAI_DAN_BASE::DAN_QUI_THUONG].GetRect().y << '\n';


//void load_all_main (SDL_Renderer* des)
//{
//    player_main[chaytrai].LoadImage("IMG/CHAY_TRAI_SUNG.png",des);
//    player_main[chayphai].LoadImage("IMG/CHAY_PHAI_SUNG.png",des);
//    player_main[bayphai].LoadImage("IMG/bay_phai.png",des);
//    player_main[baytrai].LoadImage("IMG/bay_trai.png",des);
//    player_main[damphai].LoadImage("IMG/DAO_DAM_PHAI.png",des);
//    player_main[damtrai].LoadImage("IMG/DAO_DAM_TRAI.png",des);
//    player_main[lontrai].LoadImage("IMG/LON_TRAI1.png",des);
//    player_main[lonphai].LoadImage("IMG/LON_PHAI1.png",des);
//}

//BaseObject tamdung;
//BaseObject tamdung2;
//SDL_Rect nutdung = {SCREEN_WIDTH - 80, 0, 80,78 };
//SDL_Rect tieptuc = {625 , 460 -32 , 115,40};
//SDL_Rect playagain = {450, 800, 120, 71};
//SDL_Rect restart = {600, 740 , 160 -32 , 60 };
//SDL_Rect cut = { 625 , 670 -32 , 120 , 30};
//
//BaseObject anhdau;
//BaseObject anhcho;
//BaseObject gameover;                                // anh dau tien hien len
//BaseObject gBackground;                             // khai bao 1 em background
//GAMEMAP game_map;                                   //khai bao 1 em gamemap
//MainObject player_nvc;                              //khai bao nhan vat chinh
//Sword kiem;
//SDL_Window * gWindow = nullptr;
//SDL_Renderer * gRenderer = nullptr;
//SDL_Event gEvent;

//VUNO qui_no ;
//VUNO nvc_no;
//VUNO daulau ;
//VUNO boss_tan_xac ;
