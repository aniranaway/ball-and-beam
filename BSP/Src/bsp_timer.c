/** 
    *@file      bsp_timer.c
    *@brief     Implementation of the BSP timer file
    *@author    Anish Rangarajan
*/

#include "bsp_timer.h"
#include "stm32l476xx.h"
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_def.h"
#include "stm32l4xx_hal_tim.h"
#include "sysErrors.h"
#include <stdint.h>

extern TIM_HandleTypeDef htim2;

SYS_ERRORS_t bsp_timer_Init(BSP_Timer_Handle_t *timer_handle){

    switch (timer_handle->timer_bus) {
        case TIMER_BUS_2: timer_handle->timer_ref = &htim2;
                        break;
    }

    switch (timer_handle->pwm_channel) {
        case PWM_CHANNEL_1: timer_handle->timer_channel = TIM_CHANNEL_1;
                        break;
    }
}

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

uint32_t bsp_get_millis(){
    return HAL_GetTick();
}