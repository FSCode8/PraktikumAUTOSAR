#include <stdio.h>
#include "simulatedControllFlow.h"
#include "runnable_Input_Controller.h"
#include "runnable_Indicator_Logic.h"
#include "runnable_Cornering_Light_Logic.h"
#include "runnable_Message_Controller.h"
#include "runnable_LM.h"


// Function 

void set_Input_values(sint8 IndicatorLever, sint16 SteeringAngle, uint8 HazardLightsStatus, uint8 CarLightsStatus, sint16 Velocity)
{
    IndicatorLever_value = IndicatorLever;
    SteeringAngle_value = SteeringAngle;
    HazardLightsStatus_value = HazardLightsStatus;
    CarLightsStatus_value = CarLightsStatus;
    Velocity_value = Velocity; 
}

Std_ReturnType scheduling_cycle_ZSE()
{
    Std_ReturnType status = E_OK;

    Input_Controller_runnable();
    if (status != E_OK) return status;
    Indicator_Light_Logic_runnable();
    if (status != E_OK) return status;
    Cornering_Light_Logic_runnable();
    if (status != E_OK) return status;
    Message_Controller_runnable();
    if (status != E_OK) return status;

    return status;
}

Std_ReturnType scheduling_cycle_LM_Module()
{
    Std_ReturnType status = E_OK;

    status = LM_Controller_runnable();

    return status;
}

