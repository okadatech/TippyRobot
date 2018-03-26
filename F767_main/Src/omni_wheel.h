/*
 * mecanum.h
 *
 *  Created on: 2017/11/05
 *      Author: okada_tech
 */

#ifndef OMNI_WHEEL_H_
#define OMNI_WHEEL_H_

#include "management.h"

#define bleak_time 0

int max(int a,int b);
long map_m(long x, long in_min, long in_max, long out_min, long out_max) ;
void HOUI_Correction();
void motor_move(uint8_t comand,uint16_t digree,uint16_t power);

#endif /* OMNI_WHEEL_H_ */
