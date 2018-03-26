/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f3xx_hal.h"
#include "iwdg.h"
#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include "myatan2.h"
#include "stdlib.h"
#include "xprintf.h"
#include "microsectimer.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
int IR[12];
int IRkyori;;
float Vx,Vy,digree;
uint8_t count;
uint8_t Txdata[13];
uint32_t sortdata0[3]={0}, sortdata1[3]={0}, sortdata2[3]={0}, sortdata3[3]={0}, sortdata4[3]={0},
		 sortdata5[3]={0}, sortdata6[3]={0},sortdata7[3]={0}, sortdata8[3]={0}, sortdata9[3]={0},
		 sortdata10[3]={0}, sortdata11[3]={0};
uint32_t tempdata0[3]={0},tempdata1[3]={0},tempdata2[3]={0},tempdata3[3]={0},tempdata4[3]={0},
		 tempdata5[3]={0},tempdata6[3]={0},tempdata7[3]={0},tempdata8[3]={0},tempdata9[3]={0},
		 tempdata10[3]={0},tempdata11[3];
int32_t IRdata[12];
int int_sort( const void *p, const void *q ) {
    return *(uint32_t*)p - *(uint32_t*)q;
}
#define data_cnt  sizeof(sortdata0)/sizeof(uint32_t)
/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_USART1_UART_Init();
  MX_IWDG_Init();

  /* USER CODE BEGIN 2 */

  init_xpritf(&huart2);
  xdev_out(uart_putc);
  //HAL_I2C_Slave_Transmit_IT(&hi2c1,(uint8_t*)Txdata,3);
  count=0;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
	  for(uint8_t j=0;j<12;j++){
		  IR[j]=0;
	  }
	  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,1);
	  delayUs(5);
	  for(int k=0;k<1020;k++){
		  IR[0]=IR[0]+HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_7);
		  IR[1]=IR[1]+HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0);
		  IR[2]=IR[2]+HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1);
		  IR[3]=IR[3]+HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_8);
		  IR[4]=IR[4]+HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_9);
		  IR[5]=IR[5]+HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_10);
		  IR[6]=IR[6]+HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_11);
		  IR[7]=IR[7]+HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_12);
		  IR[8]=IR[8]+HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3);
		  IR[9]=IR[9]+HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4);
		  IR[10]=IR[10]+HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5);
		  IR[11]=IR[11]+HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_15);
	  }
	  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,0);

  	  tempdata0[count]=IR[0];
  	  tempdata1[count]=IR[1];
  	  tempdata2[count]=IR[2];
  	  tempdata3[count]=IR[3];
  	  tempdata4[count]=IR[4];
  	  tempdata5[count]=IR[5];
  	  tempdata6[count]=IR[6];
  	  tempdata7[count]=IR[7];
  	  tempdata8[count]=IR[8];
  	  tempdata9[count]=IR[9];
  	  tempdata10[count]=IR[10];
  	  tempdata11[count]=IR[11];

  	  for(uint8_t i=0;i<3;i++){
  	  sortdata0[i]=tempdata0[i];
  	  sortdata1[i]=tempdata1[i];
  	  sortdata2[i]=tempdata2[i];
  	  sortdata3[i]=tempdata3[i];
  	  sortdata4[i]=tempdata4[i];
  	  sortdata5[i]=tempdata5[i];
  	  sortdata6[i]=tempdata6[i];
  	  sortdata7[i]=tempdata7[i];
  	  sortdata8[i]=tempdata8[i];
  	  sortdata9[i]=tempdata9[i];
  	  sortdata10[i]=tempdata10[i];
  	  sortdata11[i]=tempdata11[i];
  	  }

  	  qsort(sortdata0,data_cnt,4,int_sort);
  	  qsort(sortdata1,data_cnt,4,int_sort);
  	  qsort(sortdata2,data_cnt,4,int_sort);
  	  qsort(sortdata3,data_cnt,4,int_sort);
  	  qsort(sortdata4,data_cnt,4,int_sort);
  	  qsort(sortdata5,data_cnt,4,int_sort);
  	  qsort(sortdata6,data_cnt,4,int_sort);
  	  qsort(sortdata7,data_cnt,4,int_sort);
  	  qsort(sortdata8,data_cnt,4,int_sort);
  	  qsort(sortdata9,data_cnt,4,int_sort);
  	  qsort(sortdata10,data_cnt,4,int_sort);
  	  qsort(sortdata11,data_cnt,4,int_sort);

  	  IRdata[0]=sortdata0[1];
  	  IRdata[1]=sortdata1[1];
  	  IRdata[2]=sortdata2[1];
  	  IRdata[3]=sortdata3[1];
  	  IRdata[4]=sortdata4[1];
  	  IRdata[5]=sortdata5[1];
  	  IRdata[6]=sortdata6[1];
  	  IRdata[7]=sortdata7[1];
  	  IRdata[8]=sortdata8[1];
  	  IRdata[9]=sortdata9[1];
  	  IRdata[10]=sortdata10[1];
  	  IRdata[11]=sortdata11[1];


	  IRdata[0]=IRdata[0]-30;
	  if(IRdata[0]<10){
		IRdata[0]=0;
	  }
	  IRdata[1]=IRdata[1]-180;
	  if(IRdata[1]<10){
		 IRdata[1]=0;
	  }
	  IRdata[2]=IRdata[2]-100;
	  if(IRdata[2]<10){
		 IRdata[2]=0;
	  }
	  IRdata[3]=IRdata[3]-80;
	  if(IRdata[3]<10){
		 IRdata[3]=0;
	  }
	  IRdata[4]=IRdata[4]-80;
	  if(IRdata[4]<10){
		 IRdata[4]=0;
	  }
	  IRdata[5]=IRdata[5]-80;
	  if(IRdata[5]<10){
		 IRdata[5]=0;
	  }
	  IRdata[6]=IRdata[6]-100;
	  if(IRdata[6]<10){
		 IRdata[6]=0;
	  }
	  IRdata[7]=IRdata[7]-40;
	  if(IRdata[7]<10){
		 IRdata[7]=0;
	  }
	  IRdata[8]=IRdata[8]-130;
	  if(IRdata[8]<10){
		 IRdata[8]=0;
	  }
	  IRdata[9]=IRdata[9]-70;
	  if(IRdata[9]<10){
		 IRdata[9]=0;
	  }
	  IRdata[10]=IRdata[10]-60;
	  if(IRdata[10]<10){
		 IRdata[10]=0;
	  }
	  IRdata[11]=IRdata[11]-120;
	  if(IRdata[11]<10){
		 IRdata[11]=0;
	  }


	  digree=0;
	  IRkyori=IRdata[0];
	    for(int m=0;m<12;m++){
	    if(IRkyori<IRdata[m]){IRkyori=IRdata[m];}
	    }
	  if(IRkyori==0){
	    digree=0;
	  }
	  if(IRdata[0]>400){
		  Vy=(IRdata[1])*0.5+(IRdata[2])*0.866025404+(IRdata[10])*(-0.866025404)+(IRdata[11])*(-0.5);
		  Vx=(IRdata[0])+(IRdata[1])*0.866025404+(IRdata[2])*0.5+(IRdata[10])*0.5+(IRdata[11])*(-0.866025404);
		  digree = myAtan2(Vy,Vx)/3.1415926*180;
		  IRkyori=IRdata[0];
	  }
	    if(IRkyori==IRdata[0]){
	      Vy=(IRdata[1])*0.5+(IRdata[2])*0.866025404+(IRdata[10])*(-0.866025404)+(IRdata[11])*(-0.5);
	      Vx=(IRdata[0])+(IRdata[1])*0.866025404+(IRdata[2])*0.5+(IRdata[10])*0.5+(IRdata[11])*(-0.866025404);
	       digree = myAtan2(Vy,Vx)/3.1415926*180;
	      }
	     else if(IRkyori==IRdata[1]){
	         Vy=IRdata[1]*0.5+(IRdata[2])*0.866025404+(IRdata[3])+(IRdata[11])*(-0.5);
	         Vx=IRdata[0]+(IRdata[1])*0.866025404+(IRdata[2])*0.5+(IRdata[11])*(-0.866025404);
	          digree = myAtan2(Vy,Vx)/3.1415926*180;
	        }
	     else if(IRkyori==IRdata[11]){
	      Vy=(IRdata[1]+50)*0.5+(IRdata[9])*(-1)+(IRdata[10])*(-0.866025404)+(IRdata[11])*(-0.5);
	      Vx=(IRdata[0]+50)+(IRdata[1]+50)*0.866025404+(IRdata[10])*0.5+(IRdata[11])*(-0.866025404);
	       digree = myAtan2(Vy,Vx)/3.1415926*180;
	      }
	     else if(IRkyori==IRdata[2]){
	       Vy=IRdata[1]*0.5+IRdata[2]*0.866025404+IRdata[3]+IRdata[4]*0.866025404;
	        Vx=IRdata[0]+IR[1]*0.866025404+IRdata[2]*0.5+IRdata[4]*(-0.5);
	         digree = myAtan2(Vy,Vx)/3.1415926*180;
	      }
	     else if(IRkyori==IRdata[10]){
	       Vy=IRdata[8]*(-0.866025404)+IRdata[9]*(-1)+IRdata[10]*(-0.866025404)+IRdata[11]*(-0.5);
	       Vx=(IRdata[0]+50)+IRdata[8]*(-0.5)+IRdata[10]*0.5+IRdata[11]*(-0.866025404);
	      digree = myAtan2(Vy,Vx)/3.1415926*180;
	      }
	      else if(IRkyori==IRdata[3]){
	       Vy=IRdata[1]*0.5+IRdata[2]*0.866025404+IRdata[3]+IRdata[4]*0.866025404+IRdata[5]*0.5;
	       Vx=IRdata[1]*0.866025404+IRdata[2]*0.5+IRdata[4]*(-0.5)+IRdata[5]*(-0.866025404);
	       digree = myAtan2(Vy,Vx)/3.1415926*180;
	       }
	      else if(IRkyori==IRdata[9]){
	       Vy=IRdata[7]*(-0.5)+IRdata[8]*(-0.866025404)+IRdata[9]*(-1)+IRdata[10]*(-0.866025404)+IRdata[11]*(-0.5);
	       Vx=IRdata[7]*(-0.866025404)+IRdata[8]*(-0.5)+IRdata[10]*0.5+IRdata[11]*(-0.866025404);
	       digree = myAtan2(Vy,Vx)/3.1415926*180;
	       }
	      else if(IRkyori==IRdata[4]){
	         Vy=IRdata[2]*0.866025404+(IRdata[3])+(IRdata[4])*0.866025404+(IRdata[5])*0.5;
	         Vx=IRdata[2]*0.5+(IRdata[4])*(-0.5)+(IRdata[5])*(-0.866025404)+(IRdata[6])*(-1);
	         digree = myAtan2(Vy,Vx)/3.1415926*180;
	       }
	      else if(IRkyori==IRdata[8]){
	       Vy=IRdata[7]*(-0.5)+(IRdata[8])*(-0.866025404)+(IRdata[9])*(-1)+(IRdata[10])*(-0.866025404);
	       Vx=IRdata[6]*(-1)+(IRdata[7])*(-0.866025404)+(IRdata[8])*(-0.5)+(IRdata[10])*0.5;
	       digree = myAtan2(Vy,Vx)/3.1415926*180;
	       }
	      else if(IRkyori==IRdata[5]){
	        Vy=IRdata[3]+(IRdata[4])*0.866025404+(IRdata[5])*0.5+(IRdata[7])*(-0.5);
	        Vx=IRdata[4]*(-0.5)+IRdata[5]*(-0.866025404)+(IRdata[6])*(-1)+(IRdata[7])*(-0.866025404);
	        digree = myAtan2(Vy,Vx)/3.1415926*180;
	       }
	       else if(IRkyori==IRdata[7]){
	        Vy=IRdata[5]*0.5+(IRdata[7])*(-0.5)+(IRdata[8])*(-0.866025404)+(IRdata[9])*(-1);
	        Vx=IRdata[5]*(-0.866025404)+(IRdata[6])*(-1)+(IRdata[7])*(-0.866025404)+(IRdata[8])*(-0.5);
	       digree = myAtan2(Vy,Vx)/3.1415926*180;
	       }
	       else if(IRkyori==IRdata[6]){
	        Vy=IRdata[4]*0.866025404+(IRdata[5])*0.5+(IRdata[7])*(-0.5)+(IRdata[8])*(-0.866025404);
	        Vx=IRdata[4]*(-0.5)+(IRdata[5])*(-0.866025404)+(IRdata[6])*(-1)+(IRdata[7])*(-0.866025404)+(IRdata[8])*(-0.5);
	        digree = myAtan2(Vy,Vx)/3.1415926*180;
	        }
	       if(digree<0){
	    digree=digree+360;
	    }


		 xprintf(" rad=%d",(int)digree);
		 xprintf(" R=%d",(int)IRkyori);
	 	 /*for(uint8_t i=0;i<12;i++){
	 	  xprintf(" %d=%d",i,IRdata[i]);
	 	  }*/
	 	  xprintf("\r\n");
		  Txdata[0]=254;
		  Txdata[1]=(uint8_t)((((uint16_t)digree) & 0b1111111100000000)>>8);
		  Txdata[2]=(uint8_t)(((uint16_t)digree) & 0b0000000011111111);
		  Txdata[3]=(uint8_t)((((uint16_t)IRkyori) & 0b1111111100000000)>>8);
		  Txdata[4]=(uint8_t)(((uint16_t)IRkyori) & 0b0000000011111111);
		  HAL_UART_Transmit(&huart1,(uint8_t*)Txdata,5,0xff);

  	  if(count>=2){
  		  count=0;
  	  }
  	  else{
  		  count++;
  	  }

		HAL_IWDG_Refresh(&hiwdg);
  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler_Debug */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
