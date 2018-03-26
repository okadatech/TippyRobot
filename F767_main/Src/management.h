/*
 * management.h
 *
 *  Created on: 2018/01/22
 *      Author: okada_tech
 */

#ifndef MANAGEMENT_H_
#define MANAGEMENT_H_

#include <stdbool.h>
#include <string.h>
#include "stm32f7xx_hal.h"
#include "dma.h"
#include "i2c.h"
#include "iwdg.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "math.h"
#include <stdlib.h>
#define ARM_MATH_CM7
#include "arm_math.h"
#include "xprintf.h"
#include "microsectimer.h"
#include "myatan2.h"
#include "DFPlayer_Mini_mp3.h"
#include "actuator.h"
#include "omni_wheel.h"
#include "sensor.h"

int temp1,temp2,y;
int power1,power2,power3,power4,digree,power;
uint16_t HOUI,HOUI_def;
int digtemp;
uint8_t Rxbuf_opneMV[11];
uint8_t Rxbuf_Ultrasonic[11];
uint8_t Rxbuf_IR[5];
uint16_t IR[2];
uint16_t Ultasonic[5];
int16_t openMVdata[6];
int16_t balldata[3];
int16_t markerdata[3];
int16_t IRdata[2];
uint8_t mode;
uint8_t place[2];
uint16_t TRa;
uint16_t TLa;
uint8_t linetemp;
uint16_t  mofumofu,mofumofu2;
#endif /* MANAGEMENT_H_ */
