#include "runnable_Cornering_Light_Logic.h"

uint8 convert_IndicatorLever_to_IndicatorMSG(sint8 IndicatorStatus)
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

Std_ReturnType Indicator_Light_Logic_runnable(void)
{
    Std_ReturnType status = E_OK;

    static sint8 previousIndicatorStatus = 0; // 0 = neutral, 1 = right-tip, 2 = right-set, -1 = left-tip, -2 = left-set, 0x0F = hazard lights on
    static sint8 previous_MSG = 0;
    static uint8 blinking = 0; // flag if it was blinking before, to keep the rythm
    static uint16 num_blink = 0; // count blink periods
    static uint64 time_ms = 0;
    static uint64 last_sending_ms = 0;

    sint8 MSG_IndicatorLever_value = 0; // 0 = neutral, 1 = right-tip, 2 = right-set, -1 = left-tip, -2 = left-set
    uint8 MSG_HazardLightsStatus_value = 0; // 0 = off, 1 = on

    uint8 MSG_IndicatorLights_value = 0;

    // Read values from RTE
    Rte_Read_MSG_IndicatorLever(&MSG_IndicatorLever_value);
    if (status != E_OK) return status;
    Rte_Read_MSG_HazardLightsStatus(&MSG_HazardLightsStatus_value);
    if (status != E_OK) return status;

    // Check if hazard lights are on
    if (MSG_HazardLightsStatus_value == 1)  // #07
    {
        if(!blinking) 
        {    // not blinking before
            status = Rte_Write_MSG_IndicatorLights(0xF0); // Hazard lights on
            if (status != E_OK) return status;
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
                if (status != E_OK) return status;
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
                if(MSG_IndicatorLights_value == 0xFF) return E_NOT_OK;

                status = Rte_Write_MSG_IndicatorLights(MSG_IndicatorLights_value); 
                if (status != E_OK) return status;

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
                if(time_ms-last_sending_ms == 1000) // full blinking period
                {
                    MSG_IndicatorLights_value = convert_IndicatorLever_to_IndicatorMSG(MSG_IndicatorLever_value);
                    
                    status = Rte_Write_MSG_IndicatorLights(MSG_IndicatorLights_value); 
                    if (status != E_OK) return status;

                    previousIndicatorStatus = MSG_IndicatorLever_value;
                    
                    if(MSG_IndicatorLever_value == 0)
                    {
                        blinking = 0;
                    }
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
                            if (status != E_OK) return status;

                            blinking = 1;
                            num_blink += 1;
                            previousIndicatorStatus = MSG_IndicatorLever_value;
                            previous_MSG = previous_MSG;
                            last_sending_ms = time_ms;
                        }
                        else
                        {
                            status = Rte_Write_MSG_IndicatorLights(0x00); 
                            if (status != E_OK) return status;

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
                        if(MSG_IndicatorLights_value == 0xFF) return E_NOT_OK;

                        status = Rte_Write_MSG_IndicatorLights(MSG_IndicatorLights_value); 
                        if (status != E_OK) return status;

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
                            if (status != E_OK) return status;

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
                        if (status != E_OK) return status;

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
                        if(MSG_IndicatorLights_value == 0xFF) return E_NOT_OK;

                        status = Rte_Write_MSG_IndicatorLights(MSG_IndicatorLights_value);
                        if (status != E_OK) return status;

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