#include "runnable_Message_Controller.h"

ReturnType Message_Controller_runnable()
{
    ReturnType status = OK;

    static uint64_t time_ms = 0;
    static uint64_t last_sending_ms = 0;
    static uint8_t previous_MSG_IndicatorLights = 0;
    static uint8_t previous_MSG_CornerLightsStatus = 0;

    uint8_t MSG_IndicatorLights = 0;
    uint8_t MSG_CornerLightsStatus = 0;

    uint8_t MSG_LM = 0;

    status = Rte_Read_MSG_IndicatorLights(&MSG_IndicatorLights);
    if((MSG_IndicatorLights & 0x0F) != 0) status = ERROR;   // check if unplausible value
    if (status != OK) return status;

    status = Rte_Read_MSG_CornerLightsStatus(&MSG_CornerLightsStatus);
    if((MSG_CornerLightsStatus & 0xF0) != 0) status = ERROR;   // check if unplausible value
    if (status != OK) return status;

    if(previous_MSG_IndicatorLights != MSG_IndicatorLights)
    {
        MSG_LM = MSG_IndicatorLights | MSG_CornerLightsStatus;
        status = Rte_Write_MSG_LM(MSG_LM);
        if (status != OK) return status;
        previous_MSG_IndicatorLights = MSG_IndicatorLights;
        previous_MSG_CornerLightsStatus = MSG_CornerLightsStatus;
        last_sending_ms = time_ms;
    }   
    else
    {
        if (time_ms-last_sending_ms >= 1000)
        {
            MSG_LM = MSG_IndicatorLights | MSG_CornerLightsStatus;
            status = Rte_Write_MSG_LM(MSG_LM);
            if (status != OK) return status;
            previous_MSG_IndicatorLights = MSG_IndicatorLights;
            previous_MSG_CornerLightsStatus = MSG_CornerLightsStatus;
            last_sending_ms = time_ms;
        }
        else if(MSG_CornerLightsStatus != previous_MSG_CornerLightsStatus)
        {
            MSG_LM = MSG_CornerLightsStatus;
            status = Rte_Write_MSG_LM(MSG_LM);
            if (status != OK) return status;
            previous_MSG_CornerLightsStatus = MSG_CornerLightsStatus;
        }    
    } 
    time_ms += 10;

    return status;
}