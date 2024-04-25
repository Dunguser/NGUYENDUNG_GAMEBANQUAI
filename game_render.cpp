
#include "game_render.h"

void render_game()
{
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);  // clear renderer
    SDL_RenderClear(gRenderer);

    gBackground.Render(gRenderer, nullptr);                 // in anh background
    tamdung.Render( gRenderer, nullptr);
    map_data = game_map.GetMap();                           //xu li di chuyen, va cham map

    if ( player_nvc.get_tangmang() )
    {
        so_mang.tangmang();                                 // an kim cuong tang mang
        player_nvc.tang_mang(false);
        solanchetmax ++;                                     //cout << "solanchetmax " << solanchetmax << endl;
    }

    if ( player_nvc.gethangnong() == true)
    {
        kiem.change_gocquay( 30 );
        int jj = player_nvc.GetRect().x - player_nvc.get_width_frame();
        int ii = player_nvc.GetRect().y - player_nvc.get_height_frame();
        kiem.render_kiem(gRenderer, jj, ii, nullptr, nullptr, SDL_FLIP_NONE);
    }

    // player_nvc
    player_nvc.XU_LI_BAN_DAN(gRenderer, SCREEN_WIDTH / 2.5, SCREEN_HEIGHT / 2.5, map_data);     // xu li ban dan
    player_nvc.SetMapXY(map_data.start_x_, map_data.start_y_);                                  //xu li map di chuyen theo nhan vat
    player_nvc.ShowMain(gRenderer);                                                             //hien nhan vat chinh
    player_nvc.DiChuyenNhanVat(map_data);
    player_nvc.show_cucmau(gRenderer, maumau);

    if (player_nvc.get_y_hientai() >= 1800 && player_nvc.get_x_hientai() >= 6000 && win_game == false)      // qui vuong
    {
        quivuong.xulibossbandan(gRenderer);
        quivuong.SetMapXY(map_data.start_x_, map_data.start_y_);
        quivuong.DICHUYENTHEO_NVC(player_nvc, gRenderer);
        quivuong.showboss(gRenderer);
        quivuong.DICHUYEN_BOSS(map_data);
        quivuong.show_mau_boss(gRenderer, mauboss);

        if (quivuong.gethanglanh())
        {
            uatuc.change_gocquay(30);
            int jj = quivuong.GetRect().x - quivuong.get_width_frame();
            int ii = quivuong.GetRect().y - quivuong.get_height_frame();
            uatuc.render_kiem( gRenderer, jj, ii, nullptr, nullptr, SDL_FLIP_NONE);
        }
    }

    game_map.SetMap( map_data );                                      // cap nhat vi tri moi cho start_x_, start_y_
    game_map.DrawMap( gRenderer  );                                    //ve ban do

    so_mang.Show( gRenderer );

    if (player_nvc.getchongchong()) phung.show(gRenderer);
    if (player_nvc.getchobay()) duocbay.show(gRenderer);

    for (int i = 0; i < (int)threats_list.size(); i++)              // xu li quai vat
    {
        ThreatsObject* p_qui = threats_list.at(i);
        if (p_qui != nullptr)
        {
            p_qui->SetMapXY( map_data.start_x_, map_data.start_y_ );
            p_qui->Di_chuyen_trong_pham_vi( gRenderer, map_data );
            p_qui->DICHUYEN_QUI(map_data);
            p_qui->pham_vi_bay_dan_qui( gRenderer, SCREEN_WIDTH / 3, SCREEN_HEIGHT / 3, map_data);
            p_qui->ShowQui(gRenderer);
        }
    }

    for (int i = 0; i < (int)threats_list.size(); ++i)           // khởi tạo lại đạn quỉ
    {
        ThreatsObject* p_qui = threats_list.at(i);
        if (p_qui->get_bang_dan_qui().empty())
        {
            BulletObject* dan_qui = new BulletObject();          //them dan
            p_qui->init_dan_qui(dan_qui, gRenderer);
        }
    }
}

void render_game_2()
{
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);  // clear renderer
    SDL_RenderClear(gRenderer);

    gBackground2.Render(gRenderer, nullptr);                 // in anh background
    tamdung.Render( gRenderer, nullptr);
    map_data = game_map_2.GetMap();                           //xu li di chuyen, va cham map

    if ( player_nvc.gethangnong() == true )
    {
        kiem.change_gocquay( 30 );
        int jj = player_nvc.GetRect().x - player_nvc.get_width_frame();
        int ii = player_nvc.GetRect().y - player_nvc.get_height_frame();
        kiem.render_kiem(gRenderer, jj, ii, nullptr, nullptr, SDL_FLIP_NONE);
    }

    // player_nvc
    player_nvc.XU_LI_BAN_DAN(gRenderer, SCREEN_WIDTH / 2.5, SCREEN_HEIGHT / 2.5, map_data);     // xu li ban dan
    player_nvc.SetMapXY(map_data.start_x_, map_data.start_y_);                                  //xu li map di chuyen theo nhan vat
    player_nvc.ShowMain(gRenderer);                                                             //hien nhan vat chinh
    player_nvc.DiChuyenNhanVat(map_data);
    player_nvc.show_cucmau(gRenderer, maumau);

    if ( player_nvc.get_y_hientai() >= 1800 && player_nvc.get_x_hientai() >= 6000 && win_game == false )      // qui vuong
    {
        quivuong.xulibossbandan(gRenderer);
        quivuong.SetMapXY(map_data.start_x_, map_data.start_y_);
        quivuong.DICHUYENTHEO_NVC(player_nvc, gRenderer);
        quivuong.showboss(gRenderer);
        quivuong.DICHUYEN_BOSS(map_data);
        quivuong.show_mau_boss(gRenderer, mauboss);

        if (quivuong.gethanglanh())
        {
            uatuc.change_gocquay(35);
            int jj = quivuong.GetRect().x - quivuong.get_width_frame();
            int ii = quivuong.GetRect().y - quivuong.get_height_frame();
            uatuc.render_kiem(gRenderer, jj, ii, nullptr, nullptr, SDL_FLIP_NONE);
        }
    }

    game_map_2.SetMap( map_data );                                      // cap nhat vi tri moi cho start_x_, start_y_
    game_map_2.DrawMap( gRenderer );                                    //ve ban do

    if ( player_nvc.get_tangmang() )
    {
        so_mang.tangmang();                                 // an kim cuong tang mang
        player_nvc.tang_mang(false);
        solanchetmax ++;                                     //cout << "solanchetmax " << solanchetmax << endl;
    }
    so_mang.Show( gRenderer );

    if ( player_nvc.getchongchong() ) phung.show(gRenderer);
    if ( player_nvc.getchobay() ) duocbay.show(gRenderer);

}
