/*
 * mecanum.c
 *
 *  Created on: 2017/11/05
 *      Author: okada_tech
 */


#include "omni_wheel.h"

void motor_move(uint8_t comand,uint16_t digree,uint16_t power){
			/*
				 150;¶‰ñ“]
				 200;‰E‰ñ“]
				 125;360“x@•ûˆÊC³‚ ‚è
				  */
	power=power;
		  switch(comand){

		  case 125:
			  if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13)|| HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_6)
				||HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_5)|| HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_14)){
				  if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13)){
						motor1(1000,0);
						motor2(1000,0);
						motor3(1000,0);
						motor4(1000,0);
				  }
				  if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_6)){
						motor1(0,1000);
						motor2(1000,0);
						motor3(0,1000);
						motor4(1000,0);
				  }
				  if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_5)){
						motor1(1000,0);
						motor2(0,1000);
						motor3(1000,0);
						motor4(0,1000);
				  }
				  if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_14)){
						motor1(0,1000);
						motor2(0,1000);
						motor3(0,1000);
						motor4(0,1000);
				  }

			  }
			  else{
					if(digree>=0 && digree<=360){
						if(linetemp!=0){
						if((linetemp&0b00000001)==1){
							if(digree<35 || digree>325){
								motor1(0,0);
								motor2(0,0);
								motor3(0,0);
								motor4(0,0);
							}
						}
						if(((linetemp&0b00000010)>>1)==1){
							if(digree>55 && digree<125){
								motor1(0,0);
								motor2(0,0);
								motor3(0,0);
								motor4(0,0);
							}
						}
						if(((linetemp&0b00000100)>>2)==1){
							if(digree>235 && digree<305){
								motor1(0,0);
								motor2(0,0);
								motor3(0,0);
								motor4(0,0);
							}
						}
						if(((linetemp&0b00001000)>>3)==1){
							if(digree>145 && digree<215){
							motor1(0,0);
							motor2(0,0);
							motor3(0,0);
							motor4(0,0);
							}
						}
						}
						else{
					if(digree>=0 && digree<=45){
						power1=(float)arm_sin_f32((45-digree)*M_PI/180)*power;
						power2=(float)arm_sin_f32((135-digree)*M_PI/180)*power;
						power3=(float)arm_sin_f32((225-digree)*M_PI/180)*-1*power;
						power4=(float)arm_sin_f32((315-digree)*M_PI/180)*-1*power;
						temp1=max(power1,power2);
						temp2=max(power3,temp1);
						y=max(power4,temp2);
						power1=power1*((float)power/y);
						power2=power2*((float)power/y);
						power3=power3*((float)power/y);
						power4=power4*((float)power/y);
						motor1(0,power1);
						motor2(0,power2);
						motor3(0,power3);
						motor4(0,power4);
					}
					else if(digree>45 && digree<=90){
						power1=(float)arm_sin_f32((digree-45)*M_PI/180)*power;
						power2=(float)arm_sin_f32((135-digree)*M_PI/180)*power;
						power3=(float)arm_sin_f32((225-digree)*M_PI/180)*power;
						power4=(float)arm_sin_f32((315-digree)*M_PI/180)*-1*power;
						temp1=max(power1,power2);
						temp2=max(power3,temp1);
						y=max(power4,temp2);
						power1=power1*((float)power/y);
						power2=power2*((float)power/y);
						power3=power3*((float)power/y);
						power4=power4*((float)power/y);
						motor1(power1,0);
						motor2(0,power2);
						motor3(power3,0);
						motor4(0,power4);
							  }
					else if(digree>90 && digree<=135){
						power1=(float)arm_sin_f32((digree-45)*M_PI/180)*power;
						power2=(float)arm_sin_f32((135-digree)*M_PI/180)*power;
						power3=(float)arm_sin_f32((225-digree)*M_PI/180)*power;
						power4=(float)arm_sin_f32((315-digree)*M_PI/180)*-1*power;
						temp1=max(power1,power2);
						temp2=max(power3,temp1);
						y=max(power4,temp2);
						power1=power1*((float)power/y);
						power2=power2*((float)power/y);
						power3=power3*((float)power/y);
						power4=power4*((float)power/y);
						motor1(power1,0);
						motor2(0,power2);
						motor3(power3,0);
						motor4(0,power4);
					}
					else if(digree>135 && digree<=180){
						power1=(float)arm_sin_f32((digree-45)*M_PI/180)*power;
						power2=(float)arm_sin_f32((digree-135)*M_PI/180)*power;
						power3=(float)arm_sin_f32((225-digree)*M_PI/180)*power;
						power4=(float)arm_sin_f32((315-digree)*M_PI/180)*power;
						temp1=max(power1,power2);
						temp2=max(power3,temp1);
						y=max(power4,temp2);
						power1=power1*((float)power/y);
						power2=power2*((float)power/y);
						power3=power3*((float)power/y);
						power4=power4*((float)power/y);
						motor1(power1,0);
						motor2(power2,0);
						motor3(power3,0);
						motor4(power4,0);
					}
					else if(digree>180 && digree<=225){
						power1=(float)arm_sin_f32((digree-45)*M_PI/180)*power;
						power2=(float)arm_sin_f32((digree-135)*M_PI/180)*power;
						power3=(float)arm_sin_f32((225-digree)*M_PI/180)*power;
						power4=(float)arm_sin_f32((315-digree)*M_PI/180)*power;
						temp1=max(power1,power2);
						temp2=max(power3,temp1);
						y=max(power4,temp2);
						power1=power1*((float)power/y);
						power2=power2*((float)power/y);
						power3=power3*((float)power/y);
						power4=power4*((float)power/y);
						motor1(power1,0);
						motor2(power2,0);
						motor3(power3,0);
						motor4(power4,0);
					}
					else if(digree>225 && digree<=270){
						power1=(float)arm_sin_f32((digree-45)*M_PI/180)*-1*power;
						power2=(float)arm_sin_f32((digree-135)*M_PI/180)*power;
						power3=(float)arm_sin_f32((digree-225)*M_PI/180)*power;
						power4=(float)arm_sin_f32((315-digree)*M_PI/180)*power;
						temp1=max(power1,power2);
						temp2=max(power3,temp1);
						y=max(power4,temp2);
						power1=power1*((float)power/y);
						power2=power2*((float)power/y);
						power3=power3*((float)power/y);
						power4=power4*((float)power/y);
						motor1(0,power1);
						motor2(power2,0);
						motor3(0,power3);
						motor4(power4,0);
					}
					else if(digree>270 && digree<=315){
						power1=(float)arm_sin_f32((digree-45)*M_PI/180)*-1*power;
						power2=(float)arm_sin_f32((digree-135)*M_PI/180)*power;
						power3=(float)arm_sin_f32((digree-225)*M_PI/180)*power;
						power4=(float)arm_sin_f32((315-digree)*M_PI/180)*power;
						temp1=max(power1,power2);
						temp2=max(power3,temp1);
						y=max(power4,temp2);
						power1=power1*((float)power/y);
						power2=power2*((float)power/y);
						power3=power3*((float)power/y);
						power4=power4*((float)power/y);
						motor1(0,power1);
						motor2(power2,0);
						motor3(0,power3);
						motor4(power4,0);
					}
					else if(digree>315 && digree<=360){
						power1=(float)arm_sin_f32((digree-45)*M_PI/180)*-1*power;
						power2=(float)arm_sin_f32((digree-135)*M_PI/180)*-1*power;
						power3=(float)arm_sin_f32((digree-225)*M_PI/180)*power;
						power4=(float)arm_sin_f32((digree-315)*M_PI/180)*power;
						temp1=max(power1,power2);
						temp2=max(power3,temp1);
						y=max(power4,temp2);
						power1=power1*((float)power/y);
						power2=power2*((float)power/y);
						power3=power3*((float)power/y);
						power4=power4*((float)power/y);
						motor1(0,power1);
						motor2(0,power2);
						motor3(0,power3);
						motor4(0,power4);
					}
				}
					}
				else{
					motor1(0,0);
					motor2(0,0);
					motor3(0,0);
					motor4(0,0);
				}
			  }
		  break;

		  case 130:
			  if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13)|| HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_6)
				||HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_5)|| HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_14)){
					  if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13)){
							motor1(1000,0);
							motor2(1000,0);
							motor3(1000,0);
							motor4(1000,0);
					  }
					  if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_6)){
							motor1(0,1000);
							motor2(1000,0);
							motor3(0,1000);
							motor4(1000,0);
					  }
					  if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_5)){
							motor1(1000,0);
							motor2(0,1000);
							motor3(1000,0);
							motor4(0,1000);
					  }
					  if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_14)){
							motor1(0,1000);
							motor2(0,1000);
							motor3(0,1000);
							motor4(0,1000);
					  }

				  }
				  else{

				if(digree>=0 && digree<=360){
				if(digree>=0 && digree<=45){
					power1=(float)arm_sin_f32((45-digree)*M_PI/180)*power;
					power2=(float)arm_sin_f32((135-digree)*M_PI/180)*power;
					power3=(float)arm_sin_f32((225-digree)*M_PI/180)*-1*power;
					power4=(float)arm_sin_f32((315-digree)*M_PI/180)*-1*power;
					temp1=max(power1,power2);
					temp2=max(power3,temp1);
					y=max(power4,temp2);
					power1=power1*((float)power/y);
					power2=power2*((float)power/y);
					power3=power3*((float)power/y);
					power4=power4*((float)power/y);
					motor1(0,power1);
					motor2(0,power2);
					motor3(0,power3);
					motor4(0,power4);
				}
				else if(digree>45 && digree<=90){
					power1=(float)arm_sin_f32((digree-45)*M_PI/180)*power;
					power2=(float)arm_sin_f32((135-digree)*M_PI/180)*power;
					power3=(float)arm_sin_f32((225-digree)*M_PI/180)*power;
					power4=(float)arm_sin_f32((315-digree)*M_PI/180)*-1*power;
					temp1=max(power1,power2);
					temp2=max(power3,temp1);
					y=max(power4,temp2);
					power1=power1*((float)power/y);
					power2=power2*((float)power/y);
					power3=power3*((float)power/y);
					power4=power4*((float)power/y);
					motor1(power1,0);
					motor2(0,power2);
					motor3(power3,0);
					motor4(0,power4);
						  }
				else if(digree>90 && digree<=135){
					power1=(float)arm_sin_f32((digree-45)*M_PI/180)*power;
					power2=(float)arm_sin_f32((135-digree)*M_PI/180)*power;
					power3=(float)arm_sin_f32((225-digree)*M_PI/180)*power;
					power4=(float)arm_sin_f32((315-digree)*M_PI/180)*-1*power;
					temp1=max(power1,power2);
					temp2=max(power3,temp1);
					y=max(power4,temp2);
					power1=power1*((float)power/y);
					power2=power2*((float)power/y);
					power3=power3*((float)power/y);
					power4=power4*((float)power/y);
					motor1(power1,0);
					motor2(0,power2);
					motor3(power3,0);
					motor4(0,power4);
				}
				else if(digree>135 && digree<=180){
					power1=(float)arm_sin_f32((digree-45)*M_PI/180)*power;
					power2=(float)arm_sin_f32((digree-135)*M_PI/180)*power;
					power3=(float)arm_sin_f32((225-digree)*M_PI/180)*power;
					power4=(float)arm_sin_f32((315-digree)*M_PI/180)*power;
					temp1=max(power1,power2);
					temp2=max(power3,temp1);
					y=max(power4,temp2);
					power1=power1*((float)power/y);
					power2=power2*((float)power/y);
					power3=power3*((float)power/y);
					power4=power4*((float)power/y);
					motor1(power1,0);
					motor2(power2,0);
					motor3(power3,0);
					motor4(power4,0);
				}
				else if(digree>180 && digree<=225){
					power1=(float)arm_sin_f32((digree-45)*M_PI/180)*power;
					power2=(float)arm_sin_f32((digree-135)*M_PI/180)*power;
					power3=(float)arm_sin_f32((225-digree)*M_PI/180)*power;
					power4=(float)arm_sin_f32((315-digree)*M_PI/180)*power;
					temp1=max(power1,power2);
					temp2=max(power3,temp1);
					y=max(power4,temp2);
					power1=power1*((float)power/y);
					power2=power2*((float)power/y);
					power3=power3*((float)power/y);
					power4=power4*((float)power/y);
					motor1(power1,0);
					motor2(power2,0);
					motor3(power3,0);
					motor4(power4,0);
				}
				else if(digree>225 && digree<=270){
					power1=(float)arm_sin_f32((digree-45)*M_PI/180)*-1*power;
					power2=(float)arm_sin_f32((digree-135)*M_PI/180)*power;
					power3=(float)arm_sin_f32((digree-225)*M_PI/180)*power;
					power4=(float)arm_sin_f32((315-digree)*M_PI/180)*power;
					temp1=max(power1,power2);
					temp2=max(power3,temp1);
					y=max(power4,temp2);
					power1=power1*((float)power/y);
					power2=power2*((float)power/y);
					power3=power3*((float)power/y);
					power4=power4*((float)power/y);
					motor1(0,power1);
					motor2(power2,0);
					motor3(0,power3);
					motor4(power4,0);
				}
				else if(digree>270 && digree<=315){
					power1=(float)arm_sin_f32((digree-45)*M_PI/180)*-1*power;
					power2=(float)arm_sin_f32((digree-135)*M_PI/180)*power;
					power3=(float)arm_sin_f32((digree-225)*M_PI/180)*power;
					power4=(float)arm_sin_f32((315-digree)*M_PI/180)*power;
					temp1=max(power1,power2);
					temp2=max(power3,temp1);
					y=max(power4,temp2);
					power1=power1*((float)power/y);
					power2=power2*((float)power/y);
					power3=power3*((float)power/y);
					power4=power4*((float)power/y);
					motor1(0,power1);
					motor2(power2,0);
					motor3(0,power3);
					motor4(power4,0);
				}
				else if(digree>315 && digree<=360){
					power1=(float)arm_sin_f32((digree-45)*M_PI/180)*-1*power;
					power2=(float)arm_sin_f32((digree-135)*M_PI/180)*-1*power;
					power3=(float)arm_sin_f32((digree-225)*M_PI/180)*power;
					power4=(float)arm_sin_f32((digree-315)*M_PI/180)*power;
					temp1=max(power1,power2);
					temp2=max(power3,temp1);
					y=max(power4,temp2);
					power1=power1*((float)power/y);
					power2=power2*((float)power/y);
					power3=power3*((float)power/y);
					power4=power4*((float)power/y);
					motor1(0,power1);
					motor2(0,power2);
					motor3(0,power3);
					motor4(0,power4);
				}
			}
				else{
				motor1(0,0);
				motor2(0,0);
				motor3(0,0);
				motor4(0,0);
			}
				  }
		  		  break;

		  case 150://LS
				motor1(0,power);
				motor2(0,power);
				motor3(power,0);
				motor4(power,0);
		  break;

		  case 200://RS
				motor1(power,0);
				motor2(power,0);
				motor3(0,power);
				motor4(0,power);
		  break;

		  default:
				motor1(0,0);
			    motor2(0,0);
			    motor3(0,0);
			    motor4(0,0);
		  break;
		  }
	}

