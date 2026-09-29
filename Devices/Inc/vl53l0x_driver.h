/** 
    *@file      vl53l0x_driver.h
    *@brief     Intermediate driver file  that interacts with the ST API
    *@author    Anish Rangarajan
*/

#ifndef VL53L0x_DRIVER_H
#define VL53L0x_DRIVER_H

#include "vl53l0x_platform.h"
#include "sysErrors.h"

#define VL53L0X_I2C_ADDRESS  (0x29 << 1)

/**
 * @brief   Vl53l0x initialization function.
 * @param   vl53l0x_handle   Pointer to the BSP I2C handle structure.
 * @note    This function is typically called during device initialization.
 * 
 * @return  SYS_ERRORS_t  AR_STATUS_OK on success, or AR_STATUS_ERROR on failure.
 */
SYS_ERRORS_t vl53l0x_driver_init(VL53L0X_Dev_t *vl53l0x_handle);


/**
 * @brief   Vl53l0x measurement function.
 * @param   vl53l0x_handle   Pointer to the BSP I2C handle structure.
 * @param   distance_mm      Distance returned in mm
 * 
 * @return  SYS_ERRORS_t  AR_STATUS_OK on success, or AR_STATUS_ERROR on failure.
 */
SYS_ERRORS_t vl53l0x_driver_get_Readings(VL53L0X_Dev_t *vl53l0x_handle, uint16_t *distance_mm);


















#endif