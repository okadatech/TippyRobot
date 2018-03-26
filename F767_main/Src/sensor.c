/*
 * sensor.c
 *
 *  Created on: 2018/01/22
 *      Author: okada_tech
 */


#include "sensor.h"



const int  HMC6352_ADDRESS = (0x21<<1);

void HMC6352_init(I2C_HandleTypeDef *handler){
	HMC6352_I2C = handler;
	uint8_t send_cmd[3];
	send_cmd[0]='G';
	send_cmd[1]=0x74;
	send_cmd[2]=0x72;
	HAL_I2C_Master_Transmit(HMC6352_I2C,HMC6352_ADDRESS ,(uint8_t*)send_cmd,3,0x0f);
	delayUs(70);
}


int HMC6352_def_set(){
	    uint8_t yaw[2];
	    uint16_t  def;
	    HAL_I2C_Master_Receive(HMC6352_I2C,HMC6352_ADDRESS,(uint8_t*)yaw,2,0x0f);
	    uint8_t yawl=yaw[0];
	    uint8_t yawh=yaw[1];
	    def = ((yawh<< 8 ) | yawl ) /10 ;
	    def=(def-359);
	    if(def<0){
	    	def=360+def;
	    }
	    return def;
}

int HMC6352_yaw_get(uint16_t def){
	uint8_t dihgreetemp = digree;
	if(mofumofu>1){
    uint8_t yaw[2];
    uint16_t digree;
    HAL_Delay(10);
    HAL_I2C_Master_Receive(HMC6352_I2C,HMC6352_ADDRESS,(uint8_t*)yaw,2,0x0f);
    uint8_t yawh=yaw[0];
    uint8_t yawl=yaw[1];
    int Hx;
    Hx = ((yawh<< 8 ) | yawl ) /10 ;
    Hx=(Hx-359);
    Hx = Hx - def;
     if(Hx<0){
     digree=Hx+360;
     }
     else{
     digree=Hx;
     }
     return digree;
	mofumofu=0;
	}
	else{
		return dihgreetemp;
		mofumofu++;
	}
}


void JY901_init(I2C_HandleTypeDef *handler){
	 JY901_I2C = handler;
}

/* cmd=1  Angular velocity Calibration
 * cmd=2  Magnetic Calibration
 * cmd=3  Calibration end
 * cmd=4  Save
 */
void HOUI_calibration(uint32_t time,uint8_t cmd){
	uint8_t send_cmd[3];
	uint8_t cycletime=0;
	if(time>1000){
		cycletime=time/1000;
	}
	switch(cmd){
	case 1:
		send_cmd[0]=0x01;
		send_cmd[1]=0x01;
		send_cmd[2]=0x00;
		HAL_I2C_Master_Transmit(JY901_I2C,JY901_I2C_ADDRESS,(uint8_t*)send_cmd,3,0xF);
		HAL_Delay(time);
	break;
	case 2:
		send_cmd[0]=0x01;
		send_cmd[1]=0x02;
		send_cmd[2]=0x00;
		HAL_I2C_Master_Transmit(JY901_I2C,JY901_I2C_ADDRESS,(uint8_t*)send_cmd,3,0xF);
		send_cmd[0]='C';
		HAL_I2C_Master_Transmit(HMC6352_I2C,HMC6352_ADDRESS,(uint8_t*)send_cmd,1,0xF);
		for(uint8_t i=0;i<cycletime;i++){
			HAL_Delay(1000);
			HAL_IWDG_Refresh(&hiwdg);
		}
	break;

	case 3:
		send_cmd[0]=0x01;
		send_cmd[1]=0x00;
		send_cmd[2]=0x00;
		HAL_I2C_Master_Transmit(JY901_I2C,JY901_I2C_ADDRESS,(uint8_t*)send_cmd,3,0xF);
		send_cmd[0]='E';
		HAL_I2C_Master_Transmit(HMC6352_I2C,HMC6352_ADDRESS,(uint8_t*)send_cmd,1,0xF);
		HAL_Delay(time);
	break;

	case 4:
		send_cmd[0]=0x00;
		send_cmd[1]=0x00;
		send_cmd[2]=0x00;
		HAL_I2C_Master_Transmit(JY901_I2C,JY901_I2C_ADDRESS,(uint8_t*)send_cmd,3,0xF);
		HAL_Delay(time);
	break;
	}
}

