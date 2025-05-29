#include "runnable_Input_Controller.h"

ReturnType Input_Controller_runnable(void)
{
    // Read the input values
    ReturnType status = OK;

    int8_t IndicatorLever;
    int16_t SteeringAngle;
    uint8_t HazardLightsStatus;
    uint8_t CarLightsStatus;
    int16_t Velocity;
    
    // Read the input values
    status = Rte_Read_IndicatorLever(&IndicatorLever);
    if (status != OK) return status;

    status = Rte_Read_SteeringAngle(&SteeringAngle);
    if (status != OK) return status;

    status = Rte_Read_HazardLightsStatus(&HazardLightsStatus);
    if (status != OK) return status;

    status = Rte_Read_CarLightsStatus(&CarLightsStatus);
    if (status != OK) return status;

    status = Rte_Read_Velocity(&Velocity);
    if (status != OK) return status;


    // Send the input values
    status = Rte_Write_MSG_IndicatorLever(IndicatorLever);
    if (status != OK) return status;

    status = Rte_Write_MSG_SteeringAngle(SteeringAngle);
    if (status != OK) return status;    

    status = Rte_Write_MSG_HazardLightsStatus(HazardLightsStatus);  
    if (status != OK) return status;

    status = Rte_Write_MSG_CarLightsStatus(CarLightsStatus);
    if (status != OK) return status;
    status = Rte_Write_MSG_Velocity(Velocity);
    if (status != OK) return status;


    return status;  // success
} 