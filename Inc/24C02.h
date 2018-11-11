#ifndef __24C02_H
#define __24C02_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
                      
/* Private define ------------------------------------------------------------*/
#define AT24C01A
//#define AT24C01

#define ADDR_24LC02        0xA0
#define I2C_PAGESIZE    4


/* Maximum Timeout values for flags and events waiting loops. These timeouts are
   not based on accurate values, they just guarantee that the application will 
   not remain stuck if the I2C communication is corrupted.
   You may modify these timeout values depending on CPU frequency and application
   conditions (interrupts routines ...). */   
#define I2C_Open_FLAG_TIMEOUT         ((uint32_t)0x1000)
#define I2C_Open_LONG_TIMEOUT         ((uint32_t)0xffff)

/* Private function prototypes -----------------------------------------------*/
uint8_t I2C_Read(I2C_HandleTypeDef  I2Cx,uint8_t I2C_Addr,uint8_t addr,uint8_t  buf,uint16_t num);
uint8_t I2C_Write(I2C_HandleTypeDef  I2Cx,uint8_t I2C_Addr,uint8_t addr,uint8_t  buf,uint16_t num);

#endif 

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
