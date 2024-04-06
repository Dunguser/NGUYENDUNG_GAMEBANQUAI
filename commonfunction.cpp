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

    if( bottomA <= topB ) return false;
    if( topA >= bottomB ) return false;
    if( rightA <= leftB ) return false;
    if( leftA >= rightB ) return false;

    return true;

}

//    // Case 1: size object 1 < size object 2
//    if (leftA > leftB && leftA < rightB)
//    {
//        if (topA > topB && topA < bottomB) return true;
//    }
//    if (leftA > leftB && leftA < rightB)
//    {
//        if (bottomA > topB && bottomA < bottomB) return true;
//    }
//    if (rightA > leftB && rightA < rightB)
//    {
//        if (topA > topB && topA < bottomB) return true;
//    }
//    if (rightA > leftB && rightA < rightB)
//    {
//        if (bottomA > topB && bottomA < bottomB) return true;
//    }
//
//    // Case 2: size object 1 < size object 2
//    if (leftB > leftA && leftB < rightA)
//    {
//        if (topB > topA && topB < bottomA) return true;
//    }
//    if (leftB > leftA && leftB < rightA)
//    {
//        if (bottomB > topA && bottomB < bottomA) return true;
//    }
//    if (rightB > leftA && rightB < rightA)
//    {
//        if (topB > topA && topB < bottomA) return true;
//    }
//    if (rightB > leftA && rightB < rightA)
//    {
//        if (bottomB > topA && bottomB < bottomA) return true;
//    }
//
//    // Case 3: size object 1 = size object 2
//    if (topA == topB && rightA == rightB && bottomA == bottomB)
//    {
//        return true;
//    }
//    return false;















