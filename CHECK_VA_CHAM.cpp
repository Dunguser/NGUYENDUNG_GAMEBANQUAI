#include "CHECK_VA_CHAM.h"

using namespace std;


void va_qui_voi_dan_nvc()
{
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
}
void va_qui_voi_kiem_nvc()
{
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
}

void va_nvc_voi_danqui()
{
    for(int i=0; i< (int) threats_list.size(); i++)             // xu li quai vat
    {
        ThreatsObject* p_qui = threats_list.at(i);
        if(p_qui != nullptr)
        {
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
                            if( solanchet < solanchetmax )
                            {
                                if (level_1)player_nvc.set_vitri_nvc ( player_nvc.get_x_hientai() - 100, player_nvc.get_y_hientai() + 500 );
                                else player_nvc.SetRect (500, 500);
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
}

void va_nvc_voi_danboss()
{
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
                    if ( solanchet < solanchetmax )
                    {
                        if (level_1)player_nvc.set_vitri_nvc ( player_nvc.get_x_hientai() - 100, player_nvc.get_y_hientai() + 500 );
                        else player_nvc.SetRect (500, 500);
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

}
void va_nvc_bi_bossdam()
{
    bool andam = false;
    SDL_Rect rect_nvc = player_nvc.GetRectFrame();
    if(quivuong.trangthaidam())
    {
        andam = SDLCommonFunc ::CheckCollision(rect_nvc, quivuong.getrectframe());
        if(andam)
        {
            Mix_PlayChannel ( -1, tiengdam, 0 ); //cout<<" an dam ";
            for (int ex = 0; ex < num_frame_no; ex++)
            {
                int x_no,y_no;
                if( player_nvc.get_x_hientai()<quivuong.get_x_bosspos())
                {
                    x_no = player_nvc.GetRect().x + player_nvc.get_width_frame() * 0.5;
                    y_no = player_nvc.GetRect().y ;
                }
                else
                {
                    x_no = player_nvc.GetRect().x ;
                    y_no = player_nvc.GetRect().y ;
                }
                no_dam.set_frame(ex);
                no_dam.SetRect(x_no, y_no);
                no_dam.set_clip();
                no_dam.show( gRenderer );
            }
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
            if ( player_nvc.get_solantrungdan() >= 5 )                 // an bao nhieu vien dan - so quai roi chet
            {
                solanchet++;
                if ( solanchet < solanchetmax )
                {
                    if (level_1)player_nvc.set_vitri_nvc ( player_nvc.get_x_hientai() - 100, player_nvc.get_y_hientai() + 500 );
                    else player_nvc.SetRect (500, 500);
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

}
void va_nvc_voi_kiemboss()
{
    if( quivuong.gethanglanh() == true )
    {
        SDL_Rect rect_kiem1 = uatuc.GetRect();
        SDL_Rect main_rect = player_nvc.GetRectFrame();
        int jj = quivuong.GetRect().x - quivuong.get_width_frame()  ;       //cout<<boss_rect.w <<" "<<boss_rect.h<<endl;;
        int ii = quivuong.GetRect().y - quivuong.get_height_frame()  ;
        SDL_Rect rect_uatuc = {jj,ii, rect_kiem1.w, rect_kiem1.h };
        bool main_an_uatuc = SDLCommonFunc :: CheckCollision( rect_uatuc, main_rect );
        if(main_an_uatuc)
        {
            Mix_PlayChannel ( -1, quaibichem, 0 );
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
            bi_uatuc_chem ++ ;
            if ( bi_uatuc_chem >= 100 )
            {
                player_nvc.trungdan();
                bi_uatuc_chem = 0;
            }

            if (player_nvc.get_solantrungdan() >= 5 )                    // an bao nhieu vien dan - so quai roi chet
            {
                solanchet ++ ;
                if ( solanchet < solanchetmax )
                {
                    if (level_1)player_nvc.set_vitri_nvc( player_nvc.get_x_hientai() - 100, player_nvc.get_y_hientai() + 500 );
                    else if ( level_2) player_nvc.SetRect ( 500, 500);
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

void va_haikiemvoinhau()
{
    if( quivuong.gethanglanh() == true && player_nvc.gethangnong() == true && abs(player_nvc.get_x_hientai()- quivuong.get_x_bosspos()) <= 600)
    {
        SDL_Rect rect_kiem1 = uatuc.GetRect();
        int jj = quivuong.GetRect().x - quivuong.get_width_frame()  ;       //cout<<boss_rect.w <<" "<<boss_rect.h<<endl;;
        int ii = quivuong.GetRect().y - quivuong.get_height_frame()  ;
        SDL_Rect rect_uatuc = {jj,ii, rect_kiem1.w, rect_kiem1.h };

        SDL_Rect rect2 = kiem.GetRect();
        int jj1 = player_nvc.GetRect().x - player_nvc.get_width_frame()  ;       //cout<<boss_rect.w <<" "<<boss_rect.h<<endl;;
        int ii1 = player_nvc.GetRect().y - player_nvc.get_height_frame()  ;
        SDL_Rect rect_kiem = {jj1,ii1, rect2.w, rect2.h };

        if(SDLCommonFunc::CheckCollision(rect_uatuc, rect_kiem))
        {
            Mix_PlayChannel( -1, vakiem, 0 );
        }

    }
}


void va_boss_voi_dan_nvc()
{
    vector<BulletObject*> dan_nvc = player_nvc.get_bang_dan();
    for(int i=0; i<(int)dan_nvc.size(); i++)
    {
        BulletObject* dan = dan_nvc.at(i);
        if(dan != nullptr)
        {

            SDL_Rect boss_rect = quivuong.getrectframe();
            SDL_Rect dan_rect = dan->GetRect();                 // dan khong co nhieu frame nen ko can get frame
            bool qui_an_dan = SDLCommonFunc::CheckCollision( dan_rect, boss_rect);
            if( qui_an_dan )
            {
                //if(level_2)cout<<"dan trung boss "<<endl;

                Mix_PlayChannel( -1, bom, 0 );                        //cout<<"qui "<<qui_rect.x <<" "<< dan_rect.x<<endl;
                for(int no = 0 ; no < num_frame_no ; no ++)         // xu li anh no
                {

                    int x_pos = quivuong.GetRect().x ;             // vi tri no la vi tri qui
                    int y_pos = quivuong.GetRect().y ;

                    qui_no.set_frame( no );
                    qui_no.SetRect ( x_pos, y_pos );
                    qui_no.show ( gRenderer );
                    if(level_2)cout<<" no boss  "<<endl; cout<<x_pos <<" "<<y_pos <<endl;
                }
                player_nvc.loaiboviendan(i);
                boss_andan++;
                if(boss_andan >= 1 )
                {
                    quivuong.trungdan();
                    boss_andan = 0;
                }

                if ( quivuong.get_solan_boss_andan() ==  4 )
                {
                    Uint32 startTime = SDL_GetTicks();          // Thời gian bắt đầu hiển thị boss_tan_xac
                    Uint32 elapsedTime = 0;

                    while (elapsedTime < 1000)                  // Hiển thị boss_tan_xac trong 3 giây
                    {
                        for (int no = 0; no < num_frame_no; no++)       // xử lí ảnh nổ
                        {
                            int x_pos = quivuong.GetRect().x - 55 ;     // vị trí nổ là vị trí quái
                            int y_pos = quivuong.GetRect().y - 40 ;
                            boss_tan_xac.set_frame(no);
                            boss_tan_xac.SetRect(x_pos, y_pos);
                            boss_tan_xac.show(gRenderer);
                        }
                        SDL_RenderPresent(gRenderer);
                        elapsedTime = SDL_GetTicks() - startTime;       // Tính thời gian đã trôi qua
                    }

                    qui_no.free();
                    quivuong.free();
                    SDL_Delay( 2000 );
                    SDL_RenderPresent(gRenderer);
                    win_game = true;
                }
            }
        }
    }

}
void va_boss_voi_kiem_nvc()
{
    if( player_nvc.gethangnong() == true )
    {
        SDL_Rect rect_kiem1 = kiem.GetRect();

        SDL_Rect boss_rect = quivuong.getrectframe();

        int jj = player_nvc.GetRect().x - player_nvc.get_width_frame()  ;       //cout<<boss_rect.w <<" "<<boss_rect.h<<endl;;
        int ii = player_nvc.GetRect().y - player_nvc.get_height_frame()  ;
        SDL_Rect rect_kiem = {jj,ii, rect_kiem1.w, rect_kiem1.h };

        bool qui_an_kiem = SDLCommonFunc :: CheckCollision( rect_kiem, boss_rect );
        if(qui_an_kiem)
        {
            if(level_2)cout<<"boss an kiem"<<endl;
            Mix_PlayChannel ( -1, quaibichem, 0 );
            for(int no = 0 ; no < num_frame_no ; no ++)                         // xu li anh no
            {
                int x_pos = quivuong.GetRect().x ;                                 // vi tri no la vi tri qui
                int y_pos = quivuong.GetRect().y ;
                qui_no.set_frame( no );
                qui_no .SetRect( x_pos, y_pos );  cout<<x_pos <<" "<<y_pos <<endl;
                qui_no.show(gRenderer);
            }
            qui_vuong_bichem ++;
            if ( qui_vuong_bichem >= 6000 )
            {
                quivuong.trungdan();
                qui_vuong_bichem = 0 ;
            }
            if( quivuong.get_solan_boss_andan() ==  4 )
            {
                Uint32 startTime = SDL_GetTicks();                  // Thời gian bắt đầu hiển thị boss_tan_xac
                Uint32 elapsedTime = 0;
                while ( elapsedTime < 1000 )                        // Hiển thị boss_tan_xac trong 3 giây
                {
                    for (int no = 0; no < num_frame_no; no++)       // xử lí ảnh nổ
                    {
                        int x_pos = quivuong.GetRect().x - 55 ;     // vị trí nổ là vị trí quái
                        int y_pos = quivuong.GetRect().y - 40 ;
                        boss_tan_xac.set_frame(no);
                        boss_tan_xac.SetRect(x_pos, y_pos );
                        boss_tan_xac.show(gRenderer);
                    }
                    SDL_RenderPresent(gRenderer);
                    elapsedTime = SDL_GetTicks() - startTime;       // Tính thời gian đã trôi qua
                }
                boss_tan_xac.free();
                quivuong.free();
                win_game = true;
            }
        }
    }

}


void qui_con_khonhon()
{
    for(int i=0; i<(int)threats_list.size(); i++)
    {
        ThreatsObject* p_qui = threats_list.at(i);
        if ( abs(player_nvc.get_x_hientai() - p_qui->get_x_quipos()) < 100 && abs( player_nvc.get_y_hientai() - p_qui->get_y_quipos() < 10 ) &&  abs(player_nvc.get_x_hientai() - p_qui->get_x_quipos())> 60 )
        {
            if(!player_nvc.gethangnong())
            {
                if( player_nvc.get_x_hientai() > p_qui->get_x_quipos() ) threats_list[i]->set_va_bando ( ThreatsObject :: cham_trai);
                else threats_list[i]->set_va_bando(ThreatsObject :: cham_phai);
            }
            else
            {
                if( player_nvc.get_x_hientai() > p_qui->get_x_quipos() ) threats_list[i]->set_va_bando ( ThreatsObject :: cham_phai);
                else threats_list[i]->set_va_bando(ThreatsObject :: cham_trai);
            }
        }
    }
}

void check_va_cham1()
{
    va_qui_voi_dan_nvc();
    va_qui_voi_kiem_nvc();

    va_nvc_voi_danqui();
    va_nvc_voi_kiemboss();
    va_nvc_bi_bossdam();
    va_nvc_voi_danboss();

    va_boss_voi_dan_nvc();
    va_boss_voi_kiem_nvc();

    va_haikiemvoinhau();

    qui_con_khonhon();

}
void check_va_cham3()
{
    va_qui_voi_dan_nvc();
    va_qui_voi_kiem_nvc();

    va_nvc_voi_danqui();
    va_nvc_voi_kiemboss();
    va_nvc_bi_bossdam();
    va_nvc_voi_danboss();

    va_boss_voi_dan_nvc();
    va_boss_voi_kiem_nvc();

    va_haikiemvoinhau();

    qui_con_khonhon();

}


void check_va_cham2()
{
    va_nvc_voi_kiemboss();
    va_nvc_bi_bossdam();
    va_nvc_voi_danboss();

    va_boss_voi_dan_nvc();
    va_boss_voi_kiem_nvc();

    va_haikiemvoinhau();
}