int JY901_def_set(){
	    uint8_t yaw[2];
	    uint16_t  def;
	    HAL_I2C_Mem_Read(JY901_I2C,JY901_I2C_ADDRESS,0x3F,I2C_MEMADD_SIZE_8BIT,(uint8_t*)yaw,2,0xFF);
	    uint8_t yawl=yaw[0];
	    uint8_t yawh=yaw[1];
	    def = ((yawh<< 8 ) | yawl ) * 180/ 32768 ;
	    def=(def-359)*(-1);
	    if(def<0){
	    	def=360+def;
	    }
	    return def;
}

int JY901_yaw_get(uint16_t def){
    uint8_t yaw[2];
    uint16_t digree;
    HAL_I2C_Mem_Read(JY901_I2C,JY901_I2C_ADDRESS,0x3F,I2C_MEMADD_SIZE_8BIT,(uint8_t*)yaw,2,0xFF);
    uint8_t yawl=yaw[0];
    uint8_t yawh=yaw[1];
    int Hx;
    Hx = ((yawh<< 8 ) | yawl ) * 180/ 32768 ;
    Hx=(Hx-359)*(-1);
    Hx = Hx - def;
     if(Hx<0){
     digree=Hx+360;
     }
     else{
     digree=Hx;
     }
     return digree;
}


void openMV_data_get(){
	int j = 0;
	while (Rxbuf_opneMV[j] != 254 && j < 11) {
			j++;
	}
	if(j>=11){
			for (int k = 0; k < 10; k++) {
				data_openMV[k] = 0;
			}
	}
	else {
			for (int k = 0; k < 10; k++) {
				if ((j + k) >= 10) {
					data_openMV[k] = Rxbuf_opneMV[k - (10 - j)];
				}
				else {
					data_openMV[k] = Rxbuf_opneMV[j + k + 1];
				}
			}
	}

	  openMVdata[0]=data_openMV[0];
	  openMVdata[1]=data_openMV[1]+(data_openMV[2]<<8);
	  openMVdata[2]=data_openMV[3]+(data_openMV[4]<<8);
	  openMVdata[3]=data_openMV[5];
	  openMVdata[4]=data_openMV[6]+(data_openMV[7]<<8);
	  openMVdata[5]=data_openMV[8]+(data_openMV[9]<<8);

	  openMVdata[1]=154-openMVdata[1];
	  openMVdata[2]=115-openMVdata[2];
	  openMVdata[4]=155-openMVdata[4];
	  openMVdata[5]=122-openMVdata[5];

	  balldata[0]= sqrt((openMVdata[1]*openMVdata[1])+(openMVdata[2]*openMVdata[2]));
	  balldata[1]=(float)(myAtan2((float)openMVdata[1],(float)openMVdata[2])/M_PI*180);
	  if(balldata[1]<0){
		 balldata[1]= 360+balldata[1];
	  }
	  float32_t Rdata;
	  Rdata=(7.5309*exp(0.0412*balldata[0]));
	  if(Rdata<10){Rdata=0;}
	  balldata[2]=(int)Rdata;

	  markerdata[0]= sqrt((openMVdata[3]*openMVdata[3])+(openMVdata[4]*openMVdata[4]));
	  markerdata[1]=(float)(myAtan2((float)openMVdata[3],(float)openMVdata[4])/M_PI*180);
	  if(markerdata[1]<0){
		  markerdata[1]= 360+markerdata[1];
	  }
	  float32_t Rdata_marker;
	  Rdata_marker=(7.5309*exp(0.0412*markerdata[0]));
	  if(Rdata_marker<10){Rdata_marker=0;}
	  markerdata[2]=(int)Rdata_marker;
}

