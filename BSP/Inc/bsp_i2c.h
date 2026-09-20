/** 
    *@file      bsp_i2c.h
    *@brief     File that abstracts HAL i2c transmit and receive funcitons with support for multiple bytes
    *@author    Anish Rangarajan
*/

#ifndef BSP_I2C_H
#define BSP_I2C_H

/**
 * @brief I2C struct handle.
 */

typedef struct {
    void    *i2c_reference;     /**< Generic pointer to the underlying hardware handle */
    uint8_t i2c_address;        /**< Target device I2C address */
} BSP_I2C_Handle_t;




















#endif