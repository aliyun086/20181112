
ʹ��HAL�����IIC�ӿڵ�24C02
Polling mode��ѯģʽ
HAL_I2C_Mem_Write();
HAL_StatusTypeDef HAL_I2C_Mem_Write(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_I2C_Mem_Read();
HAL_StatusTypeDef HAL_I2C_Mem_Read(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);


������datasheet��д��page write��
д��һ��ֻ��дһҳ��8 bytes�����������д��ҳ�ף���һҳ��ѭ����
�����ƺ�Ҳֻ�ܶ�һҳ��

Ҫд�ڶ�ҳ������MemAddress��ָ��0x08��0x10֮��ĵ�ַ��

����OLED








