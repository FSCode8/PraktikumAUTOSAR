#include <stdio.h>
#include "simulatedControllFlow.h"
#include "runnable_Input_Controller.h"
#include "runnable_Indicator_Logic.h"
#include "runnable_Cornering_Light_Logic.h"
#include "runnable_Message_Controller.h"
#include "runnable_LM.h"


// Function 

ReturnType set_Input_values(int8_t IndicatorLever, int16_t SteeringAngle, uint8_t HazardLightsStatus, uint8_t CarLightsStatus, int16_t Velocity)
{
    IndicatorLever_value = IndicatorLever;
    SteeringAngle_value = SteeringAngle;
    HazardLightsStatus_value = HazardLightsStatus;
    CarLightsStatus_value = CarLightsStatus;
    Velocity_value = Velocity; 

    return OK;
}

ReturnType scheduling_cycle_ZSE()
{
    ReturnType status = OK;

    Input_Controller_runnable();
    if (status != OK) return status;
    //Indicator_Light_Logic_runnable();
    Cornering_Light_Logic_runnable();
    if (status != OK) return status;
    Message_Controller_runnable();
    if (status != OK) return status;

    return status;
}

ReturnType scheduling_cycle_LM_Module()
{
    ReturnType status = OK;

    status = LM_Controller_runnable();

    return status;
}