void getplace(){
	if((Ultasonic[2]+Ultasonic[4])>150 && (Ultasonic[2]+Ultasonic[4])<220){
		 TLa=Ultasonic[2]*182/(Ultasonic[2]+Ultasonic[4]);
		 TRa=Ultasonic[4]*182/(Ultasonic[2]+Ultasonic[4]);
		  if(TLa<=65){place[0]=1;}
		  else if(TRa<=65){place[0]=5;}
		  else if(TLa>65 && TLa<80){place[0]=2;}
		  else if(TRa>65 && TRa<80){place[0]=4;}
		  else if(TRa<120 && TRa>=80){place[0]=3;}
		  else if(TLa<120 && TLa>=80){place[0]=3;}
		  else{place[0]=6;}
	}
	/*else{
		if(TIM2->CNT<=29900){place[0]=1;}
		else if(TIM2->CNT>=23100){place[0]=5;}
		else if(TIM2->CNT<=23100 && TIM2->CNT>=23070){place[0]=2;}
		else if(TIM2->CNT>=29900 && TIM2->CNT<=29930){place[0]=4;}
		else if(TIM2->CNT<=230700 && TIM2->CNT>=30000){place[0]=3;}
		else if(TIM2->CNT>=293000 && TIM2->CNT<=30000){place[0]=3;}
		else{place[0]=6;}
	}*/
	if(Ultasonic[3]>111){place[1]=5;}
	else if(Ultasonic[3]<=111 && Ultasonic[3]>97){place[1]=4;}
	else if(Ultasonic[3]<=97 && Ultasonic[3]>63){place[1]=3;}
	else if(Ultasonic[3]<=63 && Ultasonic[3]>33){place[1]=2;}
	else if(Ultasonic[3]<=33){place[1]=1;}
	else {place[1]=6;}
}


void Ultrasonic_get(){
	int j = 0;
		while (Rxbuf_Ultrasonic[j] != 253 && j < 11) {
				j++;
		}
		if(j>=11){
				for (int k = 0; k < 10; k++) {
					tempdata_ultrasonic[k] = 0;
				}
		}
		else {
				for (int k = 0; k < 10; k++) {
					if ((j + k) >= 10) {
						tempdata_ultrasonic[k] = Rxbuf_Ultrasonic[k - (10 - j)];
					}
					else {
						tempdata_ultrasonic[k] = Rxbuf_Ultrasonic[j + k + 1];
					}
				}
		}
		Ultasonic[0]=tempdata_ultrasonic[0]+(tempdata_ultrasonic[1]<<8);
		Ultasonic[1]=tempdata_ultrasonic[2]+(tempdata_ultrasonic[3]<<8);
		Ultasonic[2]=tempdata_ultrasonic[4]+(tempdata_ultrasonic[5]<<8);
		Ultasonic[3]=tempdata_ultrasonic[6]+(tempdata_ultrasonic[7]<<8);
		Ultasonic[4]=tempdata_ultrasonic[8]+(tempdata_ultrasonic[9]<<8);

}

void IR_get(){
	int j = 0;
	while (Rxbuf_IR[j] != 254 && j < 5) {
		j++;
	}
	if(j>=5){
		for (int k = 0; k < 4; k++) {
			IRtempdata[0] = 0;
		}
	}
	else {
		for (int k = 0; k < 4; k++) {
			if ((j + k) >= 4) {
				IRtempdata[k] = Rxbuf_IR[k - (4 - j)];
			}
			else {
				IRtempdata[k] = Rxbuf_IR[j + k + 1];
			}
		}
	}

	IR[1]=IRtempdata[1]+(IRtempdata[0]<<8);
	IR[0]=IRtempdata[3]+(IRtempdata[2]<<8);

}



