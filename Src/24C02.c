#include "24C02.h"
#include "stdio.h"
__IO uint32_t  I2CTimeout = I2C_Open_LONG_TIMEOUT;

//static void I2C_delay(uint16_t cnt);

/*******************************************************************************
* Function Name  : I2C_delay
* Description    : 
* Input          : None
* Output         : None
* Return         : None
* Attention         : None
*******************************************************************************/
//static void I2C_delay(uint16_t cnt)
//{
//    while(cnt--);
//}
/*******************************************************************************
* Function Name  : I2C_Read
* Description    : 
* Input          : 
* Output         : 
* Return         : 
* Attention         : None
*******************************************************************************/
uint8_t I2C_Read(I2C_HandleTypeDef  I2Cx, uint8_t I2C_Addr, uint8_t addr, uint8_t  buf,uint16_t num)
{
    uint8_t err=0;
    while(HAL_I2C_Mem_Read (&I2Cx ,I2C_Addr,addr,I2C_MEMADD_SIZE_8BIT,&buf,num,I2CTimeout)  );
    
    //err = HAL_I2C_Mem_Read(I2Cx, I2C_Addr, addr, I2C_MEMADD_SIZE_8BIT, buf, num, I2CTimeout);
    if(err)
    return err;
    else 
    return 0;
}    

/*******************************************************************************
* Function Name  : I2C_WriteOneByte
* Description    : 
* Input          : 
* Output         : None
* Return         : 
* Attention         : None
*******************************************************************************/
uint8_t I2C_WriteOneByte(I2C_HandleTypeDef *I2Cx,uint8_t I2C_Addr,uint8_t addr,uint8_t value)
{
//    uint8_t err=0;
    
    while( HAL_I2C_Mem_Write(I2Cx, I2C_Addr, addr, I2C_MEMADD_SIZE_8BIT, &value, 0x01, I2CTimeout));
    //I2C_delay(50000);
//    if(err)
//        return 1;
//    else 
//        return 0;   
		return 0;			
}

 
/*******************************************************************************
* Function Name  : I2C_Write
* Description    : 
* Input          : 
* Output         : None
* Return         : 
* Attention         : None
*******************************************************************************/
uint8_t I2C_Write(I2C_HandleTypeDef  I2Cx,uint8_t I2C_Addr,uint8_t addr,uint8_t  buf,uint16_t num)
{
    //uint8_t err=0;
    
    while(num--)
    {
        I2C_WriteOneByte(&I2Cx, I2C_Addr,addr++,buf++);
//        if(I2C_WriteOneByte(I2Cx, I2C_Addr,addr++,*buf++))
//        {
//            err++;
//        }
    }
//    if(err)
//        return 1;
//    else 
        return 0;    
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
