/*
 * actuator.h
 *
 *  Created on: 2017/11/05
 *      Author: okada_tech
 */

#ifndef ACTUATOR_H_
#define ACTUATOR_H_
#include "management.h"

TIM_MasterConfigTypeDef sMasterConfig;
TIM_OC_InitTypeDef sConfigOC;
TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig;

void light(int R,int B,int G);
void motor1(int m1b,int m1a);
void motor2(int m2b,int m2a);
void motor3(int m3b,int m3a);
void motor4(int m4a,int m4b);
void beep(uint8_t time,uint16_t on_time,uint16_t off_time);
long map_a(long x, long in_min, long in_max, long out_min, long out_max);
#endif /* ACTUATOR_H_ */
