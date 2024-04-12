#ifndef SOUND_
#define SOUND_

#include <SDL_mixer.h>
#include<bits/stdc++.h>
using namespace std;

class SOUND
{
public:
    SOUND();
    ~SOUND();

    void loadsound();

    Mix_Music* sungluc ;
    Mix_Music* kiem;
};
#endif // SOUND_SYSTEM_APPEND
