
#ifndef GAME_MAP_H_
#define GAME_MAP_H_

#include"commonfunction.h"
#include "BaseObject.h"
#include<bits/stdc++.h>

#define MAX_TILES 30 //  cac cai hinh anh toi da chen vao, da,soi,co


// MAP moi chi luu chi so, ko luu hinh anh
// can them 1 doi tuong de hien hinh anh
// ke thua tu BaseObject
class TileMat:public BaseObject
{
public:
    TileMat(){;}
    ~TileMat(){;}

};

//GAMEMAP ket hop cung TileMat de in hinh anh ban do ra
class GAMEMAP
{
public:
    GAMEMAP(){;}
    ~GAMEMAP(){;}

    void LoadMap( const string& name);//doc thong tin cua file de xay dung ban do
    void LoadTiles(SDL_Renderer*screen);// load cac hinh anh tile, vi du ngoi o 1.png, co o 2.png
    void DrawMap(SDL_Renderer*screen);//fill toan bo hinh anh vao cac vi tri
    MAP GetMap()const {return game_map_;}// lay map ra

    void SetMap(MAP &map_data)// kien thiet map// tao map
    {
        game_map_=map_data;
    }

private:
    MAP game_map_; //chua toan bo thong tin cua ban do. trang thai, chi so,vi tri
    TileMat tile_mat[MAX_TILES]; // doi tuong luu tru hinh anh// vi du cai gach, da cay


};

#endif // GAME_MAP_H_
