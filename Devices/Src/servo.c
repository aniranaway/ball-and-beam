/** 
    *@file      servo.c
    *@brief     Implementation of the Servo
    *@author    Anish Rangarajan
*/

#include "servo.h"
#include "bsp_timer.h"
#include "sysErrors.h"
#include <stdint.h>

static float map(float x, float in_min, float in_max, float out_min, float out_max) {
    // Safety check to prevent divide-by-zero
    if (in_max == in_min) return out_min;
    
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

uint16_t servo_angle_to_pulse(float angle) {
    return map(angle, 0.0f, 180.0f, (float)SERVO_ZERO_PULSE, (float)SERVO_END_PULSE);
}

float servo_pulse_to_angle(float pulse) {
    return map(pulse, (float)SERVO_ZERO_PULSE, (float)SERVO_END_PULSE, 0.0f, 180.0f);
}

SYS_ERRORS_t servo_init(Servo_Handle_t *servo_handle){
    SYS_ERRORS_t status = bsp_pwm_start(servo_handle->timerHandle);
    if (status != AR_STATUS_OK) {
        return status;
    }
    return servo_move(servo_handle, 90.0f - SERVO_OFFSET_ANGLE);
}


SYS_ERRORS_t servo_move(Servo_Handle_t *servo_handle, float angle)
{
    if (angle < 0.0f) angle = 0.0f;
    if (angle > 180.0f) angle = 180.0f;
    servo_handle->servoAngle = angle;
    uint16_t pulse = servo_angle_to_pulse(angle);

    if(pulse > SERVO_END_PULSE) pulse = SERVO_END_PULSE;
    if(pulse < SERVO_ZERO_PULSE) pulse = SERVO_ZERO_PULSE;

    return bsp_duty_cycle_set(servo_handle->timerHandle, pulse);
}