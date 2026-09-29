/** 
    *@file      bsp_i2c.c
    *@brief     Implementation of the i2c wrapper 
    *@author    Anish Rangarajan
*/


#include "bsp_i2c.h"
#include "stm32l4xx_hal.h"
#include "sysErrors.h"

extern I2C_HandleTypeDef hi2c1;
extern I2C_HandleTypeDef hi2c2;

SYS_ERRORS_t bsp_i2c_Init(BSP_I2C_Handle_t *i2c_handle){
    switch (i2c_handle->i2c_bus) {
        case I2C_BUS_1: i2c_handle->i2c_reference = &hi2c1;
                        break;
        case I2C_BUS_2: i2c_handle->i2c_reference = &hi2c2;
                        break;
        default:
            return AR_STATUS_ERROR;
    }
    return AR_STATUS_OK;
}

SYS_ERRORS_t bsp_i2c_Read_Register(BSP_I2C_Handle_t *i2c_handle, uint8_t start_reg, uint8_t *read_buffer ,uint16_t byte_count){
    if(HAL_I2C_Mem_Read((I2C_HandleTypeDef*)i2c_handle->i2c_reference, i2c_handle->i2c_address, start_reg, I2C_MEMADD_SIZE_8BIT, read_buffer, byte_count, HAL_MAX_DELAY) != HAL_OK)
        return AR_STATUS_ERROR;
    return AR_STATUS_OK ;
}


SYS_ERRORS_t bsp_i2c_Write_Register(BSP_I2C_Handle_t *i2c_handle,uint8_t start_reg, uint8_t *write_data, uint16_t byte_count){
    if(HAL_I2C_Mem_Write((I2C_HandleTypeDef*)i2c_handle->i2c_reference, i2c_handle->i2c_address, start_reg, I2C_MEMADD_SIZE_8BIT, write_data, byte_count, HAL_MAX_DELAY) != HAL_OK)
        return AR_STATUS_ERROR;
    return AR_STATUS_OK ;
}