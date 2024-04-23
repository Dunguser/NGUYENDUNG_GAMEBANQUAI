#ifndef PLAY_POWER_
#define PLAY_POWER_

#include "commonfunction.h"
#include "BaseObject.h"

using namespace std;

class PlayerPower : public BaseObject
{
public :
    PlayerPower();
    ~PlayerPower ();

    void AddPos (const int& xPos);

    void Show(SDL_Renderer* screen);
    void Init(SDL_Renderer* screen, const string& path );
    void tangmang();
    void giammang();

    void set_chi_so_mang (const int & g) { chi_so_mang = g;}
    int get_chi_so_mang() const { return chi_so_mang;}
    vector<int>get_o_mang(){return vitri_omang;}
private:
    int chi_so_mang;
    vector<int> vitri_omang;// luu vi tri xuat trai tym
    int x_pos;
    int y_pos;
};




class Hotrobay : public BaseObject
{
public:
    Hotrobay();
    ~Hotrobay();
    void init(SDL_Renderer* screen,const string& path);
    void show(SDL_Renderer* screen);
    void SetPos(const int& x, const int & y ){ x_pos = x; y_pos = y;}

private:
    int x_pos;
    int y_pos;
};


#endif // PLAY_POWER_
