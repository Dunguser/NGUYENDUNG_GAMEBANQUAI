#include "MainObject.h"
#include "BulletObject.h"
using namespace std;


MainObject::MainObject()
{
    x_biendoi_=0;// khi di chuyen thi tang/giam bao nhieu
    y_biendoi_=0; // an trai giam bao nhieu, nhay tang bao nhieu

    x_now_pos = 7400;//vi tri x hien tai
    y_now_pos = 2000 ;

    width_frame_ =0; // kich thuoc 1 frame vi 1 anh co 5,7,8 frame
    height_frame_=0;

    frame_=0; //luu chi so cua frame, frame thu may

    status_=1; // luu trang thai di chuyen ben trai hay ben phai

    trang_thai_vao.len_ =0;// luu trang thai di chuyen cua nhan vat
    trang_thai_vao.nhay_ =0;
    trang_thai_vao.sang_phai =0;
    trang_thai_vao.sang_trai =0;
    trang_thai_vao.xuong_ =0;
    trang_thai_vao.bay_ =0;
    trang_thai_vao.can_chien_ =0;
    trang_thai_vao.chet_ = 0;

    tren_mat_dat = false;

    roi_xuong_vuc = false;

    map_x_=0;// mep moi cua ban do khi nhan vat di chuyen
    map_y_=0;

    tien_an_duoc = 0;
    come_back_time_ = 0;
    chobay = false;
    hanchebay = 0;

    sung = nullptr;
    kiem1 = nullptr ;
    andohotro = nullptr ;
}

MainObject::~MainObject()
{

}

void MainObject::loadamthanh_nvc()
{
    sung = Mix_LoadMUS( "sound/lucphat1.mp3");
    kiem1 = Mix_LoadMUS("sound/kiem.mp3");
    andohotro = Mix_LoadMUS ( "sound/ando.mp3");
    if(kiem1 == nullptr || sung == nullptr || andohotro == nullptr ) cout<<Mix_GetError();
}
bool MainObject::LoadMainImg(const string&path,SDL_Renderer *screen)
{
    SDL_Texture* cuoicung = nullptr;
    SDL_Surface* kaka=IMG_Load(path.c_str());
    if(kaka == nullptr)
    {
        cout<<"failed to load image HINH CHINH "<<path.c_str()<<endl;
        return 0;
    }
    SDL_SetColorKey(kaka,SDL_TRUE,SDL_MapRGB(kaka->format,255,255,255));
    cuoicung=SDL_CreateTextureFromSurface(screen,kaka);
    if(cuoicung==nullptr)
    {
        cout<<"failed";
        return 0;
    }
    rect_.w = kaka->w;
    rect_.h = kaka->h;
    SDL_FreeSurface ( kaka );
    mTexture = cuoicung;
    if( mTexture == nullptr)
    {
        cout<< " ngu ";
        return 0;
    }
    width_frame_ = rect_.w / SO_FRAME;
    height_frame_ = rect_.h;
    return 1;
}


void MainObject::ShowMain(SDL_Renderer*des)
// xau frame nhan vat chinh // di chuyen di dau
{
    if(trang_thai_vao.bay_==1)
    {
        if(status_ == bay_trai_) LoadMainImg("IMG/bay_trai.png",des);
        else if( status_ == bay_phai_ ) LoadMainImg("IMG/bay_phai.png",des);
    }
    else if(trang_thai_vao.can_chien_==1)
    {
        if(status_==ben_trai_) LoadImage("IMG/DAO_DAM_TRAI.png",des);
        else if(status_==ben_phai_) LoadImage("IMG/DAO_DAM_PHAI.png",des);
    }
    else if (trang_thai_vao.chet_ == 1)
    {
        LoadImage("IMG/CHET.png",des);
    }
    else
    {
        if(tren_mat_dat == true)
        {
            if( status_== ben_trai_) LoadMainImg("IMG/CHAY_TRAI_SUNG.png",des);
            else if( status_ == ben_phai_) LoadMainImg("IMG/CHAY_PHAI_SUNG.png",des);
        }
    }
    if(trang_thai_vao.sang_trai==1 || trang_thai_vao.sang_phai==1
            ||trang_thai_vao.can_chien_==1 || trang_thai_vao.chet_ == 1 )

    {
        frame_++;// neu co bien doi thi frame tang
    }
    else frame_=0;

    if(frame_ >= SO_FRAME) frame_=0;

    rect_.x = x_now_pos - map_x_; //vi tri xuat hien
    rect_.y = y_now_pos - map_y_;

    SDL_Rect*currentclip=&frame_clip_[frame_];//hien tai la dang cai anh nao // lay anh nay ma in ra

    // in frame  ra
    SDL_Rect renderquad = {rect_.x, rect_.y, width_frame_, height_frame_};
    SDL_RenderCopy( des, mTexture, currentclip, &renderquad);
}

