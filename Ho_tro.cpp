#include "Ho_tro.h"

void ho_tro()
{
    // phong chu tinh thoi gian cho
    string time1 = " TIME : ";
    thoi_gian = SDL_GetTicks()/1000 ;
    time_play = thoi_gian - last_time + 1 ;
    if(cai_time)
    {
        last_time = thoi_gian ;
        time_play = thoi_gian - last_time + 1 ;
        cai_time = false;
    }
    string show_time_play = to_string(time_play);
    time1 += show_time_play;
    thoi_gian_choi.SetText(time1);
    thoi_gian_choi.LoadFromRenderText(gFont, gRenderer);
    thoi_gian_choi.RenderText(gRenderer, SCREEN_WIDTH - 180, 20);

    string da_diet = "KILLED : ";
    string showkill = to_string(so_qui_bi_giet);
    da_diet += showkill;
    da_giet.SetText(da_diet);
    da_giet.LoadFromRenderText(gFont, gRenderer);
    da_giet.RenderText(gRenderer, SCREEN_WIDTH - 180, 50);

    string tien_hientai = "MONEY : ";
    tien_hientai = "MONEY : ";
    tong_tien = player_nvc.get_tienanduoc();
    string show_tien = to_string(tong_tien);
    tien_hientai += show_tien;
    antien.SetText(tien_hientai);
    antien.LoadFromRenderText(gFont, gRenderer);
    antien.RenderText(gRenderer, SCREEN_WIDTH - 180, 80);

    SDL_RenderPresent(gRenderer); //xuat ra man hinh hien tai

    // thoi gian cham lai ---------------------------------------------------------
    {

        ImpTimer fps_timer;
        real_imp_time = fps_timer.get_ticks();
        time_one_frame = 1000 / FRAME_PER_SECOND;
        if (real_imp_time < time_one_frame)
        {
            int delay_time = time_one_frame - real_imp_time;
            if (delay_time > 0)
                SDL_Delay(delay_time);
        }
    }

    thoi_gian_choi.Free();
    antien.Free();
    da_giet.Free();
}


void ho_tro_2()
{
    string time1 = " TIME : ";
    thoi_gian = SDL_GetTicks()/1000 ;
    time_play = thoi_gian - last_time + 1 ;
    if(cai_time)
    {
        last_time = thoi_gian ;
        time_play = thoi_gian - last_time + 1 ;
        cai_time = false;
    }

    string show_time_play = to_string(time_play);
    time1 += show_time_play;
    thoi_gian_choi.SetText(time1);
    thoi_gian_choi.LoadFromRenderText(gFont, gRenderer);
    thoi_gian_choi.RenderText(gRenderer, SCREEN_WIDTH - 180, 20);
    thoi_gian_choi.Free();

    SDL_RenderPresent ( gRenderer );

    ImpTimer fps_timer;
    real_imp_time = fps_timer.get_ticks();
    time_one_frame = 1000 / FRAME_PER_SECOND;
    if (real_imp_time < time_one_frame)
    {
        int delay_time = time_one_frame - real_imp_time;
        if (delay_time > 0)
            SDL_Delay(delay_time);
    }

}
