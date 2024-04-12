#ifndef QUIVUONG_
#define QUIVUONG_

#include <bits/stdc++.h>
#include "commonfunction.h"
#include "BaseObject.h"
#include "GAMEMAP.h"
#include <SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include "BulletObject.h"


using namespace std;

#define TOCDOROI 0.8
#define ROITOIDA 40
#define TOCDOCHAY 9
#define O_TRONG 0
#define NHAYBTH 20
#define NHAY_CAO_BAY 10
#define TOC_DO_BAY 20
#define SO_FRAME 8


class QUIVUONG  :: public BaseObject
{
public :
    QUIVUONG ();
    ~QUIVUONG();

    enum di_chuyen
    {
        trai,
        phai,
    };


};













#endif // QUIVUONG_
