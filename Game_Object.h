

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "toancuc.h"
#include "ThreatsObject.h"


void load_tat_ca_qui(SDL_Renderer* des);
void load_all_boss(SDL_Renderer* des);
void load_all_main(SDL_Renderer* des);


void khoitaono_dam(VUNO& nodam);
void khoitaovuno(VUNO& qui_no);
void khoitaonhanvatchinh_no(VUNO& nvc_no);
void khoitaonodaulau(VUNO& daulau);
void khoitaonoboss(VUNO& boss_die);

extern vector<ThreatsObject*> threats_list;
vector<ThreatsObject*> Make_Threat_List();

#endif // GAME_OBJECT_H
