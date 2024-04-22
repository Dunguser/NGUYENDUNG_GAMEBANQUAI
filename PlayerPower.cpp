#include "PlayerPower.h"
using namespace std;

PlayerPower::PlayerPower()
{
    chi_so_mang = 0;
}
PlayerPower::~PlayerPower() {}
void PlayerPower:: AddPos(const int& xp)
{
    vitri_omang.push_back(xp);
}

void PlayerPower ::Show (SDL_Renderer* screen)
{
    for(int i= 0 ; i <(int)vitri_omang.size(); i++)
    {
        rect_.x = vitri_omang.at(i);
        rect_.y = 10;
        Render(screen);
    }
}
void PlayerPower :: Init(SDL_Renderer* screen,const string& path)
{
    LoadImage( path.c_str(), screen );
    if( (int)vitri_omang.size()>0 ) vitri_omang.clear();
    for(int i = 0; i < chi_so_mang; i++)
    {
        AddPos(20 + 40*i);
    }
}
void PlayerPower :: tangmang()
{
    chi_so_mang ++ ;
    int cuoi = vitri_omang.back();
    cuoi += 40;
    vitri_omang.push_back( cuoi );
}

void PlayerPower ::giammang()
{
    chi_so_mang --;
    vitri_omang.pop_back();
}




Hotrobay::Hotrobay()
{
    x_pos = 0;
    y_pos = 0;
}
Hotrobay::~Hotrobay() {}
void Hotrobay::init(SDL_Renderer* screen, const string& path)
{
    bool ret = LoadImage(path.c_str(),screen);
    if(ret==0)
    {
        cout<<"that bai";
    }
}
void Hotrobay::show(SDL_Renderer* screen)
{
    rect_.x = x_pos;
    rect_.y = y_pos;
    Render(screen,nullptr);
}

//PlayerMoney ::PlayerMoney()
//{
//    x_pos_ = 0;
//    y_pos_ = 0;
//}
//
//PlayerMoney::~PlayerMoney()
//{
//
//}
//void PlayerMoney :: Init(SDL_Renderer* screen)
//{
//     LoadImg("img/money.png",screen);
//}
//
//void PlayerMoney :: Show(SDL_Renderer* screen)
//{
//    rect_.x = x_pos_;
//    rect_.y = y_pos_;
//    Render(screen);
//}




