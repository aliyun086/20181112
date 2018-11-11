
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
	
/**
	******************************************************************************
	* @user                   IIC接口定义
	******************************************************************************
	*
	*							 GND   电源地
  *              VCC   接3.3v电源
  *              SCL   接PB6（SCL）
  *              SDA   接PB7（SDA）
	*
	*******************************************************************************
	*/
	
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
#include "i2c.h"
#include "usart.h"
#include "gpio.h"
#include "delay.h"
#include "oled.h"
#include "bmp.h"
#include "24c02.h"
#include "stdio.h"
#include "string.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
	uint8_t TEXT_Buffer2[4][8] = {"STM32Cub","eMX & KE","IL_RTE I","IC TEST"};
	uint8_t TEXT_Buffer[] = {"STM32CubeMX & KEIL_RTE IIC TEST"};
	#define SIZE_OF_BUF sizeof(TEXT_Buffer)	
	uint8_t datatemp[SIZE_OF_BUF];	
	uint8_t time_buff[7] = {0,0,12,1,7,5,24};  //24=00011000——18的BCD码
	extern	I2C_HandleTypeDef  hi2c1;
	volatile unsigned int timenum;       
	volatile unsigned long time_delay;  
	uint16_t w24c02=0xA0 ;
	uint16_t r24c02=0xA1 ;
	uint16_t OLED=0x78 ;
	uint16_t DS3231_w=0xD0 ;
	uint16_t DS3231_r=0xD1 ;
	uint16_t DS3231_24c02_w=0xAE ;
	uint16_t DS3231_24c02_r=0xAF ;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */	
	//uint8_t *pData=TEXT_Buffer;
	uint16_t Size=SIZE_OF_BUF;
	uint32_t Timeout=1000;
	uint8_t t=' ';
	uint8_t second=0,minute=0,hour=0,day=0,month=0,year=0;

	
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
  MX_USART1_UART_Init();
  MX_I2C1_Init();
	OLED_Init();
	OLED_Clear();
	
	printf(" \r\n  \r\n *******************  BEGIN ! *******************\r\n  \r\n");
	if(HAL_I2C_IsDeviceReady(&hi2c1, OLED, 3, Timeout)== HAL_OK) 
	printf("OLED is ready ! \r\n");
	delay_ms(10);
	if(HAL_I2C_IsDeviceReady(&hi2c1, w24c02, 3, Timeout)== HAL_OK) 
	printf("24c02 is ready ! \r\n");
	delay_ms(10);
	if(HAL_I2C_IsDeviceReady(&hi2c1, DS3231_w, 3, Timeout)== HAL_OK) 
	printf("DS3231 is ready ! \r\n");
	delay_ms(10);
	if(HAL_I2C_IsDeviceReady(&hi2c1, DS3231_24c02_w, 3, Timeout)== HAL_OK) 
	printf("DS3231_24c02 is ready ! \r\n");
	delay_ms(10);
	printf(" \r\n  \r\n   \r\n");
  /* USER CODE BEGIN 2 */	
	//OLED第一页
	OLED_ShowCHinese(0,0,0);//中
	OLED_ShowCHinese(18,0,1);//景
	OLED_ShowCHinese(36,0,2);//园
	OLED_ShowCHinese(54,0,3);//电
	OLED_ShowCHinese(72,0,4);//子
	OLED_ShowCHinese(90,0,5);//科
	OLED_ShowCHinese(108,0,6);//技	
	OLED_ShowString(6,3,"0.96' OLED TEST",16);
	OLED_ShowString(0,6,"ASCII:",16);  
	OLED_ShowString(63,6,"CODE:",16);  
	OLED_ShowChar(48,6,t,16);//显示ASCII字符	   
	t++;	if(t>'~')t=' ';
	OLED_ShowNum(103,6,t,3,16);//显示ASCII字符的码值 	
	delay_ms(3000);
	//OLED第二页
	OLED_DrawBMP(0,0,128,8,BMP1);  //图片显示(图片显示慎用，生成的字表较大，会占用较多空间，FLASH空间8K以下慎用)
	delay_ms_it(3000);
	//OLED第三页
	OLED_DrawBMP(0,0,128,8,BMP2);
	delay_ms_it(3000);
	OLED_Clear();
	
		
	//写24c02  	
	HAL_I2C_Mem_Write(&hi2c1, w24c02,0,I2C_MEMADD_SIZE_8BIT,"abcdefghi",8,1500);
	delay_ms(5);
	HAL_I2C_Mem_Write(&hi2c1, w24c02,8,I2C_MEMADD_SIZE_8BIT,"12345678",8,1500);
	delay_ms(5);	
	printf("written %d bytes into 24C02 success ! \r\n" ,Size);
	//读24c02
	while(HAL_I2C_Mem_Read(&hi2c1, r24c02,0,I2C_MEMADD_SIZE_8BIT,datatemp,8,1500)){		delay_ms(5);	}
	printf("read success ! \r\n");	
	printf(" %s \r\n",datatemp);
	//获取I2C总线状态	
	//printf("HAL_RCC_GetHCLKFreq = %d \r\n",HAL_RCC_GetHCLKFreq());	
	printf(" the state is   %d  \r\n",HAL_I2C_GetState(&hi2c1));
  printf(" the mode is   %d  \r\n",HAL_I2C_GetMode(&hi2c1));
	//uint32_t HAL_I2C_GetError(I2C_HandleTypeDef *hi2c);	
	
	//DS3231初始化
  //HAL_I2C_Master_Transmit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout)
	while(HAL_I2C_Mem_Write(&hi2c1, DS3231_w,0,I2C_MEMADD_SIZE_8BIT,time_buff,7,1500)){		delay_ms(5);		}
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */	
		//OLED第四页
//		OLED_ShowString(0,3,"Hello world ! ",16);
//		delay_ms_it(3000);
//		OLED_Clear();
//		//OLED第五页
//		OLED_DrawBMP(0,0,128,8,BMP2);
//		delay_ms_it(3000);
//		OLED_Clear();
//		//OLED第六页
//		OLED_ShowNum(3, 3,18, 2, 16);
//		delay_ms_it(3000);
//    OLED_Clear();		
		
		//读DS3231
		//HAL_I2C_Master_Transmit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout)
//		while(HAL_I2C_Master_Receive(&hi2c1, DS3231_r, datatemp, 3, 10)){		delay_ms(5);		}
//		printf("read DS3231 success ! \r\n");	
//		printf(" %d \r\n",datatemp[0]);
//		printf(" %d \r\n",datatemp[1]);
//		printf(" %d \r\n",datatemp[2]);		
		
		while(HAL_I2C_Mem_Read(&hi2c1, DS3231_r,0,I2C_MEMADD_SIZE_8BIT,datatemp,7,1500)){		delay_ms(200);		}
		//second = time_buff[0]&0x0f;
		//year = time_buff[6]&0x0f;
		if(datatemp[0]^second){ 
			second = datatemp[0]; 
			printf(" %d second \r\n",second&0x0f);	
			year = datatemp[6];
			printf(" %d year \r\n", ((year>>4)*10)+(year&0x0f));
		}
		//if(datatemp[6]^year){  	}		
  }
  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
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
int stdout_putchar (int ch){
	while ((USART1->SR &  0x0040) == (uint8_t)RESET);
	USART1->DR = (uint8_t)ch;
	return ch;
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
