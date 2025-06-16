#include <stdio.h>
#include "simulatedControllFlow.h"
#include "runnable_Input_Controller.h"
#include "runnable_Indicator_Logic.h"
#include "runnable_Cornering_Light_Logic.h"
#include "runnable_Message_Controller.h"
#include "runnable_LM.h"


// Variables inside the ZSE ECU
int8_t MSG_IndicatorLever_value = 0;
int16_t MSG_SteeringAngle_value = 0;
uint8_t MSG_HazardLightsStatus_value = 0;
uint8_t MSG_CarLightsStatus_value = 0;
int16_t MSG_Velocity_value = 0;

uint8_t MSG_IndicatorLights_value = 0;

uint8_t MSG_CorneringLightStatus_value = 0;

uint8_t MSG_LM_value = 0;

// Variables from extern
int8_t IndicatorLever_value = 0;
int16_t SteeringAngle_value = 0;
uint8_t HazardLightsStatus_value = 0;
uint8_t CarLightsStatus_value = 0;
int16_t Velocity_value = 0;

// Function prototypes
ReturnType set_Input_values(int8_t IndicatorLever, int16_t SteeringAngle, uint8_t HazardLightsStatus, uint8_t CarLightsStatus, int16_t Velocity);
ReturnType scheduling_cycle_ZSE(void);
ReturnType scheduling_cycle_LM_Module(void);

// Tests

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

ReturnType set_Input_values(int8_t IndicatorLever, int16_t SteeringAngle, uint8_t HazardLightsStatus, uint8_t CarLightsStatus, int16_t Velocity)
{
    IndicatorLever_value = IndicatorLever;
    SteeringAngle_value = SteeringAngle;
    HazardLightsStatus_value = HazardLightsStatus;
    CarLightsStatus_value = CarLightsStatus;
    Velocity_value = Velocity; 
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

