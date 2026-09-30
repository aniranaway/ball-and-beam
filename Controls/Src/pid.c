/** 
    *@file      pid.c
    *@brief     Implementation of the PID file
    *@author    Anish Rangarajan
*/

#include "pid.h"

float PID_Compute(PID_Handle_t *pid_handle, float measurement){
    float error =  pid_handle->set_point - measurement;

    return pid_handle->Kp * error;
 }