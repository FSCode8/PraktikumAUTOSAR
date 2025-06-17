#include "runnable_Cornering_Light_Logic.h"

uint8_t convert_IndicatorLever_to_IndicatorMSG(int8_t IndicatorStatus)
{
    switch(IndicatorStatus)
    {
        case -2:
            MSG_IndicatorLights_value = 0xA0;
            break;
        case -1:
            MSG_IndicatorLights_value = 0xA0;
            break;
        case 0:
            MSG_IndicatorLights_value = 0x00;
            break;
        case 1:
            MSG_IndicatorLights_value = 0x50;
            break;
        case 2:
            MSG_IndicatorLights_value = 0x50;
            break;
        default:
            return 0xFF;
            break;
    }
    return MSG_IndicatorLights_value;
}

ReturnType Indicator_Light_Logic_runnable(void)
{
    ReturnType status = OK;

    static int8_t previousIndicatorStatus = 0; // 0 = neutral, 1 = right-tip, 2 = right-set, -1 = left-tip, -2 = left-set, 0x0F = hazard lights on
    static int8_t previous_MSG = 0;
    static uint8_t blinking = 0; // flag if it was blinking before, to keep the rythm
    static uint16_t num_blink = 0; // count blink periods
    static uint64_t time_ms = 0;
    static uint64_t last_sending_ms = 0;

    int8_t MSG_IndicatorLever_value = 0; // 0 = neutral, 1 = right-tip, 2 = right-set, -1 = left-tip, -2 = left-set
    uint8_t MSG_HazardLightsStatus_value = 0; // 0 = off, 1 = on

    uint8_t MSG_IndicatorLights_value = 0;

    // Read values from RTE
    Rte_Read_MSG_IndicatorLever(&MSG_IndicatorLever_value);
    if (status != OK) return status;
    Rte_Read_MSG_HazardLightsStatus(&MSG_HazardLightsStatus_value);
    if (status != OK) return status;

    // Check if hazard lights are on
    if (MSG_HazardLightsStatus_value == 1)  // #07
    {
        if(!blinking) 
        {    // not blinking before
            status = Rte_Write_MSG_IndicatorLights(0xF0); // Hazard lights on
            if (status != OK) return status;
            previousIndicatorStatus = 0x0F; // Set previous status to hazard lights
            previous_MSG = 0xF0;
            blinking = 1; 
            num_blink = 0;
            last_sending_ms = time_ms;
        }
        else
        {
            if(time_ms-last_sending_ms == 1000)
            {
                status = Rte_Write_MSG_IndicatorLights(0xF0); // Hazard lights on
                if (status != OK) return status;
                previousIndicatorStatus = 0x0F; // Set previous status to hazard lights
                previous_MSG = 0xF0;
                blinking = 1;
                num_blink = 0;
                last_sending_ms = time_ms;
            }
        }
    }
    else    // Hazard lights off
    {
        if(!blinking)   // Not blinking before
        {
            if (MSG_IndicatorLever_value != 0)
            {
                MSG_IndicatorLights_value = convert_IndicatorLever_to_IndicatorMSG(MSG_IndicatorLever_value);
                if(MSG_IndicatorLights_value == 0xFF) return ERROR;

                status = Rte_Write_MSG_IndicatorLights(MSG_IndicatorLights_value); 
                if (status != OK) return status;

                previousIndicatorStatus = MSG_IndicatorLever_value; 
                previous_MSG = MSG_IndicatorLights_value;
                blinking = 1;
                num_blink = 1;
                last_sending_ms = time_ms;
            }                                                
        }
        else    // Blinking state   
        {
            if(previousIndicatorStatus == 0x0F) // Hazard lights change
            {
                previousIndicatorStatus = MSG_IndicatorLever_value;
                
                if(MSG_IndicatorLever_value == 0)
                {
                    blinking = 0;
                }
            }
            else if(previousIndicatorStatus == MSG_IndicatorLever_value) // same state
            {
                if(time_ms-last_sending_ms == 1000) // full blinking period
                {
                    if (MSG_IndicatorLever_value == 0)  // neutral state 
                    {
                        if(num_blink < 3) // send the old message, if it's not done blinking 3 times
                        {
                            status = Rte_Write_MSG_IndicatorLights(previous_MSG); 
                            if (status != OK) return status;

                            blinking = 1;
                            num_blink += 1;
                            previousIndicatorStatus = MSG_IndicatorLever_value;
                            previous_MSG = previous_MSG;
                            last_sending_ms = time_ms;
                        }
                        else
                        {
                            status = Rte_Write_MSG_IndicatorLights(0x00); 
                            if (status != OK) return status;

                            blinking = 0;   // not blinking anymore
                            num_blink = 0;  // reset blink count
                            previousIndicatorStatus = 0x00;
                            previous_MSG = MSG_IndicatorLights_value;
                            last_sending_ms = time_ms;   
                        }
                    }
                    else    // not neutral state
                    {
                        MSG_IndicatorLights_value = convert_IndicatorLever_to_IndicatorMSG(MSG_IndicatorLever_value);
                        if(MSG_IndicatorLights_value == 0xFF) return ERROR;

                        status = Rte_Write_MSG_IndicatorLights(MSG_IndicatorLights_value); 
                        if (status != OK) return status;

                        blinking = 1;
                        num_blink += 1;
                        previousIndicatorStatus = MSG_IndicatorLever_value;
                        previous_MSG = MSG_IndicatorLights_value;
                        last_sending_ms = time_ms;
                    }
                }
            }
            else    // state change
            {
                if(MSG_IndicatorLever_value == 0)   // neutral state
                {
                    if(num_blink < 3)
                    {
                        if(time_ms-last_sending_ms == 1000)
                        {
                            status = Rte_Write_MSG_IndicatorLights(previous_MSG);
                            if (status != OK) return status;

                            blinking = 1;
                            num_blink += 1;
                            previousIndicatorStatus = MSG_IndicatorLever_value;
                            previous_MSG = previous_MSG;
                            last_sending_ms = time_ms;
                        }
                    }
                    else
                    {
                        status = Rte_Write_MSG_IndicatorLights(0x00); // Neutral state
                        if (status != OK) return status;

                        blinking = 0;   // not blinking anymore
                        num_blink = 0;  // reset blink count
                        previousIndicatorStatus = 0x00;
                        previous_MSG = MSG_IndicatorLights_value;
                        last_sending_ms = time_ms;   
                    }
                }
                else
                {
                    if(time_ms-last_sending_ms == 1000)
                    {
                        MSG_IndicatorLights_value = convert_IndicatorLever_to_IndicatorMSG(MSG_IndicatorLever_value);
                        if(MSG_IndicatorLights_value == 0xFF) return ERROR;

                        status = Rte_Write_MSG_IndicatorLights(MSG_IndicatorLights_value);
                        if (status != OK) return status;

                        // Update previous values
                        blinking = 1;
                        num_blink = 1;
                        previousIndicatorStatus = MSG_IndicatorLever_value;
                        previous_MSG = MSG_IndicatorLights_value;
                        last_sending_ms = time_ms;
                    }
                    else
                    {
                        num_blink = 0; // Reset blink count to 1, as we are in a new state
                        previousIndicatorStatus = MSG_IndicatorLever_value;
                    }
                }
            }
        }
    }
    time_ms += 10;

    return status;
}