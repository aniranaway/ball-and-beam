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
#include "pid.h"
#include "sysErrors.h"
#include "vl53l0x_driver.h" 
#include <stdio.h>

/* BSP Global Declarations */
BSP_I2C_Handle_t    i2c_handle    = {.i2c_bus = I2C_BUS_1, .i2c_address = VL53L0X_I2C_ADDRESS};
BSP_UART_Handle_t   uart_handle   = {.uart_bus= UART_BUS_2};
BSP_Timer_Handle_t  timer_handle  = {.timer_bus = TIMER_BUS_2, .pwm_channel = PWM_CHANNEL_1};

/* Device Declarations */
VL53L0X_Dev_t   VL53L0X_Sensor  = {.bsp_handle = &i2c_handle, .vl53l0x_data_ready = 0};
Servo_Handle_t  servo_handle    = {.timerHandle = &timer_handle};

/* Variable Declarations */
uint32_t last_log_time = 0;
SYS_ERRORS_t status = AR_STATUS_OK;


/*Control Declarations*/
PID_Handle_t beam_control = {.Kp = 0.3f, .Ki = 0.0f, .Kd = 0.3f, .set_point = 85, .prev_measure = 0};

void App_Init(void)
{
    /* Comms Initialization - Halt immediately if hardware fails to start */
    if (bsp_i2c_Init(&i2c_handle) != AR_STATUS_OK)                status = AR_STATUS_ERROR;
    if (bsp_timer_Init(&timer_handle) != AR_STATUS_OK)          status = AR_STATUS_ERROR;
    if (bsp_uart_Init(&uart_handle) != AR_STATUS_OK)             status = AR_STATUS_ERROR;
    
    bsp_gpio_register_interrupt(0, vl53l0x_driver_data_ready, &VL53L0X_Sensor);

    /* Device Initialization */
    if (vl53l0x_driver_init(&VL53L0X_Sensor) != AR_STATUS_OK) status = AR_STATUS_ERROR;
    if (servo_init(&servo_handle) != AR_STATUS_OK)              status = AR_STATUS_ERROR;


}

void App_Run(void)
{
    while(status ==  AR_STATUS_OK)
    {   

        if (VL53L0X_Sensor.vl53l0x_data_ready == 1)
        {
            VL53L0X_Sensor.vl53l0x_data_ready = 0;
            status = vl53l0x_driver_get_Readings(&VL53L0X_Sensor);
            if (status == AR_STATUS_OK) 
            {
                
                status = servo_move(&servo_handle, 90 + PID_Compute(&beam_control, VL53L0X_Sensor.distance_mm));
            }    
            
        }
        
        if (bsp_get_millis() - last_log_time >= 100)
        {
            last_log_time = bsp_get_millis();
            char tx_buffer[50];
            uint16_t len = snprintf(tx_buffer, sizeof(tx_buffer), "Distance: %u mm\r\n", VL53L0X_Sensor.distance_mm);
            bsp_uart_transmit(&uart_handle, tx_buffer, len);
        }
    }
    if(status != AR_STATUS_OK)
        {
            char tx_buffer[50];
            uint16_t len = snprintf(tx_buffer, sizeof(tx_buffer), "Error:\n");
            bsp_uart_transmit(&uart_handle, tx_buffer, len);
        }
}

