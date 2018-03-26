/*
 * actuator.c
 *
 *  Created on: 2017/11/05
 *      Author: okada_tech
 */
#include "actuator.h"

void light(int R,int B,int G){

	  sConfigOC.Pulse = B;
	  HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_1);
	  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
	  sConfigOC.Pulse = G;
	  HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_2);
	  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
	  sConfigOC.Pulse = R;
	  HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_3);
	  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
}

void motor1(int m1b,int m1a){
	if(m1a==1000 && m1b==1000){
		HAL_GPIO_WritePin(GPIOF,GPIO_PIN_9,1);
		HAL_GPIO_WritePin(GPIOF,GPIO_PIN_10,1);
		sConfigOC.Pulse = 1000;
		HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2);
		HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	}
	else if(m1a==0 && m1b==0){
		HAL_GPIO_WritePin(GPIOF,GPIO_PIN_9,1);
		HAL_GPIO_WritePin(GPIOF,GPIO_PIN_10,1);
		sConfigOC.Pulse = 1000;
		HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2);
		HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	}
	else if(m1a==m1b){
		HAL_GPIO_WritePin(GPIOF,GPIO_PIN_9,1);
		HAL_GPIO_WritePin(GPIOF,GPIO_PIN_10,1);
		sConfigOC.Pulse = m1a;
		HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2);
		HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	}
	else if(m1a>m1b){
		HAL_GPIO_WritePin(GPIOF,GPIO_PIN_9,1);
		HAL_GPIO_WritePin(GPIOF,GPIO_PIN_10,0);
		sConfigOC.Pulse = m1a;
		HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2);
		HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	}
	else{
		HAL_GPIO_WritePin(GPIOF,GPIO_PIN_9,0);
		HAL_GPIO_WritePin(GPIOF,GPIO_PIN_10,1);
		sConfigOC.Pulse = m1b;
		HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2);
		HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	}
}

void motor2(int m2b,int m2a){

	if(m2a==1000 && m2b==1000){
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,1);
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,1);
		sConfigOC.Pulse = 1000;
		HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_3);
		HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
	}
	else if(m2a==0 && m2b==0){
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,1);
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,1);
		sConfigOC.Pulse = 1000;
		HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_3);
		HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
	}
	else if(m2a==m2b){
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,1);
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,1);
		sConfigOC.Pulse = m2a;
		HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_3);
		HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
	}
	else if(m2a>m2b){
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,1);
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,0);
		sConfigOC.Pulse = m2a;
		HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_3);
		HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
	}
	else{
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,0);
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,1);
		sConfigOC.Pulse = m2b;
		HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_3);
		HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
	}
}

void motor3(int m3b,int m3a){
	if(m3a==1000 && m3b==1000){
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,1);
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,1);
		sConfigOC.Pulse = m3a;
		HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_4);
		HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
	}
	else if(m3a==0 && m3b==0){
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,1);
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,1);
		sConfigOC.Pulse = 1000;
		HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_4);
		HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
	}
	else if(m3a==m3b){
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,1);
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,1);
		sConfigOC.Pulse = m3a;
		HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_4);
		HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
	}
	else if(m3a>m3b){
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,1);
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,0);
		sConfigOC.Pulse = m3a;
		HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_4);
		HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
	}
	else{
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,0);
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,1);
		sConfigOC.Pulse = m3b;
		HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_4);
		HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
	}}



void motor4(int m4a,int m4b){
if(m4a==1000 && m4b==1000){
	HAL_GPIO_WritePin(GPIOF,GPIO_PIN_7,1);
	HAL_GPIO_WritePin(GPIOF,GPIO_PIN_8,1);
	sConfigOC.Pulse = 1000;
	HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
}
else if(m4a==0 && m4b==0){
	HAL_GPIO_WritePin(GPIOF,GPIO_PIN_7,1);
	HAL_GPIO_WritePin(GPIOF,GPIO_PIN_8,1);
	sConfigOC.Pulse = 1000;
	HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
}
else if(m4a==m4b){
	HAL_GPIO_WritePin(GPIOF,GPIO_PIN_7,1);
	HAL_GPIO_WritePin(GPIOF,GPIO_PIN_8,1);
	sConfigOC.Pulse = m4a;
	HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
}
else if(m4a>m4b){
	HAL_GPIO_WritePin(GPIOF,GPIO_PIN_7,1);
	HAL_GPIO_WritePin(GPIOF,GPIO_PIN_8,0);
	sConfigOC.Pulse = m4a;
	HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
}
else{
	HAL_GPIO_WritePin(GPIOF,GPIO_PIN_7,0);
	HAL_GPIO_WritePin(GPIOF,GPIO_PIN_8,1);
	sConfigOC.Pulse = m4b;
	HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
}
}
void beep(uint8_t time,uint16_t on_time,uint16_t off_time){
	for(uint8_t fortime=0;fortime<time;fortime++){
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,1);
		HAL_Delay(on_time);
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,0);
		HAL_Delay(off_time);
	}
}

long map_a(long x, long in_min, long in_max, long out_min, long out_max) {
	  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	}
