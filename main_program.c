#include <stdio.h>
#include "autosar_simu.h"
#include "simulatedControllFlow.h"
#include "runnable_Input_Controller.h"
#include "runnable_Indicator_Logic.h"
#include "runnable_Cornering_Light_Logic.h"
#include "runnable_Message_Controller.h"
#include "runnable_LM.h"


// Variables inside the ZSE ECU
sint8 MSG_IndicatorLever_value = 0;
sint16 MSG_SteeringAngle_value = 0;
uint8 MSG_HazardLightsStatus_value = 0;
uint8 MSG_CarLightsStatus_value = 0;
sint16 MSG_Velocity_value = 0;

uint8 MSG_IndicatorLights_value = 0;

uint8 MSG_CorneringLightStatus_value = 0;

uint8 MSG_LM_value = 0;

// Variables from extern
sint8 IndicatorLever_value = 0;
sint16 SteeringAngle_value = 0;
uint8 HazardLightsStatus_value = 0;
uint8 CarLightsStatus_value = 0;
sint16 Velocity_value = 0;

int main()
{

    // Call the Input_Controller_runnable 
    Input_Controller_runnable();

    // Print the output values
    printf("IndicatorLever_value: %d\n", IndicatorLever_value);
    printf("SteeringAngle_value: %d\n", SteeringAngle_value);
    printf("HazardLightsStatus_value: %d\n", HazardLightsStatus_value);
    printf("CarLightsStatus_value: %d\n", CarLightsStatus_value);
    printf("Velocity_value: %d\n", Velocity_value);

    // Call the Indicator_Light_Logic_runnable
    Indicator_Light_Logic_runnable();

    // Call the Cornering_Light_Logic_runnable
    Cornering_Light_Logic_runnable();

    printf("MSG_CorneringLightStatus: 0x%02x\n", MSG_CorneringLightStatus_value);

    Message_Controller_runnable();

    printf("MSG_LM: 0x%02x\n", MSG_LM_value);

    LM_Controller_runnable();


    return 0;
}