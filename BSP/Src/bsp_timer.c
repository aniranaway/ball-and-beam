/** 
    *@file      bsp_timer.c
    *@brief     Implementation of the BSP timer file
    *@author    Anish Rangarajan
*/

#include "bsp_timer.h"
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_def.h"
#include "sysErrors.h"
#include <stdint.h>

SYS_ERRORS_t bsp_pwm_start(BSP_Timer_Handle_t *bsp_timer_handle){
    HAL_StatusTypeDef status;
    status = HAL_TIM_PWM_Start((TIM_HandleTypeDef*)bsp_timer_handle->timer_ref, bsp_timer_handle->timer_channel);
    if(status != HAL_OK)
        return AR_STATUS_ERROR;

return AR_STATUS_OK;
}

SYS_ERRORS_t bsp_duty_cycle_set(BSP_Timer_Handle_t *bsp_timer_handle, uint16_t pulse){
    __HAL_TIM_SET_COMPARE((TIM_HandleTypeDef*)bsp_timer_handle->timer_ref, bsp_timer_handle->timer_channel,pulse);
return AR_STATUS_OK;
}