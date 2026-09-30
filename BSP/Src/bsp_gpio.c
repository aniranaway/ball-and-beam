#include "bsp_gpio.h"
#include "stm32l4xx_hal.h"
#include <stddef.h>

static bsp_gpio_cb_t gpio_callbacks[MAX_INTERRUPTS] = {NULL};
static void *gpio_args[MAX_INTERRUPTS] = {NULL};

void bsp_gpio_register_interrupt(uint16_t pin_number, bsp_gpio_cb_t callback_func, void *args) {
    if (pin_number < MAX_INTERRUPTS) {
        gpio_callbacks[pin_number]  = callback_func; 
        gpio_args[pin_number]    = args;
    }
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    for (int i = 0; i <= MAX_INTERRUPTS - 1; i++) {
        
        if (GPIO_Pin == (1 << i)) 
        { 
            if (gpio_callbacks[i] != NULL) 
            {
                gpio_callbacks[i](gpio_args[i]);
            }
            
            break;
        }
    }
}