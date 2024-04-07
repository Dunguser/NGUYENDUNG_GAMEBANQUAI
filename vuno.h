#ifndef VU_NO_
#define VU_NO_

#include "commonfunction.h"
#include "BaseObject.h"


using namespace std;

#define num_frame_no 8
class VUNO : public BaseObject
{
public :
    VUNO();
    ~VUNO();

    void set_clip();
    void set_frame(const int & fr) {frame_ = fr;}
    virtual bool LoadImage ( const string& path , SDL_Renderer* screen);
    void show(SDL_Renderer* screen);
    int get_frame_height()const { return frame_height ;}
    int get_frame_width()const { return frame_width ; }
private:
    int frame_height;
    int frame_width;

    int frame_;
    SDL_Rect frame_clip_[num_frame_no];
};



#endif // VU_NO_