void MainObject::Set_Clips_chay()
// ham tao clip tu nhung hinh anh lien tiep
{
    if( width_frame_>0 && height_frame_>0)
    {
        for(int i=0; i<SO_FRAME; i++)
        {
            frame_clip_[i].w = width_frame_;
            frame_clip_[i].h = height_frame_;
            frame_clip_[i].y = 0;
            frame_clip_[i].x = i*width_frame_;
        }
    }
}

void MainObject::XuLiXuKienBanPhim(SDL_Event events,SDL_Renderer*screen)
// xu li cac phim bam sang trai, sang phai, bay
{
    if(events.type==SDL_KEYDOWN)
    {
        if(events.key.keysym.sym == SDLK_RIGHT)
        {
            status_ = ben_phai_;
            trang_thai_vao.sang_phai = 1;
            trang_thai_vao.sang_trai = 0;
            LoadMainImg("IMG/CHAY_PHAI_SUNG.png",screen);
        }
        else if(events.key.keysym.sym==SDLK_LEFT)
        {
            status_=ben_trai_;
            trang_thai_vao.sang_phai=0;
            trang_thai_vao.sang_trai=1;
            LoadMainImg("IMG/CHAY_TRAI_SUNG.png",screen);
        }
        else if(events.key.keysym.sym==SDLK_UP||events.key.keysym.sym == SDLK_w)
        {
            trang_thai_vao.nhay_ = 1 ;
        }
        else if(events.key.keysym.sym == SDLK_a)
        {
            status_=ben_trai_;
            trang_thai_vao.sang_phai=0;
            trang_thai_vao.sang_trai=1;
            if(tren_mat_dat==true) LoadMainImg("IMG/CHAY_TRAI_SUNG.png",screen);
            else LoadMainImg("IMG/LON_TRAI1.png",screen);
        }
        else if(events.key.keysym.sym == SDLK_d)
        {
            status_=ben_phai_;
            trang_thai_vao.sang_phai = 1;
            trang_thai_vao.sang_trai = 0;
            if(tren_mat_dat==true) LoadMainImg("IMG/CHAY_PHAI_SUNG.png",screen);
            else LoadMainImg("IMG/LON_PHAI1.png",screen);
        }
        else if(events.key.keysym.sym == SDLK_c)
        {
            if(chobay == true)
            {
                trang_thai_vao.bay_ = 1;
                status_= bay_phai_ ;
                trang_thai_vao.sang_phai=0;
                trang_thai_vao.sang_trai=0;
                trang_thai_vao.can_chien_=0;
                LoadMainImg("IMG/bay_phai.png",screen);
            }
        }
        else if(events.key.keysym.sym == SDLK_z)
        {
            if(chobay == true )
            {
                trang_thai_vao.bay_ = 1;
                status_ = bay_trai_;
                trang_thai_vao.sang_trai=0;
                trang_thai_vao.sang_phai=0;
                trang_thai_vao.can_chien_=0;
                LoadMainImg("IMG/bay_trai.png",screen);
            }
        }
        else if(events.key.keysym.sym == SDLK_x)
        {
            if(tren_mat_dat==true)
            {
                trang_thai_vao.can_chien_ = 1;
                trang_thai_vao.sang_phai=0;
                trang_thai_vao.sang_trai=0;
                trang_thai_vao.bay_=0;
                if(status_==ben_trai_||status_==bay_trai_) LoadMainImg("IMG/DAO_DAM_TRAI.png",screen);
                else if(status_==ben_phai_||status_==bay_phai_) LoadMainImg("IMG/DAO_DAM_PHAI.png",screen);
            }
            if(chongchong == true)
            {
                kichhoathangnong(true);
                playmusic ( kiem1 );
            }
        }
    }
    else if(events.type==SDL_KEYUP)
    {
        if(events.key.keysym.sym == SDLK_RIGHT||events.key.keysym.sym == SDLK_d)
        {
            trang_thai_vao.sang_phai=0;
        }
        else if(events.key.keysym.sym == SDLK_LEFT||events.key.keysym.sym == SDLK_a)
        {
            trang_thai_vao.sang_trai=0;
        }
        else if(events.key.keysym.sym == SDLK_UP || events.key.keysym.sym == SDLK_w)
        {
            trang_thai_vao.nhay_ = 0;
        }
        else if(events.key.keysym.sym == SDLK_z)
        {
            trang_thai_vao.bay_=0;
            hanchebay--;
            if(hanchebay == 0) setchobay(false);
        }
        else if(events.key.keysym.sym == SDLK_c)
        {
            trang_thai_vao.bay_ = 0;
            hanchebay--;
            if(hanchebay == 0) setchobay(false);
        }
        else if(events.key.keysym.sym == SDLK_x)
        {
            trang_thai_vao.can_chien_=0;
        }
    }

    // xu li xay dung dan , va nap dan vao bang , lenh ban bang chuot trai
    if(events.type == SDL_MOUSEBUTTONDOWN)
    {
        if(events.button.button == SDL_BUTTON_LEFT)// ban dan
        {
            BulletObject* viendan = new BulletObject();
            KHOI_TAO_DAN_1(viendan,screen);
            playmusic( sung );
        }
        else if(events.button.button == SDL_BUTTON_RIGHT)
        {
            BulletObject* l = new BulletObject();
            KHOI_TAO_DAN_2(l,screen);
            playmusic( sung );
        }

    }
}



