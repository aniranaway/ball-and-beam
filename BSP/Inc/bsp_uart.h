#ifndef BSP_UART_H
#define BSP_UART_H
#include <stdint.h>
#include "sysErrors.h"

#define UART_BUS_2       (0x01)

/**
 * @brief UART struct handle.
 */

typedef struct 
{
    uint8_t uart_bus;
    void    *uart_reference;     /**< Generic pointer to the underlying hardware handle */
} BSP_UART_Handle_t;


/**
 * @brief   UART Init function.
 * @return  SYS_ERRORS_t  AR_STATUS_OK on success, or AR_STATUS_ERROR on failure.
 */
SYS_ERRORS_t bsp_uart_Init(BSP_UART_Handle_t *uart_handle);



/**
 * @brief   UART function to write to the COM port.
 * 
 * 
 * @param   uart_handle   Pointer to the BSP UART handle structure.
 * @param   tx_buffer     Buffer containing transmission data
 * 
 * @return  SYS_ERRORS_t  AR_STATUS_OK on success, or AR_STATUS_ERROR on failure.
 */
SYS_ERRORS_t bsp_uart_transmit(BSP_UART_Handle_t *uart_handle, char* tx_buffer, uint16_t len);

















#endif
