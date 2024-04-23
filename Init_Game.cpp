#include "Init_Game.h"

using namespace std;

void InitGame()
{
    if(!Init()||!LoadMedia()) cout<<"failed to init or loadmedia";         //kiem tra khoi tao
    anhcho.SetRect(160,50);
    anhcho.Render(gRenderer,nullptr);
    SDL_RenderPresent(gRenderer);
    SDL_Delay(500);                                 // ảnh chờ đầu tiên
    anhdau.Render(gRenderer,nullptr);               // anh dau

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
    quivuong.loadamthanh_boss();

    vector<ThreatsObject*> threats_list = Make_Threat_List();       // khai bao 1 dong quai vat
    load_tat_ca_qui ( gRenderer );
    load_all_boss ( gRenderer );
    load_all_main( gRenderer);

    khoitaovuno(qui_no);
    khoitaonhanvatchinh_no(nvc_no);
    khoitaonodaulau (daulau);
    khoitaonoboss ( boss_tan_xac);
    khoitaono_dam ( no_dam );

    thoi_gian_choi.setcolor (TextObject :: RED_TEXT );              //thoi_gian_choi.LoadFromRenderText( gFont, gRenderer);
    da_giet.setcolor (TextObject :: RED_TEXT);                       //da_giet.LoadFromRenderText( gFont, gRenderer );
    antien.setcolor (TextObject :: RED_TEXT );                      //antien.LoadFromRenderText (gFont,gRenderer );

    so_mang.set_chi_so_mang(3);
    so_mang.Init( gRenderer, "IMG/tym.png" );

    phung.init(gRenderer,"IMG/phung.png");
    phung.SetPos(800,10);

    duocbay.init(gRenderer,"IMG/congcubay.png");
    duocbay.SetPos(900,10);

    //
    kiem = player_nvc.getkiem();
    if(!kiem.Loadkiem("IMG/kiem.png",gRenderer)) cout<<"failed to load kiem nvc -100000";
    uatuc = quivuong.get_kiemboss();
    if(!uatuc.Loadkiem("IMG/QUAI/kiemquai.png",gRenderer)) cout<<"failed to load kiem qui";


    menu_.SetRect ( SCREEN_WIDTH / 2 - 180, SCREEN_HEIGHT / 3 - 60 );

    player_nvc.load_cucmau ( gRenderer);
    quivuong.load_cucmau_boss ( gRenderer );

    int ret_menu = menu_.showmenu ( gRenderer );
    if(ret_menu != 1) quit = true;

}


void restartGame()
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
    so_mang.set_chi_so_mang(3);
    solanchetmax = so_mang.get_chi_so_mang();               // cout<<"so mang "<<solanchetmax<<endl;
    solanchet = 0;

    phung.SetPos(800,10);
    duocbay.SetPos(900,10);
    cai_time = true;
    maumau = 0;
    mauboss = 0 ;
    player_nvc.show_cucmau( gRenderer, maumau);
    player_nvc.kichhoatchongchong( false );
    player_nvc.kichhoathangnong( false );
    quivuong.set_solan_boss_andan(0);
}

void restartGame2()
{
    isPaused = false; printf( "restart\n");
//    so_mang.Init( gRenderer, "IMG/tym.png" );
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

    so_mang.set_chi_so_mang(3);
    vector<int> kaka = so_mang.get_o_mang();
    so_mang.Init( gRenderer, "IMG/tym.png" );
    cout<<kaka.size()<<endl;
   // cout<<"so mang " << so_mang.get_chi_so_mang() << endl;
    solanchetmax = so_mang.get_chi_so_mang();//cout<<"solanchetmax "<<solanchetmax<<endl;

    solanchet = 0;
    phung.SetPos(800,10);
    duocbay.SetPos(900,10);
    cai_time = true;
    maumau = 0;
    mauboss = 0 ;
    player_nvc.show_cucmau( gRenderer, maumau);
    player_nvc.kichhoatchongchong( false );
    player_nvc.kichhoathangnong( false );
    quivuong.set_solan_boss_andan(0);
}
