/** 
    *@file      app.c
    *@brief     Application Implementation
    *@author    Anish Rangarajan
*/
#include "bsp_timer.h"
#include "bsp_i2c.h"
#include "bsp_uart.h"
#include "bsp_gpio.h"
#include "servo.h"
#include "vl53l0x_driver.h"
#include <stdint.h>

/* BSP Global Declarations */
BSP_I2C_Handle_t    i2c_handle    = {.i2c_bus = I2C_BUS_1, .i2c_address = VL53L0X_I2C_ADDRESS};
BSP_UART_Handle_t   uart_handle   = {.uart_bus= UART_BUS_2};
BSP_Timer_Handle_t  timer_handle  = {.timer_bus = TIMER_BUS_2, .pwm_channel = PWM_CHANNEL_1};

/* Device Declarations */
VL53L0X_Dev_t   VL53L0X_Sensor  = {.bsp_handle = &i2c_handle, .vl53l0x_data_ready = 0};
Servo_Handle_t  servo_handle    = {.timerHandle = &timer_handle};
uint16_t distance_mm = 0;
uint32_t last_log_time = 0;
uint16_t calibrationSamples = 0;
float calibrationValues = 0;
uint16_t setPoint = 0;



void App_Init(void)
{
    /* Comms Initialization */
    bsp_i2c_Init(&i2c_handle);
    bsp_timer_Init(&timer_handle);
    bsp_uart_Init(&uart_handle);
    bsp_gpio_register_interrupt(0, On_Sensor_Data_Ready,&VL53L0X_Sensor);

    /* Device Initialization */
    vl53l0x_driver_init(&VL53L0X_Sensor);
    servo_init(&servo_handle);
}

void App_Run(void)
{
    while(1)
    {   
          
        if (VL53L0X_Sensor.vl53l0x_data_ready == 1)
        {
            VL53L0X_Sensor.vl53l0x_data_ready = 0;
            vl53l0x_driver_get_Readings(&VL53L0X_Sensor, &distance_mm);
            
        }
        
        if (bsp_get_millis() - last_log_time >= 100)
        {
            last_log_time = bsp_get_millis();
            char tx_buffer[50];
            uint16_t len = snprintf(tx_buffer, sizeof(tx_buffer), "SetPoint: %u mm | Distance: %u mm\r\n", setPoint, distance_mm);
            bsp_uart_transmit(&uart_handle, tx_buffer, len);
        }
    }
}

