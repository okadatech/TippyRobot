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
#include "i2c.h"
#include "iwdg.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
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
void read_Ultrasonic();
/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
int start;
int Duration[5];
int Distance[5];
int Distance_temp[5];
uint32_t timeout;
uint8_t Echo;
uint8_t Txbuf[11];
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
  MX_I2C1_Init();
  MX_USART1_UART_Init();
  MX_IWDG_Init();
  MX_TIM6_Init();

  /* USER CODE BEGIN 2 */

	init_xpritf(&huart2);
	xdev_out(uart_putc);
	HAL_IWDG_Refresh(&hiwdg);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
	  read_Ultrasonic();

	  if(Distance[3]==0){Distance[3]=Distance_temp[3];}

	  for(int i=0;i<5;i++){
	  	 if(Distance[i]==5000){Distance[i]=Distance_temp[i];}
	  }


	  for(int i=0;i<5;i++){
	  xprintf(" [%d]=%d",i,Distance[i]);
	  }
	  xprintf("\r\n");
	  HAL_IWDG_Refresh(&hiwdg);

	  Txbuf[0]=253;
	  Txbuf[1]= (uint8_t)( Distance[0] & 0b0000000011111111);
	  Txbuf[2]= (uint8_t)((Distance[0] & 0b1111111100000000)>>8);
	  Txbuf[3]= (uint8_t)( Distance[1] & 0b0000000011111111);
	  Txbuf[4]= (uint8_t)((Distance[1] & 0b1111111100000000)>>8);
	  Txbuf[5]= (uint8_t)( Distance[2] & 0b0000000011111111);
	  Txbuf[6]= (uint8_t)((Distance[2] & 0b1111111100000000)>>8);
	  Txbuf[7]= (uint8_t)( Distance[3] & 0b0000000011111111);
	  Txbuf[8]= (uint8_t)((Distance[3] & 0b1111111100000000)>>8);
	  Txbuf[9]= (uint8_t)( Distance[4] & 0b0000000011111111);
	  Txbuf[10]=(uint8_t)((Distance[4] & 0b1111111100000000)>>8);
	  HAL_UART_Transmit(&huart1,(uint8_t*)Txbuf,11,0x0f);
	  HAL_IWDG_Refresh(&hiwdg);

	  for(int i=0;i<5;i++){
		  Distance_temp[i]=Distance[i];
	  }
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI
                              |RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
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

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_I2C1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
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
void read_Ultrasonic(){

	  	  //HAL_Delay(3);
		  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,0);
		  HAL_Delay(1);
		  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,1);
		  delayUs(20);
		  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,0);
		  Echo=HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_8);
		  start = getUs();
		  timeout=0;
		  while(Echo==0 && timeout==0){
			  if(getUs()-start>2000){
				  timeout=1;
			  }
			  Echo=HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_8);
		  }
		  if(timeout==0){
			  timeout=0;
			  start = getUs();
			  Echo=HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_8);
			  while(Echo==1 && timeout==0){
				  if(getUs()-start>20000){
					  timeout=1;
		           }
			  Echo=HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_8);
		      }
			  Duration[0]=getUs()-start;
		           if(timeout==1){
		        	   Distance[0]=5000;
		           }
		           else{
		        	   Distance[0] = Duration[0]*340*100/1000000/2;
		           }
		  }
		  else{
		  Distance[0]=5000;
		  }

		  HAL_IWDG_Refresh(&hiwdg);

		  //HAL_Delay(3);
		  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,0);
		  HAL_Delay(1);
		  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,1);
		  delayUs(20);
		  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,0);
		  Echo=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3);
		  start = getUs();
		  timeout=0;
		  while(Echo==0 && timeout==0){
			  if(getUs()-start>2000){
				  timeout=1;
			  }
			  Echo=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3);
		  }
		  if(timeout==0){
			  timeout=0;
			  start = getUs();
			  Echo=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3);
			  while(Echo==1 && timeout==0){
				  if(getUs()-start>20000){
					  timeout=1;
				  }
				  Echo=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3);
			  }
			  Duration[3]=getUs()-start;
			  if(timeout==1){
				  Distance[3]=5000;
			  }
			  else{
				  Distance[3] = Duration[3]*340*100/1000000/2;
			  }
		  }
		  else{
			  Distance[3]=5000;
		  }
		  HAL_IWDG_Refresh(&hiwdg);


		  //HAL_Delay(3);
		  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,0);
		  HAL_Delay(1);
		  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,1);
		  delayUs(20);
		  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,0);
		  Echo=HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_12);
		  start = getUs();
		  timeout=0;
		  while(Echo==0 && timeout==0){
			  if(getUs()-start>2000){
				  timeout=1;
			  }
			  Echo=HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_12);
		  }
		  if(timeout==0){
			  timeout=0;
			  start = getUs();
			  Echo=HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_12);
			  while(Echo==1 && timeout==0){
				  if(getUs()-start>20000){
					  timeout=1;
				  }
				  Echo=HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_12);
			  }
			  Duration[2]=getUs()-start;
			  if(timeout==1){
				  Distance[2]=5000;
			  }
			  else{
				  Distance[2] = Duration[2]*340*100/1000000/2;
			  }
		  }
		  else{
			  Distance[2]=5000;
		  }
		  HAL_IWDG_Refresh(&hiwdg);

		  //HAL_Delay(3);
		  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,0);
		  HAL_Delay(1);
		  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,1);
		  delayUs(20);
		  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,0);
		  Echo=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4);
		  start = getUs();
		  timeout=0;
		  while(Echo==0 && timeout==0){
			  if(getUs()-start>2000){
				  timeout=1;
			  }
			  Echo=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4);
		  }
		  if(timeout==0){
			  timeout=0;
			  start = getUs();
			  Echo=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4);
			  while(Echo==1 && timeout==0){
				  if(getUs()-start> 20000){
					  timeout=1;
				  }
				  Echo=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4);
			  }
			  Duration[4]=getUs()-start;
			  if(timeout==1 ){
				  Distance[4]=5000;
			  }
			  else{
				  Distance[4] = Duration[4]*340*100/1000000/2;
			  }
		  }
		  else{
			  Distance[4]=5000;
		  }
		  HAL_IWDG_Refresh(&hiwdg);


		  //HAL_Delay(3);
		  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,0);
		  HAL_Delay(1);
		  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,1);
		  delayUs(20);
		  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,0);
		  Echo=HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_11);
		  start = getUs();
		  timeout=0;
		  while(Echo==0 && timeout==0){
			  if(getUs()-start>2000){
				  timeout=1;
			  }
			  Echo=HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_11);
		  }
		  if(timeout==0){
			  timeout=0;
			  start = getUs();
			  Echo=HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_11);
			  while(Echo==1 && timeout==0){
				  if(getUs()-start>20000){
					  timeout=1;
				  }
				  Echo=HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_11);
			  }
			  Duration[1]=getUs()-start;
			  if(timeout==1){
				  Distance[1]=5000;
			  }
			  else{
				  Distance[1] = Duration[1]*340*100/1000000/2;
			  }
		  }
		  else{
			  Distance[1]=5000;
		  }
		  HAL_IWDG_Refresh(&hiwdg);


}
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
