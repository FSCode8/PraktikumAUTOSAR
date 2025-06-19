#include "runnable_Input_Controller.h"

Std_ReturnType Input_Controller_runnable(void)
{
    // Read the input values
    Std_ReturnType status = E_OK;

    sint8 IndicatorLever;
    sint16 SteeringAngle;
    uint8 HazardLightsStatus;
    uint8 CarLightsStatus;
    sint16 Velocity;
    
    // Read the input values
    status = Rte_Read_IndicatorLever(&IndicatorLever);
    if (status != E_OK) return status;

    status = Rte_Read_SteeringAngle(&SteeringAngle);
    if (status != E_OK) return status;

    status = Rte_Read_HazardLightsStatus(&HazardLightsStatus);
    if (status != E_OK) return status;

    status = Rte_Read_CarLightsStatus(&CarLightsStatus);
    if (status != E_OK) return status;

    status = Rte_Read_Velocity(&Velocity);
    if (status != E_OK) return status;


    // Send the input values
    status = Rte_Write_MSG_IndicatorLever(IndicatorLever);
    if (status != E_OK) return status;

    status = Rte_Write_MSG_SteeringAngle(SteeringAngle);
    if (status != E_OK) return status;    

    status = Rte_Write_MSG_HazardLightsStatus(HazardLightsStatus);  
    if (status != E_OK) return status;

    status = Rte_Write_MSG_CarLightsStatus(CarLightsStatus);
    if (status != E_OK) return status;
    status = Rte_Write_MSG_Velocity(Velocity);
    if (status != E_OK) return status;


    return status;  // success
} 