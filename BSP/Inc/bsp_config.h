/** 
    *@file      bsp_config.h
    *@brief     Configuration File to implement communication buses and GPIO pins
    *@author    Anish Rangarajan
*/

#ifndef BSP_CONFIG_H
#define BSP_CONFIG_H

/**
 * @brief I2C communication bus identifiers for the BSP layer.
 */
typedef enum I2C_COMM_BUS{
    I2C_BUS_1,              /**< Primary I2C peripheral bus */
    I2C_BUS_2,              /**< Secondary I2C peripheral bus */
}I2C_Comm_Bus_t;


#endif