void MainObject::XU_LI_BAN_DAN(SDL_Renderer* des, const int& x_gioihan, const int& y_gioihan, MAP& map_data) // xu li ban dan
{
    // kiem tra so dan ban
    for(int i=0; i<(int)bangdan_nvc.size(); i++)
    {
        // lay vien dan ra khoi bang
        BulletObject*viendan = bangdan_nvc.at(i);// ham at de truy cap vao phan tu thu i // no cung tuong tu [] nhung no kiem tra ranh gioi
        if(viendan!=nullptr)
        {
            int khoang_cach_=abs( rect_.x - viendan->GetRect().x)+width_frame_+30;
            if(viendan->gettrongmanhinh()==true)// co trong man hinh, cho phep di chuyen
            {
                if(khoang_cach_ < x_gioihan && khoang_cach_>0 )
                {
                    viendan->pham_vi_dan_bay( x_gioihan, y_gioihan, x_now_pos, y_now_pos, map_data);
                    viendan->Render(des);
                }
                else viendan->settrongmanhinh(false);
            }
            else
            {
                if(status_==ben_trai_||status_==bay_trai_)
                {
                    viendan->SetRect(this->rect_.x-30,this->rect_.y+height_frame_*0.45);
                }
                else if(status_==ben_phai_||status_==bay_phai_)
                {
                    viendan->SetRect(this->rect_.x+width_frame_-30,this->rect_.y+height_frame_*0.45);
                }
            }
        }
    }
}

