#ifndef BSP_GPIO_H
#define BSP_GPIO_H

#include <stdint.h>

#define MAX_INTERRUPTS      (uint16_t ) 16

/**
 * @brief Gpio callback function pointer.
 */
typedef void (*bsp_gpio_cb_t)(void *args);


/**
 * @brief   GPIO function subscribe to a pin's interrupt.
 */
void bsp_gpio_register_interrupt(uint16_t pin_number, bsp_gpio_cb_t callback_func, void *args);


#endif