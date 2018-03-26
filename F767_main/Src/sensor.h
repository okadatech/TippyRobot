/*
 * sensor.h
 *
 *  Created on: 2018/01/22
 *      Author: okada_tech
 */

#ifndef SENSOR_H_
#define SENSOR_H_

#include "management.h"
#include "stm32f7xx_hal.h"
#include "i2c.h"
#include "iwdg.h"
#include <stdbool.h>
#include <string.h>


uint8_t data_openMV[10];
uint8_t tempdata_ultrasonic[10];
uint8_t IRtempdata[4];
I2C_HandleTypeDef *JY901_I2C;
I2C_HandleTypeDef *HMC6352_I2C;

#define JY901_I2C_ADDRESS (0x50<<1)
void HMC6352_init(I2C_HandleTypeDef *handler);
int HMC6352_def_set();
int HMC6352_yaw_get(uint16_t def);
void JY901_init(I2C_HandleTypeDef *handler);
void HOUI_calibration(uint32_t time,uint8_t cmd);
int JY901_def_set();
int JY901_yaw_get(uint16_t def);
void openMV_data_get();
void Ultrasonic_get();
void IR_get();
void Line_Reset(int digree_cam,int digree_ir,int cmd);
uint8_t make_end_flug();
void getplace();
#endif /* SENSOR_H_ */