void MainObject::DiChuyenNhanVat(MAP &map_data) //xu li cho nhan vat di chuyen, va cham coi ban do
{
    if(come_back_time_==0)
    {
        x_biendoi_ = 0;// cho no roi xuong ban do
        y_biendoi_ += TOCDOROI;

        if(y_biendoi_>=ROITOIDA) y_biendoi_ = ROITOIDA; //toc do roi toi da

        // di chuyen qua trai, phai//khi di chuyen sang trai thi x giam
        if(trang_thai_vao.sang_trai==1)  x_biendoi_-=TOCDOCHAY;
        else if(trang_thai_vao.sang_phai==1) x_biendoi_+=TOCDOCHAY;

        if( trang_thai_vao.nhay_== 1 )// nhay binh thuong
        {
            if(tren_mat_dat==true) y_biendoi_= - NHAYBTH;
            tren_mat_dat = false;
            trang_thai_vao.nhay_ = 0;
        }

        if(trang_thai_vao.bay_ == 1)// trang thai bay
        {
            if(status_ == bay_phai_)
            {
                x_biendoi_ += TOC_DO_BAY;
                y_biendoi_ = -5;
            }
            else if(status_ == bay_trai_)
            {
                x_biendoi_ -= TOC_DO_BAY;
                y_biendoi_ = -5;
            }
            tren_mat_dat = false ;
        }
        CheckToMap(map_data);// kiem tra va cham
        MAP_DI_CHUYEN_THEO_NV(map_data);//tinh toan thong so cua map khi nhan vat di chuyen
    }
    if(come_back_time_ > 0)
    {
        come_back_time_ --;
        if(come_back_time_ == 0)
        {
            y_now_pos = SCREEN_HEIGHT*1.5;;
            x_now_pos -= 256;
            x_biendoi_ = 0;
            y_biendoi_ = 0;
        }
    }
}

