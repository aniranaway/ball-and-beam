/** 
    *@file      bsp_uart.c
    *@brief     Implementation of the uart wrapper 
    *@author    Anish Rangarajan
*/

#include "bsp_uart.h"
#include "stm32l4xx_hal.h"
#include "sysErrors.h"

extern UART_HandleTypeDef huart2;

SYS_ERRORS_t bsp_uart_Init(BSP_UART_Handle_t *uart_handle){
    switch (uart_handle->uart_bus) {
        case UART_BUS_2: uart_handle->uart_reference = &huart2;
                        break;
        default:
            return AR_STATUS_ERROR;
    }
    return AR_STATUS_OK;
}

SYS_ERRORS_t bsp_uart_transmit(BSP_UART_Handle_t *uart_handle, char* tx_buffer, uint16_t len)
{
    HAL_UART_Transmit(uart_handle->uart_reference, (uint8_t*)tx_buffer, len, 10); 
    return AR_STATUS_OK ;
}