void HOUI_Correction(){
	HOUI=JY901_yaw_get(HOUI_def);
if(HOUI>= 5 && HOUI<=355){
	motor1(1000,1000);
	motor2(1000,1000);
	motor3(1000,1000);
	motor4(1000,1000);
	while(HOUI>=5 && HOUI<=355){
	HOUI=JY901_yaw_get(HOUI_def);
	if(HOUI<180){
	motor1(0,(int)map_m(HOUI,0,180,200,500));
	motor2(0,(int)map_m(HOUI,0,180,200,500));
	motor3((int)map_m(HOUI,0,180,200,500),0);
	motor4((int)map_m(HOUI,0,180,200,500),0);
	//xprintf("LS now");
	//xprintf(" speed= %d\r\n",(int)map_m(HOUI,0,180,70,300));
	}
	else{
		motor1((int)map_m(HOUI,359,180,200,500),0);
		motor2((int)map_m(HOUI,359,180,200,500),0);
		motor3(0,(int)map_m(HOUI,359,180,200,500));
		motor4(0,(int)map_m(HOUI,359,180,200,500));
		//xprintf("RS now");
		//xprintf(" speed= %d\r\n",(int)map_m(HOUI,359,180,70,300));
	}
  	  HAL_IWDG_Refresh(&hiwdg);
  	  if(make_end_flug()==0){return;}
	}
	motor1(1000,1000);
	motor2(1000,1000);
	motor3(1000,1000);
	motor4(1000,1000);
}
}

int max(int a,int b){
	if(a>b){return a;}
	else{return b;}
}
long map_m(long x, long in_min, long in_max, long out_min, long out_max) {
	  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	}
