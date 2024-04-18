#ifndef ALL_ANH_NVC
#define ALL_ANH_NVC


#include "BaseObject.h"
#include "BulletObject.h"
#include <bits/stdc++.h>
enum trang_thai_main
{
    chaytrai,
    chayphai,
    lontrai,
    lonphai,
    baytrai,
    bayphai,
    damtrai,
    damphai,
};
extern BaseObject player_main [8];

enum LOAI_DAN_BASE
{
    DAN1_TRAI,
    DAN1_PHAI,
    DAN3,
    DAN4,

    DAN_QUI_TRAI,
    DAN_QUI_PHAI,

    DAN_QUI_THUONG,
    ten_trai ,
    ten_phai ,
};

extern BaseObject dan_[9];
//extern BulletObject dan_[9];

#endif // ALL_ANH_NVC
