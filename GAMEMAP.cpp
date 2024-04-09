
#include"GAMEMAP.h"
using namespace std;

void GAMEMAP::LoadMap(const string &name)
{
    FILE*fp=NULL;
    fopen_s(&fp,name.c_str(),"rb");
    if(fp==NULL)
    {
        return ;
    }
    game_map_.othu_x_=0;
    game_map_.othu_y_=0;
    for(int i=0; i<MAX_MAP_Y; i++)
    {
        for(int j=0; j<MAX_MAP_X; j++)
        {
            fscanf(fp,"%d",&game_map_.tile[i][j]);
            int val=game_map_.tile[i][j];
            if(val>0)
            {
                if(j>game_map_.othu_x_)
                {
                    game_map_.othu_x_=j;
                }
                if(i>game_map_.othu_y_)
                {
                    game_map_.othu_y_=i;
                }
            }
        }
    }

    // phan nay giai thich cho cho max_x_ ben ham checktomap
    game_map_.max_x_=(game_map_.othu_x_+1)*TILE_SIZE;
    game_map_.max_y_=(game_map_.othu_y_+1)*TILE_SIZE;

    game_map_.start_x_=0;
    game_map_.start_y_=0;
    game_map_.file_name_=name;
    fclose(fp);
}


void  GAMEMAP::LoadTiles(SDL_Renderer*screen)
// load cac hinh anh tile, vi du ngoi o 1.png, co o 2.png
{
    string img="E:/bat_dau_game/MAP/";
    for(int i=0; i<MAX_TILES; i++)
    {
        string haphuong=img+to_string(i)+".png";
        ifstream file(haphuong);
        if(!file)
        {
            continue;
        }
        else
        {
            tile_mat[i].LoadImage(haphuong,screen);
        }
    }
}
void  GAMEMAP::DrawMap(SDL_Renderer*screen)
//fill toan bo hinh anh vao cac vi tri
{
    int x1=0,x2=0,y1=0,y2=0;// xac dinh cac diem fill hinh anh
    x1=(game_map_.start_x_%TILE_SIZE)*-1;// fill tu x1->x2
    x2=x1+SCREEN_WIDTH+(x1==0?0:TILE_SIZE);

    y1=(game_map_.start_y_%TILE_SIZE)*-1;
    y2=y1+SCREEN_HEIGHT+(y1==0?0:TILE_SIZE);
    // bat dau fill

    int map_x=0,map_y=0; // vi tri cua o
    map_y=game_map_.start_y_/TILE_SIZE;

    for(int i=y1; i<y2; i+=TILE_SIZE)
    {
        map_x=game_map_.start_x_/TILE_SIZE;
        for(int j=x1; j<x2; j+=TILE_SIZE)
        {
            int val=game_map_.tile[map_y][map_x];
            if(val>0)
            {
                tile_mat[val].SetRect(j,i);// in ra tai vi tri (j,i)
                tile_mat[val].Render(screen,NULL);// in ra
            }
            map_x++;
            if (map_x >= MAX_MAP_X || map_y >= MAX_MAP_Y) break;// Thêm kiểm tra để tránh vòng lặp vô hạn
        }
        map_y++;
        if (map_y >= MAX_MAP_Y) break;// Thêm kiểm tra để tránh vòng lặp vô hạn
    }
}



























//#include<iostream>
//#include "gamemap.h"
//#include "commonfunction.h"
//
//using namespace std;
//
//// doc file va load cac cai 0,1,2,3,4 de tao map
//void GAMEMAP::LoadMap(const string &name)
//{
//    FILE*fp=NULL;
//    fopen_s(&fp,name.c_str(),"rb");
//    if(fp==NULL)
//    {
//        return ;
//    }
//    game_map_.othu_x_=0;
//    game_map_.othu_y_=0;
//    for(int i=0; i<MAX_MAP_Y; i++)
//    {
//        for(int j=0; j<MAX_MAP_X; j++)
//        {
//            fscanf(fp,"%d",&game_map_.tile[i][j]);
//            int val=game_map_.tile[i][j];
//            if(val>0)
//            {
//                if(j>game_map_.othu_x_)
//                {
//                    game_map_.othu_x_=j;
//                }
//                if(i>game_map_.othu_y_)
//                {
//                    game_map_.othu_y_=i;
//                }
//            }
//        }
//    }
//    game_map_.othu_x_=(game_map_.othu_x_+1)*TILE_SIZE;
//    game_map_.othu_y_=(game_map_.othu_y_+1)*TILE_SIZE;
//
//    game_map_.start_x_=0;
//    game_map_.start_y_=0;
//    game_map_.file_name_=name;
//    fclose(fp);
//}
//
//void GAMEMAP::LoadTiles(SDL_Renderer*screen)
//{
//    char file_img[100];
//    FILE*fp=NULL;
//    for(int i=0; i<MAX_TILES; i++)
//    {
//        //sprintf(file_img,"E:/hoccodetrochoi/map/%d.png",i);
//        sprintf(file_img,"MAP/%d.png",i);
//        fopen_s(&fp,file_img,"rb");
//        if(fp==NULL)
//        {
//            continue;
//        }
//        fclose(fp);
//        tile_mat[i].LoadImage(file_img,screen);
//    }
//}
//void GAMEMAP::DrawMap(SDL_Renderer* screen)
//{
//    int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
//    int map_x = 0, map_y = 0;
//
//    map_x = game_map_.start_x_ / TILE_SIZE;
//    map_y = game_map_.start_y_ / TILE_SIZE;
//
//    x1 = (game_map_.start_x_ % TILE_SIZE) * (-1);
//    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);
//
//    y1 = (game_map_.start_y_ % TILE_SIZE) * (-1);
//    y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);
//
//    for (int i = y1; i < y2; i += TILE_SIZE)
//    {
//        map_x = game_map_.start_x_ / TILE_SIZE;
//        for (int j = x1; j < x2; j += TILE_SIZE)
//        {
//            int val = game_map_.tile[map_y][map_x];
//            if (val > 0)
//            {
//                // set vi tri
//                tile_mat[val].SetRect(j, i);
//                tile_mat[val].Render(screen,NULL);
//            }
//            map_x++;
//            // Thêm kiểm tra để tránh vòng lặp vô hạn
//            if (map_x >= MAX_MAP_X || map_y >= MAX_MAP_Y)
//            {
//                break;
//            }
//        }
//        map_y++;
//        // Thêm kiểm tra để tránh vòng lặp vô hạn
//        if (map_y >= MAX_MAP_Y)
//        {
//            break;
//        }
//    }
//}
//
