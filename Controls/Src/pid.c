/** 
    *@file      pid.c
    *@brief     Implementation of the PID file
    *@author    Anish Rangarajan
*/

#include "pid.h"

float PID_Compute(PID_Handle_t *pid_handle, float measurement, uint32_t elapsed_time){
    float error =  pid_handle->set_point - measurement;

    if (elapsed_time == 0) elapsed_time = 1;
    float dt = (float)elapsed_time / 1000.0f;

    if (pid_handle->prev_measure == 0.0f) {
            pid_handle->integrator = 0.0f;
            pid_handle->prev_measure = measurement;
            pid_handle->prev_derivative = 0.0f;
            return (pid_handle->Kp * error); // Skip derivative on loop 1
        }

    float derivative = (pid_handle->prev_measure - measurement) / dt;
    float derivative_filtered = (pid_handle->low_pass_filter_alpha * pid_handle->prev_derivative) + ((1.0f - pid_handle->low_pass_filter_alpha) * derivative);

    pid_handle->integrator += error * dt;

    if (pid_handle->Ki > 0.0001f || pid_handle->Ki < -0.0001f) {
        float integrator_limit = pid_handle->integrator_limit / pid_handle->Ki;
        if (pid_handle->integrator > integrator_limit)  pid_handle->integrator = integrator_limit;
        if (pid_handle->integrator < -integrator_limit) pid_handle->integrator = -integrator_limit;
    } else {
        pid_handle->integrator = 0.0f;
    }

    pid_handle->prev_measure = measurement;
    pid_handle->prev_derivative = derivative_filtered;
    pid_handle->prev_error = error;
    return (pid_handle->Kp * error) + (pid_handle->Ki * pid_handle->integrator) + (pid_handle->Kd * derivative_filtered);
 }
