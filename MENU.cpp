#include "MENU.h"

using namespace std;

MENU::MENU()
{

}
MENU::~MENU()
{

}

int MENU::showmenu(SDL_Renderer* des, TTF_Font* font)
{
    bool ret = LoadImage("IMG/menu.jpg", des);
    if (ret == false)
    {
        cout << SDL_GetError();
        return -3333;
    }

    for (int i = 0; i < so_lua_chon; i++)
    {
        vitriluachon[i].x = SCREEN_WIDTH/2 - 80 ;
        vitriluachon[i].y = 400+ 50 * i;
    }

    text_menu[0].SetText("START");
    text_menu[1].SetText("TUTORIAL");
    text_menu[2].SetText("OPTIONS");
    text_menu[3].SetText("SHOP");

    for (int i = 0; i < so_lua_chon; i++)
    {
        text_menu[i].setcolor(TextObject::BLACK_TEXT);
    }

    bool di_den[so_lua_chon] = {0, 0, 0, 0};
    SDL_Event chuot;

    int xc = 0, yc = 0; // vị trí của con trỏ chuột
    while (true)
    {
        Render(des, nullptr); // vẽ hình ảnh menu lên màn hình
        // Vẽ các dòng chữ trên menu
        for (int i = 0; i < so_lua_chon; i++)
        {
            text_menu[i].LoadFromRenderText(font, des);
            text_menu[i].RenderText(des, vitriluachon[i].x, vitriluachon[i].y);
            //cout<<i<<" ";
        }

        while (SDL_PollEvent(&chuot))
        {
            switch (chuot.type)
            {
            case SDL_QUIT:
                return 1;
            case SDL_MOUSEMOTION:
            {

                xc = chuot.motion.x;
                yc = chuot.motion.y;
                cout<< xc <<" ; "<<yc<<endl;
                for (int i = 0; i < so_lua_chon; i++)
                {
                    SDL_Rect kaka = text_menu[i].text(vitriluachon[i].x,vitriluachon[i].y);;
                    if (check_chuot_chon(xc, yc, kaka))
                    {
                        if (di_den[i] == false)
                        {
                            di_den[i] = true;
                            text_menu[i].setcolor(TextObject::RED_TEXT);
                        }
                    }
                    else
                    {
                        if (di_den[i] == true)
                        {
                            di_den[i] = false;
                            text_menu[i].setcolor(TextObject::BLACK_TEXT);
                        }
                    }
                }
            }
            break;
            case SDL_MOUSEBUTTONDOWN:
            {
                xc = chuot.motion.x;
                yc = chuot.motion.y;

                for (int i = 0; i < so_lua_chon; i++)
                {
                    SDL_Rect kaka = text_menu[i].text(vitriluachon[i].x,vitriluachon[i].y);;
                    if (check_chuot_chon(xc, yc, kaka))
                    {
                        return i+1; // đã chọn lựa chọn thứ i
                    }
                }
            }
            break;
            case SDL_KEYDOWN:
                if (chuot.key.keysym.sym == SDLK_ESCAPE) return 1;
            default:
                break;
            }
        }
        SDL_RenderPresent(des); // cập nhật màn hình
    }
    return 20;
}

bool MENU:: check_chuot_chon (int x,int y, SDL_Rect rect)
{
    if(x >= rect.x && x<= rect.x + rect.w &&
            y >= rect.y && y <= rect.y + rect.h )
    {
        return true;
    }
    return false;
}




//int MENU::showmenu (SDL_Renderer* des, TTF_Font * font)
//{
//    bool ret = LoadImage("IMG/menu.jpg",des);
//    if(ret == false)
//    {
//        cout<<SDL_GetError();
//        return -3333;
//    }
//
//    for(int i =0 ; i< so_lua_chon ; i++)
//    {
//        vitriluachon[i].x = 200 ;
//        vitriluachon [i].y = 200+ 50*i;
//    }
//    text_menu[0].SetText("START");
//    text_menu[0].setcolor(TextObject::BLACK_TEXT);
//    text_menu[0].RenderText(des, vitriluachon[0].x, vitriluachon[0].y);
//
//    text_menu[1].SetText("TOTURIAL");
//    text_menu[1].setcolor(TextObject::BLACK_TEXT);
//    text_menu[1].RenderText(des, vitriluachon[1].x, vitriluachon[1].y);
//
//    text_menu[2].SetText("OPTIONS");
//    text_menu[2].setcolor(TextObject::BLACK_TEXT);
//    text_menu[2].RenderText(des, vitriluachon[2].x, vitriluachon[2].y);
//
//    text_menu[3].SetText("SHOP");
//    text_menu[3].setcolor(TextObject::BLACK_TEXT);
//    text_menu[3].RenderText(des, vitriluachon[2].x, vitriluachon[2].y);
//
//    bool di_den[so_lua_chon] = {0,0,0,0};
//    SDL_Event chuot;
//
//    int xc = 0, yc = 0; // vi tri cua con tro chuot
//    while(true)
//    {
////        SDL_Rect renderquad = {rect_.x,rect_.y,width_frame_,height_frame_};
////        SDL_RenderCopy(des, mTexture, nullptr, &renderquad);
//
//        Render(des,nullptr);// load anh len
//        for(int i=0;i<so_lua_chon;i++)// load cac lua chon tren menu
//        {
//            text_menu[i].LoadFromRenderText( font , des );
//
//        }
//        while(SDL_PollEvent( &chuot ))// vong lap su kien
//        {
//            switch (chuot.type)
//            {
//            case SDL_QUIT:
//                return 1;
//            case SDL_MOUSEMOTION:
//                {
//                    xc = chuot.motion.x;
//                    yc = chuot.motion.y;
//                    for(int i=0;i<so_lua_chon;i++)
//                    {
//                        SDL_Rect kaka = text_menu[i].text(vitriluachon[i].x,vitriluachon[i].y);
//                        if(check_chuot_chon( xc, yc, kaka))
//                        {
//                            if(di_den[i] == false)
//                            {
//                                di_den[i] = true;
//                                text_menu[i].setcolor(TextObject :: RED_TEXT);
//                            }
//                        }
//                        else
//                        {
//                            if(di_den[i] == true)
//                            {
//                                di_den[i] = false;
//                                text_menu[i].setcolor(TextObject :: BLACK_TEXT);
//                            }
//                        }
//                    }
//                }
//                break;
//
//            case SDL_MOUSEBUTTONDOWN:
//                {
//                    xc = chuot.motion.x;
//                    yc = chuot.motion.y;
//
//                    for(int i=0;i<so_lua_chon;i++)
//                    {
//                        SDL_Rect kaka = text_menu[i].text(vitriluachon[i].x,vitriluachon[i].y);
//                        if(check_chuot_chon( xc, yc, kaka))
//                        {
//                            return i; // da chon lua_chon thi i+1
//                        }
//                    }
//                }
//                break;
//            case SDL_KEYDOWN:
//                if(chuot.key.keysym.sym == SDLK_ESCAPE)return 1;
//            default:
//                break;
//            }
//        }
//    }
//    SDL_Flip(des);
//    return 1;
//}
