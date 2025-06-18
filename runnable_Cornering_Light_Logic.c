#include "runnable_Cornering_Light_Logic.h"

Std_ReturnType Cornering_Light_Logic_runnable(void)
{
    Std_ReturnType status = E_OK;

    // declare variables
    int16 MSG_SteeringAngle_value = 0; // clockwise positive, counterclockwise negative
    uint8 MSG_CarLightsStatus_value = 0;  // 0 = off, 1 = on
    int16 MSG_Velocity_value = 0;     // in km/h, positive = forward, negative = backward
    int8 MSG_IndicatorLever_value = 0;    // 0 = neutral, 1 = right-tip, 2 = right-set, -1 = left-tip, -2 = left-set

    uint8 MSG_IndicatorLights_value = 0;

    // Read values from RTE
    Rte_Read_MSG_IndicatorLever(&MSG_IndicatorLever_value);
    if (status != E_OK) return status;
    Rte_Read_MSG_SteeringAngle(&MSG_SteeringAngle_value);
    if (status != E_OK) return status;
    Rte_Read_MSG_CarLightsStatus(&MSG_CarLightsStatus_value);
    if (status != E_OK) return status;
    Rte_Read_MSG_Velocity(&MSG_Velocity_value);
    if (status != E_OK) return status;

    Rte_Read_MSG_IndicatorLights(&MSG_IndicatorLights_value);
    if (status != E_OK) return status;

    // #22
    if(MSG_Velocity_value > 70) // velocity is above 70 km/h 
    {
        status = Rte_Write_MSG_CornerLightsStatus(0x00); // send Message
        return status;
    }
   
    // #23
    if(MSG_SteeringAngle_value <= 15 && MSG_SteeringAngle_value >= -15) // steering angle is in default range
    {
        if(MSG_IndicatorLever_value == 0)  
        {
            status = Rte_Write_MSG_CornerLightsStatus(0x00); // send Message 
            return status;
        }
    }
    else 
    {
        // #20
        if(MSG_SteeringAngle_value > 20) // right
        {
            status = Rte_Write_MSG_CornerLightsStatus(0x04); // send Message
            return status;
        }
        if(MSG_SteeringAngle_value < -20)  // left
        {
            status = Rte_Write_MSG_CornerLightsStatus(0x08); // send Message
            return status;
        }
    }

    // #21
    if(MSG_Velocity_value <= 65)
    {
       if(MSG_IndicatorLights_value != 0xF0)   // all Indicator Lights on (1111 0000) -> HazardLights on
        {
            if(MSG_CarLightsStatus_value == 1) // Car Lights on 
            {
                if((MSG_IndicatorLights_value & 0x50) == 0x50) // right Indicator Lights on (0000 1111)
                {
                    status = Rte_Write_MSG_CornerLightsStatus(0x04); // send Message
                }
                else if((MSG_IndicatorLights_value & 0xA0) == 0xA0) // left Indicator Lights on (0000 1111)
                {
                    status = Rte_Write_MSG_CornerLightsStatus(0x08); // send Message
                }
            }
        } 
    }

    return status;
}