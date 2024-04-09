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

using namespace std;

bool Init();
bool LoadMedia();
void close();
SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
SDL_Event gEvent;
TTF_Font * gFont = nullptr ; // phong chu
TTF_Font * gFont2 = nullptr;

BaseObject gBackground;// khai bao 1 em background
GAMEMAP game_map;//khai bao 1 em gamemap
MainObject player_nvc;//khai bao nhan vat chinh

void load_tat_ca_qui(SDL_Renderer* des);// load tat ca cac anh cua qui
vector<ThreatsObject*> Make_Threat_List();//tạo lập lớp threart object // lớp quỉ

void khoitaovuno( VUNO& qui_no);
void khoitaonhanvatchinh_no( VUNO& nvc_no );



int main(int messi,char* kaka [] )
{
    if(!Init()||!LoadMedia()) return -1000; //kiem tra khoi tao
    game_map.LoadMap("MAP/map03.dat");//xu li ban do: map
    game_map.LoadTiles( gRenderer );
    player_nvc.LoadMainImg("IMG/CHAY_PHAI_SUNG.png",gRenderer); //xu li nhan vat chinh
    player_nvc.Set_Clips_chay();
    vector<ThreatsObject*> threats_list = Make_Threat_List(); // khai bao 1 dong quai vat
    load_tat_ca_qui ( gRenderer );

    VUNO qui_no ; // nổ khi bắn quái
    khoitaovuno(qui_no);
    VUNO nvc_no; //nổ khi ăn đạn của quỉ
    khoitaonhanvatchinh_no(nvc_no);

    TextObject thoi_gian_choi ; // khai báo phông chữ thời gian chơi gamme
    thoi_gian_choi.setcolor(TextObject :: RED_TEXT );
    TextObject da_giet;
    da_giet.setcolor(TextObject :: RED_TEXT);
    UINT so_qui_bi_giet = 0 ;
    TextObject antien ;
    antien.setcolor (TextObject :: RED_TEXT );
    UINT tong_tien = 0;

    PlayerPower so_mang;
    so_mang.set_chi_so_mang(5);
    so_mang.Init(gRenderer);
    int solanchetmax = so_mang.get_chi_so_mang();
    cout<<"so mang "<<solanchetmax<<endl;

    int solanchet = 0;
    //

    bool quit = false; // vong lap chinh

    //menu
    MENU menu_;
    int ret_menu = menu_.showmenu( gRenderer , gFont2 );
    if(ret_menu != 1) quit = true;
    while(!quit)
    {
        while( SDL_PollEvent( &gEvent ) != 0 )
        {
            if( gEvent.type == SDL_QUIT) quit=true;
            player_nvc.XuLiXuKienBanPhim( gEvent, gRenderer );//nhan vat chinh, ban phim
        }
        SDL_SetRenderDrawColor( gRenderer, 255, 255, 255, 255);// clear renderer
        SDL_RenderClear( gRenderer );

        gBackground.Render( gRenderer, nullptr );// in anh background
        MAP map_data = game_map.GetMap();//xu li di chuyen, va cham map

        player_nvc.XU_LI_BAN_DAN( gRenderer, SCREEN_WIDTH/2.5, SCREEN_HEIGHT/2.5, map_data);// xu li ban dan

        //

        player_nvc.SetMapXY( map_data.start_x_, map_data.start_y_); //xu li map di chuyen theo nhan vat
        player_nvc.ShowMain( gRenderer ) ;//hien nhan vat chinh
        player_nvc.DiChuyenNhanVat( map_data );
        game_map.SetMap( map_data ); // cap nhat vi tri moi cho start_x_, start_y_
        game_map.DrawMap( gRenderer );//ve ban do

        so_mang.Show(gRenderer);
        for(int i=0; i< (int) threats_list.size(); i++)  // xu li quai vat
        {
            ThreatsObject* p_qui = threats_list.at(i);
            if(p_qui!=nullptr)
            {
                p_qui->SetMapXY( map_data.start_x_, map_data.start_y_ );
                p_qui->Di_chuyen_trong_pham_vi( gRenderer, map_data );
                p_qui->DICHUYEN_QUI( map_data );
                p_qui->pham_vi_bay_dan_qui(gRenderer, SCREEN_WIDTH/3,SCREEN_HEIGHT/3,map_data);
                p_qui->ShowQui( gRenderer );
//
                SDL_Rect rect_nvc = player_nvc.GetRectFrame();
                bool locdan = false;
                vector<BulletObject*> qui_dan = p_qui->get_bang_dan_qui();
                //cout<<"id: " << i << " : has " << qui_dan.size()<<endl;
                for( int j = 0; j < (int) qui_dan.size(); j ++ )
                {
                    BulletObject* dan1 = qui_dan.at(j);
                    if(dan1!=nullptr)
                    {
                        locdan = SDLCommonFunc :: CheckCollision( dan1->GetRect(),rect_nvc );
                        if(locdan)
                        {
                            for(int ex = 0; ex < num_frame_no ; ex++ )
                            {
                                int x_no = player_nvc.GetRect().x - player_nvc.get_width_frame() * 0.5;
                                int y_no = player_nvc.GetRect().y - player_nvc.get_height_frame() * 0.5;

                                nvc_no.set_frame(ex);
                                nvc_no.SetRect(x_no,y_no);
                                nvc_no.set_clip();
                                nvc_no.show(gRenderer);
                                //
                            }
                            p_qui->loaiboviendan(j);
                            player_nvc.trungdan();
                            if( player_nvc.get_solantrungdan() >= 45 &&player_nvc.get_solantrungdan()%45 ==0 )
                            {
                                solanchet++;
                                //cout<<"so lan da chet "<<solanchet<<endl;
                                if(solanchet <= solanchetmax)
                                {
                                    player_nvc.SetRect ( 100, 100);
                                    player_nvc.set_comebacktime(10);
                                    SDL_Delay( 1000 );
                                    so_mang.giammang();
                                    so_mang.Render(gRenderer);
                                    continue;
                                }
                                else
                                {
                                    const wchar_t* wideString = L"   GameOver \n";
                                    int bufferSize = WideCharToMultiByte(CP_UTF8, 0, wideString, -1, NULL, 0, NULL, NULL);
                                    char* buffer = new char[bufferSize];
                                    WideCharToMultiByte(CP_UTF8, 0, wideString, -1, buffer, bufferSize, NULL, NULL);
                                    if (MessageBox(NULL, buffer, "Info", MB_OK | MB_ICONSTOP) == IDOK)
                                    {
                                       close();
                                       delete[] buffer;
                                       for (auto obj : threats_list) //giai phong bo nho da cap phat
                                        {
                                            obj->free();
                                            obj = nullptr;
                                        }
                                        threats_list.clear(); // xóa vector
                                        return 0;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        // xử lí viên đạn va chạm
        vector<BulletObject*> dan_nvc = player_nvc.get_bang_dan();// lấy ra băng đạn của nhân vật chính
        for(int i=0;i<(int)dan_nvc.size();i++)
        {
            BulletObject* dan = dan_nvc.at(i);
            if(dan!=nullptr)
            {
                for(int j = 0; j< (int)threats_list.size(); j++) //kiểm tra từng viên đạn với từng quái
                {
                    ThreatsObject* qui1 = threats_list.at(j);
                    if(qui1 != nullptr)
                    {
                        SDL_Rect qui_rect = qui1->GetRectFrame();
                        SDL_Rect dan_rect = dan->GetRect(); // dan khong co nhieu frame nen ko can get frame
                        bool qui_an_dan = SDLCommonFunc::CheckCollision( dan_rect, qui_rect);
                        if(qui_an_dan)
                        {
                            for(int no = 0 ; no < num_frame_no ; no ++)// xu li anh no
                            {
                                int x_pos = qui1->GetRect().x ;// vi tri no la vi tri qui
                                int y_pos = qui1->GetRect().y ;

                                qui_no.set_frame( no );
                                qui_no .SetRect(x_pos , y_pos);
                                qui_no.show(gRenderer);
                            }
                            player_nvc.loaiboviendan(i);
                            qui1->trungdan();
                            if(qui1->get_solantrungdan() ==  3)
                            {
                                qui1->free();
                                threats_list.erase(threats_list.begin()+j);
                                so_qui_bi_giet ++;
                            }
                        }
                    }
                }
            }
        }

        // khởi tạo lại đạn quỉ
        for (int i = 0; i < (int) threats_list.size(); ++ i)
        {
            ThreatsObject* p_qui = threats_list.at(i);
            if (p_qui->get_bang_dan_qui().empty())
            {
                BulletObject* dan_qui = new BulletObject(); //them dan
                p_qui->init_dan_qui( dan_qui, gRenderer);
            }
        }

        // phong chu tinh thoi gian choi
        string time = " TIME : ";
        Uint32 thoi_gian = SDL_GetTicks()/1000;
        Uint32 time_play = thoi_gian ++;
        string show_time_play = to_string ( time_play );
        time += show_time_play;
        thoi_gian_choi.SetText( time );
        thoi_gian_choi.LoadFromRenderText( gFont, gRenderer);
        thoi_gian_choi.RenderText( gRenderer, SCREEN_WIDTH - 180 , 20 );

        string da_diet = "KILLED : ";
        string showkill = to_string( so_qui_bi_giet );
        da_diet += showkill;
        da_giet.SetText ( da_diet );
        da_giet.LoadFromRenderText(gFont, gRenderer );
        da_giet.RenderText( gRenderer , SCREEN_WIDTH - 180, 50 );

        string tien_hientai = "MONEY : ";
        tong_tien = player_nvc.get_tienanduoc();
        string show_tien = to_string (tong_tien);
        tien_hientai += show_tien;
        antien.SetText (tien_hientai);
        antien.LoadFromRenderText (gFont,gRenderer );
        antien.RenderText (gRenderer , SCREEN_WIDTH-180 , 80);

        SDL_RenderPresent(gRenderer);//xuat ra man hinh hien tai

        // thoi gian cham lai ---------------------------------------------------------
        ImpTimer fps_timer;
        int real_imp_time = fps_timer.get_ticks();
        int time_one_frame = 1000/FRAME_PER_SECOND;
        if( real_imp_time < time_one_frame)
        {
            int delay_time = time_one_frame-real_imp_time;
            if(delay_time > 0) SDL_Delay(delay_time);
        }
    }
    for (auto obj : threats_list) //giai phong bo nho da cap phat
    {
        obj->free();
        obj = nullptr;
    }
    threats_list.clear(); // xóa vector
    close();
    return 0;
}

void load_tat_ca_qui(SDL_Renderer* des)
{
//    tat_ca_anh_qui[ditrai].LoadImage("IMG/quai_di_trai.png",des);
//    tat_ca_anh_qui[diphai].LoadImage("IMG/quai_di_phai.png",des);
    tat_ca_anh_qui[ditrai].LoadImage("IMG/quai_di_trai2.png",des);
    tat_ca_anh_qui[diphai].LoadImage("IMG/quai_di_phai2.png",des);
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

            p_qui->set_x_quipos( 100*i+1200 );  // cai dat vi tri xuat hien
            p_qui->set_y_quipos( 360);

            int gioi_han_trai = p_qui->get_x_quipos()-100; // gioi han trai,phai
            int gioi_han_phai = p_qui->get_x_quipos()+100;

            p_qui->set_gioi_han_dichuyen( gioi_han_trai, gioi_han_phai );
            p_qui->set_trang_thai_trai(1);

            BulletObject* dan_qui = new BulletObject(); //them dan
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

                if(TTF_Init()==-1){printf(TTF_GetError());return false ; }

            }
        }
    }
    return true;
}
bool LoadMedia()// tai anh nen
{
    if(!gBackground.LoadImage("IMG/G_BACK_GROUND_NET.jpg",gRenderer))return 0;
    gFont = TTF_OpenFont ("FONT/turok.ttf",24);
    gFont2 = TTF_OpenFont ("FONT/starcraft.ttf",40);
    if( gFont == nullptr || gFont2 == nullptr )
    {
        cout<<TTF_GetError();return 0;
    }
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
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
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








//                            std::cout <<"dan  "<< dan1->GetRect().x << ' ' << dan1->GetRect().y << ' ' << dan1->GetRect().x + dan1->GetRect().w << ' ' << dan1->GetRect().y + dan1->GetRect().h <<" ha phuong "<< '\n';
//                            std::cout <<"nvc "<< rect_nvc.x << ' ' << rect_nvc.y << ' ' << rect_nvc.x + rect_nvc.w << ' ' << rect_nvc.y + dan1->GetRect().h<<" vu xuan dung " << '\n';
//                            std::cout << "collision\n";



//        //xử lí viên đạn quỉ trúng nhân vật chính
//        for( int i = 0; i < (int) threats_list.size(); i++)
//        {
//            ThreatsObject* p_qui = threats_list.at(i);
//            if( p_qui != nullptr)
//            {
//
//            }
//        }


//                        SDL_Rect qui_rect;
//                        qui_rect.x = qui1->GetRect().x;
//                        qui_rect.y = qui1->GetRect().y;
//                        qui_rect.w = qui1->get_width_frame();// có nhiều frame lên phải dùng frame chứ không được dùng toàn bộ kích thước ảnh của quỉ
//                        qui_rect.h = qui1->get_height_frame();


//            if(i<10)
//            {
//                p_qui->set_x_quipos(350+i*150);
//                p_qui->set_y_quipos(100) ;
//            }
//            else if(i>=10&&i<20)
//            {
//                p_qui->set_x_quipos(600+i*180);
//                p_qui->set_y_quipos(500) ;
//            }
//            else
//            {
//                p_qui->set_x_quipos(100+i*50);
//                p_qui->set_y_quipos(800) ;
//            }

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
