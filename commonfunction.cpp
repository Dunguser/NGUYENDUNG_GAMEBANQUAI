#include "commonfunction.h"

bool  SDLCommonFunc::CheckCollision(const SDL_Rect& object1,const SDL_Rect& object2)
{
    int leftA = object1.x;
    int rightA = object1.x + object1.w;
    int topA = object1.y;
    int bottomA = object1.y + object1.h;

    int leftB = object2.x;
    int rightB = object2.x + object2.w;
    int topB = object2.y;
    int bottomB = object2.y + object2.h;

        // Case 1: size object 1 < size object 2
    if (leftA > leftB && leftA < rightB && topA > topB && topA < bottomB) return true;
    if (leftA > leftB && leftA < rightB && bottomA > topB && bottomA < bottomB) return true;
    if (rightA > leftB && rightA < rightB&&topA > topB && topA < bottomB) return true;
    if (rightA > leftB && rightA < rightB&&bottomA > topB && bottomA < bottomB) return true;


    // Case 2: size object 1 < size object 2
    if (leftB > leftA && leftB < rightA&&topB > topA && topB < bottomA) return true;
    if (leftB > leftA && leftB < rightA&& bottomB > topA && bottomB < bottomA) return true;
    if (rightB > leftA && rightB < rightA&&topB > topA && topB < bottomA) return true;
    if (rightB > leftA && rightB < rightA&&bottomB > topA && bottomB < bottomA) return true;

    // Case 3: size object 1 = size object 2
    if (topA == topB && rightA == rightB && bottomA == bottomB) return true;

    return false;
}


bool SDLCommonFunc:: check_chuot_chon (int x,int y, SDL_Rect rect)
{
    if(x >= rect.x && x<= rect.x + rect.w &&
            y >= rect.y && y <= rect.y + rect.h )
    {
        return true;
    }
    return false;
}

TTF_Font * gFont = nullptr ; // phong chu
TTF_Font * gFont2 = nullptr;
Mix_Music * nhacnen = nullptr;//am thanh
Mix_Chunk * bom = nullptr;
Mix_Chunk * danquino = nullptr  ;
Mix_Chunk* quaibichem = nullptr ;
Mix_Chunk* tiengdam = nullptr ;
Mix_Chunk* daulauno = nullptr ;

//BaseObject tamdung;
//BaseObject tamdung2;
//SDL_Rect nutdung = {SCREEN_WIDTH - 80, 0, 80,78 };
//SDL_Rect tieptuc = {625 , 460 -32 , 115,40};
//SDL_Rect playagain = {450, 800, 120, 71};
//SDL_Rect restart = {600, 740 , 160 -32 , 60 };
//SDL_Rect cut = { 625 , 670 -32 , 120 , 30};



