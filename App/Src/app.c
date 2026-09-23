/** 
    *@file      app.c
    *@brief     Application Implementation
    *@author    Anish Rangarajan
*/
#include "i2c.h"
#include "main.h"
#include "bsp_i2c.h"
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_gpio.h"
#include "sysErrors.h"
#include "vl53l0x_platform.h"
#include "vl53l0x_driver.h"

extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart2;

#define VL53L0X_I2C_ADDRESS  (0x29 << 1)

BSP_I2C_Handle_t i2cHandle      = {.i2c_reference = &hi2c1, .i2c_address = VL53L0X_I2C_ADDRESS};
VL53L0X_Dev_t   VL53L0X_Sensor  = {.bsp_handle = &i2cHandle};
volatile uint8_t vl53l0x_data_ready = 0;
uint16_t distance_mm = 0;
uint32_t last_log_time = 0;
void App_Init(void)
{
    vl53l0x_driver_init(&VL53L0X_Sensor);
}

void App_Run(void)
{
    while(1)
    {
        if (vl53l0x_data_ready == 1)
        {
            vl53l0x_data_ready = 0;
            if (vl53l0x_driver_get_Readings(&VL53L0X_Sensor, &distance_mm) == AR_STATUS_OK)
            {
                
            }
        if (HAL_GetTick() - last_log_time >= 100) // Log every 100ms
        {
            last_log_time = HAL_GetTick();
            char tx_buffer[50];
            int len = snprintf(tx_buffer, sizeof(tx_buffer), "Distance: %u mm\r\n", distance_mm);
            HAL_UART_Transmit(&huart2, (uint8_t*)tx_buffer, len, 10); 
        }
        }
    }
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
    
    if (GPIO_Pin == GPIO_PIN_0)
    {
        vl53l0x_data_ready = 1;
    }
}
