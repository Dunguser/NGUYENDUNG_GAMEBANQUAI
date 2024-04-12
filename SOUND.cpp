
#include "SOUND.h"
using namespace std;

SOUND::SOUND()
{
    sungluc = nullptr;
    kiem = nullptr;
}
SOUND::~SOUND()
{

}
void SOUND::loadsound()
{
    cout<<"kaka"<<endl;
    sungluc = Mix_LoadMUS("sound/lucphat1.mp3");
    kiem = Mix_LoadMUS("sound/kiem.mp3");
    if(sungluc == nullptr )cout<<"failed"<<endl;
}
