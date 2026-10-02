/** 
    *@file      pid.h
    *@brief     Header file that contains pid structs and function declarations
    *@author    Anish Rangarajan
*/
#include <stdint.h>

#ifndef PID_H
#define PID_H

/**
 * @brief PID struct handle.
 */

typedef struct {
    float Kp;
    float Ki;
    float Kd;

    float low_pass_filter_alpha;

    float set_point;
    float prev_measure;
    float prev_derivative;
    float error;
} PID_Handle_t;



/**
 * @brief   Function that computes new setpoint and performs the PID loop.
 * 
 * 
 * @param   pid_handler   Pointer to the PID struct handle.
 * @param   measurement   Measured value.
 * @return  float         Control logic
 */

float PID_Compute(PID_Handle_t *pid_handle, float measurement, uint32_t elapsed_time);




#endif