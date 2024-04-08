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

    void SetNum (const int& num){ chi_so_mang = num ;}
    void AddPos (const int& xPos);
    void Show(SDL_Renderer* screen);
    void Init(SDL_Renderer* screen );
    void tangmang();
    void giammang();

    void set_chi_so_mang (const int & g) { chi_so_mang = g;}
    int get_chi_so_mang() const { return chi_so_mang;}

private:
    int chi_so_mang;
    vector<int> vitri_omang;// luu vi tri xuat trai tym
};



#endif // PLAY_POWER_