void MainObject::CheckToMap(MAP&map_data)// kiem tra nhan vat va cham voi ban do
{
    int x1=0,x2=0; // gioi han kiem tra ngang // theo o vuong
    int y1=0,y2=0;                     //doc

    // kiem tra theo chieu ngang--------------------------

    // chieu cao nho nhat // chieu cao frame hay chieu cao o=64
    int height_min=min(height_frame_,TILE_SIZE);

    // tim o hien tai dang dung la oo bao nhieu
    int sai_so_can_co=1;
    x1=(x_now_pos+x_biendoi_)/TILE_SIZE;
    x2=( x_now_pos + x_biendoi_ + width_frame_ - sai_so_can_co)/TILE_SIZE;

    y1=( y_now_pos + y_biendoi_)/TILE_SIZE;
    y2=( y_now_pos + y_biendoi_ + height_min - sai_so_can_co)/TILE_SIZE;

    //kiem tra theo x1,x2,y1,y2 co o trong ban do hay ko
    if( x1 >= 0 && x2 < MAX_MAP_X && y1>=0 && y2 < MAX_MAP_Y ) // nhan vat o trong ban do
    {
        if( x_biendoi_>0 )//di sang phai
        {
            int val1 = map_data.tile[y1][x2]; // an tien / take money
            int val2 = map_data.tile[y2][x2];

            if( val1==MONEY )
            {
                map_data.tile[y1][x2]=0; playmusic(andohotro);
                an_tien();
            }
            if(val2==MONEY)
            {
                map_data.tile[y2][x2]=0;playmusic(andohotro);
                an_tien();
            }
            if( val1 == TANG_MANG )
            {
                map_data.tile[y1][x2]=0;playmusic(andohotro);
                tang_mang(true);
            }
            if(val2 == TANG_MANG)
            {
                map_data.tile[y2][x2]=0;playmusic(andohotro);
                tang_mang(true);
            }
            if( val1==CHO_BAY )
            {
                map_data.tile[y1][x2]=0;playmusic(andohotro);
                setchobay(true);
                hanchebay = SOLANBAY;
            }
            if(val2==CHO_BAY)
            {
                map_data.tile[y2][x2]=0;playmusic(andohotro);
                setchobay(true);
                hanchebay = SOLANBAY;
            }
            if( val1==PHUONG_HOANG )
            {
                map_data.tile[y1][x2]=0;playmusic(andohotro);
                kichhoatchongchong(true);
            }
            if(val2==PHUONG_HOANG)
            {
                map_data.tile[y2][x2]=0;playmusic(andohotro);
                kichhoatchongchong(true);
            }
            if( (val1 != O_TRONG || val2 != O_TRONG )
                    && val1!=MONEY && val2!=MONEY
                    && val1!= TANG_MANG &&val2 != TANG_MANG
                    && val1 != CHO_BAY && val2 != CHO_BAY
                    && val1 != PHUONG_HOANG && val2 != PHUONG_HOANG)// kiem tra xem ban do cho do co trong hay ko
                // dong y truoc, cot x sau // tren cung 1 hang y va cot thi duoc tang them
                // do chieu cao cua nhan vat lon hon 1 o la 64 nen phai check 2 o
            {
                x_now_pos = x2*TILE_SIZE-width_frame_-sai_so_can_co+15;//khi va cham thi phai tra lai vi tri cu
                x_biendoi_=0;//ko the tang dc nua//ko cho di chuyen nua
            }

        }
        else if(x_biendoi_<0)//sang trai
        {
            int val1=map_data.tile[y1][x1];
            int val2=map_data.tile[y2][x1];

            if(val1==MONEY)
            {
                map_data.tile[y1][x1]=0; playmusic(andohotro);
                an_tien();
            }
            if(val2==MONEY)
            {
                map_data.tile[y2][x1]=0; playmusic(andohotro);
                an_tien();
            }
            if( val1==TANG_MANG )
            {
                map_data.tile[y1][x2]=0; playmusic(andohotro);
                tang_mang(true);
            }
            if(val2==TANG_MANG)
            {
                map_data.tile[y2][x2]=0; playmusic(andohotro);
                tang_mang(true);
            }
            if( val1==CHO_BAY )
            {
                map_data.tile[y1][x2]=0; playmusic(andohotro);
                setchobay(true);
                hanchebay = SOLANBAY;
            }
            if(val2==CHO_BAY)
            {
                map_data.tile[y2][x2]=0;playmusic(andohotro);
                setchobay(true);
                hanchebay = SOLANBAY;
            }
            if( val1==PHUONG_HOANG )
            {
                map_data.tile[y1][x2] = 0;playmusic(andohotro);
                kichhoatchongchong(true);
            }
            if(val2==PHUONG_HOANG)
            {
                map_data.tile[y2][x2] = 0;playmusic(andohotro);
                kichhoatchongchong(true);
            }

            if( (val1 != O_TRONG || val2 != O_TRONG )
                    && val1!=MONEY && val2!=MONEY
                    && val1!= TANG_MANG &&val2 != TANG_MANG
                    && val1 != CHO_BAY && val2 != CHO_BAY
                    && val1 != PHUONG_HOANG && val2 != PHUONG_HOANG)
            {
                x_now_pos=(x1+sai_so_can_co)*TILE_SIZE-10;
                x_biendoi_=0;
            }
        }
    }
    // kiem tra theo chieu doc--------------------------------
    int width_min=min(width_frame_,TILE_SIZE);

    //===// can co de hinh anh uyen chuyen hon
    x1=(x_now_pos+20)/TILE_SIZE;
    x2=(x_now_pos+width_min-17)/TILE_SIZE;

    y1=(y_now_pos+y_biendoi_)/TILE_SIZE;
    y2=(y_now_pos+y_biendoi_+height_frame_-sai_so_can_co)/TILE_SIZE;

    if( x1>=0 && x2 < MAX_MAP_X && y1>=0 && y2 < MAX_MAP_Y )
    {
        if(y_biendoi_>0)// di xuong //roi xuong
        {
            int val1 = map_data.tile[y2][x1];
            int val2 = map_data.tile[y2][x2];

            if( val1 == MONEY )
            {
                map_data.tile[y2][x1]=0;playmusic(andohotro);
                an_tien();
            }
            if( val2 == MONEY )
            {
                map_data.tile[y2][x2]=0;playmusic(andohotro);
                an_tien();
            }
            if( val1==TANG_MANG )
            {
                map_data.tile[y1][x2]=0;playmusic(andohotro);
                tang_mang(true);
            }
            if(val2==TANG_MANG)
            {
                map_data.tile[y2][x2]=0;playmusic(andohotro);
                tang_mang(true);
            }
            if( val1==CHO_BAY )
            {
                map_data.tile[y1][x2]=0;playmusic(andohotro);
                setchobay(true);
                hanchebay = SOLANBAY;
            }
            if(val2==CHO_BAY)
            {
                map_data.tile[y2][x2]=0;playmusic(andohotro);
                setchobay(true);
                hanchebay = SOLANBAY;
            }
            if( val1==PHUONG_HOANG )
            {
                map_data.tile[y1][x2]=0;playmusic(andohotro);
                kichhoatchongchong(true);
            }
            if(val2==PHUONG_HOANG)
            {
                map_data.tile[y2][x2]=0;playmusic(andohotro);
                kichhoatchongchong(true);
            }
            if( (val1 != O_TRONG || val2 != O_TRONG )
                    && val1!=MONEY && val2!=MONEY
                    && val1!= TANG_MANG &&val2 != TANG_MANG
                    && val1 != CHO_BAY && val2 != CHO_BAY
                    && val1 != PHUONG_HOANG && val2 != PHUONG_HOANG)
            {
                y_now_pos=y2*TILE_SIZE-height_frame_-sai_so_can_co;
                y_biendoi_=0;
                tren_mat_dat=true;
            }
        }
        else if(y_biendoi_<0)// nhay len
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y1][x2];

            if(val1==MONEY)
            {
                map_data.tile[y1][x1]=0;playmusic(andohotro);
                an_tien();
            }
            if(val2==MONEY)
            {
                map_data.tile[y1][x2]=0;playmusic(andohotro);
                an_tien();
            }
            if( val1==TANG_MANG )
            {
                map_data.tile[y1][x2]=0;playmusic(andohotro);
                tang_mang(true);
            }
            if(val2==TANG_MANG)
            {
                map_data.tile[y2][x2]=0;playmusic(andohotro);
                tang_mang(true);
            }
            if( val1==CHO_BAY )
            {
                map_data.tile[y1][x2]=0;playmusic(andohotro);
                setchobay(true);
                hanchebay = SOLANBAY;
            }
            if(val2==CHO_BAY)
            {
                map_data.tile[y2][x2]=0;playmusic(andohotro);
                setchobay(true);
                hanchebay = SOLANBAY;
            }
            if( val1 == PHUONG_HOANG )
            {
                map_data.tile[y1][x2]=0;playmusic(andohotro);
                kichhoatchongchong(true);
            }
            if(val2 == PHUONG_HOANG)
            {
                map_data.tile[y2][x2]=0;playmusic(andohotro);
                kichhoatchongchong(true);
            }
            if( (val1 != O_TRONG || val2 != O_TRONG )
                    && val1!=MONEY && val2!=MONEY
                    && val1!= TANG_MANG &&val2 != TANG_MANG
                    && val1 != CHO_BAY && val2 != CHO_BAY
                    && val1 != PHUONG_HOANG && val2 != PHUONG_HOANG)
            {
                y_now_pos = (y1+sai_so_can_co)*TILE_SIZE;
                y_biendoi_ = 0;
            }
        }
    }
    // neu ko xay ra va cham voi cai nao
    x_now_pos += x_biendoi_;
    y_now_pos += y_biendoi_;

    if(x_now_pos < 0) x_now_pos=0;

    if(x_now_pos + width_frame_ > map_data.max_x_)
    {
        x_now_pos = map_data.max_x_ - width_frame_ - sai_so_can_co;
    }

    if(y_now_pos>=map_data.max_y_) come_back_time_ = 20; //roi xuong vuc
}

