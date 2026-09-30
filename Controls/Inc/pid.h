/** 
    *@file      pid.h
    *@brief     Header file that contains pid structs and function declarations
    *@author    Anish Rangarajan
*/


#ifndef PID_H
#define PID_H

/**
 * @brief PID struct handle.
 */

typedef struct {
    float Kp;
    float Ki;
    float Kd;

    float set_point;
    float prev_measure;
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

float PID_Compute(PID_Handle_t *pid_handle, float measurement);




#endif