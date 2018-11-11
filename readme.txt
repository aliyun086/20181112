
使用HAL库操作IIC接口的24C02
Polling mode查询模式
HAL_I2C_Mem_Write();
HAL_StatusTypeDef HAL_I2C_Mem_Write(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_I2C_Mem_Read();
HAL_StatusTypeDef HAL_I2C_Mem_Read(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);


类似于datasheet上写的page write：
写，一次只能写一页，8 bytes，超过，会回写到页首，在一页中循环。
读，似乎也只能读一页。

要写第二页，请在MemAddress处指定0x08到0x10之间的地址。

增加OLED