void MainObject::MAP_DI_CHUYEN_THEO_NV(MAP&map_data)//tinh toan thong so cua map khi nhan vat di chuyen
{
    map_data.start_x_= x_now_pos - SCREEN_WIDTH/2;
    if(map_data.start_x_<0) map_data.start_x_=0;
    else if(map_data.start_x_+SCREEN_WIDTH>=map_data.max_x_)
    {
        map_data.start_x_=map_data.max_x_-SCREEN_WIDTH;
    }
    map_data.start_y_=y_now_pos-SCREEN_HEIGHT/3;
    if(map_data.start_y_<0) map_data.start_y_=0;
    else if(map_data.start_y_+SCREEN_HEIGHT>map_data.max_y_)
    {
        map_data.start_y_=map_data.max_y_-SCREEN_HEIGHT;
    }
}

bool MainObject::get_roi_xuong_vuc()
{
    return roi_xuong_vuc;
}
void MainObject::an_tien()
{
    tien_an_duoc++ ;
}

SDL_Rect MainObject:: GetRectFrame()
{
    SDL_Rect rect;
    rect.x = rect_.x;
    rect.y = rect_.y;
    rect.h = height_frame_;
    rect.w = width_frame_;
    return rect;
}
void MainObject::loaiboviendan(const int& index) // loai bo vien dan ngoai pham vi ban
{
    int size1 = bangdan_nvc.size();
    if( size1 > 0 && index < size1)
    {
        BulletObject* viendan = bangdan_nvc.at(index);
        bangdan_nvc.erase( bangdan_nvc.begin() + index);
        if(viendan)
        {
            delete viendan;
            viendan = nullptr;
        }
    }
}
void MainObject::KHOI_TAO_DAN_2(BulletObject* viendan,SDL_Renderer*screen)
{
    if(viendan!=nullptr)
    {
        viendan->LoadImage("IMG/DAN2.png",screen);//load anh dan
        if( status_==bay_trai_ )
        {
            viendan->set_huongdan(BulletObject::ban_duoi_trai);
            viendan->SetRect(this->rect_.x+width_frame_-60,this->rect_.y+height_frame_*0.6);
        }
        else if( status_==bay_phai_ )
        {
            viendan->set_huongdan(BulletObject::ban_duoi_phai);
            viendan->SetRect(this->rect_.x+width_frame_-30,this->rect_.y+height_frame_*0.6);
        }
        viendan->set_x_biendoi(30);
        viendan->set_y_biendoi(30);
        viendan->settrongmanhinh(true);
        bangdan_nvc.push_back(viendan);
    }
}


void MainObject::KHOI_TAO_DAN_1(BulletObject* viendan, SDL_Renderer* screen)
{
    if(viendan!=nullptr)
    {
        if(status_==ben_phai_||status_==bay_phai_)
        {
            viendan->LoadImage("IMG/DAN1_PHAI.png",screen);//load anh dan
            viendan->set_huongdan( BulletObject :: ban_dan_phai );
            viendan->SetRect( this->rect_.x+width_frame_-30, this->rect_.y+height_frame_*0.45); //xet vi tri cua bien dan o dau sung
        }
        else if(status_==ben_trai_||status_==bay_trai_)
        {
            viendan->LoadImage("IMG/DAN1_TRAI.png",screen);
            viendan->set_huongdan( BulletObject::ban_dan_trai );
            viendan->SetRect( this->rect_.x-30, this->rect_.y + height_frame_*0.45);
        }
        viendan->set_x_biendoi(30);// xet toc do cua dan
        viendan->set_y_biendoi(30);
        viendan->settrongmanhinh(true);// trang thai, bam chuot là bắn , ở trong man hinh
        bangdan_nvc.push_back(viendan);// gan vao vector dan
    }
}


