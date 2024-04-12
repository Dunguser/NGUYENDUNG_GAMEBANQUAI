#ifndef ALL_ANH_QUI
#define ALL_ANH_QUI

#include "BaseObject.h"
#include <bits/stdc++.h>

using namespace std;


enum anh_qui
{
    ditrai,
    diphai,
    dem
};

extern BaseObject tat_ca_anh_qui[2];

enum boss_qui
{
    boss_run_trai,
    boss_run_phai,
    boss_dam_trai,
    boss_dam_phai,
    boss_ban_trai,
    boss_ban_phai,
    boss_lon_trai,
    boss_lon_phai,
};

extern BaseObject all_anh_boss [8];

#endif // ALL_ANH_QUI
