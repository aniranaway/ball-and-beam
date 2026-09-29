/** 
    *@file      bsp_i2c.h
    *@brief     File that abstracts HAL i2c transmit and receive funcitons with support for multiple bytes
    *@author    Anish Rangarajan
*/

#ifndef BSP_I2C_H
#define BSP_I2C_H
#include <stdint.h>
#include "sysErrors.h"

#define I2C_BUS_1       (0x00)
#define I2C_BUS_2       (0x01)
#define I2C_BUS_3       (0x02)

/**
 * @brief I2C struct handle.
 */

typedef struct 
{
    uint8_t i2c_bus;
    void    *i2c_reference;     /**< Generic pointer to the underlying hardware handle */
    uint8_t i2c_address;        /**< Target device I2C address */
} BSP_I2C_Handle_t;


/**
 * @brief   I2C Init function.
 * @return  SYS_ERRORS_t  AR_STATUS_OK on success, or AR_STATUS_ERROR on failure.
 */
SYS_ERRORS_t bsp_i2c_Init(BSP_I2C_Handle_t *i2c_handle);


/**
 * @brief   I2C function to read data from a target register.
 * 
 * @note    This function is typically called when either one or many bytes need to be read.
 * 
 * @param   i2c_handle   Pointer to the BSP I2C handle structure.
 * @param   start_reg    The starting register address to read from.
 * @param   read_buffer  Pointer to the buffer where received data will be stored.
 * @param   byte_count   Number of bytes to read.
 * 
 * @return  SYS_ERRORS_t  AR_STATUS_OK on success, or AR_STATUS_ERROR on failure.
 */
SYS_ERRORS_t bsp_i2c_Read_Register(BSP_I2C_Handle_t *i2c_handle, uint8_t start_reg, uint8_t *read_buffer ,uint16_t byte_count);


/**
 * @brief   I2C function to read data from a target register.
 * 
 * @note    This function is typically called when either one or many bytes need to be read.
 * 
 * @param   i2c_handle   Pointer to the BSP I2C handle structure.
 * @param   start_reg    The starting register address to write from.
 * @param   write_data   Pointer to the buffer where received data will be stored.
 * @param   byte_count   Number of bytes to write.
 * 
 * @return  SYS_ERRORS_t  AR_STATUS_OK on success, or AR_STATUS_ERROR on failure.
 */
SYS_ERRORS_t bsp_i2c_Write_Register(BSP_I2C_Handle_t *i2c_handle,uint8_t start_reg, uint8_t *write_data, uint16_t byte_count);










#endif