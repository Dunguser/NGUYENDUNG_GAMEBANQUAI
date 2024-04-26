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


SDL_Window * gWindow = nullptr;
SDL_Renderer * gRenderer = nullptr;
SDL_Event gEvent;


TTF_Font * gFont = nullptr ; // phong chu
TTF_Font * gFont2 = nullptr;
Mix_Music * nhacnen = nullptr;//am thanh
Mix_Chunk * bom = nullptr;
Mix_Chunk * danquino = nullptr  ;
Mix_Chunk* quaibichem = nullptr ;
Mix_Chunk* tiengdam = nullptr ;
Mix_Chunk* daulauno = nullptr ;
Mix_Chunk* vakiem = nullptr;
TTF_Font * font_bao = nullptr ;




