/** 
    *@file      servo.h
    *@brief     Header file that contains general purpose defines and enums for servo control
    *@author    Anish Rangarajan
*/
#ifndef SERVO_H
#define SERVO_H


#include "sysErrors.h"
#include <stdint.h>
#include "main.h"
#include "bsp_timer.h"

#define     SERVO_ZERO_PULSE            500
#define     SERVO_END_PULSE             2500

/**
 * @brief Servo struct handle.
 */

typedef struct {
    BSP_Timer_Handle_t    *timerHandle;     /**< Generic pointer to the underlying hardware handle */
    float    servoAngle;                    /**< Linear mapped Servo angle */
} Servo_Handle_t;


/**
 * @brief   Servo Init
 * 
* @note    This function is typically called when either one or many bytes need to be read.
 * 
 * @param   servo_handle   Pointer to the BSP Servo handle structure.

 */
SYS_ERRORS_t servo_init(Servo_Handle_t *servo_handle);

/**
 * @brief   Servo Move
 * 
 * @note    This function moves the servo to a specific angle
 * 
 * @param   servo_handle   Pointer to the BSP Servo handle structure.

 */
SYS_ERRORS_t servo_move(Servo_Handle_t *servo_handle, float angle);


#endif