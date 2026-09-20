/** 
    *@file      app.h
    *@brief     Application header that defines Init and Run functions
    *@author    Anish Rangarajan
*/

#ifndef BALL_BEAM_APP_H
#define BALL_BEAM_APP_H


/**
 * @brief  Initializes the application layer and configures base states.
 * @note   Must be called once during system startup after BSP initialization.
 */
void App_Init(void);

/**
 * @brief  Executes the main application runtime loop.
 * @details Handles periodic task execution, reading sensors from the Devices layer,
 *          running control algorithms, and updating system outputs.
 * 
 * @note   This function is typically called continuously inside the main while(1) 
 *         loop or scheduled by an RTOS task. It is designed to be non-blocking.
 */
void App_Run(void);
























#endif