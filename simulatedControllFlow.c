#include <stdio.h>
#include "simulatedControllFlow.h"
#include "runnable_Input_Controller.h"
#include "runnable_Cornering_Light_Logic.h"

int8_t IndicatorLever_value = 1;
int16_t SteeringAngle_value = 1;
uint8_t HazardLightsStatus_value = 1;
uint8_t CarLightsStatus_value = 1;
int16_t Velocity_value = 1;

int8_t MSG_IndicatorLever_value = 0;
int16_t MSG_SteeringAngle_value = 0;
uint8_t MSG_HazardLightsStatus_value = 0;
uint8_t MSG_CarLightsStatus_value = 0;
int16_t MSG_Velocity_value = 0;

uint8_t MSG_IndicatorLights_value = 0;

uint8_t MSG_CorneringLightStatus_value = 0;

uint8_t MSG_LM_value = 0;

int main()
{

    // Call the Input_Controller_runnable 
    Input_Controller_runnable();

    // Print the output values
    printf("MSG_IndicatorLever: %d\n", MSG_IndicatorLever_value);
    printf("MSG_SteeringAngle: %d\n", MSG_SteeringAngle_value);
    printf("MSG_HazardLightsStatus: %d\n", MSG_HazardLightsStatus_value);
    printf("MSG_CarLightsStatus: %d\n", MSG_CarLightsStatus_value);
    printf("MSG_Velocity: %d\n", MSG_Velocity_value);


    // Call the Cornering_Light_Logic_runnable
    Cornering_Light_Logic_runnable();

    printf("MSG_CorneringLightStatus: %d\n", MSG_CorneringLightStatus_value);


    return 0;
}