/** 
    *@file      app.c
    *@brief     Application Implementation
    *@author    Anish Rangarajan
*/
#include "i2c.h"
#include "main.h"
#include "bsp_i2c.h"
#include "vl53l0x_platform.h"
#include "vl53l0x_driver.h"

extern I2C_HandleTypeDef hi2c1;


#define VL53L0X_I2C_ADDRESS  (0x29 << 1)

BSP_I2C_Handle_t i2cHandle      = {.i2c_reference = &hi2c1, .i2c_address = VL53L0X_I2C_ADDRESS};
VL53L0X_Dev_t   VL53L0X_Sensor  = {.bsp_handle = &i2cHandle};
void App_Init(void)
{
    vl53l0x_driver_init(&VL53L0X_Sensor);
}

void App_Run(void)
{
    while(1){
        
    }
}