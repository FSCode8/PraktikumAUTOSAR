#include "runnable_LM.h"
//#include "Spi.h"

uint8 flag_position = 1; // 1 -> front left, 2 -> front right, 3 -> rear left, 4 -> rear right
uint8 flag_special_equipment = 0; // 0 -> no special equipment, 1 -> special equipment

uint8 debug_LEDs_statuses [7] = {0};
uint8 debug_indicator_status = 0;
uint8 debug_cornering_light_status = 0;

// SPI LED Stripe Control Functions
// ================================

// Buffer for 10 LEDs * 3 colors (RGB) = 30 bytes
uint8 ledStripeBuffer[30];

/**
 * Set color for a specific LED in the stripe
 * @param led_index: LED number (0-9)
 * @param red: Red intensity (0-255)
 * @param green: Green intensity (0-255)
 * @param blue: Blue intensity (0-255)
 */
void SetStripeLedColor(uint8 led_index, uint8 red, uint8 green, uint8 blue)
{
    if (led_index < 10) // Ensure valid LED index
    {
        uint8 base_index = led_index * 3;
        ledStripeBuffer[base_index] = red;      // R
        ledStripeBuffer[base_index + 1] = blue; // B  
        ledStripeBuffer[base_index + 2] = green; // G
    }
}

/**
 * Update the LED stripe with current buffer contents
 */
Std_ReturnType UpdateLedStripe(void)
{
    Std_ReturnType result = E_NOT_OK;
    
    // Write data to internal SPI buffer
    //result = Spi_WriteIB(0, ledStripeBuffer);
    
    if (result == E_OK)
    {
        // Transmit the buffer contents
        //result = Spi_SyncTransmit(0);
    }
    
    return result=E_OK; // Simulating successful transmission for this example
}

/**
 * Clear all LEDs in the stripe (turn them off)
 */
Std_ReturnType ClearLedStripeIndicator(void)
{
    uint8 i;
    for (i = 0; i < 21; i++)
    {
        ledStripeBuffer[i] = 0;
    }

    return UpdateLedStripe();
}

// Abstracted control functions for cornering and indicator lights
// =========================================================
Std_ReturnType control_cornering_light(uint8 toggle)
{
    // toggle==1 -> turn on, toggle==0 -> turn off
    debug_cornering_light_status = toggle;

    SetStripeLedColor(9, 0, 0, toggle ? 255 : 0); // Set the cornering light color based on position

    return UpdateLedStripe();
}

Std_ReturnType control_indicator_light_basic(uint8 toggle)
{
    // toggle==1 -> turn on, toggle==0 -> turn off
    debug_indicator_status = toggle;

    for (size_t i = 0; i < 7; i++)
    {
        SetStripeLedColor(i, toggle ? 255 : 0, toggle ? 255 : 0, 0); // Set to yellow
    }

    return UpdateLedStripe();
}

Std_ReturnType control_indicator_light_special(uint8 toggle, uint8 LED_numb)
{
    // toggle==1 -> turn on, toggle==0 -> turn off

    debug_LEDs_statuses[LED_numb] = toggle;

    SetStripeLedColor(LED_numb, toggle ? 255 : 0, toggle ? 255 : 0, 0); // Set to yellow
    
    return UpdateLedStripe();;
}

Std_ReturnType LM_Controller_runnable(void)
{
    Std_ReturnType status = E_OK;

    uint8 MSG_LM_value = 0;

    uint8 indicator_light =  0;
    uint8 cornering_light = 0;

    static uint8 blink_period = 0; // 1 if in an uninterruptable blink-period

    static uint64 time_ms = 0;
    static uint64 time_stamp = 0;
    static uint8 steps_special = 0;

    MSG_LM_value = Rte_IRead_MSG_LM();

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
    if (status != E_OK) return status;

    if(blink_period)
    {
        if (flag_special_equipment == 0)    // basic equipment
        {
            if (time_ms-time_stamp == 500)
            {
                status = control_indicator_light_basic(0); // control the indicator light based on the flag_position
                if (status != E_OK) return status;
            }
            else if (time_ms-time_stamp == 1000)
            {
                blink_period = 0;
            }
        }
        else if (flag_special_equipment == 1)   // special equipment
        {   
            if(steps_special<7)
            {
                if(time_ms-time_stamp == 50)
                {
                    status = control_indicator_light_special(1, 1);
                    if (status != E_OK) return status;
                    steps_special += 1;
                    time_stamp = time_ms;
                }
            }
            else
            {
                if(time_ms-time_stamp == 200)
                {
                    // Turn all LEDs off
                    status = ClearLedStripeIndicator();
                    if (status != E_OK) return status;
                }
                else if(time_ms-time_stamp == 1000)
                {
                    blink_period = 0;
                }
            }
        }
    }
    else 
    {
        if (indicator_light)
        {
            if (flag_special_equipment == 0)    // basic equipment
            {   
                status = control_indicator_light_basic(1); // Turn Indicator Light on
                if (status != E_OK) return status;
            }
            else if (flag_special_equipment == 1)   // special equipment
            {
                status = control_indicator_light_special(1, 0); // Turn LED0 on
                if (status != E_OK) return status;
                steps_special = 1;
            } 

            blink_period = 1;
            time_stamp = time_ms;
        }      
    }

    time_ms += 5;
    
    return status;
}