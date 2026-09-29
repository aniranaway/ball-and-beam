/** 
    *@file      bsp_timer.h
    *@brief     File that abstracts HAL timer funcitons with support for multiple operations
    *@author    Anish Rangarajan
*/

#ifndef BSP_TIMER_H
#define BSP_TIMER_H
#include <stdint.h>
#include "sysErrors.h"

#define TIMER_BUS_1       (0x00)
#define TIMER_BUS_2       (0x01)
#define TIMER_BUS_3       (0x02)

#define PWM_CHANNEL_1       (0x00)

/**
 * @brief Timer struct handle.
 */

typedef struct {
    void    *timer_ref;     /**< Generic pointer to the underlying hardware handle */
    uint8_t  timer_bus;
    uint8_t  pwm_channel;
    uint32_t timer_channel;    /**< Timer Channel */
} BSP_Timer_Handle_t;


/**
 * @brief   Timer Init function.
 * @return  SYS_ERRORS_t  AR_STATUS_OK on success, or AR_STATUS_ERROR on failure.
 */
SYS_ERRORS_t bsp_timer_Init(BSP_Timer_Handle_t *timer_handle);

/**
 * @brief   Timer function to start pwm.
 * 
 * 
 * @param   timer_handle_handle   Pointer to the BSP Timer handle structure.
 * 
 * @return  SYS_ERRORS_t  AR_STATUS_OK on success, or AR_STATUS_ERROR on failure.
 */
SYS_ERRORS_t bsp_pwm_start(BSP_Timer_Handle_t *timer_handle);

/**
 * @brief   Sets duty cycle for the PWM.
 * 
 * 
 * @param   timer_handle_handle   Pointer to the BSP Timer handle structure.
 * 
 * @return  SYS_ERRORS_t  AR_STATUS_OK on success, or AR_STATUS_ERROR on failure.
 */
SYS_ERRORS_t bsp_duty_cycle_set(BSP_Timer_Handle_t *timer_handle, uint16_t pulse);


/**
 * @brief   Get Millis().
 * 
 * 
 * @return  uint32  current tick in milliseconds.
 */
uint32_t bsp_get_millis();




#endif