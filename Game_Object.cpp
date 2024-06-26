#include "Game_Object.h"
using namespace std;


void load_tat_ca_qui(SDL_Renderer* des)
{
    tat_ca_anh_qui[ditrai].LoadImage("IMG/quai_di_trai2.png",des);
    tat_ca_anh_qui[diphai].LoadImage("IMG/quai_di_phai2.png",des);
}

void load_all_boss (SDL_Renderer* des)
{
    all_anh_boss[boss_run_trai].LoadImage("IMG/QUAI/qui_chay_trai.png",des);
    all_anh_boss[boss_run_phai].LoadImage("IMG/QUAI/qui_chay_phai.png",des);
    all_anh_boss[boss_dam_phai].LoadImage("IMG/QUAI/qui_dam_phai.png",des);
    all_anh_boss[boss_dam_trai].LoadImage("IMG/QUAI/qui_dam_trai.png",des);
    all_anh_boss[boss_ban_phai].LoadImage("IMG/QUAI/qui_cung_phai.png",des);
    all_anh_boss[boss_ban_trai].LoadImage("IMG/QUAI/qui_cung_trai.png",des);
    all_anh_boss[boss_lon_trai].LoadImage("IMG/QUAI/qui_lon_trai.png",des);
    all_anh_boss[boss_lon_phai].LoadImage("IMG/QUAI/qui_lon_phai.png",des);
}

vector<ThreatsObject*> Make_Threat_List()
{
    vector<ThreatsObject*> list_threats;
    int len ;
    if ( demdem== 0)
    {
        len = 40;
        demdem++;
    }
    else len =60;
    ThreatsObject* qui_tuan_tra = new ThreatsObject[len];
    for(int i=0; i< len; i++)
    {
        ThreatsObject* p_qui = qui_tuan_tra + i ;
        if(p_qui != nullptr)
        {
            p_qui->LoadImage( "IMG/quai_di_trai.png", gRenderer );
            p_qui->set_clips();

            if(i > 38)
            {
                p_qui->set_x_quipos( 7000 + i * 50 );
                p_qui->set_y_quipos ( 2500);
            }
            else
            {
                p_qui->set_x_quipos( 100*(i+2)+500 );            // cai dat vi tri xuat hien
                p_qui->set_y_quipos( 360);
            }
            int gioi_han_trai;
            int gioi_han_phai ;
            if( level_1)
            {
                gioi_han_trai = p_qui->get_x_quipos()-80;        // gioi han trai,phai
                gioi_han_phai = p_qui->get_x_quipos()+80;
            }
            if( level_3)
            {
                gioi_han_trai = p_qui->get_x_quipos() - 60;        // gioi han trai,phai
                gioi_han_phai = p_qui->get_x_quipos() + 60;
            }

            p_qui->set_gioi_han_dichuyen( gioi_han_trai, gioi_han_phai );
            p_qui->set_trang_thai_trai(1);

            BulletObject* dan_qui = new BulletObject();          //them dan
            p_qui->init_dan_qui( dan_qui, gRenderer);

            list_threats.push_back( p_qui );
        }
    }
    return list_threats;
}

void khoitaovuno(VUNO &qui_no)
{
    bool tret = qui_no.LoadImage ("IMG/dan_no_1.png",gRenderer);
    if(tret == false) cout<<" falied to load explosion "<<endl;
    qui_no.set_clip();
}
void khoitaonhanvatchinh_no( VUNO& nvc_no )
{
    bool tret = nvc_no.LoadImage ("IMG/dan_qui_no_1.png",gRenderer);
    if(tret == false) cout<<" falied to load explosion nvc"<<endl;
    nvc_no.set_clip();
}
void khoitaonodaulau ( VUNO & daulau)
{
    bool tret = daulau.LoadImage ("IMG/QUAI/no.png",gRenderer);
    if(tret == false) cout<<" falied to load explosion nvc"<<endl;
    daulau.set_clip();
}

void khoitaonoboss ( VUNO& boss_die)
{
    bool tret = boss_die.LoadImage ("IMG/QUAI/nguyentu.png",gRenderer);
    if(tret == false) cout<<" falied to load explosion nvc"<<endl;
    boss_die.set_clip();
}

void khoitaono_dam (VUNO & nodam)
{
    bool tret = no_dam.LoadImage ("IMG/QUAI/no_dam.png",gRenderer);
    if(tret == false) cout<<" falied to load explosion nvc"<<endl;
    no_dam.set_clip();
}

vector<ThreatsObject*> threats_list;
vector<ThreatsObject*> threats_list3;

void load_all_main (SDL_Renderer* des)
{
    player_main[chaytrai].LoadImage("IMG/CHAY_TRAI_SUNG.png",des);
    player_main[chayphai].LoadImage("IMG/CHAY_PHAI_SUNG.png",des);
    player_main[bayphai].LoadImage("IMG/bay_phai.png",des);
    player_main[baytrai].LoadImage("IMG/bay_trai.png",des);
    player_main[damphai].LoadImage("IMG/DAO_DAM_PHAI.png",des);
    player_main[damtrai].LoadImage("IMG/DAO_DAM_TRAI.png",des);
    player_main[lontrai].LoadImage("IMG/LON_TRAI1.png",des);
    player_main[lonphai].LoadImage("IMG/LON_PHAI1.png",des);
    player_main[chet].LoadImage("IMG/CHET.png",des);
}