void Line_Reset(int digree_cam,int digree_ir,int cmd){
	switch (cmd) {
	//PB4,PG15,PG13,PG11
		case 0:
			//Calibration
			break;
		case 1:
			//kick test
			break;
		case 2:
			//orange ball normal field
			if(openMVdata[2]==0){
				linetemp=0;
			}
			else if(openMVdata[0]>5){
				linetemp=0;
			}
			else{
				if(balldata[1]<=240 && balldata[1]>=120){//back
				}else{linetemp=linetemp&0b00000111;}
				if(balldata[1]<=150 && balldata[1]>=30){//right
				}else{linetemp=linetemp&0b00001101;}
				if(balldata[1]<=330 && balldata[1]>=210){//left
				}else{linetemp=linetemp&0b0001011;}
				if(balldata[1]>=300 || balldata[1]<=60){//Front
				}else{linetemp=linetemp&0b00001110;}
		   }

			break;
		case 3:
			//IR ball normal field
			if(IR[1]<=230 && IR[1]>=130){//back
			}else{linetemp=linetemp&0b00000111;}
			if(IR[1]<=140 && IR[1]>=40){//right
			}else{linetemp=linetemp&0b00001101;}
			if(IR[1]<=315 && IR[1]>=225){//left
			}else{linetemp=linetemp&0b0001011;}
			if(IR[1]>=310 || IR[1]<=50){//Front
			}else{linetemp=linetemp&0b00001110;}
			break;
		case 4:
			//orange ball big field
			if(openMVdata[2]==0){
				linetemp=0;
			}
			else if(openMVdata[0]>5){
				linetemp=0;
			}
			else{
				if(balldata[1]<=225 && balldata[1]>=135){//back
				}else{linetemp=linetemp&0b00000111;}
				if(balldata[1]<=135 && balldata[1]>=45){//right
				}else{linetemp=linetemp&0b00001101;}
				if(balldata[1]<=315 && balldata[1]>=225){//left
				}else{linetemp=linetemp&0b0001011;}
				if(balldata[1]>=315 || balldata[1]<=45){//Front
				}else{linetemp=linetemp&0b00001110;}
		   }
			break;
		case 5:
			//IR ball big field
			if(IR[1]<=230 && IR[1]>=130){//back
			}else{linetemp=linetemp&0b00000111;}
			if(IR[1]<=140 && IR[1]>=40){//right
			}else{linetemp=linetemp&0b00001101;}
			if(IR[1]<=320 && IR[1]>=220){//left
			}else{linetemp=linetemp&0b0001011;}
			if(IR[1]>=310 || IR[1]<=50){//Front
			}else{linetemp=linetemp&0b00001110;}
			break;
		case 6:
			//orange ball normal field use marker
			if(openMVdata[2]==0){
				linetemp=0;
			}
			else if(openMVdata[0]>5){
				linetemp=0;
			}
			else{
				if(balldata[1]<=240 && balldata[1]>=120){//back
				}else{linetemp=linetemp&0b00000111;}
				if(balldata[1]<=150 && balldata[1]>=30){//right
				}else{linetemp=linetemp&0b00001101;}
				if(balldata[1]<=330 && balldata[1]>=210){//left
				}else{linetemp=linetemp&0b0001011;}
				if(balldata[1]>=300 || balldata[1]<=60){//Front
				}else{linetemp=linetemp&0b00001110;}
		   }
			break;
		case 7:
			//mp3 player
			break;
	}

}


uint8_t make_end_flug(){
	int i=0;
	TIM3->CNT=(7- mode);
	if(HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_15)==1){
		while(HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_15)==1){
			i++;
			if(i>300){
				return 0;
			}
			xprintf("i=%d\r\n",i);
		}
	}
	if(i>=1000){return 0;}
	else{return 1;}
}
