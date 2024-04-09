#ifndef MENU_
#define MENU_

#include "commonfunction.h"
#include "TextObject.h"

#define so_lua_chon 4

using namespace std;


class MENU : public BaseObject
{
public:
    MENU();
    ~MENU();

    int showmenu ( SDL_Renderer* des, TTF_Font * font);
    bool check_chuot_chon (int x,int y, SDL_Rect rect); //toa do cua chuot co o trong cac lua chon khong

private:

    TextObject text_menu[so_lua_chon];
    SDL_Rect vitriluachon [ so_lua_chon ];
};


#endif // MENU_
