#include <stdio.h>
#include "runnable_LM.h"


uint8_t flag_position = 1; // 1 -> front left, 2 -> front right, 3 -> rear left, 4 -> rear right
uint8_t flag_special_equipment = 0; // 0 -> no special equipment, 1 -> special equipment

uint32_t time_ms = 0; // time in milliseconds

void wait_ms(uint32_t ms)
{
    uint32_t end_time = time_ms + ms; // Calculate the end time
    while (time_ms < end_time) break;
    printf("(Activated when system is fully functional):\n Waiting for %u ms...\n", ms);
}

ReturnType control_cornering_light(uint8_t toggle)
{
    // toggle==1 -> turn on, toggle==0 -> turn off
    if (toggle == 1)
    {
        printf("Cornering light ON\n");
    }
    else
    {
        printf("Cornering light OFF\n");
    }

    return OK;
}

ReturnType control_indicator_light_basic(uint8_t toggle)
{
    // toggle==1 -> turn on, toggle==0 -> turn off
    if (toggle == 1)
    {
        printf("Indicator light ON\n");
        wait_ms(500); 
        printf("Indicator light OFF after 500 ms\n");
    }
    else
    {
        printf("Indicator light OFF\n");
    }
    
    return OK;
}

ReturnType control_indicator_light_special(uint8_t toggle)
{
    // toggle==1 -> turn on, toggle==0 -> turn off
    if (toggle == 1)
    {
        printf("LED0 ON\n");
        wait_ms(50);
        printf("LED1 ON\n");
        wait_ms(50);
        printf("LED2 ON\n");
        wait_ms(50);
        printf("LED3 ON\n");
        wait_ms(50);
        printf("LED4 ON\n");
        wait_ms(50);
        printf("LED5 ON\n");
        wait_ms(50);
        printf("LED6 ON\n");
        wait_ms(50);
        printf("LED7 ON\n");
        
        wait_ms(200);
        printf("All LEDs OFF\n"); 
    }
    else
    {
        printf("Indicator light special OFF\n");
    }
    
    return OK;
}

ReturnType LM_runnable(void)
{
    ReturnType status = OK;

    uint8_t MSG_LM_value = 0;

    uint8_t indicator_light =  0;
    uint8_t cornering_light = 0;

    

    status = Rte_Read_MSG_LM(&MSG_LM_value);
    if (status != OK) return status;

    if(flag_position == 1)
    {
        if((MSG_LM_value & 0x08) != 0)
        {
           cornering_light=1;
        }
        else
        {
            cornering_light=0;
        }

        if ((MSG_LM_value & 0x80) != 0)
        {
            indicator_light=1;
        }
        else
        {
            indicator_light=0;
        }
        

    }
    else if(flag_position == 2)
    {
        if((MSG_LM_value & 0x04) != 0)
        {
           cornering_light=1;
        }
        else
        {
            cornering_light=0;
        }

        if ((MSG_LM_value & 0x40) != 0)
        {
            indicator_light=1;
        }
        else
        {
            indicator_light=0;
        }
    }
    else if(flag_position == 3)
    {
        if((MSG_LM_value & 0x02) != 0)
        {
           cornering_light=1;
        }
        else
        {
            cornering_light=0;
        }

        if ((MSG_LM_value & 0x20) != 0)
        {
            indicator_light=1;
        }
        else
        {
            indicator_light=0;
        }
    }
    else if(flag_position == 4)
    {
        	if((MSG_LM_value & 0x01) != 0)
        {
           cornering_light=1;
        }
        else
        {
            cornering_light=0;
        }

        if ((MSG_LM_value & 0x10) != 0)
        {
            indicator_light=1;
        }
        else
        {
            indicator_light=0;
        }
    }

    status = control_cornering_light(cornering_light); // control the cornering light based on the flag_position
    if (status != OK) return status;

    if (flag_special_equipment == 0)
    {
        status = control_indicator_light_basic(indicator_light); // control the indicator light based on the flag_position
        if (status != OK) return status;
    }
    else if (flag_special_equipment == 1)
    {
        control_indicator_light_special(indicator_light); // control the indicator light based on the flag_position
        if (status != OK) return status;
    }
    return status;
}