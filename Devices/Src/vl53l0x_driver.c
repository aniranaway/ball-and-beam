/** 
    *@file      vl53l0x_driver.c
    *@brief     Driver Implementation
    *@author    Anish Rangarajan
*/
#include "vl53l0x_driver.h"
#include "sysErrors.h"
#include "vl53l0x_api.h"

SYS_ERRORS_t vl53l0x_driver_init(VL53L0X_Dev_t *vl53l0x_handle)
{

    VL53L0X_Error status = VL53L0X_ERROR_NONE;
    uint32_t refSpadCount;
    uint8_t isApertureSpads;
    uint8_t VhvSettings;
    uint8_t PhaseCal;
    VL53L0X_DeviceInfo_t deviceInfo;

    /* Device Initialization - Data Init */
    status = VL53L0X_DataInit(vl53l0x_handle);     
    if(status!= VL53L0X_ERROR_NONE){return AR_STATUS_ERROR;}

    /* Device Initialization - Handshake Test */
    status = VL53L0X_GetDeviceInfo(vl53l0x_handle, &deviceInfo);
    if(status != VL53L0X_ERROR_NONE) {return AR_STATUS_ERROR; }

    /* Device Initialization - Static Init */
    status = VL53L0X_StaticInit(vl53l0x_handle);     
    if(status!= VL53L0X_ERROR_NONE){return AR_STATUS_ERROR;}

    /* Device Initialization - Spad Management */
    status = VL53L0X_PerformRefSpadManagement(vl53l0x_handle,&refSpadCount, &isApertureSpads);
    if(status!= VL53L0X_ERROR_NONE){return AR_STATUS_ERROR;}

    /* Device Initialization - Reference Calibration */
    status = VL53L0X_PerformRefCalibration(vl53l0x_handle,&VhvSettings, &PhaseCal);
    if(status!= VL53L0X_ERROR_NONE){return AR_STATUS_ERROR;}

    /* Device Initialization - Device Mode */
    status = VL53L0X_SetDeviceMode(vl53l0x_handle, VL53L0X_DEVICEMODE_CONTINUOUS_RANGING);
    if(status!= VL53L0X_ERROR_NONE){return AR_STATUS_ERROR;}

    /* Device Initialization - Start Device */
    status = VL53L0X_StartMeasurement(vl53l0x_handle);
    if(status!= VL53L0X_ERROR_NONE){return AR_STATUS_ERROR;}
    return AR_STATUS_OK;
}


SYS_ERRORS_t vl53l0x_driver_get_Readings(VL53L0X_Dev_t *vl53l0x_handle){
    VL53L0X_Error status = VL53L0X_ERROR_NONE;
    VL53L0X_RangingMeasurementData_t RangingMeasurementData;

    status = VL53L0X_GetRangingMeasurementData(vl53l0x_handle, &RangingMeasurementData);
    if(status!= VL53L0X_ERROR_NONE){return AR_STATUS_ERROR;}
    
    vl53l0x_handle->distance_mm = RangingMeasurementData.RangeMilliMeter;

   status = VL53L0X_ClearInterruptMask(vl53l0x_handle, VL53L0X_REG_SYSTEM_INTERRUPT_GPIO_NEW_SAMPLE_READY);
    if(status != VL53L0X_ERROR_NONE) { return AR_STATUS_ERROR; }

    return AR_STATUS_OK; 
}

void vl53l0x_driver_data_ready(void *vl53l0x_handle) {
    ((VL53L0X_Dev_t *)vl53l0x_handle)->vl53l0x_data_ready = 1;
}